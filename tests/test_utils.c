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

int main() {
    test_parse_string();
    return 0;
}
