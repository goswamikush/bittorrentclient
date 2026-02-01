#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tracker.h"

char *generate_tracker_url(tracker_url_params *params) {
    char *url = malloc(1024);
    sprintf(url, "%s?info_hash=%s&peer_id=%s&port=%zu&uploaded=%zu&downloaded=%zu&left=%zu&compact=%zu",
        params->tracker, params->info_hash_encoded, params->peer_id, params->port, params->bytes_uploaded, params->bytes_downloaded, params->bytes_left, params->compact);
    return url;
}

char* url_encode_hash(unsigned char *hash, size_t length) {
    char *url_encode_hash = malloc(length * 3 + 1);

    for (int i = 0; i < length; i++) {
        char curr_byte[3];

        curr_byte[0] = '%';

        int upper = hash[i] >> 4;
        curr_byte[1] = upper < 10 ? ('0' + upper) : ('a' + upper - 10);

        int lower = hash[i] & 0x0F;
        curr_byte[2] = lower < 10 ? ('0' + lower) : ('a' + lower - 10);

        memcpy(url_encode_hash + i * 3, curr_byte, 3);
    }

    url_encode_hash[length * 3] = '\0';

    return url_encode_hash;
}

int url_encode_test() {
    printf("=== URL Encode Hash Test ===\n\n");
    
    // Test case 1: Simple hash
    unsigned char hash1[] = {0x7e, 0x25, 0xc6, 0x1d, 0xd1};
    char *encoded1 = url_encode_hash(hash1, 5);
    const char *expected1 = "%7e%25%c6%1d%d1";
    
    printf("Test 1:\n");
    printf("Input:    {0x7e, 0x25, 0xc6, 0x1d, 0xd1}\n");
    printf("Expected: %s\n", expected1);
    printf("Got:      %s\n", encoded1);
    
    if (strcmp(encoded1, expected1) == 0) {
        printf("✓ TEST 1 PASSED\n\n");
    } else {
        printf("✗ TEST 1 FAILED\n\n");
    }
    
    // Test case 2: Full 20-byte hash
    unsigned char hash2[] = {
        0x7e, 0x25, 0xc6, 0x1d, 0xd1, 0x97, 0x3c, 0x28, 
        0x40, 0xa4, 0xdb, 0x3b, 0x88, 0x12, 0x0d, 0x2a, 
        0x1b, 0x7c, 0x12, 0x3c
    };
    char *encoded2 = url_encode_hash(hash2, 20);
    const char *expected2 = "%7e%25%c6%1d%d1%97%3c%28%40%a4%db%3b%88%12%0d%2a%1b%7c%12%3c";
    
    printf("Test 2:\n");
    printf("Input:    20-byte hash\n");
    printf("Expected: %s\n", expected2);
    printf("Got:      %s\n", encoded2);
    
    if (strcmp(encoded2, expected2) == 0) {
        printf("✓ TEST 2 PASSED\n\n");
    } else {
        printf("✗ TEST 2 FAILED\n\n");
    }
    
    free(encoded1);
    free(encoded2);
    
    return 0;
}

// int main() {
//     printf("=== Tracker URL Generation Test ===\n\n");
    
//     // Create test parameters
//     tracker_url_params params;
//     params.tracker = "tracker.example.com";
//     params.port = 6969;
//     params.info_hash_encoded = (unsigned char*)"%7e%25%c6%1d%d1%97%3c%28%40%a4%db%3b%88%12%0d%2a%1b%7c%12%3c";
//     params.peer_id = (unsigned char*)"-PC0001-123456789012";
//     params.bytes_uploaded = 0;
//     params.bytes_downloaded = 0;
//     params.bytes_left = 276445467;
//     params.compact = 1;
    
//     // Generate URL
//     char *url = generate_tracker_url(&params);
    
//     // Expected URL
//     const char *expected = "http://tracker.example.com:6969/announce?info_hash=%7e%25%c6%1d%d1%97%3c%28%40%a4%db%3b%88%12%0d%2a%1b%7c%12%3c&peer_id=-PC0001-123456789012&port=6969&uploaded=0&downloaded=0&left=276445467&compact=1";
    
//     // Print results
//     printf("Generated URL:\n%s\n\n", url);
//     printf("Expected URL:\n%s\n\n", expected);
    
//     // Verify
//     if (strcmp(url, expected) == 0) {
//         printf("✓ TEST PASSED: URLs match!\n");
//     } else {
//         printf("✗ TEST FAILED: URLs don't match!\n");
//     }
    
//     free(url);

//     url_encode_test();
//     return 0;
// }
