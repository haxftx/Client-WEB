#include "helpers.h"

uint32_t get_ip(char *hostname) {
	// afla ip dupa hostname
	struct addrinfo hints, *res;
	hints.ai_flags = FLAGS;
	hints.ai_family = AF_INET;
	hints.ai_socktype = 0;
	hints.ai_protocol = PORTNO;
	int ret = getaddrinfo(hostname, NULL, &hints, &res);
	if (ret < 0) {
		perror(gai_strerror(ret));
		return 0;
	}
	uint32_t ip = ((struct sockaddr_in *)(res->ai_addr))->sin_addr.s_addr;
	freeaddrinfo(res);
	return ip;
}

int main(void) {

	setvbuf(stdout, NULL, _IONBF, 0);
	char cookies[BUFLEN];
	memset(cookies, 0, BUFLEN);
	char access[BUFLEN];
	memset(access, 0, BUFLEN);
	uint32_t ip = get_ip(HOSTNAME);
	if (!ip)
		return -1;
	//adresa serverului
	struct sockaddr_in serv_addr;
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORTNO);
    serv_addr.sin_addr.s_addr = ip;

	char command[21];
	while (1) {// citesc comanda si o efectuez daca e posibil
		fgets(command, 20, stdin);
		command[strlen(command) - 1] = '\0';
		if (!strcmp(command, "exit")) {
			break;
		} else if (!strcmp(command, "register")) {
			if (strlen(cookies)) {
				printf("You are logged in\n");
				continue;
			}
			fregister(serv_addr);
		} else if (!strcmp(command, "login")) {
			if (strlen(cookies)) {
				printf("You are logged in\n");
				continue;
			} 
			login(serv_addr, cookies);
		} else if (!strcmp(command, "enter_library")) {
			if (!strlen(cookies)) {
				printf("You are not logged in\n");
				continue;
			}
			enter_library(serv_addr, cookies, access);
		} else if (!strcmp(command, "get_books")) {
			if (!strlen(cookies)) {
				printf("You are not logged in\n");
				continue;
			} else if (!strlen(access)) {
				printf("You have to get access first\n");
				continue;
			}
			get_books(serv_addr, access);
		} else if (!strcmp(command, "get_book")) {
			if (!strlen(cookies)) {
				printf("You are not logged in\n");
				continue;
			} else if (!strlen(access)) {
				printf("You have to get access first\n");
				continue;
			}
			get_book(serv_addr, access);
		} else if (!strcmp(command, "add_book")) {
			if (!strlen(cookies)) {
				printf("You are not logged in\n");
				continue;
			} else if (!strlen(access)) {
				printf("You have to get access first\n");
				continue;
			}
			add_book(serv_addr, access);
		} else if (!strcmp(command, "delete_book")) {
			if (!strlen(cookies)) {
				printf("You are not logged in\n");
				continue;
			} else  if (!strlen(access)) {
				printf("You have to get access first\n");
				continue;
			}
			delete_book(serv_addr, access);
		} else if (!strcmp(command, "logout")) {
			if (!strlen(cookies)) {
				printf("You are not logged in\n");
				continue;
			}
			logout(serv_addr, cookies);
			memset(cookies, 0 , BUFLEN);
			memset(access, 0 , BUFLEN);
		} else {
			printf("Wrong command\n");
			continue;
		}
	}
	return 0;
}