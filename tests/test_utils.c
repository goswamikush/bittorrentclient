#include <stdio.h>
#include <string.h>
#include "../utils/decoder.h"
#include "../types/tree.h"

// Test parse string method
void test_parse_string() {
    char test_string[7] = "4:spam";

    tree_node *node = parse_string(test_string);

    if (node->type == STR) {
        printf("Correct type\n");
    } else {
        printf("Incorret type\n");
    }

    if (strcmp(node->val.comp_str, "spam") == 0) {
        printf("Correct value\n");
    } else {
        printf("Incorrect value\n");
    }

    if (node->child_count == 0) {
        printf("Correct child count\n");
    } else {
        printf("Incorrect child count\n");
    }

    if (node->children == NULL) {
        printf("Correct children value\n");
    } else {
        printf("Incorrect children value\n");
    }
}

// Test add_child method
void test_add_child() {
    tree_node *parent = malloc(sizeof(tree_node));;

    parent->type = STR;
    parent->val.comp_str = "hello";
    parent->children = NULL;
    parent->child_count = 0;

    tree_node *child = malloc(sizeof(tree_node));

    child->type = STR;
    child->val.comp_str = "hello2";
    child->children = NULL;
    child->child_count = 0;

    int res = add_child(parent, child);

    if (res == 0) {
        printf("Failed to add new children\n");
        return;
    } 

    if (parent->child_count == 1) {
        printf("Successfully added to child_count\n");
    }

    if (parent->children[0] == child) {
        printf("Successfully stored child node as child in parent node\n");
    }

    return;
}

int main() {
    test_parse_string();
    test_add_child();
    return 0;
}
