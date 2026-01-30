#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../utils/encoder.h"
#include "../types/tree.h"

int test_count = 0;
int passed = 0;
int failed = 0;

void assert_equals(const char *test_name, unsigned char *result, const char *expected) {
    test_count++;
    if (strcmp((char*)result, expected) == 0) {
        printf("✓ PASS: %s\n", test_name);
        passed++;
    } else {
        printf("✗ FAIL: %s\n", test_name);
        printf("  Expected: %s\n", expected);
        printf("  Got:      %s\n", result);
        failed++;
    }
}

void test_empty_list() {
    tree_node *list = malloc(sizeof(tree_node));
    list->type = LIST;
    list->child_count = 0;
    list->children = NULL;
    
    unsigned char *result = bencode(list);
    assert_equals("Empty list", result, "le");
}

void test_empty_dict() {
    tree_node *dict = malloc(sizeof(tree_node));
    dict->type = DICT;
    dict->child_count = 0;
    dict->children = NULL;
    
    unsigned char *result = bencode(dict);
    assert_equals("Empty dictionary", result, "de");
}

void test_simple_string() {
    tree_node *str = malloc(sizeof(tree_node));
    str->type = STR;
    str->val.comp_str = "spam";
    str->val_size = 4;
    str->children = NULL;
    str->child_count = 0;
    
    unsigned char *result = bencode(str);
    assert_equals("Simple string", result, "4:spam");
}

void test_simple_int() {
    tree_node *num = malloc(sizeof(tree_node));
    num->type = INT;
    num->val.comp_int = 42;
    num->children = NULL;
    num->child_count = 0;
    
    unsigned char *result = bencode(num);
    assert_equals("Simple integer", result, "i42e");
}

void test_list_of_strings() {
    tree_node *str1 = malloc(sizeof(tree_node));
    str1->type = STR;
    str1->val.comp_str = "spam";
    str1->val_size = 4;
    str1->children = NULL;
    str1->child_count = 0;
    
    tree_node *str2 = malloc(sizeof(tree_node));
    str2->type = STR;
    str2->val.comp_str = "eggs";
    str2->val_size = 4;
    str2->children = NULL;
    str2->child_count = 0;
    
    tree_node *list = malloc(sizeof(tree_node));
    list->type = LIST;
    list->child_count = 2;
    list->children = malloc(2 * sizeof(tree_node*));
    list->children[0] = str1;
    list->children[1] = str2;
    
    unsigned char *result = bencode(list);
    assert_equals("List of strings", result, "l4:spam4:eggse");
}

void test_nested_list() {
    tree_node *str1 = malloc(sizeof(tree_node));
    str1->type = STR;
    str1->val.comp_str = "a";
    str1->val_size = 1;
    str1->children = NULL;
    str1->child_count = 0;
    
    tree_node *str2 = malloc(sizeof(tree_node));
    str2->type = STR;
    str2->val.comp_str = "b";
    str2->val_size = 1;
    str2->children = NULL;
    str2->child_count = 0;
    
    tree_node *inner_list = malloc(sizeof(tree_node));
    inner_list->type = LIST;
    inner_list->child_count = 1;
    inner_list->children = malloc(sizeof(tree_node*));
    inner_list->children[0] = str2;
    
    tree_node *outer_list = malloc(sizeof(tree_node));
    outer_list->type = LIST;
    outer_list->child_count = 2;
    outer_list->children = malloc(2 * sizeof(tree_node*));
    outer_list->children[0] = str1;
    outer_list->children[1] = inner_list;
    
    unsigned char *result = bencode(outer_list);
    assert_equals("Nested list", result, "l1:al1:bee");
}

void test_simple_dict() {
    tree_node *key = malloc(sizeof(tree_node));
    key->type = STR;
    key->val.comp_str = "foo";
    key->val_size = 3;
    key->children = NULL;
    key->child_count = 0;
    
    tree_node *val = malloc(sizeof(tree_node));
    val->type = STR;
    val->val.comp_str = "bar";
    val->val_size = 3;
    val->children = NULL;
    val->child_count = 0;
    
    tree_node *dict = malloc(sizeof(tree_node));
    dict->type = DICT;
    dict->child_count = 2;
    dict->children = malloc(2 * sizeof(tree_node*));
    dict->children[0] = key;
    dict->children[1] = val;
    
    unsigned char *result = bencode(dict);
    assert_equals("Simple dictionary", result, "d3:foo3:bare");
}

void test_dict_with_int() {
    tree_node *key = malloc(sizeof(tree_node));
    key->type = STR;
    key->val.comp_str = "age";
    key->val_size = 3;
    key->children = NULL;
    key->child_count = 0;
    
    tree_node *val = malloc(sizeof(tree_node));
    val->type = INT;
    val->val.comp_int = 25;
    val->children = NULL;
    val->child_count = 0;
    
    tree_node *dict = malloc(sizeof(tree_node));
    dict->type = DICT;
    dict->child_count = 2;
    dict->children = malloc(2 * sizeof(tree_node*));
    dict->children[0] = key;
    dict->children[1] = val;
    
    unsigned char *result = bencode(dict);
    assert_equals("Dictionary with integer value", result, "d3:agei25ee");
}

void test_nested_dict() {
    tree_node *inner_key = malloc(sizeof(tree_node));
    inner_key->type = STR;
    inner_key->val.comp_str = "x";
    inner_key->val_size = 1;
    inner_key->children = NULL;
    inner_key->child_count = 0;
    
    tree_node *inner_val = malloc(sizeof(tree_node));
    inner_val->type = STR;
    inner_val->val.comp_str = "y";
    inner_val->val_size = 1;
    inner_val->children = NULL;
    inner_val->child_count = 0;
    
    tree_node *inner_dict = malloc(sizeof(tree_node));
    inner_dict->type = DICT;
    inner_dict->child_count = 2;
    inner_dict->children = malloc(2 * sizeof(tree_node*));
    inner_dict->children[0] = inner_key;
    inner_dict->children[1] = inner_val;
    
    tree_node *outer_key = malloc(sizeof(tree_node));
    outer_key->type = STR;
    outer_key->val.comp_str = "a";
    outer_key->val_size = 1;
    outer_key->children = NULL;
    outer_key->child_count = 0;
    
    tree_node *outer_dict = malloc(sizeof(tree_node));
    outer_dict->type = DICT;
    outer_dict->child_count = 2;
    outer_dict->children = malloc(2 * sizeof(tree_node*));
    outer_dict->children[0] = outer_key;
    outer_dict->children[1] = inner_dict;
    
    unsigned char *result = bencode(outer_dict);
    assert_equals("Nested dictionary", result, "d1:ad1:x1:yee");
}

void test_dict_with_list() {
    tree_node *item1 = malloc(sizeof(tree_node));
    item1->type = INT;
    item1->val.comp_int = 1;
    item1->children = NULL;
    item1->child_count = 0;
    
    tree_node *item2 = malloc(sizeof(tree_node));
    item2->type = INT;
    item2->val.comp_int = 2;
    item2->children = NULL;
    item2->child_count = 0;
    
    tree_node *list = malloc(sizeof(tree_node));
    list->type = LIST;
    list->child_count = 2;
    list->children = malloc(2 * sizeof(tree_node*));
    list->children[0] = item1;
    list->children[1] = item2;
    
    tree_node *key = malloc(sizeof(tree_node));
    key->type = STR;
    key->val.comp_str = "nums";
    key->val_size = 4;
    key->children = NULL;
    key->child_count = 0;
    
    tree_node *dict = malloc(sizeof(tree_node));
    dict->type = DICT;
    dict->child_count = 2;
    dict->children = malloc(2 * sizeof(tree_node*));
    dict->children[0] = key;
    dict->children[1] = list;
    
    unsigned char *result = bencode(dict);
    assert_equals("Dictionary with list value", result, "d4:numsli1ei2eee");
}

int main() {
    printf("Running bencode encoder tests...\n\n");
    
    test_empty_list();
    test_empty_dict();
    test_simple_string();
    test_simple_int();
    test_list_of_strings();
    test_nested_list();
    test_simple_dict();
    test_dict_with_int();
    test_nested_dict();
    test_dict_with_list();
    
    printf("\n=================================\n");
    printf("Total tests: %d\n", test_count);
    printf("Passed: %d\n", passed);
    printf("Failed: %d\n", failed);
    printf("=================================\n");
    
    return failed > 0 ? 1 : 0;
}
