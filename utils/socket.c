#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

int create_socket(char *host, int port) {
    // Create a TCP socket (AF_INET = IPv4, SOCK_STREAM = TCP, 0 = default protocol)
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("socket creation failed");
        return -1;
    }
    
    // Resolve hostname (e.g., "torrent.ubuntu.com") to IP address
    struct hostent *server = gethostbyname(host);
    if (server == NULL) {
        perror("hostname resolution failed");
        return -1;
    }
    
    // Set up the server address structure
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;  // IPv4
    server_addr.sin_port = htons(port);  // Convert port to network byte order (big-endian)
    // Copy the resolved IP address into the structure
    memcpy(&server_addr.sin_addr.s_addr, server->h_addr, server->h_length);
    
    // Attempt to connect to the server
    printf("Connecting to %s:%d...\n", host, port);
    if (connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("connection failed");
        return -1;
    }
    
    return sock;
}

SSL_CTX* init_ssl_context() {
    SSL_library_init();
    SSL_load_error_strings();
    OpenSSL_add_all_algorithms();
    
    SSL_CTX *ctx = SSL_CTX_new(TLS_client_method());
    if (!ctx) {
        ERR_print_errors_fp(stderr);
        return NULL;
    }
    return ctx;
}

SSL* create_ssl_connection(int sock, SSL_CTX *ctx, char *host) {
    SSL *ssl = SSL_new(ctx);
    SSL_set_fd(ssl, sock);
    SSL_set_tlsext_host_name(ssl, host);  // For SNI
    
    printf("Establishing SSL connection...\n");
    if (SSL_connect(ssl) <= 0) {
        ERR_print_errors_fp(stderr);
        return NULL;
    }
    
    printf("✓ SSL connection established\n");
    return ssl;
}

int main() {
    printf("=== HTTPS Connection Test ===\n");
    
    char *host = "tracker.opentrackr.org";
    int port = 1337;
    
    // Create TCP socket
    int sock = create_socket(host, port);
    if (sock < 0) {
        printf("✗ Failed to create socket\n");
        return 1;
    }
    printf("✓ Socket created successfully: %d\n", sock);
    
    // Initialize SSL
    SSL_CTX *ctx = init_ssl_context();
    if (!ctx) {
        printf("✗ Failed to initialize SSL context\n");
        close(sock);
        return 1;
    }
    printf("✓ SSL context initialized\n");
    
    // Create SSL connection
    SSL *ssl = create_ssl_connection(sock, ctx, host);
    if (!ssl) {
        printf("✗ Failed to establish SSL connection\n");
        SSL_CTX_free(ctx);
        close(sock);
        return 1;
    }
    
    printf("✓ Successfully connected to %s:%d via HTTPS\n", host, port);
    
    // Cleanup
    SSL_shutdown(ssl);
    SSL_free(ssl);
    SSL_CTX_free(ctx);
    close(sock);
    
    return 0;
}
