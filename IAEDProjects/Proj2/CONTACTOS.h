#ifndef CONTACTOS_H
#define CONTACTOS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "HASHTABLE.h" /* Ficheiro que contem as funcoes que gerem as hashtables */

#define NOME 	1024			     
#define	EMAIL	512		             
#define TEL	64			         
#define MAX	NOME + EMAIL + TEL 	 

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
