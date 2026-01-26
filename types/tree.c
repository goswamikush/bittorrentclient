#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "tree.h"


bool tree_equals(tree_node *ground_truth, tree_node *test_node) {
    // Compare types
    if (ground_truth->type != test_node->type) {
        printf("Incorrect types\n");
        return false;
    }

    printf("Correct types\n");

    // Compare child counts
    if (ground_truth->child_count != test_node->child_count) {
        printf("Incorrect child counts\n");
        return false;
    }

    printf("Correct child counts\n");

    // Compare vals
    if (ground_truth->type == STR) {
        if (strcmp(ground_truth->val.comp_str, test_node->val.comp_str) != 0) {
            printf("Incorrect values\n");
            return false;
        }
        printf("Correct values\n");
    }

    if (ground_truth->type == INT) {
        if (ground_truth->val.comp_int != test_node->val.comp_int) {
            printf("Incorrect values\n");
            return false;
        }
        printf("Correct values\n");
    }

    // Compare children
    if (ground_truth->child_count != 0) {
        for (int i = 0; i < ground_truth->child_count; i++) {
            if (!tree_equals(ground_truth->children[i], test_node->children[i])) {
                printf("Incorrect children\n");
                return false;
            }
        }
    }

    printf("Correct children\n");

    return true;
}
