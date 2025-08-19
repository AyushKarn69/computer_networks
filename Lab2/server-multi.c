#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>         // for close()
#include <pthread.h>
#include <netinet/in.h>     // for sockaddr_in
#include <sys/socket.h>     // for socket functions

void* handle_client(void* arg) {
    int client_socket = *((int*)arg);
    free(arg);  // free the allocated memory

    char buffer[1024];
    ssize_t bytes_received = recv(client_socket, buffer, sizeof(buffer) - 1, 0);

    if (bytes_received > 0) {
        buffer[bytes_received] = '\0';  // null-terminate string
        printf("Server received: %s\n", buffer);

        const char* response = "Hello from server!";
        send(client_socket, response, strlen(response), 0);
    }

    close(client_socket);
    return NULL;
}

int main() {
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));  // zero out struct

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = INADDR_ANY;  // listen on all interfaces

    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    if (listen(server_socket, 5) < 0) {
        perror("Listen failed");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port 8080\n");

    while (1) {
        int client_socket = accept(server_socket, NULL, NULL);
        if (client_socket < 0) {
            perror("Accept failed");
            continue;
        }

        // Allocate memory to pass socket descriptor safely
        int* pclient = malloc(sizeof(int));
        if (pclient == NULL) {
            perror("Malloc failed");
            close(client_socket);
            continue;
        }
        *pclient = client_socket;

        pthread_t thread_id;
        if (pthread_create(&thread_id, NULL, handle_client, pclient) != 0) {
            perror("Thread creation failed");
            free(pclient);
            close(client_socket);
            continue;
        }

        pthread_detach(thread_id);  // Automatically reclaim resources on thread exit
    }

    close(server_socket);
    return 0;
}
