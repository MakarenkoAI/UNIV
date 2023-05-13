def able_to_bonding(first_keys:list, second_keys:list):
    matches:int = 0
    compare = len(first_keys)-1
    for index in range(len(first_keys)):
        if first_keys[index] == second_keys[index]:
            matches = matches + 1
    return matches == compare
   
def separate(formula:str):
    index:int = 0
    values:list=[]
    while index < len(formula):
        if formula[index] == '(':
            index_next:int = index+1
            while index_next < len(formula) and not formula[index_next] == '(':
                index_next = index_next + 1
            if formula[index_next-1] == 'v' or formula[index_next-1] == '&':
                index_next = index_next - 1
            values.append(formula[index+1: index_next-1])
        index = index+ 1
    return values

def bonding(values:list, in_s:str):
    bond_list:list=[]
    index:int = 0
    while index < len(values):
        keys_1:list = define_keys(values[index])
        index_next = index + 1
        while index_next < len(values):
            keys_2:list = define_keys(values[index_next])
            if able_to_bonding(keys_1, keys_2):
                bond_list.append(merge(keys_1, keys_2, in_s))
            index_next = index_next + 1
        index = index + 1
   
    return bond_list

def define_keys(sub:str):
    keys:list=[]
    index:int = 0
    while index < len(sub):
        if sub[index] == '!':
            keys.append(0)
            index = index + 3
        else:
            keys.append(1)
            index = index + 2
    return keys

def merge(sub_1:str, sub_2:str, in_s:str):
    letters:list = ['A', 'B', 'C', 'D','E']
    new_key=''
    for el in range(len(sub_1)):
        if sub_1[el] == sub_2[el]:
            if sub_1[el] == 1:
                new_key = new_key + letters[el] + in_s
            if sub_1[el] == 0:
                new_key = new_key + '!' + letters[el] + in_s
    new_key = new_key[:-1]
    return new_key

def create_visited(list:list):
    visited=[]
    index = 0
    while index < len(list):
        visited.append(0)
        index +=1
    return visited

def step_three(pairs:list, in_s:str):    
    answer=[]
    
    visited:list=create_visited(pairs)
    answer,visited=create_new(answer,pairs, visited, in_s)
    answer =  del_dublicate(answer) 
    rest = add_rest(visited,pairs,[])
  
    if len(answer)>1:
        visited:list=create_visited(answer)
        old = answer
        answer,visited=create_new([],answer, visited, in_s)
        rest = add_rest(visited,old,rest)
        answer =  del_dublicate(answer) 

   
    if len(answer)>1:
        old = answer
        visited:list=create_visited(answer)
        answer,visited=create_new([],answer, visited, in_s)
        rest = add_rest(visited,old,rest)
        answer =  del_dublicate(answer) 

    answer = add_list(answer,rest)
    answer =  del_dublicate(answer) 

    return answer

def add_list(l1,l2):
    for el in l2:  l1.append(el)
    return l1

def add_rest(visited, answer,rest):
    for i in range(len(visited)):
        if visited[i] == 0: rest.append(answer[i])
    return rest

def create_new(answer, pairs, visited, in_s):
    current = 0
    while current < len(pairs):
        next = current + 1 
        while next < len(pairs):
            if not visited[current] == 1 and not visited[next] == 1:
                result = step_three_verification(pairs[current], pairs[next], in_s)
                if not result == '':
                    answer.append(result)
                    visited[current] = 1
                    visited[next] = 1
            next +=1
        current +=1
    return answer, visited

def del_odd(answer, pairs, visited, in_s):
    current = 0
    while current < len(pairs):
        next = current + 1 
        while next < len(pairs):                    
            if not visited[current] == -1 and not visited[next] == -1:
                result = step_three_verification(pairs[current], pairs[next], in_s)
                if result != '':
                    visited[current]=-1
                    visited[next]=-1
            next +=1
        current +=1
    return answer,visited

def add_zero(list:list, visited:list, answer:list):
    current = 0
    while current < len(list):
        if visited[current] == 0:
            answer.append(list[current])
        current += 1 
    return answer

def del_dublicate(list):
    list2=[]
    for item in list:
        if item not in list2:
            list2.append(item)
    return list2

def step_three_verification(arg1:str, arg2:str, symbol):
    abc1=define_abc(arg1)
    abc2=define_abc(arg2)
    impl_1:list=get_implicants(arg1)
    impl_2:list=get_implicants(arg2)
    if abc1 == abc2:  
        return try_to_bond_similiar(impl_1, impl_2)
    return ''


def get_odd_index(impl1:list,impl2:list):
    index = -1
    check = 0
    for i in range(len(impl1)):
        if impl1[i]!=impl2[i]:
            index = i
            check+=1
    if check == 1: return index
    else: return -1


def try_to_bond_similiar(impl1:list,impl2:list):
    same=''
    index = get_odd_index(impl1,impl2)
    if index != -1:
        impl=impl1
        impl[index] = -1
        same = in_abc(impl)
    return same
   
def define_abc(str:list):
    atom=['A','B','C','D','E']
    answer:list=[]
    for el in atom:
        if  not el in str: answer.append(0)
        else: answer.append(1)
    return answer

def get_implicants(formula:str):
    atom=['A','B','C','D','E']
    answer:list=[]
    for el in atom:
        if  not el in formula: answer.append(-1)
        else: answer.append(0) if  '!'+el in formula else answer.append(1)
    return answer

def in_abc(formula:str):
    atom=['A','B','C','D','E']
    answer:list=[]
    for i in range(len(formula)):
        if formula[i] == 0: answer.append('!'+atom[i]+'&')
        if formula[i] == 1: answer.append(atom[i]+'&') 
    answer=''.join(answer)
    return answer[:-1]