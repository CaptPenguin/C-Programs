#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <errno.h>

#define ADDR "96.125.115.212"
#define PORT 24194
#define KEY "ROUX"

char* xor_decrypt(char* data, int len, char* key, int key_len) {
    char* decrypted_data = (char*) malloc(len + 1);
    int i;
    for (i = 0; i < len; i++) {
        decrypted_data[i] = data[i] ^ key[i % key_len];
    }
    decrypted_data[len] = '\0';
    return decrypted_data;
}

int main() {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("Failed to create socket");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    inet_aton(ADDR, &server_addr.sin_addr);

    if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Failed to connect to server");
        exit(EXIT_FAILURE);
    }

    char buffer[1024];
 while (1) {
        printf("Enter message to send: ");
        fgets(buffer, 1024, stdin);
        buffer[strcspn(buffer, "\n")] = 0; 

        // Encrypt the message before sending
        int key_len = strlen(KEY);
        char* encrypted_buffer = xor_decrypt(buffer, strlen(buffer), KEY, key_len);

        int len = strlen(encrypted_buffer);
        if (send(sock, encrypted_buffer, len, 0) != len) {
            perror("Failed to send message");
            exit(EXIT_FAILURE);
        }

        int bytes_received = recv(sock, buffer, sizeof(buffer), 0);
        if (bytes_received < 0) {
            perror("Failed to receive message");
            exit(EXIT_FAILURE);
        } else if (bytes_received == 0) {
            printf("Server disconnected\n");
            exit(EXIT_SUCCESS);
        }

        // Decrypt the message received from the server
        char* decrypted_buffer = xor_decrypt(buffer, bytes_received, KEY, key_len);

        decrypted_buffer[bytes_received] = '\0';
        printf("Received message: %s\n", decrypted_buffer);

        free(encrypted_buffer);
        free(decrypted_buffer);
    }

    close(sock);
    return 0;
}