#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "request.h"

parsed_url *parse_url(char *url) {
    parsed_url *res = malloc(sizeof(parsed_url));

    // Get host
    char *host = malloc(128);

    size_t i = 8;

    while (url[i] != '/') {
        host[i - 8] = url[i];
        i++;
    }

    host[i - 8] = '\0';

    res->host = host;

    printf("Host name: %s\n", host);

    // Get port
    res->port = 443;

    // Get path
    res->path = url + i;

    printf("Path: %s\n", res->path);

    return res;
}

int main() {
    printf("=== URL Parsing Test ===\n\n");
    
    char url[] = "https://torrent.ubuntu.com/announce?info_hash=%da%7d%86%f0%5b%8b%ec%08%fd%7a%8c%cc%a3%f4%78%41%6b%a7%c6%d7&peer_id=-PC0001-123456789012&port=6881&uploaded=0&downloaded=0&left=0&compact=1";
    
    printf("Input URL:\n%s\n\n", url);
    
    parsed_url *result = parse_url(url);
    
    printf("Parsed Results:\n");
    printf("Host: %s\n", result->host);
    printf("Port: %zu\n", result->port);
    printf("Path: %s\n", result->path);
    
    printf("\n=== Expected ===\n");
    printf("Host: torrent.ubuntu.com\n");
    printf("Port: 443\n");
    printf("Path: /announce?info_hash=%%da%%7d%%86%%f0%%5b%%8b%%ec%%08%%fd%%7a%%8c%%cc%%a3%%f4%%78%%41%%6b%%a7%%c6%%d7&peer_id=-PC0001-123456789012&port=6881&uploaded=0&downloaded=0&left=0&compact=1\n");
    
    return 0;
}
