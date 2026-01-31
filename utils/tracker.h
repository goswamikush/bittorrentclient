#ifndef TRACKER_H
#define TRACKER_H

#include <stddef.h>

typedef struct {
    unsigned char *info_hash_encoded;
    unsigned char *peer_id;
    char *tracker;
    size_t port;
    size_t bytes_uploaded;
    size_t bytes_downloaded;
    size_t bytes_left;
    size_t compact;
} tracker_url_params;

char* generate_tracker_url(tracker_url_params *params);
char* url_encode_hash(unsigned char *hash, size_t length);

#endif 
