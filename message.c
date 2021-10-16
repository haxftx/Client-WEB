#include "helpers.h"

void create_message(char *message, char *auth, char *data, char *url,
															 char *command) {
// creeaza un mesaj de tip POST, GET, DELETE in formatul respectat de HTTP	
	char *line = calloc(BUFLEN, sizeof(char));
	if (!line) {
		fprintf(stderr, "error memory\n");
		return;
	}
	sprintf(line, "%s /api/v1/tema%s HTTP/1.1\r\n", command, url);
    strcat(message, line);
    sprintf(line, "Host: %s\r\n\r\n", HOSTNAME);
	if (auth) // autorizatia/cookie de sesiune
		strcat(message, auth);
	if (!strcmp(command, "POST")) {// daca e POST am continut
		sprintf(line, "Content-Type: application/json\r\n");
		strcat(message, line);
		sprintf(line, "Content-Length: %ld\r\n\r\n", strlen(data));
		strcat(message, line);
		strcat(message, data);
	}
	strcat(message, "\r\n\r\n\r\n");
	free(line);
}


void send_receive_message(char *message, struct sockaddr_in serv_addr,
														int flag, char *util) {
	
	int sockfd = socket(AF_INET, SOCK_STREAM, FLAGS);
	DIE(sockfd < 0, "sockfd");
	int ret = connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
	DIE(ret < 0, "connect");
	ret = send(sockfd, message, strlen(message), 0);
	DIE(ret < 0, "send");
	ret = recv(sockfd, message, BUFLEN, 0);
	DIE(ret < 0, "recv");
	close(sockfd);
	char *result = strstr(message, "{\"");;

	if (!strncmp(message, "HTTP/1.1 2", 10)) {// daca e succes
		if (flag == -1) {// logout
			printf("Succesfully logged out\n");
		} else if (flag == 0) {// register
			printf("Account succesfully created\n");
		} else if (flag == 1) {// get book
			print_book(result);
		} else if (flag == 2)// get books
			print_books(strstr(message, "["));
		else if (flag == 3) {// login
			char line[BUFLEN];
			memset(line, 0, BUFLEN);
			strcpy(line, strstr(message, "Set-Cookie: "));
			strcpy(line, strtok(line, "\r\n"));
			strcpy(util, line + 12); // salvez cookies
			printf("Succesfully logged in\n");
		} else if (flag == 4) {// enter library
			char line[BUFLEN];
			memset(line, 0 ,BUFLEN);
			strcpy(line, result);
			memset(message, 0 ,BUFLEN);
			strcpy(message, strstr(line, "\":\""));
			strcpy(line, message + 3);
			line[strlen(line) - 1] = '\0';
			strcpy(util, line);// salvez autorizatia
			printf("Now you have access to the library\n");
		} else if (flag == 5) {// add book
			printf("Book succesfully added\n");
		} else if (flag == 6) {// delete book
			printf("Book succesfully deleted\n");
		}
	} else {// eroare de la server
		//result = strstr(message, "{\"");
		if (result)
			print_error(result);
		else printf("Error : %s\n", strtok(message, "\r\n") + 9);
	}
}
