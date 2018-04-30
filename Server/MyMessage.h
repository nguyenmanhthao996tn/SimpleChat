#ifndef __MY_MESSAGE_H__
#define __MY_MESSAGE_H__

/******************** LIBRARIES ********************/
#include <stdint.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "cJSON.h"

/******************** DATA TYPE DEFINE ********************/
typedef struct
{
    uint32_t senderId;
    char *senderName;

    uint32_t receiverId;
    char *receiverName;

    char *message;
    time_t *time;
} MyMessage_t;

typedef struct
{
    MyMessage_t *(*createMessage)(uint32_t senderId, uint32_t receiverId, char *message); // create
    MyMessage_t *(*parseMessage)(char *inputJSONString);                                  // parse
    void (*deleteMessage)(MyMessage_t *myMessage);                                        // delete
} MyMessageHandler_t;

/******************** METHODS ********************/
MyMessage_t *__createMessage(uint32_t senderId, uint32_t receiverId, char *message);
MyMessage_t *__parseMessage(char *inputJSONString);   
void __deleteMessage(MyMessage_t *myMessage);

const MyMessageHandler_t MyMessageHandler = {
    __createMessage,
    __parseMessage,
    __deleteMessage};

#endif /* __MY_MESSAGE_H__ */
