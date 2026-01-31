#ifndef TRACKER_H
#define TRACKER_H

#include <stddef.h>

typedef struct {
    unsigned char* info_hash;
    unsigned char* peer_id;
    size_t port;
    size_t bytes_uploaded;
    size_t bytes_downloaded;
    size_t bytes_left;
    size_t compact;
} tracker_url_params;

char* generate_tracker_url(*tracker_url_params);

#endif 
