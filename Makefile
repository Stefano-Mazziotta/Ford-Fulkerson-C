CC = gcc
CFLAGS = -Wall -Wextra

OUTPUT_DIR = _output

main: ./code/main.c
	$(CC) $(CFLAGS) -o $(OUTPUT_DIR)/fordfulkerson-algorithm $^

.PHONY: clean

clean:
	rm -f $(OUTPUT_DIR)/fordfulkerson-algorithm