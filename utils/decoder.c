#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../types/tree.h"

tree_node *parse_string_bytes(const unsigned char *component);
tree_node *parse_int_bytes(const unsigned char *component);

int add_child(tree_node *parent, tree_node *child);

int decode(char file_path[]) {
    FILE *fptr;
    unsigned char *buffer;
    long file_size;

    fptr = fopen("big-buck-bunny.torrent", "rb");

    if (fptr == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    fseek(fptr, 0, SEEK_END);
    file_size = ftell(fptr);
    rewind(fptr);

    buffer = (unsigned char *)malloc(file_size);
    if (buffer == NULL) {
        perror("Memory allocation failed");
        fclose(fptr);
        return 1;
    }

    size_t bytes_read = fread(buffer, 1, file_size, fptr);
    if (bytes_read != file_size) {
        perror("Error reading file");
        free(buffer);
        fclose(fptr);
        return 1;
    }

    free(buffer);
    fclose(fptr);

    return EXIT_SUCCESS;
}

/*
* Decode tree implementation with passing in smaller version of previous string
* 
* Parameters
*   text - input bencoded string
*   root - tree node
*   pointer - position in string
*
* Returns
*   int - number of chars consumed
*/
int decode_tree_bytes(const unsigned char *bytes, tree_node *root, int pointer, int num_bytes) {
    if (pointer >= num_bytes) {
        return 0;
    }

    if (atoi((char*)(bytes + pointer)) != 0) {
        tree_node *curr_node = parse_string_bytes(bytes + pointer);
        add_child(root, curr_node);

        int colon_pos = 0;

        while (bytes[pointer + colon_pos] != 0x3A) {
            colon_pos++;
        }

        return atoi((char*)(bytes + pointer)) + colon_pos + 1;
    }

    if (bytes[pointer] == 0x69) {
        tree_node *curr_node = parse_int_bytes(bytes + pointer);
        add_child(root, curr_node);

        int chars_consumed = 0;

        while (bytes[pointer + chars_consumed] != 0x65) {
            chars_consumed++;
        }

        return chars_consumed + 1;
    }

    if (bytes[pointer] == 0x65) {
        return 1;
    }

    if (bytes[pointer] == 0x6C) {
        int chars_consumed = 0;

        tree_node *curr_node = malloc(sizeof(tree_node));

        curr_node->type = LIST;
        curr_node->val.comp_str = NULL;
        curr_node->children = NULL;
        curr_node->child_count = 0;

        add_child(root, curr_node);
        
        pointer++;
        while (bytes[pointer] != 0x65 && bytes[pointer]) {
            int step = decode_tree_bytes(bytes, curr_node, pointer, num_bytes);
            pointer += step;
            chars_consumed += step;
        }

        return chars_consumed + 2;
    }

    if (bytes[pointer] == 0x64) {
        int chars_consumed = 0;

        tree_node *curr_node = malloc(sizeof(tree_node));

        curr_node->type = DICT;
        curr_node->val.comp_str = NULL;
        curr_node->children = NULL;
        curr_node->child_count = 0;

        add_child(root, curr_node);

        pointer++;
        while (bytes[pointer] != 0x65 && bytes[pointer] != 0x00) {
            int step = decode_tree_bytes(bytes, curr_node, pointer, num_bytes);
            pointer += step;
            chars_consumed += step;
        }

        return chars_consumed + 2;
    }

    return 0;
}

/*
* Parses bencoded strings i.e. '4:spam'
*
* Parameters:
*    str - bencoded string component
*
* Returns:
*    pointer to tree_node
*/
tree_node *parse_string_bytes(const unsigned char *bytes) { 
    // Find string length
    int colon_pos = 0;

    while (bytes[colon_pos] != 0x3a) {
        colon_pos++;
    }

    int str_len = atoi((char*)(bytes));

    // Get string value
    char *str_value = malloc(str_len + 1);
    memcpy(str_value, bytes + colon_pos + 1, str_len);
    str_value[str_len] = '\0';

    // Create new node
    tree_node *node = malloc(sizeof(tree_node));

    node->type = STR;
    node->val.comp_str = str_value;
    node->child_count = 0;
    node->children = NULL;
    
    return node;
};

/*
* Parses bencoded numbers i.e. 'i3e'
*
* Parameters:
*    str - bencoded string component
*
* Returns:
*    pointer to tree_node
*/
tree_node *parse_int_bytes(const unsigned char *bytes) { 
    // Obtain number
    int number = atoi((char*)(bytes + 1));
    
    // Create new node
    tree_node *node = malloc(sizeof(tree_node));

    node->type = INT;
    node->val.comp_int = number;
    node->child_count = 0;
    node->children = NULL;
    
    return node;
};

/*
* Adds child to the children member of tree_node struct
* 
* Parameters:
*   parent - pointer to tree_node
*   child - pointer to tree_node
*
* Returns:
*   int of whether the operation was successful or not
*/
int add_child(tree_node *parent, tree_node *child) {
    tree_node **new_children = realloc(parent->children, sizeof(tree_node *) * (parent->child_count + 1));

    if (!new_children) {
        return 0;
    }

    parent->children = new_children;
    parent->children[parent->child_count] = child;
    parent->child_count++;

    return 1;
}
