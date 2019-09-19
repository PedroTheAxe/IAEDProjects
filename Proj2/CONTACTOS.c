#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CONTACTOS.h" /* Ficheiro que contem os prototipos e declaracoes das funcoes que gerem a lista de contactos */

/* Funcao mk_list
   Input: Nada
   Output: Lista
   Descricao: A seguinte funcao aloca memoria para
   a hashtable e para a lista duplamente ligada, tratando
   de inicializar todos os respetivos indices a NULL.
*/
list* mk_list() 
{
	int i;
	list *lista = malloc(sizeof(list));
	lista->head = NULL;
	lista->last = NULL;
	lista->hashtable = malloc(sizeof(contact) * HASHSIZE);
	for (i = 0; i < HASHSIZE; i++) 
	{
		*(lista->hashtable+i) = NULL;
	}

	return lista;
}

/* Funcao findContact
   Input: Lista e string que contem nome do contacto
   Output: Contacto (se este existir).
*/
contact* findContact(list* l, char buffer[MAX]) 
{
	contact* toFind;

	int contactHash = hash(buffer) % HASHSIZE;

	for (toFind = *(l->hashtable + contactHash); toFind && strcmp(toFind->nome, buffer) != 0; toFind = toFind->collision);
	
	return toFind;
}

/* Funcao contactDelete (r)
   Input: r <nome>
   Output: Nada (excepto erro)
   Descricao: A seguinte funcao apaga um
   contacto dado um nome.
 */
list* contactDelete(list* l, domainhash** domainTable, char buffer[MAX]) 
{
	char domain[MAX];

	int contactHash;

	contact* toDelete, *contactCollision;

	toDelete = l->head;

	buffer = strtok(buffer, "\n");

	if ((toDelete = findContact(l, buffer))) {

		getDomain(toDelete->email, domain);
		removeDomain(domainTable, domain);

		if (toDelete->next != NULL) {
    		
    		toDelete->next->previous = toDelete->previous;
		}

		if (toDelete->previous != NULL) {
    	
    		toDelete->previous->next = toDelete->next;
		} 

		if (toDelete == l->head) 
		{
			l->head = toDelete->next;
		}

		if (toDelete == l->last) 
		{
			l->last = toDelete->previous;
		}

		contactHash = hash(buffer) % HASHSIZE;
		contactCollision = *(l->hashtable + contactHash);

		if (strcmp(contactCollision->nome, buffer) == 0) 
		{
			*(l->hashtable + contactHash) = contactCollision->collision;
		} else 
		{
			for(;strcmp(contactCollision->collision->nome, buffer) != 0;contactCollision=contactCollision->collision);
			
			contactCollision->collision = contactCollision->collision->collision;
		}

		free(toDelete->nome);
		free(toDelete->email);
		free(toDelete->tel);
		free(toDelete);
		
		return l;
	}
	
	printf("Nome inexistente.\n");

	return l;
}


/* Funcao contactEmailChange (e)
   Input: e <nome> <novo-email>
   Output: Nada (excepto erro)
   Descricao: A seguinte funcao altera o 
   endereco de email de um contacto dado o nome.
*/
list* contactEmailChange(list* l, domainhash** domainTable, char buffer[MAX]) 
{
	contact* toChange;

	char domain[MAX];

	buffer = strtok(buffer, " ");

	if ((toChange = findContact(l, buffer))) 
		{
			getDomain(toChange->email, domain);
			removeDomain(domainTable, domain);
			free(toChange->email);

			buffer = strtok(NULL,"\n");
			toChange->email = malloc(sizeof(char) * (strlen(buffer) + 1));
			strcpy(toChange->email, buffer);

			getDomain(toChange->email, domain);
			addDomain(domainTable, domain);

			return l;
		}

	printf("Nome inexistente.\n");

	return l;
}


/* Funcao contactDomainOccurence (c)
   Input: c <dominio>
   Output: <dominio>:<numero-de-ocorrencias>
   Descricao: A seguinte funcao conta o numero
   de ocorrencias de um dominio de um e-mail dado.
*/
void contactDomainOccurrence(domainhash** domainTable, char buffer[MAX]) 
{
	buffer[strlen(buffer)-1] = '\0';

	printf("%s:%d\n", buffer, getValue(domainTable, buffer));

	return;
}

/* Funcao findContact (p)
   Input: p <nome>
   Output: <nome> <email> <telefone> (ou erro se nao existir)
   Descricao: A seguinte funcao procura um contacto.
*/
void contactSearch(list* l,char buffer[MAX]) 
{
	contact* toFind;

	buffer = strtok(buffer, "\n"); /* remove o \n que vem do fgets */

	if ((toFind = findContact(l, buffer))) 
		{
			printf("%s ",toFind->nome);
			printf("%s ",toFind->email);
			printf("%s",toFind->tel);

			return;
		}

	printf("Nome inexistente.\n"); 

}

/* Funcao contactList (l)
   Input: l
   Output: Nada
   Descricao: A seguinte funcao lista os
   contactos introduzidos pela ordem em que
   foram introduzidos.
*/
void contactList(list* l) 
{
	contact* temp = l->head;

	if (temp == NULL)  
	{
		return;
	}
	while (temp != NULL) 
	{
		printf("%s ",temp->nome);
		printf("%s ",temp->email);
		printf("%s",temp->tel);

		temp = temp->next;
	}
	return;	
 }


/* Funcao contactAdd (a)
   Input: a <nome> <email> <telefone>
   Output: Nada (excepto erro)
   Descricao: A seguinte funcao adiciona um
   novo contacto.
*/
list* contactAdd(list* l, domainhash** domainTable, char* buffer) 
{
	int contactHash;

	contact* novo_contacto;

	char domain[MAX];

	char* ptr = strtok(buffer, " ");

	if (findContact(l, buffer)) 
	{
		printf("Nome existente.\n");

		return l;
	}

	novo_contacto = malloc(sizeof(contact));
	novo_contacto->nome = malloc(sizeof(char) * (strlen(ptr) + 1));
	strcpy(novo_contacto->nome, ptr);

	ptr = strtok(NULL, " ");
	novo_contacto->email = malloc(sizeof(char) * (strlen(ptr) + 1));
	strcpy(novo_contacto->email, ptr);
	getDomain(novo_contacto->email, domain);
	addDomain(domainTable, domain); 

	ptr = strtok(NULL, " "); 
	novo_contacto->tel = malloc(sizeof(char) * (strlen(ptr) + 1));
	strcpy(novo_contacto->tel, ptr);

	novo_contacto->next = NULL;
	novo_contacto->previous = l->last;
	novo_contacto->collision = NULL;

	contactHash = hash(novo_contacto->nome) % HASHSIZE;

	if (*(l->hashtable + contactHash) == NULL) 
	{
		*(l->hashtable + contactHash) = novo_contacto;
	} else 
	{
		novo_contacto->collision = *(l->hashtable + contactHash);
		*(l->hashtable + contactHash) = novo_contacto;
	}

	if (l -> head == NULL) 
	{
		l->head = novo_contacto;
	} else 
	{
		l->last->next = novo_contacto;
	}

	l->last = novo_contacto;

	return l;
}


/* Funcao freeList
   Input: Lista
   Output: Nada
   Descricao: A seguinte funcao liberta toda a 
   memoria alocada tanto para a lista duplamente ligada
   como para a hashtable.
*/
void freeList(list* l) 
{
	contact* next_contact;

	while (l->head != NULL) 
	{
		next_contact = l->head->next;
		
		free(l->head->nome);
		free(l->head->email);
		free(l->head->tel);
		free(l->head);

		l->head = next_contact;
	}

	free(l->hashtable);
	free(l);

	return;
}
