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

def bonding(values:list, in_s:str, out_s:str):
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
    letters:list = ['A', 'B', 'C', 'D']
    new_key=''
    for el in range(len(sub_1)):
        if sub_1[el] == sub_2[el]:
            if sub_1[el] == 1:
                new_key = new_key + letters[el] + in_s
            if sub_1[el] == 0:
                new_key = new_key + '!' + letters[el] + in_s
    new_key = new_key[:-1]
    return new_key
##
def delete_link(list:list, symbol):
    return list

def delete_link(list:list, symbol):
    return list

def create_visited(list:list):
    visited=[]
    index = 0
    while index < len(list):
        visited.append(0)
        index +=1
    return visited

def sub_spisok(pairs:list):
    answer1=[]
    answer2=[]
    answer3=[]
    for el in pairs:
        counter=0
        if 'A' in el: counter+=1
        if 'B' in el: counter+=1
        if 'C' in el: counter+=1
        if counter == 2:
            answer2.append(el)
        if counter == 1:
            answer1.append(el)
        if counter == 3:
            answer3.append(el)
    return [answer1, answer2, answer3]

def step_three(pairs:list, symbol:str):
    pairs = delete_link(pairs, symbol)
    if symbol == 'v': in_s = '&'
    else: in_s = 'v'
    separation = sub_spisok(pairs)
    pairs = separation[1]
    visited:list=create_visited(pairs)
    answer=[]
    answer,visited=create_new(answer,pairs, visited, in_s)
    
    answer,visited=del_odd(answer, pairs, visited, in_s)

    answer = add_zero(pairs, visited, answer)
    answer =  del_dublicate(answer) + separation[0] + separation[2]
    return answer

def create_new(answer, pairs, visited, in_s):
    current = 0
    while current < len(pairs):
        next = current + 1 
        while next < len(pairs):
            if not visited[current] == 1 and not visited[next] == 1:
                result = step_three_verification(pairs[current], pairs[next], in_s)
                if not result[0][0] == '':
                    if result[1] == 1:
                        visited[current] = 1
                        visited[next] = 1
                        answer.append(result[0][0])
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
                visited = del_odd_checking(result, pairs, visited)
            next +=1
        current +=1
    return answer,visited

def del_odd_checking(result, pairs, visited):
    if not result[0][0] == '':
        if result[1] == 0:
            if result[0][0] in pairs:
                i = pairs.index(result[0][0])
                visited[i] = -1
            if result[0][1] in pairs:
                i = pairs.index(result[0][1])
                visited[i] = -1
    return visited

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
        return [try_to_bond_similiar(impl_1, impl_2), 1]
    else:
        return [try_to_bond(impl_1, impl_2, symbol), 0]
    
def try_to_bond(impl1:list,impl2:list, in_s):
    if len(impl1[0]) == 2:
        oppos_impl = impl1[0][1]
        if oppos_impl in impl2:
                new1 = impl1[1]
                new2 = impl2[0] if not oppos_impl == impl2[0] else impl2[1]
                return [new1+in_s+new2, new2+in_s+new1]
    elif len(impl1[0]) == 1:
        oppos_impl = '!' + impl1[0]
        if oppos_impl in impl2:
            new1 = impl1[1]
            new2 = impl2[0] if not oppos_impl == impl2[0] else impl2[1]
            return [new1+in_s+new2, new2+in_s+new1]
    if len(impl1[1]) == 2:
        oppos_impl = impl1[1][1]
        if oppos_impl in impl2:
            new1 = impl1[0]
            new2 = impl2[0] if not oppos_impl == impl2[0] else impl2[1]
            return [new1+in_s+new2, new2+in_s+new1]
    elif len(impl1[1]) == 1:
        oppos_impl = '!' + impl1[1]
        if oppos_impl in impl2:
            new1 = impl1[0]
            new2 = impl2[0] if not oppos_impl == impl2[0] else impl2[1]
            return [new1+in_s+new2, new2+in_s+new1]
    return ['','']

def try_to_bond_similiar(impl1:list,impl2:list):
    same=''
    if len(impl1[0]) == 2:
        oppos_impl = impl1[0][1]
        if oppos_impl in impl2:
            if impl1[1] in impl2:
                same = impl1[1]
                return [same, same]
    elif len(impl1[0]) == 1:
        oppos_impl = '!' + impl1[0]
        if oppos_impl in impl2:
            if impl1[1] in impl2:
                same = impl1[1]
                return [same, same]
    if len(impl1[1]) == 2:
        oppos_impl = impl1[1][1]
        if oppos_impl in impl2:
            if impl1[0] in impl2:
                same = impl1[0]
                return [same, same]
    elif len(impl1[1]) == 1:
        oppos_impl = '!' + impl1[1]
        if oppos_impl in impl2:
            if impl1[0] in impl2:
                same = impl1[0]
                return [same, same]
    return [same, same]
   
def define_abc(str:list):
    answer:list=[]
    answer.append(1) if 'A' in str  else answer.append(0)
    answer.append(1) if 'B' in str  else answer.append(0)
    answer.append(1) if 'C' in str  else answer.append(0)
    return answer

def get_implicants(formula:str):
    answer=[]
    abc_list=['A','B','C']
    for el in abc_list:
        if '!' + el in formula:
            answer.append('!'+el)
        if el  in formula and not '!'+el in formula:
            answer.append(el)
    return answer

def truth_first():
    table=[
        ['0','0','0'],        ['0','0','1'],
        ['0','1','0'],        ['0','1','1'],
        ['1','0','0'],        ['1','0','1'],
        ['1','1','0'],        ['1','1','1']    
    ]
    q = [ '0','0', '0', '1', '0',  '1',  '1',  '1' ]
    s = ['0','1','1','0','1','0','0','1']
    print('  X', '   Y', '    P', '  Q', ' S', sep=' ')
    for i in range(len(table)):
        print(table[i], q[i], s[i], sep='  ')
    return table, q,s

def truth_second():
    table=[
        ['0','0','0','0'],  ['0','0','0','1'], ['0','0','1','0'],
        ['0','0','1','1'],  ['0','1','0','0'], ['0','1','0','1'],
        ['0','1','1','0'],  ['0','1','1','1'], ['1','0','0','0'],
        ['1','0','0','1'],  ['1','0','1','0'], ['1','0','1','1']
      #  ['1','1','0','0'],  ['1','1','0','1'], ['1','1','1','0'],
      #  ['1','1','1','1']
            
    ]
    y1 = ['0','0','0','0','1','1','1','1','1','1','1','1']
    y2 = ['1','1','1','1','0','0','0','0','1','1','1','1']
    y3 = ['0','0','1','1','0','0','1','1','0','0','1','1']
    y4 = ['0','1','0','1','0','1','0','1','0','1','0','1']
    print(' X1', '  X2', '  X3', '  X4', '  Y1','Y2','Y3','Y4', sep=' ')
    for i in range(len(table)):
        print(table[i], y1[i], y2[i],y3[i],y4[i], sep='  ')
    return table, y1,y2,y3,y4