CC = gcc
CFLAGS= -Wall -pthread

SRC = main.c 
OUT = hilos

all: $(OUT)

$(OUT): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(OUT)

clean:
	rm -f $(OUT)