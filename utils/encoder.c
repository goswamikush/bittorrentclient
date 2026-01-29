#include <stdio.h>
#include <string.h>
#include <math.h>
#include "../types/tree.h"

unsigned char *bencode_string(tree_node *node);

unsigned char *bencode(tree_node *node) {
    unsigned char *res;

    if (node->type == STR) {
        bencode_string(node);
    }

    return res;
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

int main() {
    tree_node *test_node = malloc(sizeof(tree_node));

    char test_val[6] = "hello";

    test_node->type = STR;
    test_node->val.comp_str = test_val;
    test_node->val_size = 5;

    printf("Final bencoded string: %s\n", bencode_string(test_node));
    
    return 0;
}
