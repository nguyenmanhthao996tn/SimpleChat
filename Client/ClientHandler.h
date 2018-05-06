// Init
// SendMessage
// SetInitErrorCallback
// SetMessageReceiveCallback
// GetUserList
// Stop

#ifndef __CLIENT_HANDLER__
#define __CLIENT_HANDLER__

/******************** LIBRARIES ********************/
#include "MyMessage.h"

/******************** DEFINE ********************/

/******************** DATA TYPE DEFINE ********************/
struct
{
    int id;
    char name;
} OnlineUser_t;

typedef struct
{
    char *serverAddress;
    int serverPort;
    int listenSocketFd;
    OnlineUser_t * onlineUserList;
} Client_t;

typedef struct
{

} ClientHandler_t;

/******************** METHODS ********************/

#endif /* __CLIENT_HANDLER__ */
