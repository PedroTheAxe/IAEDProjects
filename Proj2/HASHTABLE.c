#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "HASHTABLE.h"

/* Ficheiro que contem as funcoes utilizadas
na implementacao das hashtables */


/* Funcao has
   Input: String
   Output: Key (indice para bucket da hashtable)
   Descricao: A seguinte funcao recebe uma string
   e calcula o bucket adequado para a mesma dentro
   da hashtable.
*/
unsigned int hash(char* str) 
{
    unsigned int hash = 5381;
    while(*str) 
    {
        hash = 33 * hash ^ (unsigned char) *str++;
    }
    return hash;
}


/* Funcao createDomainHash: 
   Input: Nada
   Output: Hashtable (Inicializada)
   Descricao: A seguinte funcao aloca memória para
   a hashtable dos dominios e inicializa todos os
   seus buckets a NULL.
*/
domainhash** createDomainHash() 
{
	int i;
	
	domainhash** domainTable = malloc(sizeof(domainhash) * DOMAINHASHMAX);

	for (i=0; i<DOMAINHASHMAX; i++) 
	{
		*(domainTable+i) = NULL;
	}

	return domainTable;

}

/* Funcao freeDomainHash:
   Input: Hashtable
   Output: Nada
   Descricao: A seguinte funcao recebe a hashtable dos
   dominios e liberta toda a memoria previamente alocada 
   para a mesma.
*/
void freeDomainHash(domainhash** domainTable) 
{
	int i;
	domainhash *current, *next;
	for (i=0; i<DOMAINHASHMAX; i++) 
	{
		current = *(domainTable + i);
		while (current != NULL) 
		{
			next = current->collision;
			
			free(current->domain);
			free(current);
			
			current = next;
		}
	}

	free(domainTable);
}

/* Funcao addDomain
   Input: Hashtable e dominio
   Output: Nada
   Descricao: A seguinte funcao recebe uma hashtable
   e um dominio e calcula em que bucket adicionar
   esse dominio. De acordo com o numero de dominios
   iguais no bucket a funcao incrementa o domaincounter.
*/
void addDomain(domainhash** domainTable, char* key) 
{

	domainhash* domainPtr;

	int domainIndex = hash(key) % DOMAINHASHMAX;

	/* Este for percorre todos os elementos do bucket até este
	ser NULL ou até encontrar o dominio que pretendo */
	for (domainPtr=*(domainTable + domainIndex);              \
	domainPtr != NULL && strcmp(key, domainPtr->domain) != 0; \
	domainPtr = domainPtr->collision);

	if (domainPtr != NULL) /* Verifica se o dominio esta no bucket */
	{
		domainPtr->domaincounter++;
	} 
	else /* Se o bucket nao contiver esse dominio */
	{
		domainPtr = malloc(sizeof(domainhash));
		domainPtr->domain = malloc(sizeof(char) * (strlen(key) + 1));

		strcpy(domainPtr->domain,key);
		
		domainPtr->domaincounter = 1;
		domainPtr->collision = *(domainTable + domainIndex);
		*(domainTable + domainIndex) = domainPtr;
	}	
}

/* Funcao removeDomain
   Input: Hashtable e dominio
   Output: Nada
   Descricao: A seguinte funcao recebe uma hashtable
   e um dominio e calcula em que bucket remover esse
   dominio. De acordo com o numero de dominios iguais
   no bucket a funcao decrementa o domaincounter.
*/
void removeDomain(domainhash** domainTable, char* key) 
{
	domainhash* domainPtr;

	int domainIndex = hash(key) % DOMAINHASHMAX;

	for (domainPtr=*(domainTable + domainIndex);              \
	domainPtr != NULL && strcmp(key, domainPtr->domain) != 0; \
	domainPtr = domainPtr->collision);

	if (domainPtr != NULL && domainPtr->domaincounter > 0) 
	{
		domainPtr->domaincounter--;
	} 
}

/* Funcao: getValue
   Input: Hashtable e dominio
   Output: Numero de vezes que o dominio aparece
   Descricao: A seguinte funcao recebe uma hashtable
   e um dominio e devolve a quantidade de vezes que 
   o dominio aparece no seu bucket correspondente.
*/
int getValue(domainhash** domainTable, char* key) 
{
	domainhash* domainPtr;

	int domainIndex = hash(key) % DOMAINHASHMAX;

	for (domainPtr=*(domainTable + domainIndex);              \
	domainPtr != NULL && strcmp(key, domainPtr->domain) != 0; \
	domainPtr = domainPtr->collision);

	if (domainPtr == NULL) 
	{
		return 0;
	}

	return domainPtr->domaincounter;
}

/* Funcao: getDomain
   Input: Email
   Output: Dominio
   Descricao: Esta funcao recebe o email de um
   contacto e retorna o dominio do mesmo.
*/
void getDomain(char* buffer, char* answer) 
{
	int i;
	for (i = 0; buffer[i] != '@'; i++);
	strcpy(answer, buffer + 1 + i);
}
