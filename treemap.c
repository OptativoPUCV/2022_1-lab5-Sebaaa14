#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treemap.h"

typedef struct TreeNode TreeNode;


struct TreeNode {
    Pair* pair;
    TreeNode * left;
    TreeNode * right;
    TreeNode * parent;
};

struct TreeMap {
    TreeNode * root;
    TreeNode * current;
    int (*lower_than) (void* key1, void* key2);
};

int is_equal(TreeMap* tree, void* key1, void* key2){
    if(tree->lower_than(key1,key2)==0 &&  
        tree->lower_than(key2,key1)==0) return 1;
    else return 0;
}


TreeNode * createTreeNode(void* key, void * value) {
    TreeNode * new = (TreeNode *)malloc(sizeof(TreeNode));
    if (new == NULL) return NULL;
    new->pair = (Pair *)malloc(sizeof(Pair));
    new->pair->key = key;
    new->pair->value = value;
    new->parent = new->left = new->right = NULL;
    return new;
}

TreeMap * createTreeMap(int (*lower_than) (void* key1, void* key2)) {
    TreeMap * nuevo = (TreeMap *)malloc(sizeof(TreeMap));
    nuevo->root = NULL;
    nuevo->current = NULL;
    nuevo->lower_than = lower_than;
    return nuevo;
}


void insertTreeMap(TreeMap * tree, void* key, void * value) {
  if (tree == NULL) return;
  TreeNode * aux = tree->root;
  TreeNode * parent = NULL;
    
  while (aux != NULL) {
    parent = aux;
      if (tree->lower_than(key,aux->pair->key)) {
        aux = aux->left;
      } 
        else if (tree->lower_than(aux->pair->key,key)) {
          aux = aux->right;
        } 
          else return;
    }
    
  TreeNode * nuevo = createTreeNode(key, value);
  nuevo->parent = parent;
    
  if (parent == NULL) {
    tree->root = nuevo;
    } else if (tree->lower_than(key,parent->pair->key)) {
      parent->left = nuevo;
      } else {
        parent->right = nuevo;
    }
    tree->current = nuevo;
}

TreeNode * minimum(TreeNode * x){
    if (x == NULL) return NULL;
    while (x->left !=NULL){
      x=x->left;
    }
    return x;
}


void removeNode(TreeMap * tree, TreeNode* node) {

}

void eraseTreeMap(TreeMap * tree, void* key){
    if (tree == NULL || tree->root == NULL) return;

    if (searchTreeMap(tree, key) == NULL) return;
    TreeNode* node = tree->current;
    removeNode(tree, node);

}




Pair * searchTreeMap(TreeMap * tree, void* key) {
    if (tree == NULL || tree->root == NULL) return NULL;
    TreeNode * aux = tree->root;
    
    while (aux != NULL) {
        if (tree->lower_than(key, aux->pair->key)) {
            aux = aux->left;
        }
        else if (tree->lower_than(aux->pair->key, key)) {
            aux = aux->right;
        }else break;
    }
    tree->current = aux;
    if (aux == NULL) return NULL;
    return aux->pair;
}


Pair * upperBound(TreeMap * tree, void* key) {
  if (tree == NULL || tree->root == NULL) return NULL;
  TreeNode * aux = tree->root;
  TreeNode * upper = NULL;
    
  while (aux != NULL) {
  if( (upper==NULL || tree->lower_than(aux->pair->key, upper->pair->key)) && !tree->lower_than(aux->pair->key,key))
    upper=aux;
    
    if (tree->lower_than(key, aux->pair->key)) {
      aux = aux->left;
      }else if (tree->lower_than(aux->pair->key, key)) {
        aux = aux->right;
      }else break;
    }
    tree->current = upper;
    if (upper == NULL) return NULL;
    return upper->pair;
}

Pair * firstTreeMap(TreeMap * tree) {
    if (tree == NULL || tree->root == NULL) return NULL;
    
    TreeNode * aux = tree->root;
    
    tree->current = minimum(aux);
    
    if (tree->current == NULL) return NULL;
    
    return tree->current->pair;
}

Pair * nextTreeMap(TreeMap * tree) {
    if (tree == NULL || tree->root == NULL || tree->current == NULL) return NULL;
    
    if (tree->current->right != NULL) {
        TreeNode * aux = tree->current->right;

        tree->current = minimum(aux);
        
        return tree->current->pair;
    }
    
    TreeNode * aux = tree->current->parent;
    
    while (aux != NULL && tree->current == aux->right) {
        tree->current = aux;
        aux = aux->parent;
    }
    
    tree->current = aux;
    
    if (aux == NULL) return NULL;
    
    return aux->pair;
}
