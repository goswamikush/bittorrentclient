#ifndef REQUEST_H
#define REQUEST_H

#include <stddef.h>

typedef struct {
    char *host;
    size_t port;
    char* path;

} parsed_url;

parsed_url *parse_url(char *url);

#endif
