/*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*/
/*			     Projeto 2 de IAED                             */
/*		    Autor: Pedro Morais -> (Número 93607)                  */ 
/*		                                                           */
/*  Descricao do Projeto 2:                                                */
/*                                                                         */
/*  Desenvolvimento, em linguagem C, de um sistema de gestao de contactos. */
/*  A interaccao com o programa ocorre atraves de um conjunto de linhas    */
/*  compostas por:                                                         */
/*	                                                                   */
/*  <comando> <número de argumentos dependente do comando a executar>      */
/*                                                                         */
/*  Comandos:                                                              */
/*                                                                         */
/*  a -> a <nome> <email> <telefone> // Adiciona um novo contacto.         */
/*  l -> l // Lista todos os contactos por ordem de introducao.            */
/*  p -> p <nome> // Procura um contacto.                                  */
/*  r -> r <nome> // Apaga um contacto.                                    */
/*  e -> e <nome> <email> // Altera o endereco de email de um contacto.    */
/*  c -> c <dominio> // Conta o número de ocorrencias de um dominio.       */
/*  x -> x // Termina o programa.                                          */
/*                                                                         */
/*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CONTACTOS.h" /* Ficheiro que contem as funcoes que gerem os contactos */

/* Funcao main, funciona como selecionador de operacoes
utilizando um switch case para todos as funcoes pedidas no enunciado. */
int main() 
{
	char buffer[MAX];

	char function;

	int running;

	list* lista;

	domainhash** domainTable;

	lista = mk_list();

	domainTable = createDomainHash();

	running = 1;


	while (running == 1) 
	{
		function = getchar();
		switch(function) 
		{
			case 'a':
				getchar();
				fgets(buffer, MAX, stdin);
				lista = contactAdd(lista, domainTable, buffer);
				break;  
			case 'l':
				contactList(lista);
				break;
			case 'p':
				getchar();
				fgets(buffer, MAX, stdin);
				contactSearch(lista,buffer); 
				break;
			case 'r':
				getchar();
				fgets(buffer, MAX, stdin);
				lista = contactDelete(lista, domainTable, buffer);
				break; 
			case 'e':
				getchar();
				fgets(buffer, MAX, stdin);
				contactEmailChange(lista, domainTable, buffer);
				break;	
			case 'c':
				getchar();
				fgets(buffer, MAX, stdin);
				contactDomainOccurrence(domainTable, buffer);
				break; 
			case 'x':
				running = 0;
				freeList(lista);
				freeDomainHash(domainTable);
				break;	
		}
	}
	return 0;
}
