 # Алвафит для вводимых формул 
abc:list = ['A', 'B', 'C', 'D','E', 'F', 'G', 'H', 'I', 'J', 'K', 'L',
			'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z']


# Символы для логических операций 
connective:list = [ "&", "v", ">", "(", ")", "~", "!"]

# Список для псевдоэлементарных подформул и формул
data:list = []

# Список для всех интерпретаций атомарных формул 
interpretation:list = []

# Список уникальных атомарных формул #
atoms:list = []

# Список для промежуточных и итоговой таблиц истинности подформул #
answer:list = []

def equality_abc(el:str):
	# Проверяет соответствие элемента алфавиту #
	for atom in abc:
		if el == atom: return True
	return False

def get_list_of_atoms(formula:str):
	# Возращает список атомарных уникальных подформул формулы #
	global atoms
	for el in formula:
		if equality_abc(el): atoms.append(el)

	atoms = sorted(list(set(atoms)))
	return atoms

def create_interpretation():
	# Заполнение списка интерпретаций атомарных подформул #
	global interpretation
	global atoms

	interpretation.append(atoms)
	for index in range(2 ** len(atoms)):
		interpretation.append(format(index, 'b'))

	interpretation = fix_interpretation(len(atoms))
	return interpretation

def fix_interpretation(size:int):
	# Корректирование интерпретации #
	global interpretation
	for index, el in enumerate(interpretation):
		if not len(el) == size:
			addition = '0' * (size - len(el))
			interpretation[index] = addition + el

	return interpretation

def transform_formula(formula:str):
	# Разбиение формулы на (псевдо)элементарные подформулы #
	iteration_number:int = get_number_of_brackets(formula) + 1
	while iteration_number:
		for index, el in enumerate(formula):
			if el == '(':
				index_close = find_close_bracket(formula, index)
				if index_close:
					subformula:str = formula[index:index_close]
					subformula += ')'
					data.append(subformula)
					formula = formula.replace(subformula, str(len(data)), 1)
					break
		iteration_number -=1

def find_close_bracket(formula:str, index_open_bracket:int):
	# Находит индекс первой закрывающейся скобки после открывающейся #
	for index in range(index_open_bracket+1, len(formula)):
		if formula[index] == '(': return 0
		if formula[index] == ')': return index
	return False

def get_number_of_brackets(formula:str):
	result:int = 0
	for el in formula:
		if el == '(': result+=1
	return result

def solution():
	# Заполнение таблиц истинности для каждой подформулы #
	global data
	global answer
	for el in data:
		first_list:list = []
		second_list:list = []
		temp_answer:list = []
		if el[1] == '!':  # Для унарной операции
			if equality_abc(el[2]): # Если элементарная формула
				index_atom = atoms.index(el[2])
				first_list = get_list_of_atom_value(index_atom)
			elif el[2].isdigit(): # Если псевдоэлементарная формула
				index_atom = int(el[2])
				first_list = answer[index_atom - 1]

			for el_ in range(len(first_list)):
				temp_answer.append(solve(int(first_list[el_]), '!')) # сохраняем таблицу истинности для подформулы
			answer.append(temp_answer)
		else:# Для бинарных операций
			if equality_abc(el[1]):#Если элементарная формула
				index_atom = atoms.index(el[1])
				first_list = get_list_of_atom_value(index_atom)
			elif el[1].isdigit():# Если псевдоэлементарная формула
				index_atom = int(el[1])
				first_list = answer[index_atom - 1]
					
			if equality_abc(el[3]):#Если элементарная формула
				index_atom = atoms.index(el[3])
				second_list = get_list_of_atom_value(index_atom)
			elif el[3].isdigit():#Если псевдоэлементарная формула
				index_atom = int(el[3]) 
				second_list = answer[index_atom - 1]

			for el_ in range(len(first_list)):
				temp_answer.append(solve(int(first_list[el_]), el[2], int(second_list[el_])))# сохраняем таблицу истинности для подформулы
			answer.append(temp_answer)
			

def solve(first:int, connection:str, second:int = 0):
	# Возращает решение операции #
	if connection == '~': return first == second
	if connection == '>': 
		if first == 1 and second == 0:
				return 0 
		else: 
				return 1
	if connection == '&': return first & second
	if connection == 'v': return first or second
	if connection == '!': return not first

def get_list_of_atom_value(index:int):
	# Возращает интерпретацию определенной атомарной формулы #
	global interpretation
	result:list = []
	for el in range(1, len(interpretation)):
		result.append(interpretation[el][index])
	return result

def SKNF():
	global interpretation
	global atoms
	result:list = answer[len(answer) - 1]
	sknf:list = []
	for index in range(len(result)):
		if result[index] == 0:
			sknf.append("(")
			numbers:str = interpretation[index+1]
			print(int(numbers, 2), '&')
			for ind,atom in enumerate(numbers):
				if atom == '1' and not ind == len(numbers) - 1:
					sknf.append('(!' + atoms[ind] + ")v")
				if atom == '1' and ind == len(numbers) - 1:
					sknf.append('(!' + atoms[ind] + ")")
				if atom == '0' and not ind == len(numbers) - 1:
					sknf.append(atoms[ind] + "v")
				if atom == '0' and ind == len(numbers) - 1:
					sknf.append(atoms[ind])
			if index == len(result) - 1:
				sknf.append(")")
			if not index == len(result) - 1:
				sknf.append(")&\n")
	var:str = ''.join(sknf)
	if var[-1] == '&':
		var = var[:-1]
	print(var)

def SDNF():
	global interpretation
	global atoms
	result:list = answer[len(answer) - 1]
	sdnf:list = []
	for index in range(len(result)):
		if result[index] == 1:
			sdnf.append("(")
			numbers:str = interpretation[index+1]
			print(int(numbers, 2), 'v')
			for ind,atom in enumerate(numbers):
				if atom == '0' and ind < len(numbers) - 1:
					sdnf.append('(!' + atoms[ind] + ")&")
				if atom == '0' and ind == len(numbers) - 1:
					sdnf.append('(!' + atoms[ind] + ")")
				if atom == '1' and  ind < len(numbers) - 1:
					sdnf.append(atoms[ind] + "&")
				if atom == '1' and ind == len(numbers) - 1:
					sdnf.append(atoms[ind])
			if index == len(result) - 1:
				sdnf.append(")")
			if not index == len(result) - 1:
				sdnf.append(")v\n")
	var:str = ''.join(sdnf)
	if var[-1] == 'v':
		var = var[:-1]
	print(var)

def get_info():
	global interpretation
	global answer
	print(interpretation[0])
	for el in range(len(answer)):
		print(data[el], answer[el], sep='\t')

	buf:str = ''.join(map(str, answer[-1]))
	result:int = int(buf, 2)
	print(result)
	
