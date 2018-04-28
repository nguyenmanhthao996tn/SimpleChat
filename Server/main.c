#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <netdb.h>
#include <netinet/in.h>

#include <strings.h>

int main(int argc, char **argv)
{
    char buffer[255];
    struct sockaddr_in serv_addr, cli_addr;
    unsigned int clilen;
    int sockfd = socket(AF_INET, SOCK_STREAM, 0), portno, newsockfd, n;
    if (sockfd < 0)
    {
        perror("ERROR opening socket");
        exit(EXIT_FAILURE);
    }

    /* Initialize socket structure */
    bzero((char *)&serv_addr, sizeof(serv_addr));
    portno = 5001;

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);

    /* Now bind the host address using bind() call.*/
    if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        perror("ERROR on binding");
        exit(EXIT_FAILURE);
    }

    /* Now start listening for the clients, here process will
     * go in sleep mode and will wait for the incoming connection
     */

    listen(sockfd, 5);
    clilen = sizeof(cli_addr);

    /* Accept actual connection from the client */
    newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);

    if (newsockfd < 0)
    {
        perror("ERROR on accept");
        exit(EXIT_FAILURE);
    }

    /* If connection is established then start communicating */
    bzero(buffer, 256);
    n = read(newsockfd, buffer, 255);

    if (n < 0)
    {
        perror("ERROR reading from socket");
        exit(EXIT_FAILURE);
    }

    printf("Here is the message: %s\n", buffer);

    /* Write a response to the client */
    n = write(newsockfd, "I got your message", 18);

    if (n < 0)
    {
        perror("ERROR writing to socket");
        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}
