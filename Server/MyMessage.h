#ifndef __MY_MESSAGE_H__
#define __MY_MESSAGE_H__

/******************** LIBRARIES ********************/
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "cJSON.h"
#include "config.h"

/******************** DEFINE ********************/
#define SENDER_ID_KEY "SENDER_ID"
#define SENDER_NAME_KEY "SENDER_NAME"
#define RECEIVER_ID_KEY "RECEIVER_ID"
#define RECEIVER_NAME_KEY "RECEIVER_NAME"
#define MESSAGE_CONTENT_KEY "MESSAGE"
#define SEND_TIME_KEY "TIME"

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
    MyMessage_t *(*createMessage)(uint32_t senderId, char *senderName, uint32_t receiverId, char *receiverName, char *message, char *timeString); // create
    MyMessage_t *(*parseMessageFromJSON)(char *inputJSONString);                                                                                  // parse
    void (*deleteMessage)(MyMessage_t *myMessage);                                                                                                // delete
    char *(*toString)(MyMessage_t *myMessage);                                                                                                    // to string
    char *(*toJSONString)(MyMessage_t *myMessage);                                                                                                // to JSON string
} MyMessageHandler_t;

/******************** METHODS ********************/
MyMessage_t *__createMessage(uint32_t senderId, char *senderName, uint32_t receiverId, char *receiverName, char *message, char *timeString);
MyMessage_t *__parseMessage(char *inputJSONString);
void __deleteMessage(MyMessage_t *myMessage);
char *__myMessageToString(MyMessage_t *myMessage);
char *__myMessageToJSONString(MyMessage_t *myMessage);

time_t dateParse(const char *input);
char *dateToString(time_t *input);

#endif /* __MY_MESSAGE_H__ */
