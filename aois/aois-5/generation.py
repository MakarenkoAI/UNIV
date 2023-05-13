def generate_double(x:int, number_atoms:int):
    if x < 0: return '1111'
    rez=bin(x)[2:]
    while len(rez) < number_atoms: 
        rez = '0' + rez
    return rez

def generate_interpretation_list(number_atoms:int):
    answer:list=[]
    for el in range(2**number_atoms):
        answer.append(generate_double(int(el),number_atoms))
    return answer

def generate_V(number_atoms:int, value:int):
    answer:list=[]
    for _ in range(2**number_atoms):
        answer.append(str(value))
    return answer

def generate_Q(number_atoms:int, diff:int):
    answer:list=[]
    for el in range(2**number_atoms):
        answer.append(generate_double(int(el)- diff,number_atoms))
    return answer

def generate_H(list1:list, list2:list):
    answer:list=[]
    word:str=''
    for i in range(len(list1)):
        for j in range(len(list1[i])):
           if list1[i][j] != list2[i][j]: word = word + '1'
           else: word = word + '0'
        answer.append(word)
        word=''
    return answer

def print_truth_table(content):
    print('Qi*', 'V', 'Qi','H1','|', 'V', 'Qi','H2',sep='\t')
    for el in range(len(content[0])): 
        print(content[0][el], content[1][el], content[2][el], content[3][el], '|', content[4][el], content[5][el],content[6][el],sep='\t')

def generate(number_atoms, diff):
    R = generate_interpretation_list(number_atoms)
    Q = generate_Q(number_atoms,diff)
    H1 = generate_H(R,R)
    H2 = generate_H(R,Q)
    Vzero = generate_V(number_atoms,0)
    Vone = generate_V(number_atoms,1)
    print_truth_table([R,Vzero,R,H1,Vone,Q,H2])
    return [R,Vzero,R,H1,Vone,Q,H2]
 