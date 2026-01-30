#include <stdio.h>
#include <string.h>
#include <math.h>
#include "../types/tree.h"

unsigned char *bencode_string(tree_node *node);
unsigned char *bencode_int(tree_node *node);

unsigned char *bencode(tree_node *node) {
    if (node->type == LIST || node->type == DICT) {
        // Process everything within the list which should return a string
        tree_node **children = node->children;
        int child_count = node->child_count;

        unsigned char *curr_string = malloc(1);

        if (node->type == LIST) {
            curr_string[0] = 'l';
        } else {
            curr_string[0] = 'd';
        }

        size_t total_string_length = 1;

        for (int i = 0; i < child_count; i++) {
            // Get bencoded of children
            unsigned char *child = bencode(children[i]);
            size_t curr_len = strlen((char*)child);
            total_string_length += curr_len;

            // Allocate memory to store each child
            curr_string = realloc(curr_string, total_string_length);

            memcpy(curr_string + total_string_length - curr_len, child, curr_len);
        }

        curr_string = realloc(curr_string, total_string_length + 2);

        curr_string[total_string_length] = 'e';
        curr_string[total_string_length + 1] = '\0';

        return curr_string;
    }

    if (node->type == STR) {
        return bencode_string(node);
    }

    if (node->type == INT) {
        return bencode_int(node);
    }

    return NULL;
}

unsigned char *bencode_string(tree_node *node) {
    // Length
    size_t str_length = node->val_size;

    // Digit length
    int digit_length = 0;
    size_t str_length_copy = str_length; 

    while (str_length_copy > 0) {
        str_length_copy /= 10;
        digit_length++;
    }

    printf("Digit length %d\n", digit_length);

    // Content
    char *content = node->val.comp_str;

    // Create new string
    unsigned char *bencoded_string = malloc(str_length + digit_length + 2);

    // Add str_length into array
    int i = 0;
    str_length_copy = str_length;
    while (i < digit_length) {
        int curr_digit = str_length_copy % 10;
        char curr_digit_char = curr_digit + '0';

        str_length_copy = str_length_copy / 10;

        int curr_index = digit_length - i - 1;

        bencoded_string[curr_index] = (char)curr_digit_char;

        printf("Curr index %d\n", curr_index);
        printf("Curr char %c\n", bencoded_string[curr_index]);

        i++;
    }

    // Add colon
    bencoded_string[digit_length] = ':';

    // Add word
    memcpy(bencoded_string + digit_length + 1, content, strlen(content));

    bencoded_string[str_length + digit_length + 1] = '\0';

    printf("Bencoded string: %s\n", bencoded_string);

    return bencoded_string;
}

unsigned char *bencode_int(tree_node *node) {
    // Int num of digits
    int int_value = node->val.comp_int;

    int int_value_copy = int_value;

    int i = 0;
    int total_length = 0;
    while (int_value_copy > 0) {
        int_value_copy = int_value_copy / 10;
        total_length++;
    }

    // Allocate mem for bencoded_int
    unsigned char *bencoded_int = malloc(total_length + 3);

    // Add prefix 'i'
    bencoded_int[0] = 'i';

    // Add suffix 'e'
    bencoded_int[total_length + 1] = 'e';

    // Add null terminator
    bencoded_int[total_length + 2] = '\0';

    // Add digits in between
    int_value_copy = int_value;
    i = total_length;
    while (i > 0) {
        int curr_digit = int_value_copy % 10 + '0';
        int_value_copy = int_value_copy / 10;

        bencoded_int[i] = (char)curr_digit;

        i--;
    }

    printf("Bencoded int %s\n", bencoded_int);

    return bencoded_int;
}
