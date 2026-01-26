#include <stdio.h>
#include <string.h>
#include "../utils/decoder.h"

void print_tree(const tree_node *node, int depth);

// Test decoder
void test_decoder() {
    printf("=== Test Suite 1 ===\n");

    const char *text = "ll2:hiee";
    tree_node *root_node = malloc(sizeof(tree_node));
    int pointer = 0;

    decode_tree(text, root_node, 0);
    print_tree(root_node, 2);

    printf("\n=== Test Suite 2 ===\n");

    const char *text_2 = "ll2:hiel3:heyee";
    tree_node *root_node_2 = malloc(sizeof(tree_node));
    int pointer_2 = 0;

    decode_tree(text_2, root_node_2, 0);
    print_tree(root_node_2, 3);
}

void test_decoder_4() {
    printf("=== Test Suite 4 ===\n");

    const char *text_4 = "l1:al1:bee";
    tree_node *root_node_4 = malloc(sizeof(tree_node));
    int pointer_4 = 0;

    // Initialize root
    root_node_4->type = LIST;
    root_node_4->children = NULL;
    root_node_4->child_count = 0;

    decode_tree(text_4, root_node_4, 0);

    // Visual inspection
    print_tree(root_node_4, 0);

    printf("=== End Test Suite 4 ===\n\n");
}

void test_decoder_5() {
    printf("=== Test Suite 5 ===\n");

    const char *text = "l1:al1:bl1:ceee";
    tree_node *root_node = malloc(sizeof(tree_node));
    int pointer = 0;

    // Initialize root node
    root_node->type = LIST;
    root_node->children = NULL;
    root_node->child_count = 0;

    decode_tree(text, root_node, 0);

    // Visual verification
    print_tree(root_node, 0);

    printf("=== End Test Suite 5 ===\n\n");
}

void test_decoder_6() {
    printf("=== Test Suite 6 ===\n");

    const char *text = "l1:ae";
    tree_node *root_node = malloc(sizeof(tree_node));
    int pointer = 0;

    // Initialize root node
    root_node->type = LIST;
    root_node->children = NULL;
    root_node->child_count = 0;

    decode_tree(text, root_node, 0);

    // Visual verification
    print_tree(root_node, 0);

    printf("=== End Test Suite 6 ===\n\n");
}

void test_decoder_7() {
    printf("=== Test Suite 7 ===\n");

    const char *text = "l1:al1:bel1:cee";
    tree_node *root_node = malloc(sizeof(tree_node));
    int pointer = 0;

    // Initialize root node
    root_node->type = LIST;
    root_node->children = NULL;
    root_node->child_count = 0;

    decode_tree(text, root_node, 0);

    // Visual verification
    print_tree(root_node, 0);

    printf("=== End Test Suite 7 ===\n\n");
}


int main() {
    test_decoder();
    test_decoder_4();
    test_decoder_5();
    test_decoder_6();
    test_decoder_7();
    return 0;
}

void print_tree(const tree_node *node, int depth) {
    if (!node) return;

    for (int i = 0; i < depth; i++) {
        printf("  ");
    }

    switch (node->type) {
        case LIST:
            printf("LIST (%zu children)\n", node->child_count);
            break;
        case STR:
            printf("STR \"%s\"\n", node->val.comp_str ? node->val.comp_str : "(null)");
            break;
        case INT:
            printf("INT %d\n", node->val.comp_int);
            break;
        case DICT:
            printf("DICT (%zu children)\n", node->child_count);
            break;
    }

    for (size_t i = 0; i < node->child_count; i++) {
        print_tree(node->children[i], depth + 1);
    }
}
