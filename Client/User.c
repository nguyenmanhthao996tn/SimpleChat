#include "User.h"

/******************** METHODS ********************/
User_t *__createUser(void)
{
    User_t *user;
    user = (User_t *)malloc(sizeof(User_t));

    user->id = 0;
    user->username = NULL;
    user->onlineState = OFFLINE;

    return user;
}

void __setId(User_t *user, int id)
{
    if (user)
    {
        user->id = id;
    }
}

void __setUsername(User_t *user, char *name)
{
    if (user)
    {
        user->username = (char *)malloc(sizeof(char) * strlen(name));
        strcpy(user->username, name);
    }
}

void __setOnlineState(User_t *user, OnlineState_t onlineState)
{
    if (user)
    {
        user->onlineState = onlineState;
    }
}

int __deleteUser(User_t *user)
{

    if (user)
    {
        if (user->username)
        {
            free(user->username);
        }
        free(user);
    }
}
