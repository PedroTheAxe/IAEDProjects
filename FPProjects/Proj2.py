# ############################ #
# Projeto 2 Pedro Morais 93607 #
# ############################ #

# ############################################## #
# TAD Celula - Escolhi a representacao de listas #
# ############################################## #

def cria_celula(v):
    '''
    cria_celula: {-1,0,1} ---> celula
    Funcao que recebe o valor de estado de uma celula e devolve uma celula com esse valor
    '''
    if v in (-1,0,1):
        return [v]
    else:
        raise ValueError('cria_celula: argumento invalido.')

def obter_valor(c):
    '''
    obter_valor: celula ---> {-1,0,1}
    Funcao que devolve o valor associado a celula c
    '''
    return c[0]

def inverte_estado(c):
    '''
    inverte_estado: celula ---> celula
    Funcao que devolve a celula resultante de inverter o estado da celula no argumento
    '''
    aux = c #Variavel auxiliar que torna a funcao destrutiva
    if c == [1]:
        aux[0] = 0
    elif c == [0]:
        aux[0] = 1
    return c
    
def eh_celula(n):
    '''
    eh_celula: universal ---> logico
    Funcao que devolve verdadeira no caso do seu argumento ser do tipo celula
    '''
    if isinstance(n,list) and len(n) == 1 and n[0] in (1,0,-1):
        return True
    return False

def celulas_iguais(c1, c2):
    '''
    celulas_iguais: celula x celula ---> logico
    Funcao que devolve verdadeiro apenas se c1 e c2 sao celulas e estao no mesmo estado
    '''
    if eh_celula(c1) and eh_celula(c2):
        return obter_valor(c1) == obter_valor(c2)
    return False

def celula_para_str(c):
    '''
    celula_para_str: celula ---> cadeia de caracteres
    Funcao que devolve uma cadeira de caracteres que representa a celula que e o seu argumento.
    O estado ativo e representado por '1', o estado inativo e representado por '0' e o estado
    incerto e representado por 'x'B
    '''
    if obter_valor(c) == 1:
        return '1'
    if obter_valor(c) == 0:
        return '0'
    if obter_valor(c) == -1:
        return 'x'
    
# ############## #
# TAD Coordenada #
# ############## #

def cria_coordenada(l,c):
    '''
    cria_coordenada: natural x natural ---> coordenada
    Funcao que devolve a coordenada correspondente a linha l e a coluna c.
    Os argumentos tem de ser naturais e pertencer ao intervalo {0,1,2}
    '''
    if isinstance(l,int) and isinstance(c, int) and 3 > l >= 0 and 3 > c >= 0:
        return (l,c)
    raise ValueError('cria_coordenada: argumentos invalidos.')

def coordenada_linha(c):
    '''
    coordenada_linha: coordenada ---> natural
    Funcao que devolve o natural correspondente a linha da coordenada c    
    '''
    return c[0]

def coordenada_coluna(c):
    '''
    coordenada_coluna: coordenada ---> natural
    Funcao que devolve o natural correspondente a coluna da coordenada c    
    '''    
    return c[1]
        
def eh_coordenada(n):
    '''
    eh_coordenada: universal ---> logico
    Funcao que devolve verdadeiro no caso do seu argumento ser do tipo coordenada   
    '''
    if isinstance(n, tuple) and len(n) == 2:
        for i in n:
            if type(i) != int or i not in (0,1,2):
                return False
        return True
    return False

def coordenadas_iguais(c1,c2):
    '''
    coordenadas_iguais: coordenada x coordenada ---> logico
    Funcao que devolve verdadeiro apenas se c1 e c2 representam coordenadas na mesma posicao
    '''
    if eh_coordenada(c1) and eh_coordenada(c2):
        return coordenada_linha(c1) == coordenada_linha(c2) and \
               coordenada_coluna(c1) == coordenada_coluna(c2)
    return False

def coordenada_para_str(c):
    '''
    coordenada_para_str: coordenada ---> cadeira de caracteres
    Funcao que devolve a cadeira de caracteres que representa o seu argumento
    '''
    return str(c)

# ############# #
# TAD Tabuleiro #
# ############# #

def tabuleiro_inicial():
    '''
    tabuleiro_inicial: {} ---> tabuleiro
    Funcao que devolve o tabuleiro que representa o seu estado inicial do jogo, representado
    na Figura 1 do enunciado
    '''
    return [[cria_celula(-1),cria_celula(-1),cria_celula(-1)],\
            [cria_celula(0),cria_celula(0),cria_celula(-1)],\
            [cria_celula(0),cria_celula(-1)]]

def str_para_tabuleiro(t):
    '''
    str_para_tabuleiro: cadeira de caracteres ---> tabuleiro
    Devolve o tabuleiro correspondente a cadeira de caracteres que e o seu argumento.
    Esta cadeira de caracteres corresponde a representacao interna do tabuleiro tal como
    usada no primeiro projeto, ou seja, um tuplo de 3 tuplos, sendo que os dois primeiros
    tem 3 elementos e o ultimo tem 2 elementos
    '''
    if type(t) != str:
        raise ValueError('str_para_tabuleiro: argumento invalido.')
    x = eval(t)
    if not (type(x) == tuple and len(x) == 3 and \
           all(type(e) == tuple for e in x) and \
           all(len(e) == 2 if i == 2 else len(e) == 3 for i, e in enumerate(x)) and \
           all((n in (0, 1, -1) for e in x for n in e))): # Verifica se o argumento inserido e um tabuleiro de acordo com a representacao do primeiro projeto
        raise ValueError('str_para_tabuleiro: argumento invalido.')
    return [[cria_celula(x[0][0]),cria_celula(x[0][1]),cria_celula(x[0][2])],\
            [cria_celula(x[1][0]),cria_celula(x[1][1]),cria_celula(x[1][2])],\
            [cria_celula(x[2][0]),cria_celula(x[2][1])]]

def tabuleiro_dimensao(t):
    '''
    tabuleiro_dimensao: tabuleiro ---> natural
    Funcao que devolve o natural correspondente ao numero de linhas(e consequentemente colunas)
    do tabuleiro presente no argumento   
    '''
    return len(t)

def tabuleiro_celula(t, coor):
    '''
    tabuleiro_celula: tabuleiro x coordenada ---> celula
    Funcao que devolve a celula presente na coordenada coor do tabuleiro t
    '''
    for i in coor:
        if i not in (0,1,2) or (coor == cria_coordenada(2,0)): #
            raise ValueError('tabuleiro_celula: argumento invalido.')
    return t[coordenada_linha(coor)][coordenada_coluna(coor)-1] if \
           coordenada_linha(coor) == 2 else t[coordenada_linha(coor)][coordenada_coluna(coor)] #Se coordenada_linha(coor) == 2 Entao a coordenada (2,1) devolve a celula na coordenada(2,0) a coordenada (2,2) devolve a celula na coordenada(2,1), visto que a coordenada(2,0) nao existe

def tabuleiro_substitui_celula(t,cel,coor):
    '''
    tabuleiro_sustitui_celula: tabuleiro x celula x coordenada ---> tabuleiro
    Funcao que devolve o tabuleiro que resulta de substituir a celula existente na coordenada coor do tabuleiro pela nova celula cel
    '''
    if not eh_tabuleiro(t) or not eh_coordenada(coor) or coor == (2,0):
        raise ValueError('tabuleiro_substitui_celula: argumentos invalidos.')
    else:
        if coordenada_linha(coor) == 2:
            coor = cria_coordenada(coordenada_linha(coor), coordenada_coluna(coor) - 1) #Mesmo raciocinio que a funcao passada, tendo em conta que a coordenada (2,0) nao existe          
        t[coordenada_linha(coor)][coordenada_coluna(coor)] = cel
    return t

def tabuleiro_inverte_estado(t, coor):
    '''
    tabuleiro_inverte_estado: tabuleiro x coordenada ---> tabuleiro
    Funcao que devolve o tabuleiro que resulta de inverter o estado da celula presente na coor do tabuleiro
    '''
    if not eh_tabuleiro(t) or not eh_coordenada(coor) or coor == (2,0):
        raise ValueError('tabuleiro_inverte_estado: argumentos invalidos.')
    else:
        if coordenada_linha(coor) == 2:
            coor = cria_coordenada(coordenada_linha(coor), coordenada_coluna(coor) - 1) #Mesmo raciocinio que a funcao passada, tendo em conta que a coordenada (2,0) nao existe               
        t[coordenada_linha(coor)][coordenada_coluna(coor)] = \
            inverte_estado(t[coordenada_linha(coor)][coordenada_coluna(coor)])
    return t
   
def eh_tabuleiro(t):
    '''
    eh_tabuleiro: universal ---> logico
    Funcao que devolve Verdadeiro no caso do argumento inserido ser do tipo na nossa representacao de tabuleiro
    '''
    if isinstance(t, list) and len(t) == 3 and type(t[0]) == list and  all(type(e) == list for e in t): 
        if len(t[0]) == 3 and len(t[1]) == 3 and len(t[2]) == 2:   
            for i in range(len(t)):
                for el in t[i]:
                    if not eh_celula(el):  
                        return False   
            return True
    return False


def tabuleiros_iguais(t1, t2):
    '''
    tabuleiros_iguais: tabuleiro x tabuleiro ---> logico
    Funcao que devolve verdadeiro apenas no caso de t1 e t2 forem tabuleiros que contenham
    celulas iguais em cada uma das coordenadas
    '''
    if not eh_tabuleiro(t1) or not eh_tabuleiro(t2): 
        return False
    return t1 == t2
    
def tabuleiro_para_str(t):
    '''
    tabuleiro_+ara_str: tabuleiro ---> cadeira de caracteres
    Funcao que devolve a cadeira de caracteres que representa o seu argumento. A sua representacao
    externa e identica a apresentada no primeiro projeto, representando o tabuleiro com os qubits
    a fazer um angulo de 45 graus com a horizontal
    '''
    return ('+-------+\n|...' + celula_para_str(t[0][2]) + '...|\n|..' + \
            celula_para_str(t[0][1]) + '.' + celula_para_str(t[1][2]) + \
            '..|\n|.' + celula_para_str(t[0][0]) + '.' + celula_para_str(t[1][1]) + \
            '.' + celula_para_str(t[2][1]) + '.|\n|..' + celula_para_str(t[1][0]) + \
            '.' + celula_para_str(t[2][0]) + '..|\n+-------+')

# ####################### #
# Operacoes de Alto nivel #
# ####################### #

def porta_x(t, p):
    '''
    porta_x: tabuleiro x {'E','D'} ---> tabuleiro
    Funcao que aplica uma transformacao de porta_x num determinado lado do tabuleiro,
    dependendo do valor do segundo argumento inserido
    '''
    if not (eh_tabuleiro(t) and (p == 'E' or p == 'D')):
        raise ValueError('porta_x: argumentos invalidos.')
    else:
        if p == 'D':
            tabuleiro_inverte_estado(t,cria_coordenada(0,1))
            tabuleiro_inverte_estado(t,cria_coordenada(1,1))
            tabuleiro_inverte_estado(t,cria_coordenada(2,1))
        else:
            tabuleiro_inverte_estado(t,cria_coordenada(1,0))
            tabuleiro_inverte_estado(t,cria_coordenada(1,1))
            tabuleiro_inverte_estado(t,cria_coordenada(1,2))
    return t
            

def porta_z(t,p):
    '''
    porta_z: tabuleiro x {'E','D'} ---> tabuleiro
    Funcao que aplica uma transformacao de porta_z num determinado lado do tabuleiro,
    dependendo do valor do segundo argumento inserido
    '''    
    if not (eh_tabuleiro(t) and (p == 'E' or p == 'D')):
        raise ValueError('porta_z: argumentos invalidos.')
    else:
        if p == 'D':
            tabuleiro_inverte_estado(t,cria_coordenada(0,2))
            tabuleiro_inverte_estado(t,cria_coordenada(1,2))
            tabuleiro_inverte_estado(t,cria_coordenada(2,2))
        else:
            tabuleiro_inverte_estado(t,cria_coordenada(0,0))
            tabuleiro_inverte_estado(t,cria_coordenada(0,1))
            tabuleiro_inverte_estado(t,cria_coordenada(0,2))
    return t
        
def porta_h(t,p):
    '''
    porta_h: tabuleiro x {'E','D'} ---> tabuleiro
    Funcao que aplica uma transformacao de porta_h num determinado lado do tabuleiro,
    dependendo do valor do segundo argumento inserido
    '''    
    if not (eh_tabuleiro(t) and (p == 'E' or p == 'D')):
        raise ValueError('porta_h: argumentos invalidos.')
    else:
        if p == 'E':
            t_aux = [tabuleiro_celula(t,cria_coordenada(0,0)),tabuleiro_celula(t,cria_coordenada(0,1)),\
                     tabuleiro_celula(t,cria_coordenada(0,2))] #Criacao de uma variavel para copiar os valores de um dos lados da transformacao
            tabuleiro_substitui_celula(t,tabuleiro_celula(t,cria_coordenada(1,0)),cria_coordenada(0,0))
            tabuleiro_substitui_celula(t,t_aux[0],cria_coordenada(1,0))
            tabuleiro_substitui_celula(t,tabuleiro_celula(t,cria_coordenada(1,1)),cria_coordenada(0,1))
            tabuleiro_substitui_celula(t,t_aux[1],cria_coordenada(1,1))
            tabuleiro_substitui_celula(t,tabuleiro_celula(t,cria_coordenada(1,2)),cria_coordenada(0,2))
            tabuleiro_substitui_celula(t,t_aux[2],cria_coordenada(1,2))
        else:
            t_aux = [tabuleiro_celula(t,cria_coordenada(0,2)),tabuleiro_celula(t,cria_coordenada(1,2)),\
                     tabuleiro_celula(t,cria_coordenada(2,1))] #Criacao de uma variavel para copiar os valores de um dos lados da transformacao
            tabuleiro_substitui_celula(t,tabuleiro_celula(t,cria_coordenada(0,1)),cria_coordenada(0,2))
            tabuleiro_substitui_celula(t,t_aux[0],cria_coordenada(0,1))
            tabuleiro_substitui_celula(t,tabuleiro_celula(t,cria_coordenada(1,1)),cria_coordenada(1,2))
            tabuleiro_substitui_celula(t,t_aux[1],cria_coordenada(1,1))
            tabuleiro_substitui_celula(t,tabuleiro_celula(t,cria_coordenada(2,2)),cria_coordenada(2,1))
            tabuleiro_substitui_celula(t,t_aux[2],cria_coordenada(2,2))
    return t

# ################## #
# Funcoes adicionais #
# ################## #


def hello_quantum(a):
    '''
    hello_quantum: cadeira de caracteres ---> logico
    Funcao principal do jogo que permite jogar um jogo completo de Hello Quantum!
    O argumento e uma cadeia de caracteres que contem a descricao do tabuleiro
    objetivo e o numero maximo de jogadas, separados por ':'. A funcao devolve
    verdadeiro se o jogador conseguir chegar ao tabuleiro objetivo no numero de
    jogadas ideais e false em caso contrario.
    '''
    t = a.split(':')[0] #Separa a cadeira de caracteres inserida no tabuleiro objetivo e no numero de jogadas maximas
    i = 0
    print('Bem-vindo ao Hello Quantum!\nO seu objetivo e chegar ao tabuleiro:')
    print(tabuleiro_para_str(str_para_tabuleiro(t)))
    print('Comecando com o tabuleiro que se segue:')
    print(tabuleiro_para_str(tabuleiro_inicial()))
    t1 = tabuleiro_inicial()
    while tabuleiro_para_str(t1) != tabuleiro_para_str(str_para_tabuleiro(t)): #Este while funciona enquant o tabuleiro inicial for diferente do tabuleiro objetivo
        i += 1 #Contador para o numero de jogadas
        if i > int(a.split(':')[1]): #Se o numero de jogadas for maior que o numero de jogadas ideais a funcao para pois ja nao vale a pena continuar
            break
        porta = str(input('Escolha uma porta para aplicar (X, Z ou H): '))
        lado = str(input('Escolha um qubit para analisar (E ou D): '))  
        if porta == 'X':
            if lado == 'E':
                t1 = porta_x(t1,'E')          
            else:
                t1 = porta_x(t1,'D')
        elif porta == 'Z':
            if lado == 'E':
                t1 = porta_z(t1,'E')
            else:
                t1 = porta_z(t1,'D')
        else:
            if lado == 'E':
                t1 = porta_h(t1,'E')
            else:
                t1 = porta_h(t1,'D')                
        print(tabuleiro_para_str(t1))
    if int(a.split(':')[1]) == i: #Verifica se o numero de jogadas foi o ideal e devolve um booleano
        print('Parabens, conseguiu converter o tabuleiro em',i,'jogadas!')
        return True
    else:
        return False

hello_quantum('((1, -1, 0), (-1, -1, -1), (-1, 1)):4')