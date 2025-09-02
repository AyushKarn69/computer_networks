#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>         // for close()
#include <pthread.h>
#include <netinet/in.h>     // for sockaddr_in
#include <sys/socket.h>     // for socket functions
#include <fcntl.h>          // for open()
#include <sys/stat.h>       // for stat()

#define PORT 8080
#define BUFFER_SIZE 4096

void* handle_client(void* arg) {
    int client_socket = *((int*)arg);
    free(arg);

    char buffer[BUFFER_SIZE];
    ssize_t bytes_received = recv(client_socket, buffer, sizeof(buffer) - 1, 0);

    if (bytes_received > 0) {
        buffer[bytes_received] = '\0';
        printf("Server received:\n%s\n", buffer);

        // Very basic HTTP request check
        if (strncmp(buffer, "GET /", 5) == 0) {
            // Open index.html
            FILE *file = fopen("index.html", "r");
            if (!file) {
                const char* not_found =
                    "HTTP/1.1 404 Not Found\r\n"
                    "Content-Type: text/plain\r\n"
                    "Content-Length: 13\r\n\r\n"
                    "404 Not Found";
                send(client_socket, not_found, strlen(not_found), 0);
            } else {
                // Get file size
                fseek(file, 0, SEEK_END);
                long file_size = ftell(file);
                rewind(file);

                // Read file content into memory
                char *file_content = malloc(file_size + 1);
                fread(file_content, 1, file_size, file);
                file_content[file_size] = '\0';
                fclose(file);

                // Prepare HTTP response header
                char header[BUFFER_SIZE];
                snprintf(header, sizeof(header),
                    "HTTP/1.1 200 OK\r\n"
                    "Content-Type: text/html\r\n"
                    "Content-Length: %ld\r\n"
                    "Connection: close\r\n\r\n", file_size);

                // Send header + content
                send(client_socket, header, strlen(header), 0);
                send(client_socket, file_content, file_size, 0);

                free(file_content);
            }
        } else {
            // Unsupported request
            const char* bad_request =
                "HTTP/1.1 400 Bad Request\r\n"
                "Content-Type: text/plain\r\n"
                "Content-Length: 12\r\n\r\n"
                "Bad Request";
            send(client_socket, bad_request, strlen(bad_request), 0);
        }
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
    memset(&server_addr, 0, sizeof(server_addr));

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

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

    printf("Server listening on http://192.168.0.162:%d\n", PORT);

    while (1) {
        int client_socket = accept(server_socket, NULL, NULL);
        if (client_socket < 0) {
            perror("Accept failed");
            continue;
        }

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

        pthread_detach(thread_id);
    }

    close(server_socket);
    return 0;
}
