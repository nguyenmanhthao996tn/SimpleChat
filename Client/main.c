/******************** LIBRARIES ********************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>
#include "config.h"

/******************** MAIN ********************/
int main(int argc, char **argv)
{
    int sockfd, port = DEFAULT_PORT_NUMBER, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    char buffer[MAX_BUFFER_SIZE];

    if (argc < 3)
    {
        fprintf(stderr, "usage %s hostname port\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    port = atoi(argv[2]);

    /* Create a socket point */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0)
    {
        perror("ERROR opening socket");
        exit(EXIT_FAILURE);
    }

    server = gethostbyname(argv[1]);

    if (server == NULL)
    {
        fprintf(stderr, "ERROR, no such host\n");
        exit(EXIT_FAILURE);
    }

    bzero((char *)&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(port);

    /* Now connect to the server */
    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        perror("ERROR connecting");
        exit(EXIT_FAILURE);
    }

    /* Now ask for a message from the user, this message
     * will be read by server
     */

    printf("Please enter the message: ");
    bzero(buffer, MAX_BUFFER_SIZE);
    fgets(buffer, MAX_BUFFER_SIZE, stdin);

    /* Send message to the server */
    n = write(sockfd, buffer, strlen(buffer));

    if (n < 0)
    {
        perror("ERROR writing to socket");
        exit(1);
    }

    /* Now read server response */
    // bzero(buffer, MAX_BUFFER_SIZE);
    // n = read(sockfd, buffer, MAX_BUFFER_SIZE);

    // if (n < 0)
    // {
    //     perror("ERROR reading from socket");
    //     exit(1);
    // }

    // printf("%s\n", buffer);

    return EXIT_SUCCESS;
}
