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
// добавление элемента
void add_node(struct tree** root,struct tree* parent, int64_t key) {
    if (*root == NULL) {
        *root = malloc(sizeof(struct tree));
        (*root)->key = key;
        (*root)->left = (*root)->right = NULL;
        (*root)->parent = parent;
    }
    if(key < (*root)->key)
        add_node(&((*root)->left), *root, key);
    else if(key > (*root)->key)
        add_node(&((*root)->right), *root, key);
    else {}
}
// поиск элемента по ключу
struct tree* find_node(struct tree* root, int64_t key) {
    if (root == NULL || root->key == key)
        return root;
    if (key < root->key)
        return find_node(root->left, key);
    else
        return find_node(root->right, key);
}
// поиск минимального элемента
struct tree* min(struct tree* root) {
    if (root->left == NULL)
        return root;
    return min(root->left);
}
// удаление элемента
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
        } else if (ptr->left != NULL && ptr->right == NULL) {
            ptr->left->parent = ptr->parent;
            if (ptr == ptr->parent->left)
                ptr->parent->left = ptr->left;
            else
                ptr->parent->right = ptr->left;
        } else {
            if (ptr == ptr->parent->left)
                ptr->parent->left = NULL;
            else 
                ptr->parent->right = NULL;
        }
        free(ptr);
        return root;
    } else {
        return root;
    }
}
// обход дерева корень -> левая ветвь -> правая ветвь
void pre_order(struct tree* root) {
    if (root) {
        printf("%"PRId64" ", root->key);
        pre_order(root->left);
        pre_order(root->right);
    }
}
// обход дерева левая ветвь -> корень -> правая ветвь
void in_order(struct tree* root) {
    if (root) {
        in_order(root->left);
        printf("%"PRId64" ", root->key);
        in_order(root->right);
    }
}
// обход дерева левая ветвь -> правая ветвь -> корень
void post_order(struct tree* root) {
    if (root->left != NULL) post_order(root->left);
    if (root->right != NULL) post_order(root->right);
    printf("%"PRId64" ", root->key);
}
// удаление дерева
void destroy_tree(struct tree** root) {
    if((*root)->left != NULL) destroy_tree(&((*root)->left));
    if((*root)->right != NULL) destroy_tree(&((*root)->right));
    free(*root);
}

int main() {
    struct tree* root = NULL;
    struct tree* parent = NULL;
    add_node(&root, parent, 9);
    add_node(&root, parent, 3);
    add_node(&root, parent, 7);
    add_node(&root, parent, 8);
    add_node(&root, parent, 4);
    add_node(&root, parent, 6);
    add_node(&root, parent, 1);
    add_node(&root, parent, 0);
    add_node(&root, parent, 11);
    post_order(root);
    printf("\n");

    rm_node(root, 3);
    rm_node(root, 900);

    pre_order(root);
    printf(" pre\n");
    in_order(root);
    printf(" in\n");
    post_order(root);
    printf(" post\n");

    destroy_tree(&root);
    root = NULL;
    return 0;
}

