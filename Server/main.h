#ifndef __MAIN_H__
#define __MAIN_H__

/******************** LIBRARIES ********************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/poll.h>
#include <sys/eventfd.h>
#include <errno.h>
#include <string.h>
#include "config.h"

/******************** DATA TYPE DEFINE ********************/
typedef enum {
    FD_NOTI = 0,
    FD_LISTEN,
    FD_CONN_MIN
} fd_pos;

/******************** GLOBAL VARIABLES ********************/
struct pollfd fds[FDS_SIZE];

/******************** METHODS ********************/
void setupPollingStruct(void);
int pollPollingStruct(void);
void addConnectionSocket(int newSocketFd);
void removeConnectionSocket(int newSocketIndex);
void messengerHandler(int incomeMessageSocketIndex);

#endif /* __MAIN_H__ */
