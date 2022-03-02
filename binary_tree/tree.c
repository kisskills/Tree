#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

struct tree {
    int64_t key;
    struct tree* left;
    struct tree* right;
    struct tree* parent;
};

void add_node(struct tree* root, const int64_t key) {
    if (root == NULL) {
        root = malloc(sizeof(struct tree));
        root->key = key;
        root->left = root->right = NULL;
        root->parent = root;
    } else {
        if (key < root->key) {
            add_node(root->left, key);
        } else if (key > root->key) {
            add_node(root->right, key);
        }
        else {}
    }
}

// надо рассмотреть три случая: нет поомков, один потомок, два потомка
void rm_node(struct tree* root, const int64_t key) {
   if (key == root->key) {
      if (root->left == NULL && root->right == NULL) {
          root->parent->left = root->parent->right = NULL;
          free(root);
      }
      if (root->left == NULL) {
          if (key < root->parent->key) root->parent->left = root->right;
          else root->parent->right = root->right;
      }
      if (root->right == NULL) {
          if (key < root->parent->key) root->parent->left = root->left;
          else root->parent->right = root->left;
      }
      if (root->left != NULL && root->right != NULL) {
          
      }

   } else {
       if (key < root->key) rm_node(root->left, key);
       if (key > root->key) rm_node(root->right, key);
   }
}

void destroy_tree(struct tree* root) {
    if (root->left != NULL) destroy_tree(root->left);
    if (root->right != NULL) destroy_tree(root->right);
    free(root);
}