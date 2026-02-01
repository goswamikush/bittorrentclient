#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>
#include "../types/tree.h"
#include "encoder.h"

unsigned char* compute_info_hash(tree_node *info_dict) {
    // Bencode the info dict
    unsigned char *bencoded = bencode(info_dict);
    size_t length = strlen((char*)bencoded); 
    
    // Hash it
    unsigned char *hash = malloc(SHA_DIGEST_LENGTH);
    SHA1(bencoded, length, hash);

    for (int i = 0; i < SHA_DIGEST_LENGTH; i++) {
        printf("%02x", hash[i]);
    }
    printf("\n");
    
    return hash;  // 20 bytes
}

// int main() {
//     // Key: "name"
//     tree_node *key_name = malloc(sizeof(tree_node));
//     key_name->type = STR;
//     key_name->val.comp_str = "name";
//     key_name->val_size = 4;
//     key_name->children = NULL;
//     key_name->child_count = 0;
    
//     // Value for "name": "example"
//     tree_node *val_name = malloc(sizeof(tree_node));
//     val_name->type = STR;
//     val_name->val.comp_str = "example";
//     val_name->val_size = 7;
//     val_name->children = NULL;
//     val_name->child_count = 0;
    
//     // Key: "piece length"
//     tree_node *key_piece_length = malloc(sizeof(tree_node));
//     key_piece_length->type = STR;
//     key_piece_length->val.comp_str = "piece length";
//     key_piece_length->val_size = 12;
//     key_piece_length->children = NULL;
//     key_piece_length->child_count = 0;
    
//     // Value for "piece length": 262144
//     tree_node *val_piece_length = malloc(sizeof(tree_node));
//     val_piece_length->type = INT;
//     val_piece_length->val.comp_int = 262144;
//     val_piece_length->children = NULL;
//     val_piece_length->child_count = 0;
    
//     // Create info dict with 2 key-value pairs (4 children)
//     tree_node *info_dict = malloc(sizeof(tree_node));
//     info_dict->type = DICT;
//     info_dict->child_count = 4;
//     info_dict->children = malloc(4 * sizeof(tree_node*));
//     info_dict->children[0] = key_name;
//     info_dict->children[1] = val_name;
//     info_dict->children[2] = key_piece_length;
//     info_dict->children[3] = val_piece_length;
    
//     printf("Computing info hash...\n");
//     unsigned char *hash = compute_info_hash(info_dict);
//     printf("Info hash computed successfully!\n");
    
//     return 0;
// }
