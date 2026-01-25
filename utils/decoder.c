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
*    tree_node
*/
tree_node parse_string(char component[]) { 
    int str_len = atoi(component[0]);
    char str_value[str_len];

    memcpy(str_value, component + 2, str_len);

    tree_node new_node = {.type STR, .}
}



