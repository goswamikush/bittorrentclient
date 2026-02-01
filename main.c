#include <stdio.h>
#include "utils/decoder.h"
#include "types/torrent_file.h"
#include "utils/info_hash.h"
#include "utils/tracker.h"


int main() {
    char file_path[] = "/Users/kushgoswami/Documents/Projects/bit_torrent_client/ubuntu-25.10-desktop-amd64.iso.torrent";

    torrent_file *parsed_torrent_file = decode(file_path);
    
    char *url_encoded_hash = url_encode_hash(parsed_torrent_file->info_hash, 20);

    tracker_url_params params;
    params.tracker = parsed_torrent_file->announce;  
    params.port = 6881;  
    params.info_hash_encoded = (unsigned char*)url_encoded_hash;
    params.peer_id = (unsigned char*)"-PC0001-123456789012"; 
    params.bytes_uploaded = 0;  
    params.bytes_downloaded = 0;  
    params.bytes_left = parsed_torrent_file->total_size;  
    params.compact = 1;  

    char *tracker_url = generate_tracker_url(&params);

    printf("Tracker URL:\n%s\n", tracker_url);

    return 0;
}
