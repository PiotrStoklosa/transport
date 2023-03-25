//Piotr Stoklosa 314987

#ifndef TRANSPORT_RECEIVE_H
#define TRANSPORT_RECEIVE_H

#include <stdbool.h>
#include <netinet/ip.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int min1000(int size, int limit);

void writeToFile(char *file_name, char *message, int length);

int receive(struct sockaddr_in server_address, bool *received, int sockfd, char *file_name, int size, int len);

#endif
