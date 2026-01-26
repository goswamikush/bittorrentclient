#include <stdio.h>
#include <string.h>
#include "../utils/decoder.h"

void print_tree(const tree_node *node);

void test_decoder() {
    int NUM_TEST_CASES = 12;

    char *test_cases[NUM_TEST_CASES];

    test_cases[0] = "ll2:hiee";
    test_cases[1] = "ll2:hiel3:heyee";
    test_cases[2] = "l1:al1:bee";
    test_cases[3] = "l1:al1:bl1:ceee";
    test_cases[4] = "l1:ae";
    test_cases[5] = "l1:al1:bel1:cee";
    test_cases[6] = "l10:aqwertgswql1:aee";
    test_cases[7] = "d3:key5:valuee";
    test_cases[8] = "d3:key5:value3:foo3:bare";
    test_cases[9] = "d4:listl1:a1:b1:cee";
    test_cases[10] = "d4:dictd3:key5:valueee";  
    test_cases[11] = "de"; 

    int i;
    for (i = 0; i < NUM_TEST_CASES; i++) {
        printf("\n=== Start Test Case %d ===\n", i);
        tree_node *root_node = malloc(sizeof(tree_node));
        decode_tree(test_cases[i], root_node, 0);

        print_tree(root_node);

        printf("=== End Test Case %d ===\n", i);
    }
}

int main() {
    test_decoder();
    return 0;
}

void print_tree(const tree_node *node) {
    static int depth = 0;
    
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
    
    depth++;
    for (size_t i = 0; i < node->child_count; i++) {
        print_tree(node->children[i]);
    }
    depth--;
}
