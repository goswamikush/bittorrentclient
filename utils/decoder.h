#ifndef DECODER_H
#define DECODER_H

#include "../types/tree.h"

void decode(char file_path[]);

tree_node *parse_string_bytes(const unsigned char *bytes);
tree_node *parse_int_bytes(const unsigned char *bytes);

int add_child(tree_node *parent, tree_node *child);

int decode_tree_bytes(const unsigned char *bytes, tree_node *root, int pointer, int num_bytes);

#endif
