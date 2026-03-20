CC=gcc
CFLAGS=-pthread -lrt

all:
	$(CC) sensor_final.c -o sensor_final $(CFLAGS)
	$(CC) process_final.c -o process_final $(CFLAGS)
	$(CC) display_final.c -o display_final $(CFLAGS)
	$(CC) logger_final.c -o logger_final
	$(CC) main_final.c -o main_final

run:
	./main_final

clean:
	rm -f sensor_final process_final display_final logger_final main_final environment_log.txt
