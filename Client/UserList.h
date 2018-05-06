/*
CreateList
Add
Remove
FindId
FindName
FindOnlineState
Count
ParseFromJsonString
ToJsonString
DeleteList
*/

#ifndef __USER_LIST__
#define __USER_LIST__

/******************** LIBRARIES ********************/
#include "User.c"

/******************** DEFINE ********************/

/******************** DATA TYPE DEFINE ********************/
typedef struct UserNode_tag
{
    User_t user;
    struct UserNode_tag *pNext;
} UserNode_t;

typedef struct
{
    UserNode_t *pHead, *pTail;
    int count;
} UserList_t;

typedef struct
{
    UserList_t *(*createList)(void);
    int (*add)(UserList_t *list, User_t user);
    int (*remove)(UserList_t *list, int id);
    int (*findId)(UserList_t *list, int id, User_t *result);
    int (*findName)(UserList_t *list, char *name, User_t **result, int resultSize);
    int (*findOnlineState)(UserList_t *list, OnlineState_t onlineState, User_t **result, int resultSize);
    int (*count)(UserList_t *list);
    int (*parseFromJsonString)(UserList_t *list, char *json);
    char *(*toJsonString)(UserList_t *list);
    int (*deleteList)(UserList_t *list);
} UserListHandler_t;

/******************** METHODS ********************/
UserList_t *__createList(void);
int __add(UserList_t *list, User_t user);
int __remove(UserList_t *list, int id);
int __findId(UserList_t *list, int id, User_t *result);
int __findName(UserList_t *list, char *name, User_t **result, int resultSize);
int __findOnlineState(UserList_t *list, OnlineState_t onlineState, User_t **result, int resultSize);
int __count(UserList_t *list);
int __parseFromJsonString(UserList_t *list, char *json);
char *__toJsonString(UserList_t *list);
int __deleteList(UserList_t *list);

const static UserListHandler_t UserListHandler = {
    __createList,
    __add,
    __remove,
    __findId,
    __findName,
    __findOnlineState,
    __count,
    __parseFromJsonString,
    __toJsonString,
    __deleteList};

#endif /* __USER_LIST__ */
