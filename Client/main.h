/******************** LIBRARIES ********************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>
#include <poll.h>
#include <pthread.h>
#include "MyMessage.h"
#include "config.h"

/******************** METHODS ********************/
void *socketPollingThread(void *arg);
