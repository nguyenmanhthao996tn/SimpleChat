/******************** LIBRARIES ********************/
#include "main.h"

/******************** MAIN ********************/
int main(int argc, char **argv)
{
    pthread_t listenThread;
    int rc;

    int sockfd, port = DEFAULT_PORT_NUMBER, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    char buffer[MAX_MESSAGE_BUFFER_SIZE];

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

    // Start listen thread
    rc = pthread_create(&listenThread, NULL, socketPollingThread, (void *)&sockfd);
    if (rc)
    {
        perror("ERROR on creating listen thread");
        exit(1);
    }
    //pthread_join(listenThread, NULL);

    /* Now ask for a message from the user, this message
     * will be read by server
     */

    printf("Please enter the message: ");
    bzero(buffer, MAX_MESSAGE_BUFFER_SIZE);
    fgets(buffer, MAX_MESSAGE_BUFFER_SIZE, stdin);

    /* Send message to the server */
    n = write(sockfd, buffer, strlen(buffer));

    if (n < 0)
    {
        perror("ERROR writing to socket");
        exit(1);
    }

    /* Now read server response */
    bzero(buffer, MAX_MESSAGE_BUFFER_SIZE);
    n = read(sockfd, buffer, MAX_MESSAGE_BUFFER_SIZE);

    if (n < 0)
    {
        perror("ERROR reading from socket");
        exit(1);
    }

    printf("%s\n", buffer);

    return EXIT_SUCCESS;
}

void *socketPollingThread(void *arg)
{
    char errorBuffer[255], messageBuffer[MAX_MESSAGE_BUFFER_SIZE];
    int listenSocketFd = *((int *)arg), messageLength;
    struct pollfd fd;

    fd.fd = listenSocketFd;
    fd.events = POLLIN;

    while (1)
    {
        int pollres = poll(&fd, 1, -1);
        if (pollres == -1)
        {
            if (errno == EINTR) // A signal occurred before any requested event
            {
                printf("ERROR: A signal occurred before any requested event\n");
                return 0;
            }
            else
            {
                snprintf(errorBuffer, 255, "ER: fail to poll: %s", strerror(errno));
                printf("%s\n", errorBuffer);
                return 0;
            }
        }

        if (fd.revents & POLLIN)
        {
            // Read income message
            messageLength = read(listenSocketFd, messageBuffer, MAX_MESSAGE_BUFFER_SIZE);
            printf("%s\n", messageBuffer);
        }
    }
}
