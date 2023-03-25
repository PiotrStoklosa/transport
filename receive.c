//Piotr Stoklosa 314987

#include "receive.h"

int min1000(int size, int limit) {
    if (limit - size < 1000) {
        return limit - size;
    }
    return 1000;
}

void writeToFile(char *file_name, char *message, int length) {
    FILE *f = fopen(file_name, "a");
    for (int i = 0; i < length; i++) {
        fputc(message[i], f);
    }
    fclose(f);
}

int receive(struct sockaddr_in server_address, bool *received, int sockfd, char *file_name, int size, int len) {

    struct sockaddr_in sender;
    socklen_t sender_len = sizeof(sender);
    char buffer[100000];
    ssize_t packet_len = recvfrom(sockfd, buffer, 1100, 0, (struct sockaddr *) &sender, &sender_len);
    if (packet_len < 0) {
        exit(EXIT_FAILURE);
    }
    if (sender.sin_port != server_address.sin_port || sender.sin_addr.s_addr != server_address.sin_addr.s_addr){
        return true;
    }
    char start[6];
    char count[6];
    char message[10005];
    for (int z = 0; z < 6; z++) {
        start[z] = '\000';
        count[z] = '\000';
    }
    for (int z = 0; z < 1004; z++) {
        message[z] = '\000';
    }
    int pointer_in_response = 0;
    pointer_in_response += 5;
    for (; buffer[pointer_in_response] != ' '; pointer_in_response++) {
        strncat(start, &buffer[pointer_in_response], 1);
    }
    pointer_in_response++;
    for (; buffer[pointer_in_response] != '\n'; pointer_in_response++) {
        strncat(count, &buffer[pointer_in_response], 1);
    }
    pointer_in_response++;
    int length = min1000(size, len);
    for (int y = 0; y < length; y++) {
        message[y] = buffer[y + pointer_in_response];
    }

    int id_int = atoi(start) / 1000;
    if (!received[id_int]) {
        received[id_int] = true;
        writeToFile(file_name, message, length);
        return false;
    }

    return true;
}
