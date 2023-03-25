//Piotr Stoklosa 314987

#include "send.h"

void sendMessage(char *message, int sockfd, struct sockaddr_in server_address) {
    ssize_t message_len = strlen(message);
    if (sendto(sockfd, message, message_len, 0, (struct sockaddr *) &server_address, sizeof(server_address)) !=
        message_len) {
        fprintf(stderr, "sendto error: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
}