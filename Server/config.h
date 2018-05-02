#ifndef __CONFIG__
#define __CONFIG__

/******************** DEFINE ********************/
#define DEFAULT_PORT_NUMBER 5000
#define MAX_MESSAGE_BUFFER_SIZE 255
#define FDS_SIZE 128
#define LISTEN_SOCKET_BACKLOG 8 /* The backlog argument defines the maximum length to which the queue of pending connections for sockfd may grow */
#define TIME_STRING_FORMAT "%Y-%m-%d %H:%M:%S"

#endif /* __CONFIG__ */
