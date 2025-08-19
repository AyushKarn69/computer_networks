#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>       // for close()
#include <arpa/inet.h>    // for sockaddr_in, inet_pton()
#include <sys/socket.h>   // for socket functions

int main(int argc, char* argv[]) {
    int client_id = (argc > 1) ? atoi(argv[1]) : 0;

    // 1. Create socket
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket < 0) {
        fprintf(stderr, "Client #%d: Socket creation failed\n", client_id);
        return 1;
    }

    // 2. Server address setup
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr)); // Zero out structure
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);

    // Use your server IP here:
    // inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr); // localhost
    inet_pton(AF_INET, "192.168.0.149", &server_addr.sin_addr);

    // 3. Connect to server
    if (connect(client_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        fprintf(stderr, "Client #%d: Connection failed\n", client_id);
        close(client_socket);
        return 1;
    }

    printf("Client #%d: Connected to server\n", client_id);

    // 4. Prepare and send message with client ID
    char msg[100];
    snprintf(msg, sizeof(msg), "Hello from client #%d", client_id);
    send(client_socket, msg, strlen(msg), 0);

    // 5. Receive response
    char buffer[1024];
    ssize_t bytes_received = recv(client_socket, buffer, sizeof(buffer) - 1, 0);
    if (bytes_received > 0) {
        buffer[bytes_received] = '\0'; // Null-terminate received data
        printf("Client #%d: Server says: %s\n", client_id, buffer);
    }

    // 6. Close socket
    close(client_socket);
    return 0;
}
