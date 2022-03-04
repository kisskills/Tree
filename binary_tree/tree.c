#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <inttypes.h>

struct tree {
    int64_t key;
    struct tree *left;
    struct tree *right;
    struct tree *parent;
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

void add_node(struct tree** root,struct tree* parent, int64_t key) {
    if (*root == NULL) {
        *root = malloc(sizeof(struct tree));
        (*root)->key = key;
        (*root)->left = (*root)->right = NULL;
        (*root)->parent = parent;
    } else {
        if(key < (*root)->key) add_node(&((*root)->left), *root, key);
        if(key > (*root)->key) add_node(&((*root)->right), *root, key);
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

struct tree* rm_node(struct tree* root, int64_t key) {
    struct tree* ptr = find_node(root, key);
    if (ptr) {
        if (ptr->left != NULL && ptr->right != NULL) {
            ptr->key = min(ptr->right)->key;
            return rm_node(ptr->right, ptr->key);
        } else if (ptr->left == NULL && ptr->right != NULL) {
            ptr->right->parent = ptr->parent;
            if (ptr == ptr->parent->left)
                ptr->parent->left = ptr->right;
            else
                ptr->parent->right = ptr->right;
            // free(ptr);
        } else if (ptr->left != NULL && ptr->right == NULL) {
            ptr->left->parent = ptr->parent;
            if (ptr == ptr->parent->left)
                ptr->parent->left = ptr->left;
            else
                ptr->parent->right = ptr->left;
            // free(ptr);
        } else {
            if (ptr == ptr->parent->left)
                ptr->parent->left = NULL;
            else 
                ptr->parent->right = NULL;
            // free(ptr);
        }
        free(ptr);
        return root;
    } else {
        return root;
    }
}

void print_tree(struct tree* root) {
    if (root->left != NULL) print_tree(root->left);
    if (root->right != NULL) print_tree(root->right);
    printf("%"PRId64" ", root->key);
}

void destroy_tree(struct tree* root) {
    if(root->left != NULL) destroy_tree(root->left);
    if(root->right != NULL) destroy_tree(root->right);
    free(root);
}
int main() {
    struct tree* root = NULL;
    struct tree* parent = NULL;
    // root = create_tree(root, 2);
    add_node(&root, parent, 9);
    add_node(&root, parent, 3);
    add_node(&root, parent, 7);
    add_node(&root, parent, 8);
    add_node(&root, parent, 4);
    add_node(&root, parent, 6);
    add_node(&root, parent, 1);
    add_node(&root, parent, 0);
    print_tree(root);
    printf("\n");

    rm_node(root, 3);
    rm_node(root, 900);
    print_tree(root);
    printf("\n");

    destroy_tree(root);
    return 0;
}

