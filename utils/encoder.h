#ifndef ENCODER_H
#define ENCODER_H

#include "../types/tree.h"

unsigned char *bencode(tree_node *node, size_t *out_length);

#endif
