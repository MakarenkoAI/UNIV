def sdnf(interpret:list, result:list):
	sdnf:list = []
	for index in range(len(result)):
		if result[index] == '1':
			sdnf.append(generate_atom_from_digit(interpret[index]))
	var:str = ''.join(sdnf)
	print(var)
	return var

def generate_atom_from_digit(list:str):
	atoms = 'ABCDEFG'
	answer='('
	for i in range(len(list)):
		if list[i] == '0': answer = answer+'!'+atoms[i]+'&'
		else: answer = answer+atoms[i]+'&'
	return answer[:-1]+')'

def plus_lists(list1:list,list2:list):
	for i in range(len(list1)):
		list1[i] = list1[i] + list2[i]
	return list1

def take_index_list(list:list, index:int):
	answer=[]
	for i in range(len(list)):
		answer.append(list[i][index])
	return answer

def make_sdnf(interpret, all_result):
	answer=[]
	for i in range(len(all_result[0])):
		result = take_index_list(all_result,i)
		print('SDNF ' + 'H'+str(i+1))
		answer.append(sdnf(interpret, result))
	return answer
	
