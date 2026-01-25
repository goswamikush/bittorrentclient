#ifndef TREE_H
#define TREE_H

#include <stdlib.h>

struct tree_node;

typedef enum {
    LIST,
    DICT,
    INT,
    STR
} node_type;

typedef union {
    int comp_int;
    char *comp_str;
} node_value;

typedef struct {
    node_type type;
    node_value val;
    size_t child_count;
    struct tree_node **children;
} tree_node;


#endif
