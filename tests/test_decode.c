#include <stdio.h>
#include <string.h>
#include "../utils/decoder.h"

// Test decoder
void test_decoder() {
    printf("=== Test Suite 1 ===\n");

    const char *text = "ll2:hiee";
    tree_node *root_node = malloc(sizeof(tree_node));
    int pointer = 0;

    decode_tree(text, root_node, pointer);

    // Verify correctness
    if (root_node->child_count == 1) {
        printf("Correct root_node child_count\n");
    }

    if (root_node->children[0]->type == LIST) {
        printf("Correct root_node child type\n");
    }

    if (root_node->children[0]->child_count == 1) {
        printf("Correct l1 node child count\n");
    } else {
        printf("%zu\n", root_node->children[0]->child_count);
    }

    printf("\n=== Test Suite 2 ===\n");

    const char *text_2 = "ll2:hiel3:heyee";
    tree_node *root_node_2 = malloc(sizeof(tree_node));
    int pointer_2 = 0;

    decode_tree(text_2, root_node_2, pointer_2);

    // Verify correctness
    if (root_node_2->child_count == 1) {
        printf("Correct root_node child_count\n");
    }

    if (root_node_2->children[0]->type == LIST) {
        printf("Correct root_node child type of LIST\n");
    }

    if (root_node_2->children[0]->children[0]->type == LIST) {
        printf("Correct root_node child type of LIST\n");
    }

    if (root_node_2->children[0]->children[0]->child_count == 1) {
        printf("Correct child count of 1\n");
    }

    // if (root_node->children[0]->type == LIST) {
    //     printf("Correct root_node child type\n");
    // }

    // if (root_node->children[1]->type == LIST) {
    //     printf("Correct root_node child type\n");
    // }

    // if (root_node->children[0]->child_count == 1) {
    //     printf("Correct l1 node child count\n");
    // } else {
    //     printf("%zu\n", root_node->children[0]->child_count);
    // }
}

int main() {
    test_decoder();
    return 0;
}
