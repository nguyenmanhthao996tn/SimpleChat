main: main.c cJSON.o MyMessage.o
	cc -o main main.c cJSON.o MyMessage.o -lpthread -Wall

cJSON.o: cJSON.c
	cc -c cJSON.c

MyMessage.o: MyMessage.c
	cc -c MyMessage.c -D _XOPEN_SOURCE

User.o: User.h User.c
	cc -c User.c

UserList.o: UserList.h UserList.c
	cc -c UserList.c

clean:
	rm main *.o
	