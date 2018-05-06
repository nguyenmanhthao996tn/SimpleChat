#include "UserList.h"

/******************** METHODS ********************/
UserList_t *__createList(void)
{
    UserList_t *list;

    list = (UserList_t *)malloc(sizeof(UserList_t));
    list->count = 0;
    list->pHead = NULL;
    list->pTail = NULL;

    return list;
}
int __add(UserList_t *list, User_t user)
{
    if (list)
    {
        UserNode_t * node = (UserNode_t *)malloc(sizeof(UserNode_t));

        if ((list->pHead == list->pTail) && (list->pHead == NULL) && (list->pTail == NULL))
        {
            list->pTail->pNext = node;
            list->pTail = node;
        }
        else
        {
            list->pHead = node;
            list->pTail = node;
        }
        list->count++;

        return 0;
    }
    else 
    {
        return -1;
    }
}

int __remove(UserList_t *list, int id) {}
int __findId(UserList_t *list, int id, User_t *result) {}
int __findName(UserList_t *list, char *name, User_t **result, int resultSize) {}
int __findOnlineState(UserList_t *list, OnlineState_t onlineState, User_t **result, int resultSize) {}
int __count(UserList_t *list)
{
    if (list)
    {
        return (list->count);
    }
    else
    {
        return -1;
    }
}
int __parseFromJsonString(UserList_t *list, char *json) {}
char *__toJsonString(UserList_t *list) {}
int __deleteList(UserList_t *list)
{
    UserNode_t *pTemp;

    if (list)
    {
        while ((list->pHead != list->pTail) && (list->pHead != NULL) && (list->pTail != NULL))
        {
            pTemp = list->pHead;
            list->pHead = list->pHead->pNext;
            free(pTemp);
        }

        free(list);
        return 0;
    }
    else
    {
        return -1;
    }
}
