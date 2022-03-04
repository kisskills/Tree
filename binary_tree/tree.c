#include <stdio.h>
<<<<<<< HEAD
#include <stdint.h>
#include <stdlib.h>
#include <inttypes.h>

struct tree {
    int64_t key;
    struct tree *left;
    struct tree *right;
    // struct tree *parent;
};
/*
struct tree* create_tree(struct tree* root, int64_t key) {
    struct tree* tmp = malloc(sizeof(struct tree));
    tmp->key = key;
    tmp->parent = NULL;
    tmp->left = tmp->right = NULL;
    root = tmp;
    return root;
}

struct tree* add_node(struct tree* root, int64_t key) {
    struct tree* root2 = root;
    struct tree* root3 = NULL;
    struct tree* tmp = malloc(sizeof(struct tree));
    tmp->key = key;

    while (root2 != NULL) {
        root3 = root2;
        if (key < root2->key)
            root2 = root2->left;
        else
            root2 = root2->right; 
    }
    tmp->parent = root3;
    tmp->left = tmp->right = NULL;

    if (key < root3->key)
        root3->left = tmp;
    else
        root3->right = tmp;
    return root;
}
*/
void add_node(struct tree** root, int64_t key) {
    if (*root == NULL) {
        *root = malloc(sizeof(struct tree));
        (*root)->key = key;
        (*root)->left = (*root)->right = NULL;
        // (*root)->parent = *root;
    } else {
        if(key < (*root)->key) add_node(&((*root)->left), key);
        if(key > (*root)->key) add_node(&((*root)->right), key);
    }
}
struct tree* find_node(struct tree* root, int64_t key) {
    if (root == NULL || root->key == key)
        return root;
    if (key < root->key)
        return find_node(root->left, key);
    else
        return find_node(root->right, key);
}
struct tree* min(struct tree* root) {
    if (root->left == NULL)
        return root;
    return min(root->left);
}
void print_tree(struct tree* root) {
    if (root->left != NULL) print_tree(root->left);
    if (root->right != NULL) print_tree(root->right);
    printf("%"PRId64, root->key);
}
int main() {
    struct tree* root = NULL;
    // root = create_tree(root, 2);
    add_node(&root, 2);
    add_node(&root, 1);
    add_node(&root, 4);
    print_tree(root);
    printf("\n");
    printf("%p %p\n", root, root->parent);
    return 0;
}

=======
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
>>>>>>> 28ef55cfcae5262e238abf0f360580bb9d8456b1
