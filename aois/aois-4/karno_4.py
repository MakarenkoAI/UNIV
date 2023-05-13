__hight = 4
__width = 4

def create_table(formula:list):
    row, column = __width, __hight
    table = [[0 for i in range(row)] for j in range(column)]
    spisok = create_list_interpret(formula) 
    rev_spisok=[]
    for el in spisok:  
        el = reverse(el)
        rev_spisok.append(el)

    for el in rev_spisok:
        x = coordinate(el[0], el[1])
        y = coordinate(el[2], el[3])
        table[x][y]=1
    return table

def coordinate(x:int,y:int):
    z = 0
    if x == 0 and y == 0:   z = 0
    if x == 0 and y == 1:   z = 1
    if x == 1 and y == 1:   z = 2
    if x == 1 and y == 0:   z = 3
    return z

def find_pairs(table):
    pairs=[]
    for i in range(len(table)):
        for j in range(len(table[i])):
            if table[i][j] == 1 and table[i][get_next(j, len(table[i]))] == 1: 
                pairs.append([i,j ,i,get_next(j, len(table[i]))]) 
    for j in range(len(table)):
        for i in range(len(table)):
            if i < 3: i_next = i+1
            if i == 3: i_next = 0
            if table[i][j] == 1 and table[i_next][j] == 1:  pairs.append([i,j, i_next,j]) 
    pairs = find_odd(pairs)
    implicants=[]
    for el in pairs: implicants.append(get_implicants(el))
    print_table(table, implicants)
    return implicants 

def print_table(table, implicants):
    print('A, B', end='')
    i = len(table) - 1
    while i >= 0:
        print('\n'+ str(i) + '|',end='  ')
        for j in range(len(table[i])):   print(table[i][j], end='  ')
        i = i -1
    print('\n - - - - - - - - -> \n   00-01-11-10    C,D')
    print('\n' , implicants)

def get_implicants(pair):
    formula=[]
    atom=['A','B','C','D']
    for index in range(len(pair)):
        if pair[index] == 0: formula.append(atom[index]+'v')
        if pair[index] == 1: formula.append('!'+ atom[index]+'v')
    formula = ''.join(formula)
    formula = formula[0:-1]
    return formula

def find_odd(pairs):
    A=[]
    for current in range(len(pairs)):
        conv_el = convert(pairs[current])
        amount = 0
        index = -1
        for i in range(4):
            if conv_el[i] != conv_el[i+4]: 
                amount += 1
                index = i
        if amount == 1 and index != -1:
            conv_el[index] = -1
            answer = conv_el[0:4]
            A.append(answer)
    return A
   
def convert(pair):
    answer:list=[]  
    for el in pair:
        if el == 0:
            answer.append(0)
            answer.append(0)
        if el == 1:
            answer.append(0)
            answer.append(1)
        if el == 2:
            answer.append(1)
            answer.append(1)
        if el == 3:
            answer.append(1)
            answer.append(0)
    return answer

def get_next(i, len):
    if i + 1 == len:  return 0
    else: return i+1 

def reverse(list:list):
    answer=[]
    for item in list:
        if item == 0: answer.append(1)
        if item == 1: answer.append(0)
        if item == -1:  answer.append(-1)
    return answer

def create_list_interpret(formula:str):
    answer=[]
    for el in formula:  answer.append(create_interpret(el))
    return answer

def create_interpret(str:str):
    answer:list=[]
    if not 'A' in str: answer.append(-1)
    else:
        answer.append(0) if '!A' in str  else answer.append(1)
    if not 'B' in str: answer.append(-1)
    else:
        answer.append(0) if '!B' in str  else answer.append(1)
    if not 'C' in str: answer.append(-1)
    else:
        answer.append(0) if '!C' in str  else answer.append(1)
    if not 'D' in str: answer.append(-1)
    else:
        answer.append(0) if '!D' in str  else answer.append(1)
    
    return answer

def bonding(formula):
    list_interpret=[]
    for el in formula:
        list_interpret.append(create_interpret(el))
    return 0 


def SKNF(interpret:list, result:list, size:int):
	sknf:list = []
	for index in range(len(result)):
		if result[index] == '0':
			sknf.append("(")
			if interpret[index][0] == '1':
					sknf.append('!A' + "v")
			else:	sknf.append('A' + "v")
			if interpret[index][1] == '1':
					sknf.append('!B' + "v")
			else:	sknf.append('B' + "v")
			if interpret[index][2] == '1':
					sknf.append('!Cv')
			else:	sknf.append('Cv')
			if interpret[index][3] == '1':
					sknf.append('!D')
			else:	sknf.append('D')
			sknf.append(")&")
	
	var:str = ''.join(sknf)
	if var[-1] == '&':
		var = var[:-1]
	return var
