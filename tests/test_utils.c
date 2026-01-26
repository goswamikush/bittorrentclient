#include <stdio.h>
#include <string.h>
#include "../utils/decoder.h"
#include "../types/tree.h"

// Test parse string method
void test_parse_string() {
    char test_string[7] = "4:spam";

    tree_node *node = parse_string(test_string);

    // Ground truth
    tree_node *ground_truth = malloc(sizeof(tree_node));

    ground_truth->type = STR;
    ground_truth->val.comp_str = "spam";
    ground_truth->child_count = 0;
    ground_truth->children = NULL;

    printf("=== Start Parse String Test ===\n");

    bool is_equal = tree_equals(ground_truth, node);

    if (is_equal) {
        printf("=== Parse String Success! ===\n\n");
    } else {
        printf("=== Parse String Failure! ===\n\n");
    }
}

// Test parse int method
void test_parse_int() {
    char test_string[8] = "i345e123";

    tree_node *node = parse_int(test_string); 

    tree_node *ground_truth = malloc(sizeof(tree_node));

    ground_truth->type = INT;
    ground_truth->val.comp_int = 345;
    ground_truth->child_count = 0;
    ground_truth->children = NULL;

    printf("=== Start Parse Int Test ===\n");

    bool is_equal = tree_equals(ground_truth, node);

    if (is_equal) {
        printf("=== Parse Int Success! ===\n\n");
    } else {
        printf("=== Parse Int Failure! ===\n\n");
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

    printf("=== Start Add Child ===\n");

    int res = add_child(parent, child);

    if (res == 0) {
        printf("=== Failed to add new children ===\n\n");
        return;
    } 

    if (parent->child_count == 1) {
        printf("Successfully added to child_count\n");
    } else {
        printf("=== Failed to add new children ===\n\n");
        return; 
    }

    if (parent->children[0] == child) {
        printf("Successfully stored child node as child in parent node\n");
    } else {
        printf("=== Failed to add new children ===\n\n");
        return;
    }

    printf("=== Add to child Success! ===\n\n");

    return;
}

int main() {
    test_parse_string();
    test_add_child();
    test_parse_int();
    return 0;
}
