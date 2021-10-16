#ifndef _HELPERS
#define _HELPERS

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netdb.h>

#include "parson.h" 

#define HOSTNAME "ec2-3-8-116-10.eu-west-2.compute.amazonaws.com"
#define BUFLEN 2048
#define PORTNO 8080
#define FLAGS 0

#define DIE(assertion, call_description)	\
	do {									\
		if (assertion) {					\
			fprintf(stderr, "(%s, %d): ",	\
					__FILE__, __LINE__);	\
			perror(call_description);		\
			exit(EXIT_FAILURE);				\
		}									\
	} while(0)


void print_books(char *str); // afiseaza cartile
void print_book(char *str); // afiseaza o carte
void print_error(char *str); // afiseaza eroarea de la server
void create_message(char *message, char *auth, char *data, char *url, char *command);
void send_receive_message(char *message, struct sockaddr_in serv_addr, int flag, char *util);
// funtiile aplicatiei
void fregister(struct sockaddr_in serv_addr);
void login(struct sockaddr_in serv_addr, char *cookies);
void add_book(struct sockaddr_in serv_addr, char *access);
void enter_library(struct sockaddr_in serv_addr, char *cookies, char *access);
void get_books(struct sockaddr_in serv_addr, char *access);
void get_book(struct sockaddr_in serv_addr, char *access);
void delete_book(struct sockaddr_in serv_addr, char *access);
void logout(struct sockaddr_in serv_addr, char *cookies);

#endif
