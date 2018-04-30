main: main.c main.h config.h
	cc -o main main.c main.h config.h -Wall

cJSON.o: cJSON.c
	cc -c cJSON.c

clean:
	rm main *.o
