//Piotr Stoklosa 314987

#include "receive.h"
#include "send.h"
#include "transport.h"

void clear_content_of_file(char *name);

void prepareMessage(char *dst, int start, int length) {
    dst[0] = 0;
    char mess1[10];
    char mess2[10];
    char mess3[10];
    sprintf(mess1, "%s", "GET ");
    sprintf(mess2, "%d ", start);
    sprintf(mess3, "%d\n", min1000(start, length));
    strcat(dst, mess1);
    strcat(dst, mess2);
    strcat(dst, mess3);
}

int main(int argc, char *argv[]) {

    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        fprintf(stderr, "socket error: %s\n", strerror(errno));
        return EXIT_FAILURE;
    }

    if (argc != 5) {
        fprintf(stderr, "usage: %s address_IP port file_name size\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *address = argv[1];
    int port = atoi(argv[2]);
    char *file_name = argv[3];
    int len = atoi(argv[4]);

    clear_content_of_file(file_name);

    int datagrams = (int) (len / 1000) + 1;
    bool received[datagrams];

    for (int i = 0; i < datagrams; i++) {
        received[i] = 0;
    }

    struct sockaddr_in server_address;
    bzero(&server_address, sizeof(server_address));
    server_address.sin_family = AF_INET;

    if (port > 65535 || port < 0) {
        fprintf(stderr, "Provide valid port!\n");
        exit(EXIT_FAILURE);
    }

    server_address.sin_port = htons(port);
    if (!inet_pton(AF_INET, address, &server_address.sin_addr)) {
        fprintf(stderr, "Provide valid address IP!\n");
        exit(EXIT_FAILURE);
    }

    char request[100];
    for (int i = 0; i < len; i += 1000) {

        int ready = 0;
        while (ready == 0) {

            prepareMessage(request, i, len);
            sendMessage(request, sockfd, server_address);

            fd_set descriptors;
            FD_ZERO (&descriptors);
            FD_SET (sockfd, &descriptors);
            struct timeval tv;
            tv.tv_sec = 2;
            tv.tv_usec = 0;
            bool not_mine = true;
            while (not_mine) {
                ready = select(sockfd + 1, &descriptors, NULL, NULL, &tv);
                if (ready == -1) {
                    fprintf(stderr, "select error");
                    exit(EXIT_FAILURE);
                } else if (ready == 0) {
                    not_mine = false;
                }
                if (ready == 1) {
                    not_mine = receive(server_address, received, sockfd, file_name, i, len);
                }
            }
        }
    }

    close(sockfd);
    return EXIT_SUCCESS;
}

void clear_content_of_file(char *name) {
    FILE *f = fopen(name, "w");
    fclose(f);
}
