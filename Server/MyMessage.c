#include "MyMessage.h"

const MyMessageHandler_t MyMessageHandler = {
    __createMessage,
    __parseMessage,
    __deleteMessage,
    __myMessageToString,
    __myMessageToJSONString};

MyMessage_t *__createMessage(uint32_t senderId, char *senderName, uint32_t receiverId, char *receiverName, char *message, char *timeString)
{
    MyMessage_t *result = (MyMessage_t *)malloc(sizeof(MyMessage_t));

    // clear
    memset(result, '\0', sizeof(MyMessage_t));

    result->senderId = senderId;

    result->senderName = (char *)malloc(sizeof(char) * sizeof(senderName));
    strcpy(result->senderName, senderName);

    result->receiverId = receiverId;

    result->receiverName = (char *)malloc(sizeof(char) * sizeof(receiverName));
    strcpy(result->receiverName, receiverName);

    result->message = (char *)malloc(sizeof(char) * sizeof(message));
    strcpy(result->message, message);

    // Get current GMT time
    result->time = (time_t *)malloc(sizeof(time_t));
    if (timeString == NULL)
    {
        time(result->time);
    }
    else
    {
        *(result->time) = dateParse(timeString);
    }
    return result;
}

MyMessage_t *__parseMessage(char *inputJSONString)
{
    int flag = 1; // true / parse successful
    cJSON *object, *senderIdObject, *senderNameObject, *receiverIdObject, *receiverNameObject, *message, *timeObject;
    object = cJSON_Parse(inputJSONString);
    int senderId, receiverId;
    char *messageString, *senderName, *receiverName, *timeString;
    if (object != NULL)
    {
        senderIdObject = cJSON_GetObjectItemCaseSensitive(object, SENDER_ID_KEY);
        if (cJSON_IsString(senderIdObject) && (senderIdObject->valuestring != NULL))
        {
            senderId = atoi(senderIdObject->valuestring);
        }
        else
        {
            flag = 0;
        }

        senderNameObject = cJSON_GetObjectItemCaseSensitive(object, SENDER_NAME_KEY);
        if (cJSON_IsString(senderNameObject) && (senderNameObject->valuestring != NULL))
        {
            senderName = (char *)malloc(sizeof(char) * sizeof(senderNameObject->valuestring));
            strcpy(senderName, senderNameObject->valuestring);
        }
        else
        {
            flag = 0;
        }

        receiverIdObject = cJSON_GetObjectItemCaseSensitive(object, RECEIVER_ID_KEY);
        if (cJSON_IsString(receiverIdObject) && (receiverIdObject->valuestring != NULL))
        {
            receiverId = atoi(receiverIdObject->valuestring);
        }
        else
        {
            flag = 0;
        }

        receiverNameObject = cJSON_GetObjectItemCaseSensitive(object, RECEIVER_NAME_KEY);
        if (cJSON_IsString(receiverNameObject) && (receiverNameObject->valuestring != NULL))
        {
            receiverName = (char *)malloc(sizeof(char) * sizeof(receiverNameObject->valuestring));
            strcpy(receiverName, receiverNameObject->valuestring);
        }
        else
        {
            flag = 0;
        }

        message = cJSON_GetObjectItemCaseSensitive(object, MESSAGE_CONTENT_KEY);
        if (cJSON_IsString(message) && (message->valuestring != NULL))
        {
            messageString = (char *)malloc(sizeof(char) * sizeof(message->valuestring));
            strcpy(messageString, message->valuestring);
        }
        else
        {
            flag = 0;
        }

        timeObject = cJSON_GetObjectItemCaseSensitive(object, SEND_TIME_KEY);
        if (cJSON_IsString(timeObject) && (timeObject->valuestring != NULL))
        {
            timeString = (char *)malloc(sizeof(char) * sizeof(timeObject->valuestring));
            strcpy(timeString, timeObject->valuestring);
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
        return MyMessageHandler.createMessage(senderId, senderName, receiverId, receiverName, messageString, timeString);
    }
    return NULL;
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

char *__myMessageToString(MyMessage_t *myMessage)
{
    char *buffer = (char *)malloc(sizeof(char) * 255);
    char *result = (char *)malloc(sizeof(char) * 1024);

    // Clean result
    memset(buffer, '\0', sizeof(buffer));
    memset(result, '\0', sizeof(result));

    strcat(result, "********** MESSAGE **********\n");

    snprintf(buffer, 255, "Sender: %s\n", myMessage->senderName);
    strcat(result, buffer);

    snprintf(buffer, 255, "Receiver: %s\n", myMessage->receiverName);
    strcat(result, buffer);

    snprintf(buffer, 255, "Send time: %s\n", ctime(myMessage->time));
    strcat(result, buffer);

    snprintf(buffer, 255, "Content:\n\t%s\n", myMessage->message);
    strcat(result, buffer);

    strcat(result, "*****************************\n");

    return result;
}

char *__myMessageToJSONString(MyMessage_t *myMessage)
{
    int flag = 1;
    char *buffer = (char *)malloc(sizeof(char) * MAX_MESSAGE_BUFFER_SIZE);

    cJSON *messageJsonObject = cJSON_CreateObject();
    if (messageJsonObject == NULL)
    {
        perror("Can't create message object\n");
        flag = 0;
    }

    // sender id
    snprintf(buffer, 15, "%d", myMessage->senderId);
    cJSON *senderIdJsonObject = cJSON_CreateString(buffer);
    if (senderIdJsonObject == NULL)
    {
        perror("Can't create sender id object\n");
        flag = 0;
    }
    cJSON_AddItemToObject(messageJsonObject, SENDER_ID_KEY, senderIdJsonObject);

    // sender name
    cJSON *senderNameJsonObject = cJSON_CreateString(myMessage->senderName);
    if (senderNameJsonObject == NULL)
    {
        perror("Can't create sender name object\n");
        flag = 0;
    }
    cJSON_AddItemToObject(messageJsonObject, SENDER_NAME_KEY, senderNameJsonObject);

    // receiver id
    snprintf(buffer, 15, "%d", myMessage->receiverId);
    cJSON *receiverIdJsonObject = cJSON_CreateString(buffer);
    if (receiverIdJsonObject == NULL)
    {
        perror("Can't create receiver id object\n");
        flag = 0;
    }
    cJSON_AddItemToObject(messageJsonObject, RECEIVER_ID_KEY, receiverIdJsonObject);

    // receiver name
    cJSON *receiverNameJsonObject = cJSON_CreateString(myMessage->receiverName);
    if (receiverNameJsonObject == NULL)
    {
        perror("Can't create receiver name object\n");
        flag = 0;
    }
    cJSON_AddItemToObject(messageJsonObject, RECEIVER_NAME_KEY, receiverNameJsonObject);

    // message
    cJSON *messageContentJsonObject = cJSON_CreateString(myMessage->message);
    if (messageContentJsonObject == NULL)
    {
        perror("Can't create message content object\n");
        flag = 0;
    }
    cJSON_AddItemToObject(messageJsonObject, MESSAGE_CONTENT_KEY, messageContentJsonObject);

    // time
    cJSON *timeSendJsonObject = cJSON_CreateString(dateToString(myMessage->time));
    if (timeSendJsonObject == NULL)
    {
        perror("Can't create timeSend object\n");
        flag = 0;
    }
    cJSON_AddItemToObject(messageJsonObject, SEND_TIME_KEY, timeSendJsonObject);

    if (flag)
    {
        strcpy(buffer, cJSON_PrintUnformatted(messageJsonObject));
    }
    else
    {
        buffer = NULL;
    }

    // Delete objects
    cJSON_Delete(messageJsonObject);

    return buffer;
}

time_t dateParse(const char *input)
{
    struct tm tm;

    /* First clear the result structure.  */
    memset(&tm, '\0', sizeof(tm));
    strptime(input, TIME_STRING_FORMAT, &tm);
    return mktime(&tm);
}

char *dateToString(time_t *input)
{
    char *buff = (char *)malloc(sizeof(char) * 20);
    strftime(buff, 20, TIME_STRING_FORMAT, localtime(input));
    return buff;
}
