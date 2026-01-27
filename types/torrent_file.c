#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "torrent_file.h"

torrent_file *write_torrent_file_struct(tree_node *root_node) {
    torrent_file *res = malloc(sizeof(torrent_file));

    // Parse out announce field
    char *announce_url;
    tree_node *parent_dict = root_node->children[0];
    for (int i = 0; i < parent_dict->child_count; i++) {
        if (parent_dict->children[i]->type == STR && 
            strcmp(parent_dict->children[i]->val.comp_str, "announce") == 0) {
            announce_url = strdup(parent_dict->children[i + 1]->val.comp_str);
        }
    }

    res->announce = announce_url;

    printf("Announce URL: %s\n", announce_url);

    // Find info dict
    tree_node *info_dict = malloc(sizeof(tree_node));

    for (int i = 0; i < parent_dict->child_count; i++) {
        if (parent_dict->children[i]->type == STR && 
            strcmp(parent_dict->children[i]->val.comp_str, "info") == 0) {
            info_dict = parent_dict->children[i + 1];
        }
    }

    // Parse piece length
    int piece_length = info_dict->child_count;

    res->piece_length = piece_length;

    printf("Piece length: %d\n", piece_length);

    return res;
}
