/******************** LIBRARIES ********************/
#include "main.h"

/******************** MAIN ********************/
int main(int argc, char **argv)
{
    /* Setup polling struct */
    setupPollingStruct();

    while (pollPollingStruct())
        ;
}

/******************** METHODS DEFINE ********************/
void setupPollingStruct(void)
{
    int listen_sockfd, noti_socket;
    struct sockaddr_in serv_addr;
    int port = DEFAULT_PORT_NUMBER;

    /* Initialize polling structure */
    bzero((char *)&fds, sizeof(fds));

    /* Setup app notification socket */
    noti_socket = eventfd(0, 0);
    if (noti_socket == -1)
    {
        perror("ERROR: Failed to create cancel socket in server");
    }

    fds[FD_NOTI].fd = noti_socket;
    fds[FD_NOTI].events = POLLIN;

    /* Open listen socket */
    listen_sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (listen_sockfd < 0)
    {
        perror("ERROR opening socket");
        exit(EXIT_FAILURE);
    }

    /* Initialize socket structure */
    bzero((char *)&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(port);

    /* Bind the host address using bind() call.*/
    if (bind(listen_sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        perror("ERROR on binding");
        exit(EXIT_FAILURE);
    }

    if (listen(listen_sockfd, LISTEN_SOCKET_BACKLOG) < 0)
    {
        perror("ERROR on listenning");
        exit(EXIT_FAILURE);
    }

    fds[FD_LISTEN].fd = listen_sockfd;
    fds[FD_LISTEN].events = POLLIN;
}

int pollPollingStruct(void)
{
    char errorBuffer[255];
    int poll_res = poll(fds, FDS_SIZE, -1);
    if (poll_res == -1)
    {
        if (errno == EINTR) // A signal occurred before any requested event
        {
            return 1;
        }
        else
        {
            snprintf(errorBuffer, 255, "ER: fail to poll: %s", strerror(errno));
            perror(errorBuffer);
            exit(EXIT_FAILURE);
        }
    }

    if (fds[FD_NOTI].revents & POLLIN)
    {
        /* For now just exit on its event */
        perror("[Note] STOPPING SERVER...");
        return 0;
    }

    if (fds[FD_LISTEN].revents & POLLIN)
    {
        --poll_res;
        int conn_socket = accept(fds[FD_LISTEN].fd, NULL, NULL);
        if (conn_socket < 0)
        {
            snprintf(errorBuffer, 255, "ER: fail to accept: %s", strerror(errno));
            perror(errorBuffer);
            exit(EXIT_FAILURE);
        }
        addConnectionSocket(conn_socket);
    }

    int i = FD_CONN_MIN;
    for (; poll_res && i < FDS_SIZE; ++i)
    {
        if (fds[i].fd && (fds[i].revents & POLLIN))
        {
            --poll_res;

            messengerHandler(i);
        }
    }

    return 1;
}

void addConnectionSocket(int newSocketFd)
{
    int i = FD_CONN_MIN;
    for (; i < FDS_SIZE; ++i)
    {
        if (fds[i].fd == 0)
        {
            fds[i].fd = newSocketFd;
            fds[i].events = POLLIN;

            break;
        }
    }

    if (i == FDS_SIZE)
    {
        perror("ER: array is full, can't add new fd");
    }
}

void removeConnectionSocket(int newSocketIndex)
{
    fds[newSocketIndex].fd = 0;
    fds[newSocketIndex].events = 0;
}

void broadcastMessageToAllConnectionSocket(char * message)
{
    int i = FD_CONN_MIN;
    for (; i < FDS_SIZE; i++)
    {
        if (fds[i].fd != 0)
        {
            write(fds[i].fd, message, sizeof(message));
        }
    }
}

void messengerHandler(int incomeMessageSocketIndex)
{
    char messageBuffer[MAX_MESSAGE_BUFFER_SIZE];

    /* Erase message buffer */
    bzero(&messageBuffer, MAX_MESSAGE_BUFFER_SIZE);

    /* Read message from fd */
    int receivedBytes = recv(fds[incomeMessageSocketIndex].fd, messageBuffer, MAX_MESSAGE_BUFFER_SIZE, 0);
    switch (receivedBytes)
    {
    case -1: /* Error */
        perror("ER: fail to recv()");
        removeConnectionSocket(incomeMessageSocketIndex);
        break;
    case 0: /* Shutdown order */
        removeConnectionSocket(incomeMessageSocketIndex);
        break;
    default:
        printf("RECV: %s", messageBuffer);
        broadcastMessageToAllConnectionSocket(messageBuffer);
        break;
    }
}
