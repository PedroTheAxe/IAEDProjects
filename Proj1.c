/*************************************************/
/*          Ficheiro: projetof.c                 */
/*      Autor: Pedro Morais (Numero 93607)       */
/*  Descrição: Sistema de reserva de salas em C  */
/*************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/* constantes */
#define MAX 64          /* numero maximo de carateres para descricao, organizador e membros */  
#define MAXINPUT 1000   /* limite para o numero de carateres no input total do utilizador */
#define INFO 9          /* numero maximo de argumentos no input do user (descricao, organizador, etc) */
#define ROOMS 10        /* numero maximo de salas */
#define MAXEVENTS 100   /* numero maximo de eventos */
#define MAXMEMBERS 4    /* numero maximo de membros, incluindo organizador */   

/*estrutura para os eventos*/
typedef struct {
    char    eventDescription[MAX];
    int     eventDay;
    int     eventStart;
    int     eventEnd;
    int     eventDuration;
    int     eventRoom;
    char    eventOrganizer[MAX];
    char    eventMembers[MAXMEMBERS][MAX];
} event;

/* base de dados da estrutura que contem um vetor de 10 indices (para as salas),
sendo que cada um destes indices contem outro vetor com 100 indices (para os eventos) */
event dataBase[ROOMS][MAXEVENTS];

/*****************   FUNCOES AUXILIARES   *****************/

/* Funcao que recebe uma string e retorna o numero de "indices"
resultantes de separar a string pelos ':' */
int splitString(char toSplit[MAX], char target[INFO][MAX]) {
    int i;
    char *word = "";
    for (i = 0; i < INFO; i++) {
        strncpy(target[i], "", MAX);
    }
    i = 0;
    word = strtok(toSplit, ":");
    while (word != NULL) {
        strncpy(target[i], word, MAX);   
        word = strtok(NULL, ":");
        i++;
    }
    return i;
}

/* Funcao que le uma string carater a carater ate encontrar o carater
\n, \0 ou EOF, devolvendo o numero de carateres lidos */
int readLine(char s[]) {
    char c;
    int n = 0;
    while ((c = getchar()) != EOF && c != '\n' && c != '\0') {
        s[n] = c;
        n++;
    }
    s[n] = '\0';
    return n;
}
/* Funcao que verifica se um membro ou uma sala esta ocupada de acordo com
os parametros que a funcao recebe, devolvendo 1 se um dos dois estiver ocupado/a */
int isMemberBusy(int eventStart, int eventEnd, char *eventDescription, int eventRoom, int eventDay, char eventMembers[MAXMEMBERS][MAX], char *eventOrganizer, int eventNumber) {
    int e,room,k,busy;
    busy = 0;
    for (e = 0; e < MAXEVENTS; e++) {
        if (e == eventNumber) { /* Para nao comparar o evento com ele mesmo */  
            continue;
        } else {                       
            if (dataBase[eventRoom][e].eventDay == eventDay) { /* Verificacoes de dia e de hora */
                if (((dataBase[eventRoom][e].eventStart <= eventStart) && (dataBase[eventRoom][e].eventEnd > eventStart)) || 
                    ((dataBase[eventRoom][e].eventStart < eventEnd) && (dataBase[eventRoom][e].eventEnd >= eventEnd)) ||
                    ((eventStart <= dataBase[eventRoom][e].eventStart) && (eventEnd >= dataBase[eventRoom][e].eventEnd)))  {
                    printf("Impossivel agendar evento %s. Sala%d ocupada.\n",eventDescription,eventRoom+1);
                    return 1;
                }
            }
        }
    }
    for (room = 0; room < ROOMS; room++) {
        for (e = 0; e < MAXEVENTS; e++) {
            if (e == eventNumber && room == eventRoom) { /* Para nao comparar o evento com ele mesmo */ 
            continue;
            } else {
                if (dataBase[room][e].eventDay == eventDay) { /* Verificacoes de dia e de hora */
                    if (((dataBase[room][e].eventStart <= eventStart) && (dataBase[room][e].eventEnd > eventStart)) ||
                    ((dataBase[room][e].eventStart < eventEnd) && (dataBase[room][e].eventEnd >= eventEnd)) ||
                    ((eventStart <= dataBase[room][e].eventStart) && (eventEnd >= dataBase[room][e].eventEnd)))  {
                        if (strcmp(dataBase[room][e].eventOrganizer, eventOrganizer) == 0) { /* Verifica se o organizador nao esta como organizador noutro evento */
                            printf("Impossivel agendar evento %s. Participante %s tem um evento sobreposto.\n",eventDescription,eventOrganizer);
                            busy = 1;
                        }
                        for (k = 0; k < MAXMEMBERS-1; k++) {
                            if (strcmp(dataBase[room][e].eventMembers[k], eventOrganizer) == 0) { /* Verifica se o organizador nao esta como membro noutro evento */
                                printf("Impossivel agendar evento %s. Participante %s tem um evento sobreposto.\n",eventDescription,eventOrganizer);
                                busy = 1;
                            }
                            if  ((strcmp(dataBase[room][e].eventMembers[0], eventMembers[k]) == 0) || 
                                ((strcmp(dataBase[room][e].eventMembers[1], eventMembers[k]) == 0) && (strcmp(dataBase[room][e].eventMembers[1], "") != 0)) || 
                                ((strcmp(dataBase[room][e].eventMembers[2], eventMembers[k]) == 0) && (strcmp(dataBase[room][e].eventMembers[2], "") != 0)) || 
                                (strcmp(dataBase[room][e].eventOrganizer, eventMembers[k]) == 0 )) { /* Verifica se os membros estao ocupados ou se os membros nao estao como organizadores noutro evento */
                            printf("Impossivel agendar evento %s. Participante %s tem um evento sobreposto.\n",eventDescription,eventMembers[k]);
                            busy = 1;
                            }
                        }
                    }
                }
            }
        }
    }
    if (busy == 1) { /* Se for 1 significa que ou a sala esta ocupada ou um dos membros ja esta ocupado */
        return 1;
    }
    return 0;
}


/* Funcao auxiliar a funcao adiciona membro. Verifica se o membro que estou a tentar adicionar ja esta ocupado e devolve 1 se sim */
int cantaddMember(int eventStart, int eventEnd, int eventDay, int eventRoom, char member[MAX], int eventNumber) {
    int rooms,k,e;
    for (rooms = 0; rooms < ROOMS; rooms++) {
        for (e = 0; e < MAXEVENTS; e++) {
            if (e == eventNumber && rooms == eventRoom) { /* Para nao comparar o evento com ele mesmo */
            continue;
            } else {
                if (dataBase[rooms][e].eventDay == eventDay) { /* Verificacoes de dia e de hora */
                    if (((dataBase[rooms][e].eventStart <= eventStart) && (dataBase[rooms][e].eventEnd > eventStart)) ||
                    ((dataBase[rooms][e].eventStart < eventEnd) && (dataBase[rooms][e].eventEnd >= eventEnd)) ||
                    ((eventStart <= dataBase[rooms][e].eventStart) && (eventEnd >= dataBase[rooms][e].eventEnd)))  {
                        for (k = 0; k < MAXMEMBERS-1; k++) { /* Verifica se o membro esta ocupado */
                            if ((strcmp(dataBase[rooms][e].eventMembers[k], member) == 0) || (strcmp(dataBase[rooms][e].eventOrganizer, member) == 0 )) {
                                printf("Impossivel adicionar participante. Participante %s tem um evento sobreposto.\n", member);
                                return 1; 
                            }
                        }
                    }
                }
            }
        }
    }
    return 0;
}

/* Funcao auxiliar a funcao muda sala. Verifica se a sala para a qual estou a tentar mudar esta ocupada */
int isRoomBusy(int eventStart, int eventEnd, char *eventDescription, int eventRoom, int eventDay) {
    int e;
    for (e = 0; e < MAXEVENTS; e++) {                      
        if (dataBase[eventRoom][e].eventDay == eventDay) { /* Verificacoes de dia e de hora */
            if (((dataBase[eventRoom][e].eventStart <= eventStart) && (dataBase[eventRoom][e].eventEnd > eventStart)) || 
                ((dataBase[eventRoom][e].eventStart < eventEnd) && (dataBase[eventRoom][e].eventEnd >= eventEnd)) ||
                ((eventStart <= dataBase[eventRoom][e].eventStart) && (eventEnd >= dataBase[eventRoom][e].eventEnd)))  {
                printf("Impossivel agendar evento %s. Sala%d ocupada.\n",eventDescription,eventRoom+1);
                return 1;
            }
        }
    } return 0;
}

/* Funcao auxiliar que recebe o numero de uma sala e de um evento e torna-o inativo de 
acordo com a minha representacao de inativo, ou seja -1 para inteiros e "" para strings */
void eventtoInactive(int room, int event) {
    int k;
    dataBase[room][event].eventDay = -1;
    dataBase[room][event].eventStart = -1;
    dataBase[room][event].eventRoom = -1;
    dataBase[room][event].eventDuration = -1;
    strncpy(dataBase[room][event].eventOrganizer, "", MAX);
    strncpy(dataBase[room][event].eventDescription, "", MAX);
    for (k = 0; k < MAXMEMBERS-1; k++) {
        strncpy(dataBase[room][event].eventMembers[k], "", MAX);
    }

}

/* Funcao auxiliar que recebe um numero de minutos e da return em formato hh:mm */
int tohhmm(int min) {
    return ((min / 60)*100 + (min % 60));
}

/* Funcao auxiliar que recebe um evento e da print no mesmo de acordo com o formato
pedido no enuncado */
void printEvent(event reserve){
    int i,k;
    k = 0;
    printf("%s %08d %04d %d Sala%d %s\n",reserve.eventDescription,
        reserve.eventDay, tohhmm(reserve.eventStart),
        reserve.eventDuration,reserve.eventRoom,reserve.eventOrganizer);
    printf("*");
    for (i = 0; i < MAXMEMBERS-1; i++) { /* Com estes dois ifs, ao printar os elementos não imprimo "" no caso de o numero de membros ser menor que 3 */
        if (strcmp(reserve.eventMembers[i], "") != 0) {
            k++;
        }
    }
    for(i = 0; i < k; i++){
        printf(" %s",reserve.eventMembers[i]);
    }
    printf("\n");
}

/* Funcao auxiliar com o algoritmo de ordenacao Bubblesort. Recebe um vetor e ordena-o no sentido ascendente relativamente a datas, horas e salas. */
void bubbleSort(event events[], int len) {
    event eventTemp;
    int j, eventTotal, eventYear, eventMonth, eventDay, eventYear2, eventDay2, eventMonth2, eventTotal2;
    while (len > 1) {
        for (j = 0; j < len-1; j++) { /* Troca a ordem da data. Passa de dd:mm:aaaa para aaaa:mm:dd */
            eventYear = (events[j].eventDay % 10000);
            eventDay =  (events[j].eventDay / 1000000);
            eventMonth = (events[j].eventDay / 10000) % 100;
            eventTotal = (eventYear * 10000) + eventMonth * 100 + eventDay;
            eventYear2 = (events[j+1].eventDay % 10000);
            eventDay2 =  (events[j+1].eventDay / 1000000);
            eventMonth2 = (events[j+1].eventDay / 10000) % 100;
            eventTotal2 = (eventYear2 * 10000) + eventMonth2 * 100 + eventDay2;
            if (eventTotal > eventTotal2) { /* comparacoes entre data do events[j] com o events[j+1] */
                eventTemp = events[j+1]; /* efetua o swap */
                events[j+1] = events[j];
                events[j] = eventTemp;
            } else if (eventTotal == eventTotal2) { /* comparacoes entre hora do events[j] com o events[j+1] */
                if (events[j].eventStart > events[j+1].eventStart) {
                    eventTemp = events[j+1]; /* efetua o swap */
                    events[j+1] = events[j];
                    events[j] = eventTemp;
                } else if (events[j].eventStart == events[j+1].eventStart) { /* comparacoes entre sala do events[j] com o events[j+1] */
                    if (events[j].eventRoom > events[j+1].eventRoom) {
                        eventTemp = events[j+1]; /* efetua o swap */
                        events[j+1] = events[j];
                        events[j] = eventTemp;
                    }
                }
            }
        }
        len--;
    }
}

/***********************   FUNCOES PRINCIPAIS   ***********************/

/* A seguinte funcao adiciona um novo evento na base de dados. Nao retorna nada 
exceto quando o evento que pretendo adicionar estaria numa sala ocupada ou um dos
membros ou organizador do mesmo se encontra ocupado. */
void eventAdd() {
    int e, k, room;
    char args[INFO][MAX];
    int eventStart;
    int eventDuration;
    int eventEnd;
    int numofArgs;
    char listofMemb[MAXMEMBERS-1][MAX];
    char s[MAXINPUT];
    readLine(s);
    numofArgs = splitString(s, args);
    eventStart =  (atoi(args[2])/100)*60 + (atoi(args[2]) % 100); /* Passa o inicio do formato hh:mm para minutos */
    eventDuration = atoi(args[3]);
    eventEnd = eventStart + eventDuration; /* Tempo em que o evento acaba no formato de minutos */
    room = atoi(args[4])-1;
    for (k = 0; k < MAXMEMBERS-1; k++) {
        if (k < (numofArgs - 6)) {
            strncpy(listofMemb[k], args[6+k], MAX);
        } else {
            strncpy(listofMemb[k], "", MAX);
        }
    }
    if (isMemberBusy(eventStart, eventEnd, args[0], room, atoi(args[1]), listofMemb, args[5], -1) == 1) {
        return; /* Verifico se os membros estao ocupados */
    } else { /* Atualizo a base de dados caso os membros nao estejam ocupados */
        for (e = 0; e < MAXEVENTS; e++) {
            if (dataBase[room][e].eventRoom == -1) {
                strncpy(dataBase[room][e].eventDescription, args[0], MAX);
                dataBase[room][e].eventDay = atoi(args[1]);
                dataBase[room][e].eventStart = eventStart;
                dataBase[room][e].eventDuration = eventDuration;
                dataBase[room][e].eventRoom = atoi(args[4]);
                dataBase[room][e].eventEnd = eventEnd;
                strncpy(dataBase[room][e].eventOrganizer, args[5], MAX);
                for (k = 0; k < MAXMEMBERS-1; k++) {
                    if (k < (numofArgs - 6)) {
                        strncpy(dataBase[room][e].eventMembers[k], args[6+k], MAX);
                    } else {
                        strncpy(dataBase[room][e].eventMembers[k], "", MAX);
                    }
                }
                return;
            }
        }
    }   
}   


/* A seguinte funcao lista todos os eventos de todas 
as salas por ordem cronologica do seu inicio. Se por
acaso existirem eventos que se iniciem ao mesmo tempo,
estes sao ordenados por ordem crescente do numero de sala */
void eventList() {
    int i, counter = 0;
    int room, e;
    event events[MAXINPUT];
    for (room = 0; room < ROOMS; room++) {
        for (i = 0; i < MAXEVENTS; i++) {
            if (dataBase[room][i].eventDay != -1) { /* Verifica quantos eventos existem */
                events[counter] = dataBase[room][i];
                counter++;
            }
        }
    }
    bubbleSort(events, counter); /* Chama a funcao auxiliar Bubblesort para ordenar os eventos */
    for (e = 0; e < counter; e++) {
        printEvent(events[e]);
    }
}

/* A seguinte funcao lista todos os eventos
de uma dada sala por ordem cronologica */
void eventListRoom() {
    int i, counter = 0;
    int room;
    int e;
    char s[MAXINPUT];
    char args[INFO][MAX];
    event events[MAXEVENTS];
    readLine(s);
    splitString(s ,args);
    room = atoi(args[0])-1;
    for (i = 0; i < MAXEVENTS; i++) {
        if (dataBase[room][i].eventDay != -1) { /* Verifica quantos eventos existem na sala */
            events[counter] = dataBase[room][i];
            counter++;
        }
    }
    bubbleSort(events, counter); /* Chama a funcao auxiliar Bubblesort para ordenar os eventos */
    for (e = 0; e < counter; e++) {
        printEvent(events[e]);
    }
}

/* A seguinte funcao apaga um
evento da base de dados */
void eventRemove() {
    int e,room,verifica,k;
    char args[INFO][MAX];
    char s[MAXINPUT];
    readLine(s);
    verifica = 0;
    splitString(s, args);
    for (room = 0; room < ROOMS; room++) {
        for (e = 0; e < MAXEVENTS; e++) {
            if (strcmp(dataBase[room][e].eventDescription,  args[0]) == 0) { /* Verifico se o evento que pretendo remover existe */
                 eventtoInactive(room,e); /* Chama a funcao auxiliar que torna um evento inativo de acordo com a minha representacao */
                 for (k = e; k < MAXEVENTS; k++) {
                     while (strcmp(dataBase[room][k].eventDescription,"") != 0) {
                         dataBase[room][e] = dataBase[room][e+1]; /* Efetuo um "Shift Left" de todos os eventos a partir do indice do evento que removi */
                     } 
                     return;                   
                 }
            }
        }
    } if (verifica != 1) {
        printf("Evento %s inexistente.\n", args[0]);
        return;
    }
}

/* A seguinte funcao altera
a hora de inicio de um evento */
void eventHourChange() {
    int e,room,verifica;
    int eventStart;
    int eventEnd;
    char args[INFO][MAX];
    char s[MAXINPUT];
    readLine(s);
    verifica = 0;
    splitString(s, args);
    for (room = 0; room < ROOMS; room++) {
        for (e = 0; e < MAXEVENTS; e++){
            if (strcmp(dataBase[room][e].eventDescription, args[0]) == 0) { /* Verifico se o evento que pretendo mudar a hora existe */
                verifica = 1;
                eventStart = ((atoi(args[1])/100)*60) + (atoi(args[1]) % 100); /* Passo o input do utilizador para minutos */
                eventEnd = eventStart + dataBase[room][e].eventDuration; /* Atualizo a hora a que o evento acaba */
                if (isMemberBusy(eventStart, eventEnd, args[0], dataBase[room][e].eventRoom-1, dataBase[room][e].eventDay,
                    dataBase[room][e].eventMembers, dataBase[room][e].eventOrganizer, e) == 1) { /* Verifico se algum membro do evento ja esta ocupado se efetuar a desejada mudanca de hora */
                    return;
                } else {
                    dataBase[room][e].eventStart = ((atoi(args[1])/100)*60) + (atoi(args[1]) % 100); /* Atualizo os valores na base de dados */
                    dataBase[room][e].eventEnd = dataBase[room][e].eventStart + dataBase[room][e].eventDuration;
                    return;
                }
            }
        }
    } if (verifica != 1) {
        printf("Evento %s inexistente.\n", args[0]);
        return;
    }
}

/* A seguinte funcao altera 
o valor da duracao de um evento */
void eventDurationChange() {
    int e,room,verifica;
    int eventStart;
    int eventEnd;
    int eventDuration;
    char args[INFO][MAX];
    char s[MAXINPUT];
    readLine(s);
    verifica = 0;
    splitString(s, args);
    for (room = 0; room < ROOMS; room++) {
        for (e = 0; e < MAXEVENTS; e++){
            if (strcmp(dataBase[room][e].eventDescription, args[0]) == 0) { /* Verifico se o evento que pretendo mudar a duracao existe */
                eventDuration = atoi(args[1]);
                eventStart = dataBase[room][e].eventStart; /* Mudo o valor da duracao do evento e da hora a que este acaba */
                eventEnd = dataBase[room][e].eventStart + eventDuration;
                if (isMemberBusy(eventStart, eventEnd, args[0], dataBase[room][e].eventRoom-1, dataBase[room][e].eventDay,
                    dataBase[room][e].eventMembers, dataBase[room][e].eventOrganizer, e) == 1) { /* Verifico se algum membro do evento ja esta ocupado se efetuar a desejada mudanca de duracao */
                    return;
                } else {
                    dataBase[room][e].eventDuration = atoi(args[1]); /* Atualizo os valores na base de dados */
                    dataBase[room][e].eventEnd = dataBase[room][e].eventStart + dataBase[room][e].eventDuration;
                    return;
                }
                verifica = 1;
            }
        }
    } if (verifica != 1) {
        printf("Evento %s inexistente.\n", args[0]);
        return;
    }
}

/* A seguinte funcao altera
a sala de um evento */
void eventRoomChange() {
    int e,room,verifica,k,t;
    int eventStart;
    int eventEnd;
    int eventRoom;
    int eventnum;
    char args[INFO][MAX];
    char s[MAXINPUT];
    readLine(s);
    verifica = 0;
    eventnum = 0;
    t = 0;
    splitString(s, args);
    for (room = 0; room < ROOMS; room++) {
        for (e = 0; e < MAXEVENTS; e++){
            if (strcmp(dataBase[room][e].eventDescription, args[0]) == 0) { /* Se mudar a sala para ela propria nao dou erro */
                if (dataBase[room][e].eventRoom == atoi(args[1])) {
                    return;
                }
                verifica = 1;
                eventStart = dataBase[room][e].eventStart;
                eventEnd = eventStart + dataBase[room][e].eventDuration;
                eventRoom = atoi(args[1]);
                while (strcmp(dataBase[eventRoom][t].eventDescription,"") != 0) {
                    t++;
                }
                if ((isRoomBusy(eventStart, eventEnd, args[0], eventRoom-1, dataBase[room][e].eventDay) == 1)) { /* Verifico se a sala para a qual pretendo mudar esta ocupada */
                    return;
                } else {
                    dataBase[room][e].eventRoom = atoi(args[1]); /* Atualizo os valores */
                    while (strcmp(dataBase[atoi(args[1])-1][eventnum].eventDescription,"") != 0) {
                        eventnum++;
                    }
                    dataBase[atoi(args[1])-1][eventnum] = dataBase[room][e]; /* Verifico em que indice e que irei colocar o evento depois de o mover */
                    for (k = e; k < MAXEVENTS; k++) {
                         if (strcmp(dataBase[room][k].eventDescription,"") != 0) {
                             dataBase[room][e] = dataBase[room][e+1]; /* Efetuo um "Shift Left" de todos os eventos a partir do indice do evento que removi */
                             }
                         }
                   eventtoInactive(room,e+1);
                   return;
                }   
            }
        }
    } if (verifica != 1) {
        printf("Evento %s inexistente.\n", args[0]);
        return;
    }
}

/* A seguinte funcao adiciona um membro a um evento ja existente. No caso
do participante ja participar no evento, nao realiza nenhuma acao */
void eventMemberAdd() {
    int room,e,k,verifica,numofmemb;
    char args[INFO][MAX];
    char s[MAXINPUT];
    readLine(s);
    verifica = 0;
    numofmemb = 1;
    splitString(s, args);
    for (room = 0; room < ROOMS; room++) {
        for (e = 0; e < MAXEVENTS; e++) {
            if (strcmp(dataBase[room][e].eventDescription, args[0]) == 0) { /* Verifico se o evento ao qual pretendo adicionar membros existe */
                verifica = 1;
                for (k = 0; k < MAXMEMBERS-1; k++) {
                    if ((strcmp(dataBase[room][e].eventMembers[k], args[1]) == 0) || (strcmp(dataBase[room][e].eventOrganizer, args[1]) == 0)) { /* Se ja participar, nao realiza nada */
                        return;
                    }
                }
                for (k = 1; k < MAXMEMBERS-1; k++) {
                    if (strcmp(dataBase[room][e].eventMembers[k], "") != 0) { /* Calcula numero de membros no evento */
                        numofmemb++;
                    }
                }
                if (numofmemb == 3) {
                    printf("Impossivel adicionar participante. Evento %s ja tem 3 participantes.\n",dataBase[room][e].eventDescription);
                    return;
                }
                if (cantaddMember(dataBase[room][e].eventStart, dataBase[room][e].eventEnd, dataBase[room][e].eventDay, dataBase[room][e].eventRoom, args[1], e) == 0) {
                    strcpy(dataBase[room][e].eventMembers[numofmemb],args[1]); /* Verifica se o membro que pretendo adicionar esta ocupado */
                }
                return;
            }
        }
    } if (verifica != 1) {
        printf("Evento %s inexistente.\n", args[0]);
    }
}

/* A seguinte funcao remove um participante de um evento ja existente. No caso
do participante nao participar no evento, nao realiza nenhuma acao */
void eventMemberRemove() {
    int room,e,k,memnum,verifica,i;
    char args[INFO][MAX];
    char s[MAXINPUT];
    readLine(s);
    verifica = 0;
    memnum = 1;
    splitString(s, args);
    for (room = 0; room < ROOMS; room++) {
        for (e = 0; e < MAXEVENTS; e++) {
            if (strcmp(dataBase[room][e].eventDescription, args[0]) == 0) {
                verifica = 1;
                if (((strcmp(dataBase[room][e].eventMembers[0], args[1]) != 0) && (strcmp(dataBase[room][e].eventMembers[1], args[1]) != 0) && (strcmp(dataBase[room][e].eventMembers[2], args[1]) != 0)) || (strcmp(dataBase[room][e].eventOrganizer, args[1]) == 0)) { /* Se nao participar, nao realiza nada */
                    return;
                }
                for (k = 1; k < MAXMEMBERS-1; k++) {
                    if (strcmp(dataBase[room][e].eventMembers[k], "") != 0) { /* Calcula numero de membros no evento */
                        memnum++;
                    }
                }
                if (memnum == 1) {
                    printf("Impossivel remover participante. Participante %s e o unico participante no evento %s.\n", dataBase[room][e].eventMembers[0],dataBase[room][e].eventDescription);
                    return;
                }
                for (k = 0; k < MAXMEMBERS-1; k++) {
                    if (strcmp(dataBase[room][e].eventMembers[k], args[1]) == 0) {
                       for (i = k; i < MAXMEMBERS; i++) {
                            strcpy(dataBase[room][e].eventMembers[i], dataBase[room][e].eventMembers[i+1]); /* Efetuo um "Shift Left" nos membros restantes a partir do indice do membro que removi */
                       }
                    }
                }
            }
        }
    }if (verifica != 1) {
        printf("Evento %s inexistente.\n", args[0]);   
    }
}

/* A seguinte funcao permite ao utilizador selecionar que operacao
pretende efetuar na base de dados (adicionar evento, remover evento, etc) */
int opSelector() {
    int running = 1;
    char op;
    while (running == 1) {   
        op = getchar(); /* Obtenho o comando que o utilizador pretende usar */
        getchar();
        if (op == 'l') {
            eventList();
        }
        switch (op) {
            case 'a':
                eventAdd();
                break;
            case 's':
                eventListRoom();
                break;
            case 'r':
                eventRemove();
                break;
            case 'i':
                eventHourChange();
                break;
            case 't':
                eventDurationChange();
                break;
            case 'm':
                eventRoomChange();
                break;
            case 'A':
                eventMemberAdd();
                break;
            case 'R':
                eventMemberRemove();
                break;
            case 'x':
                running = 0;
                break;
        }
    }
    return 0;
}

/* Funcao main, inicializa todos os eventos de todas as salas com -1
nos argumentos que sao int e "" nos que sao uma string */
int main() {
    int i,e,k;
    for (i = 0; i < ROOMS; i++) {
        for (e = 0; e < MAXEVENTS; e++) {
            dataBase[i][e].eventDay = -1;
            dataBase[i][e].eventStart = -1;
            dataBase[i][e].eventRoom = -1;
            dataBase[i][e].eventDuration = -1;
            strncpy(dataBase[i][e].eventOrganizer, "", MAX);
            strncpy(dataBase[i][e].eventDescription, "", MAX);
            for (k = 0; k < MAXMEMBERS-1; k++) {
                strncpy(dataBase[i][e].eventMembers[k], "", MAX);
            }
        }
    }
    opSelector();
    return 0;
}
