#ifndef DECODER_H
#define DECODER_H

#include "../types/tree.h"

void decode(char file_path[]);
tree_node *parse_string(const char *component);

#endif
