#include <stdio.h>
#include <stdlib.h>

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

