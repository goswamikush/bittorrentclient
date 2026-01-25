#ifndef DECODER_H
#define DECODER_H

#include "../types/tree.h"

void decode(char file_path[]);
tree_node *parse_string(const char *component);
int add_child(tree_node *parent, tree_node *child);
int decode_tree(const char *text, tree_node *root, int pointer);

#endif
