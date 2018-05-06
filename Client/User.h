#ifndef __USER__
#define __USER__

/******************** LIBRARIES ********************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/******************** DEFINE ********************/

/******************** DATA TYPE DEFINE ********************/
typedef enum {
    OFFLINE = 0,
    ONLINE
} OnlineState_t;

typedef struct
{
    int id;
    char *username;
    OnlineState_t onlineState;
} User_t;

typedef struct
{
    User_t *(*createUser)(void);
    void (*setId)(User_t *user, int id);
    void (*setUsername)(User_t *user, char *name);
    void (*setOnlineState)(User_t *user, OnlineState_t onlineState);
    int (*deleteUser)(User_t *user);
} UserHandler_t;

/******************** METHODS ********************/
User_t *__createUser(void);
void __setId(User_t *user, int id);
void __setUsername(User_t *user, char *name);
void __setOnlineState(User_t *user, OnlineState_t onlineState);
int __deleteUser(User_t *user);

const static UserHandler_t UserHandler = {
    __createUser,
    __setId,
    __setUsername,
    __setOnlineState,
    __deleteUser};

#endif /* __USER__ */
