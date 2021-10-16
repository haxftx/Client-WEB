CFLAGS = -Wall -Wextra -g

all: client

client: client.c function.c message.c helpers.c parson.c

.PHONY: clean run_client

run_client: client
	./client 

clean:
	rm -f client
