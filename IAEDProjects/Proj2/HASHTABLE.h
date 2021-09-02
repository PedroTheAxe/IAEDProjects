#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "STRUCT.h"	/* Header file que contem as estruturas utilizadas no projeto */

#define HASHSIZE 		1009  				/* Tamanho da hashtable */
#define DOMAINHASHMAX 	503 				/* Tamanho da hashtable dos dominios */

/* Funcoes utilizadas para a hashtable dos dominios e com os dominios */

unsigned int hash(char* str);

domainhash** createDomainHash();

void freeDomainHash(domainhash** domainTable);

void addDomain(domainhash** domainTable, char* key);

void removeDomain(domainhash** domainTable, char* key);

int getValue(domainhash** domainTable, char* key);

void getDomain(char* buffer, char* answer) ;

#endif