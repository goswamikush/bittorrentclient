#include <stdio.h>
#include <stdlib.h>
#include <tree.h>

int decode(char file_path[]) {
    FILE *fptr;
    char buffer[255];

    fptr = fopen("test.txt", "r");

    if (fptr == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    while (fgets(buffer, sizeof(buffer), fptr) != NULL) {
        printf("%s", buffer);
    }

    fclose(fptr);

    return EXIT_SUCCESS;
}

int decode_tree() {
    // Base case
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
tree_node *parse_string(const char *component) { 
    int str_len = atoi(component);

    char *str_value = malloc(str_len + 1);
    tree_node *node = malloc(sizeof(tree_node));

    memcpy(str_value, component + 2, str_len);
    str_value[str_len] = '\0';

    node->type = STR;
    node->val.comp_str = str_value;
    node->child_count = 0;
    node->children = NULL;
    
    return node;
};



