#include "helpers.h"

void fregister(struct sockaddr_in serv_addr) {
// creeaa si trimite catre server un POST pentru register
	char *message = calloc(BUFLEN, sizeof(char));
	if (!message) {
		fprintf(stderr, "error memory\n");
		return;
	}
	char username[51];
	char password[51];
	printf("username=");
	fgets(username, 50, stdin);
	username[strlen(username) - 1] = '\0';
	printf("password=");
	fgets(password, 50, stdin);
	password[strlen(password) - 1] = '\0';
	
	char data[150];
	// creez mesajul
	sprintf(data, "{\n\t\"username\": \"%s\",\n\t\"password\": \"%s\"\n}",
														username, password);
	create_message(message, NULL, data, "/auth/register", "POST");
	send_receive_message(message, serv_addr, 0, NULL);
	free(message);
}

void login(struct sockaddr_in serv_addr, char *cookies) {
// creeaza si trimite catre server un POST pentru login
	char *message = calloc(BUFLEN, sizeof(char));
	if (!message) {
		fprintf(stderr, "error memory\n");
		return;
	}
	char data[150];
	char username[51];
	char password[51];
	printf("username=");
	fgets(username, 50, stdin);
	username[strlen(username) - 1] = '\0';
	printf("password=");
	fgets(password, 50, stdin);
	password[strlen(password) - 1] = '\0';
	// creez mesajul
	sprintf(data, "{\n\t\"username\": \"%s\",\n\t\"password\": \"%s\"\n}",
														username, password);
	create_message(message, NULL, data, "/auth/login", "POST");	
	send_receive_message(message, serv_addr, 3, cookies);	
	free(message);
}

void add_book(struct sockaddr_in serv_addr, char *access) {
// creeaza un mesaj si-l trimite pentru adaugare unei carti	
	char *message = calloc(BUFLEN, sizeof(char));
	if (!message) {
		fprintf(stderr, "error memory\n");
		return;
	}
    char *auth = calloc(BUFLEN, sizeof(char));
	if (!auth) {
		fprintf(stderr, "error memory\n");
		free(message);
		return;
	}
	char *data = calloc(BUFLEN, sizeof(char));
	if (!data) {
		fprintf(stderr, "error memory\n");
		free(auth);
		free(message);
		return;
	}
	char title[BUFLEN], author[BUFLEN], genre[BUFLEN], publisher[BUFLEN];
	char page[10];
	// citesc datele de la tastatura
	setvbuf(stdin, NULL, _IONBF, 0);
	printf("title=");
	fgets(title, BUFLEN - 1, stdin);
	title[strlen(title) - 1] = '\0';
	printf("author=");
	fgets(author, BUFLEN - 1, stdin);
	author[strlen(author) - 1] = '\0';
	printf("genre=");
	fgets(genre, BUFLEN -1, stdin);
	genre[strlen(genre) - 1] = '\0';
	printf("publisher=");
	fgets(publisher, BUFLEN - 1, stdin);
	publisher[strlen(publisher) - 1] = '\0';
	printf("page_count=");
	fgets(page, 9, stdin);
		page[strlen(page) - 1] = '\0';
	if (!atoi(page)) {
		fprintf(stderr, "Not a number\n");
		free(auth);
		free(message);
		return;
	}// creez mesajul
	sprintf(auth, "Authorization: Bearer %s\r\n", access);
	sprintf(data, "{\n\t\"title\": \"%s\",\n\t\"author\": \"%s\",\n\t\"genre\
\": \"%s\",\n\t\"page_count\": %s,\n\t\"publisher\": \
\"%s\"\n}\r\n", title, author, genre, page, publisher);
	
	create_message(message, auth, data, "/library/books", "POST");
	send_receive_message(message, serv_addr, 5, NULL);
	free(auth);
	free(data);
	free(message);
}

void enter_library(struct sockaddr_in serv_addr, char *cookies, char *access) {
// creeaza un mesaj si-l trimite catre server pentu acces in librarie	
	char *message = calloc(BUFLEN, sizeof(char));
	if (!message) {
		fprintf(stderr, "error memory\n");
		return;
	}
    char *aux = calloc(BUFLEN, sizeof(char));
	if (!aux) {
		fprintf(stderr, "error memory\n");
		free(message);
		return;
	}// creez mesajul
    sprintf(aux, "Cookie: %s\r\n", cookies);
	create_message(message, aux, NULL, "/library/access", "GET");
	send_receive_message(message, serv_addr, 4, access);
	free(aux);
	free(message);
}

void get_books(struct sockaddr_in serv_addr, char *access) {
// creeaza si trimite un messaj catre server GET pentru cartile din cont
	char *message = calloc(BUFLEN, sizeof(char));
	if (!message) {
		fprintf(stderr, "error memory\n");
		return;
	}
    char *auth = calloc(BUFLEN, sizeof(char));
	if (!auth) {
		fprintf(stderr, "error memory\n");
		free(message);
		return;
	}// creez mesajul
    sprintf(auth, "Authorization: Bearer %s\r\n", access);
	create_message(message, auth, NULL, "/library/books", "GET");
	send_receive_message(message, serv_addr, 2, NULL);
	free(auth);
	free(message);
}

void get_book(struct sockaddr_in serv_addr, char *access) {
// creeaza si trimite un messaj catre server GET pentru o carte din cont	
	char *message = calloc(BUFLEN, sizeof(char));
	if (!message) {
		fprintf(stderr, "error memory\n");
		return;
	}
    char *auth = calloc(BUFLEN, sizeof(char));
	if (!auth) {
		fprintf(stderr, "error memory\n");
		free(message);
		return;
	}
	int id;
	char url[30];
	printf("id=");
	fgets(url, 20, stdin);
	id = atoi(url);
	if (!id) {
		free(auth);
		free(message);
		fprintf(stderr, "Not a Number\n");
		return;
	}// creez mesajul
	sprintf(url, "/library/books/%d", id);
    sprintf(auth, "Authorization: Bearer %s\r\n", access);
	create_message(message, auth, NULL, url, "GET");
	send_receive_message(message, serv_addr, 1, NULL);
	free(auth);
	free(message);
}

void delete_book(struct sockaddr_in serv_addr, char *access) {
// creeaza si trimite un messaj catre server DELETE pentru o carte din cont
	char *message = calloc(BUFLEN, sizeof(char));
	if (!message) {
		fprintf(stderr, "error memory\n");
		return;
	}
    char *auth = calloc(BUFLEN, sizeof(char));
	if (!auth) {
		fprintf(stderr, "error memory\n");
		free(message);
		return;
	}
	int id;
	char url[30];
	printf("id=");
	fgets(url, 20, stdin);
	id = atoi(url);
	if (!id) {
		fprintf(stderr, "Not a Number\n");
		free(auth);
		free(message);
		return;
	}// creez mesajul
	sprintf(url, "/library/books/%d", id);
    sprintf(auth, "Authorization: Bearer %s\r\n", access);
	create_message(message, auth, NULL, url, "DELETE");
    free(auth);
	send_receive_message(message, serv_addr, 6, NULL);	
	free(message);
}

void logout(struct sockaddr_in serv_addr, char *cookies) {
// creeaza si trimite un messaj catre server GET pentru delogare
	char *message = calloc(BUFLEN, sizeof(char));
	if (!message) {
		fprintf(stderr, "error memory\n");
		return;
	}
    char *aux = calloc(BUFLEN, sizeof(char));
	if (!aux) {
		fprintf(stderr, "error memory\n");
		free(message);
		return;
	}// creez mesajul
    sprintf(aux, "Cookie: %s\r\n", cookies);
	create_message(message, aux, NULL, "/auth/logout", "GET");
	send_receive_message(message, serv_addr, -1, NULL);
	free(aux);
	free(message);
}