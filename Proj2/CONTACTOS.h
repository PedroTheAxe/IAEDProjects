#ifndef CONTACTOS_H
#define CONTACTOS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "HASHTABLE.h" /* Ficheiro que contem as funcoes que gerem as hashtables */

#define NOME 	1024				/* Numero maximo de caracteres para o nome */
#define	EMAIL	512					/* Numero maximo de caracteres para o email */
#define TEL		64					/* Numero maximo de caracteres para o telefone*/
#define MAX		NOME + EMAIL + TEL 	/* Numero maximo de caracteres para o input total */

list* mk_list();

contact* findContact(list* l, char buffer[MAX]);

list* contactDelete(list* l, domainhash** domainTable, char buffer[MAX]);

list* contactEmailChange(list* l, domainhash** domainTable, char buffer[MAX]);

void contactDomainOccurrence(domainhash** domainTable, char buffer[MAX]);

void contactSearch(list* l,char buffer[MAX]);

void contactList(list* l);

list* contactAdd(list* l, domainhash** domainTable, char* buffer);

void freeList(list* l);

#endif