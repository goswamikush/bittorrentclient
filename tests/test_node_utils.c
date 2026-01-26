#include <stdio.h>
#include <stdbool.h>
#include "../types/tree.h"

void test_list_equals() {
    printf("=== Start List Node Equals Test===\n");

    tree_node *node1 = malloc(sizeof(tree_node));

    node1->type = LIST;
    node1->val.comp_str = NULL;
    node1->children = NULL;
    node1->child_count = 0;

    tree_node *node2 = malloc(sizeof(tree_node));

    node2->type = LIST;
    node2->val.comp_str = NULL;
    node2->children = NULL;
    node2->child_count = 0;

    bool res = tree_equals(node1, node2);

    if (res) {
        printf("Node equals success!\n");
    }

    printf("=== End List Node Equals Test===\n");
}

void test_int_equals() {
    printf("\n=== Start Int Node Equals Test===\n");
    tree_node *node1 = malloc(sizeof(tree_node));

    node1->type = INT;
    node1->val.comp_int = 5;
    node1->children = NULL;
    node1->child_count = 0;

    tree_node *node2 = malloc(sizeof(tree_node));

    node2->type = INT;
    node2->val.comp_int = 5;
    node2->children = NULL;
    node2->child_count = 0;

    bool res = tree_equals(node1, node2);

    if (res) {
        printf("Node equals success!\n");
    }

    printf("=== End Int Node Equals Test===\n");
}

void test_int_not_equals() {
    printf("\n=== Start Int Node Not Equals Test===\n");
    tree_node *node1 = malloc(sizeof(tree_node));

    node1->type = INT;
    node1->val.comp_int = 5;
    node1->children = NULL;
    node1->child_count = 0;

    tree_node *node2 = malloc(sizeof(tree_node));

    node2->type = INT;
    node2->val.comp_int = 4;
    node2->children = NULL;
    node2->child_count = 0;

    bool res = tree_equals(node1, node2);

    if (!res) {
        printf("Node not equals success!\n");
    }

    printf("=== End Int Node Not Equals Test===\n");
}

void test_child_count_not_equals() {
    printf("\n=== Start Child Count Not Equals Test===\n");
    tree_node *node1 = malloc(sizeof(tree_node));

    node1->type = INT;
    node1->val.comp_int = 5;
    node1->children = NULL;
    node1->child_count = 0;

    tree_node *node2 = malloc(sizeof(tree_node));

    node2->type = INT;
    node2->val.comp_int = 5;
    node2->children = NULL;
    node2->child_count = 1;

    bool res = tree_equals(node1, node2);

    if (!res) {
        printf("Child count not equals success!\n");
    }

    printf("=== End Child Count Not Equals Test===\n");
}

void test_children_equals() {
    printf("\n=== Start Children Equals Test===\n");
    tree_node *node1 = malloc(sizeof(tree_node));
    node1->type = LIST;
    node1->child_count = 1;
    node1->children = malloc(sizeof(tree_node*));
    
    tree_node *child1 = malloc(sizeof(tree_node));
    child1->type = INT;
    child1->val.comp_int = 10;
    child1->children = NULL;
    child1->child_count = 0;
    node1->children[0] = child1;
    
    tree_node *node2 = malloc(sizeof(tree_node));
    node2->type = LIST;
    node2->child_count = 1;
    node2->children = malloc(sizeof(tree_node*));
    
    tree_node *child2 = malloc(sizeof(tree_node));
    child2->type = INT;
    child2->val.comp_int = 10;
    child2->children = NULL;
    child2->child_count = 0;
    node2->children[0] = child2;
    
    bool res = tree_equals(node1, node2);
    if (res) {
        printf("Children equals success!\n");
    }
    printf("=== End Children Equals Test===\n");
}

void test_children_not_equals() {
    printf("\n=== Start Children Not Equals Test===\n");
    tree_node *node1 = malloc(sizeof(tree_node));
    node1->type = LIST;
    node1->child_count = 1;
    node1->children = malloc(sizeof(tree_node*));
    
    tree_node *child1 = malloc(sizeof(tree_node));
    child1->type = INT;
    child1->val.comp_int = 10;
    child1->children = NULL;
    child1->child_count = 0;
    node1->children[0] = child1;
    
    tree_node *node2 = malloc(sizeof(tree_node));
    node2->type = LIST;
    node2->child_count = 1;
    node2->children = malloc(sizeof(tree_node*));
    
    tree_node *child2 = malloc(sizeof(tree_node));
    child2->type = INT;
    child2->val.comp_int = 99; 
    child2->children = NULL;
    child2->child_count = 0;
    node2->children[0] = child2;
    
    bool res = tree_equals(node1, node2);
    if (!res) {
        printf("Children not equals success!\n");
    }
    printf("=== End Children Not Equals Test===\n");
}

int main() {
    test_list_equals();
    test_int_equals();
    test_int_not_equals();

    test_child_count_not_equals();

    test_children_equals();
    test_children_not_equals();
    return 0;
}


