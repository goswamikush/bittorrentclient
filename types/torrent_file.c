#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "torrent_file.h"
#include "../utils/info_hash.h"

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
            printf("Found info dict!\n");
            info_dict = parent_dict->children[i + 1];
        }
    }

    res->info_hash = compute_info_hash(info_dict);

    // Parse piece length
    int piece_length;
    for (int i = 0; i < info_dict->child_count; i++) {
        if (info_dict->children[i]->type == STR && 
            strcmp(info_dict->children[i]->val.comp_str, "piece length") == 0) {
                piece_length = info_dict->children[i + 1]->val.comp_int;
        }
    }

    res->piece_length = piece_length;

    printf("Piece length: %d\n", piece_length);

    // Parse pieces and pieces length
    unsigned char *pieces;
    int pieces_length;

    for (int i = 0; i < info_dict->child_count; i++) {
        if (info_dict->children[i]->type == STR && 
            strcmp(info_dict->children[i]->val.comp_str, "pieces") == 0) {
                pieces = (unsigned char*)info_dict->children[i + 1]->val.comp_str;
                pieces_length = info_dict->children[i+1]->val_size;
        }
    }

    res->pieces = pieces;
    res->pieces_length = pieces_length;

    printf("Pieces length %d\n", pieces_length);

    return res;
}
