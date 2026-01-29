#ifndef TORRENT_FILE_H
#define TORRENT_FILE_H

#include "tree.h"

typedef struct {
    char *announce;
    char *info_hash;
    int piece_length;
    unsigned char *pieces;
    char *file_name;
    int total_size;
} torrent_file;

torrent_file *write_torrent_file_struct(tree_node *node);

#endif
