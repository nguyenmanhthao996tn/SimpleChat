#include "MyMessage.h"

MyMessage_t *__createMessage(uint32_t senderId, uint32_t receiverId, char *message)
{
    MyMessage_t *result = (MyMessage_t *)malloc(sizeof(MyMessage_t));

    // clear
    bzero(result, sizeof(MyMessage_t));

    result->senderId = senderId;
    // Get sender name

    result->receiverId = receiverId;
    // Get receiver name

    result->message = message;

    // Get current GMT time
    result->time = (time_t *)malloc(sizeof(time_t));
    time(result->time);

    return result;
}

MyMessage_t *__parseMessage(char *inputJSONString)
{
    int flag = 1; // true / parse successful
    cJSON *object, *sender, *receiver, *message;
    object = cJSON_Parse(inputJSONString);
    int senderId, receiverId;
    char *messageString;
    if (object != NULL)
    {
        sender = cJSON_GetObjectItemCaseSensitive(object, "sender");
        if (cJSON_IsNumber(sender))
        {
            senderId = sender->valueint;
        }
        else
        {
            flag = 0;
        }

        receiver = cJSON_GetObjectItemCaseSensitive(object, "receiver");
        if (cJSON_IsNumber(receiver))
        {
            receiverId = receiver->valueint;
        }
        else
        {
            flag = 0;
        }

        message = cJSON_GetObjectItemCaseSensitive(object, "message");
        if (cJSON_IsString(message) && (message->valuestring != NULL))
        {
            strcpy(messageString, message->valuestring);
        }
        else
        {
            flag = 0;
        }
    }
    else
    {
        flag = 0;
    }

    if (flag)
    {
        return MyMessageHandler.createMessage(senderId, receiverId, messageString);
    }
    else
    {
        return NULL;
    }
}

void __deleteMessage(MyMessage_t *myMessage)
{
    if (myMessage != NULL)
    {
        if (myMessage->senderName != NULL)
        {
            free(myMessage->senderName);
        }

        if (myMessage->receiverName != NULL)
        {
            free(myMessage->receiverName);
        }

        if (myMessage->message != NULL)
        {
            free(myMessage->message);
        }

        if (myMessage->time != NULL)
        {
            free(myMessage->time);
        }

        free(myMessage);
    }
}
