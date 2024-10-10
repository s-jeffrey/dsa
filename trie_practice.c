#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Implemented: Checks if the right name exists at the given number
// Not Implemented: Deleting nodes

int error_flag = 0;

typedef struct _trie {
    char *name;
    struct _trie *children[10];
} trie;

trie *createNode() {
    trie *node = malloc(sizeof(trie));
    if (node == NULL) {
        error_flag = 1;
        return NULL;
    }

    // Initialize to empty and init NULL pointers
    node->name = NULL;
    for (int i = 0; i < 10; i++) {
        node->children[i] = NULL;
    }
    return node;
}

void insert(trie *root, int *digit, int length, char *name) {
    trie *current = root;
    for (int i = 0; i < length; i++) {
        int index = digit[i];
        if (current->children[index] == NULL) {
            current->children[index] = createNode();
        }
        current = current->children[index];
    }

    current->name = malloc(strlen(name) + 1);
    if (current->name) {
        strcpy(current->name, name);
    }
}

bool search(trie *root, int *digit, int length, char *name) {
    trie *current = root;

    // Follow node if it exists or return false
    for (int i = 0; i < length; i++) {
        int index = digit[i];
        if (current->children[index] == NULL) {
            return false;
        }

        current = current->children[index];

    }

    // Compare name at final node
    return (current->name != NULL && strcmp(current->name, name) == 0);
}

void freeTrie(trie *node) {
    // If nothing exists then do nothing
    if (node == NULL) {
        return;
    }

    // Recursively free connected children first
    for (int i = 0; i < 10; i++) {
        freeTrie(node->children[i]);
    }

    // Free the current node
    free(node);
}

int* str_to_ints(char *str, int *length) {
    *length = strlen(str);
    int *array = malloc(*length * sizeof(int));
    if (array == NULL) {
        error_flag = 2;
        return NULL;
    }

    for (int i = 0; i < *length; i++) {
        array[i] = str[i] - '0';
    }
    return array;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: ./trie_practice <number> <name>\n");
        return 1;
    }

    // Create root node
    trie *root = createNode();
    if (root == NULL) {
        printf("Error %d\n", error_flag);
        return 1;
    }

    // Convert passed str to int array for number
    int number_length;
    int *number = str_to_ints(argv[1], &number_length);
    if (number == NULL) {
        printf("Error %d\n", error_flag);
        return 1;
    }

    // Testing: number passes but allows testing for matching name
    insert(root, number, number_length, "Mark");
    bool result = search(root, number, number_length, argv[2]);
    printf("%s\n", result ? "true" : "false");

    free(number);
    freeTrie(root);
    return 0;
}