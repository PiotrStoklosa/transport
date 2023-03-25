//Piotr Stoklosa 314987

#ifndef TRANSPORT_SEND_H
#define TRANSPORT_SEND_H

#include <netinet/ip.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

void sendMessage(char *message, int sockfd, struct sockaddr_in server_address);

#endif
