def eh_tabuleiro(t):
    if isinstance(t, tuple) and len(t) == 3 and type(t[0]) == tuple and type(t[1]) == tuple and type(t[2]) == tuple:
        if len(t[0]) == 3 and len(t[1]) == 3 and len(t[2]) == 2:   
            for i in range(len(t)):
                for el in t[i]:
                    if isinstance(t[i], tuple) == False:
                        return False
                    if (el != 1 and el != 0 and el != -1):    
                        return False   
            return True
    return False
       
def tabuleiro_str(t):
    if not eh_tabuleiro(t) == True:
        raise ValueError('tabuleiro_str: argumento invalido')
    else:
        lista1 = []
        for i in range(len(t)):
            for el in t[i]:
                if (el == 1):
                    lista1.append(1)
                if (el == 0):
                    lista1.append(0)
                if (el == -1):
                    lista1.append('x')
    return ('+-------+\n|...' + str(lista1[2]) + '...|\n|..' + str(lista1[1]) + '.' + str(lista1[5]) + '..|\n|.' + str(lista1[0]) + '.' + str(lista1[4]) + '.' + str(lista1[7]) + '.|\n|..' + str(lista1[3]) + '.' + str(lista1[6]) + '..|\n+-------+')

def tabuleiros_iguais(t1, t2):
    if eh_tabuleiro(t1) == False or eh_tabuleiro(t2) == False:
        raise ValueError('tabuleiros_iguais: um dos argumentos nao e tabuleiro')
    else:
        return t1 == t2

def porta_x(t, lado):
    if not (eh_tabuleiro(t) == True and (lado == 'E' or lado == 'D')):
        raise ValueError('porta_x: um dos argumentos e invalido')
    listac = [[-1,-1,-1],[-1,-1,-1],[-1,-1]]
    if lado == 'D':        
        listac[0][0] = t[0][0]
        listac[0][2] = t[0][2]
        listac[1][0] = t[1][0]
        listac[1][2] = t[1][2]
        listac[2][1] = t[2][1]        
        for i in range(len(t)):
            for el in t[i]:
                if t[2][0] == 1:
                    listac[2][0] = 0
                if t[2][0] == 0:
                    listac[2][0] = 1
                if t[1][1] == 1:
                    listac[1][1] = 0
                if t[1][1] == 0:
                    listac[1][1] = 1
                if t[0][1] == 1:
                    listac[0][1] = 0
                if t[0][1] == 0:
                    listac[0][1] = 1
    if lado == 'E':
        listac[0][0] = t[0][0]
        listac[0][1] = t[0][1]
        listac[0][2] = t[0][2]
        listac[2][0] = t[2][0]
        listac[2][1] = t[2][1]
        for i in range(len(t)):
            for el in t[i]:
                if t[1][0] == 1:
                    listac[1][0] = 0
                if t[1][0] == 0:
                    listac[1][0] = 1
                if t[1][1] == 1:
                    listac[1][1] = 0
                if t[1][1] == 0:
                    listac[1][1] = 1
                if t[1][2] == 1:
                    listac[1][2] = 0
                if t[1][2] == 0:
                    listac[1][2] = 1
                    
    return (tuple(listac[0]), tuple(listac[1]), tuple(listac[2]))

def porta_z(t, lado):
    if not (eh_tabuleiro(t) == True and (lado == 'E' or lado == 'D')):
        raise ValueError('porta_z: um dos argumentos e invalido')
    listac = [[-1,-1,-1],[-1,-1,-1],[-1,-1]]
    if lado == 'D':        
        listac[0][0] = t[0][0]
        listac[0][1] = t[0][1]
        listac[1][0] = t[1][0]
        listac[1][1] = t[1][1]
        listac[2][0] = t[2][0]        
        for i in range(len(t)):
            for el in t[i]:
                if t[2][1] == 1:
                    listac[2][1] = 0
                if t[2][1] == 0:
                    listac[2][1] = 1
                if t[1][2] == 1:
                    listac[1][2] = 0
                if t[1][2] == 0:
                    listac[1][2] = 1
                if t[0][2] == 1:
                    listac[0][2] = 0           
                if t[0][2] == 0:
                    listac[0][2] = 1
    if lado == 'E':
        listac[1][0] = t[1][0]
        listac[1][1] = t[1][1]
        listac[1][2] = t[1][2]
        listac[2][0] = t[2][0]
        listac[2][1] = t[2][1]
        for i in range(len(t)):
            for el in t[i]:
                if t[0][0] == 1:
                    listac[0][0] = 0
                if t[0][0] == 0:
                    listac[0][0] = 1
                if t[0][1] == 1:
                    listac[0][1] = 0
                if t[0][1] == 0:
                    listac[0][1] = 1
                if t[0][2] == 1:
                    listac[0][2] = 0
                if t[0][2] == 0:
                    listac[0][2] = 1
                    
    return (tuple(listac[0]), tuple(listac[1]), tuple(listac[2]))

def porta_h(t, lado):
    if not (eh_tabuleiro(t) == True and (lado == 'E' or lado == 'D')):
        raise ValueError('porta_h: um dos argumentos e invalido')
    listac = [[-1,-1,-1],[-1,-1,-1],[-1,-1]]
    if lado == 'D':        
        listac[0][0] = t[0][0]
        listac[1][0] = t[1][0]        
        for i in range(len(t)):
            for el in t[i]:
                if t[0][1] == 1:
                    listac[0][2] = 1
                if t[0][1] == 0:
                    listac[0][2] = 0
                if t[0][2] == 1:
                    listac[0][1] = 1
                if t[0][2] == 0:
                    listac[0][1] = 0
                if t[1][1] == 1:
                    listac[1][2] = 1
                if t[1][1] == 0:
                    listac[1][2] = 0
                if t[1][2] == 1:
                    listac[1][1] = 1
                if t[1][2] == 0:
                    listac[1][1] = 0
                if t[2][0] == 1:
                    listac[2][1] = 1
                if t[2][0] == 0:
                    listac[2][1] = 0
                if t[2][1] == 1:
                    listac[2][0] = 1
                if t[2][1] == 0:
                    listac[2][0] = 0                    
    if lado == 'E':
        listac[2][0] = t[2][0]
        listac[2][1] = t[2][1]
        for i in range(len(t)):
            for el in t[i]:
                if t[0][0] == 1:
                    listac[1][0] = 1
                if t[0][0] == 0:
                    listac[1][0] = 0
                if t[1][0] == 1:
                    listac[0][0] = 1
                if t[1][0] == 0:
                    listac[0][0] = 0
                if t[0][1] == 1:
                    listac[1][1] = 1
                if t[0][1] == 0:
                    listac[1][1] = 0
                if t[1][1] == 1:
                    listac[0][1] = 1
                if t[1][1] == 0:
                    listac[0][1] = 0
                if t[0][2] == 1:
                    listac[1][2] = 1
                if t[0][2] == 0:
                    listac[1][2] = 0
                if t[1][2] == 1:
                    listac[0][2] = 1
                if t[1][2] == 0:
                    listac[0][2] = 0 
                    
    return (tuple(listac[0]), tuple(listac[1]), tuple(listac[2]))
