#ifndef TORRENT_FILE_H
#define TORRENT_FILE_H

typedef struct {
    char *announce;
    char *info_hash;
    int piece_length;
    char *pieces;
    char *file_name;
    int total_size;
} torrent_file

#endif
