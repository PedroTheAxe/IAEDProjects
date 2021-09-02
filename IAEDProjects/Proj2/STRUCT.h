#ifndef STRUCT_H
#define STRUCT_H

/* Header file que contem as estruturas utilizadas no projeto */


/* 	Estrutura do contacto:
 	Contem os alguns dos ponteiros necessarios para a 	
	implementacao de uma lista duplamente ligada, next 
	e previous. Tambem contem o ponteiro collision, que
	aponta para as colisoes num determinado bucket das 
	hashtables, e os dados utilizados na lista de contactos */

typedef struct str_node 

{
	struct str_node *next, *previous, *collision;
	char* nome;
	char* email;
	char*  tel;

} contact;

/* 	Estrutura da lista:
 	Contem os ponteiros necessarios para apontar para
	o primeiro e ultimo elemento da lista duplamente 
	ligada. Contem tambem um ponteiro para os ponteiros
	da hashtable implementada. */

typedef struct

{
	struct str_node *head, *last, **hashtable;

} list;

/* Estrutura da Hashtable dos domínios:
   Contem todos os tipos de dados necessarios para a
   execucao de uma hashtable que guarde o numero de
   vezes que um determinado dominio aparece. */
typedef struct domainTable
{
	struct domainTable* collision;
	char* domain;
	int domaincounter;

} domainhash;

#endif