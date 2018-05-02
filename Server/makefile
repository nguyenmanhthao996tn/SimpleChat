main: main.c main.h config.h
	cc -o main main.c main.h config.h -Wall

cJSON.o: cJSON.c
	cc -c cJSON.c

MyMessage.o: MyMessage.c
	cc -c MyMessage.c -D _XOPEN_SOURCE

test: test.c MyMessage.h MyMessage.o cJSON.h cJSON.o config.h
	cc -o test test.c MyMessage.h MyMessage.o cJSON.h cJSON.o config.h -D _XOPEN_SOURCE -Wall

clean:
	rm main *.o
