#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../types/tree.h"

tree_node *parse_string(const char *component);
int add_child(tree_node *parent, tree_node *child);

int decode(char file_path[]) {
    FILE *fptr;
    char buffer[255];

    fptr = fopen("test.txt", "r");

    if (fptr == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    while (fgets(buffer, sizeof(buffer), fptr) != NULL) {
        printf("%s", buffer);
    }

    fclose(fptr);

    return EXIT_SUCCESS;
}

int decode_tree(const char *text, tree_node *root, int pointer) {
    while (pointer < strlen(text)) {
        // Parse string components
        if (atoi(text) != 0) {
            tree_node *new_node = parse_string(text);
            add_child(root, new_node);
        }
    }
    return 0;
}

/*
* Parses bencoded strings i.e. '4:spam'
*
* Parameters:
*    str - bencoded string component
*
* Returns:
*    pointer to tree_node
*/
tree_node *parse_string(const char *component) { 
    int str_len = atoi(component);

    char *str_value = malloc(str_len + 1);
    tree_node *node = malloc(sizeof(tree_node));

    memcpy(str_value, component + 2, str_len);
    str_value[str_len] = '\0';

    node->type = STR;
    node->val.comp_str = str_value;
    node->child_count = 0;
    node->children = NULL;
    
    return node;
};

/*
* Adds child to the children member of tree_node struct
* 
* Parameters:
*   parent - pointer to tree_node
*   child - pointer to tree_node
*
* Returns:
*   int of whether the operation was successful or not
*/
int add_child(tree_node *parent, tree_node *child) {
    tree_node **new_children = realloc(parent->children, sizeof(tree_node *) * (parent->child_count + 1));

    if (!new_children) {
        return 0;
    }

    parent->children = new_children;
    parent->children[parent->child_count] = child;
    parent->child_count++;

    return 1;
}
