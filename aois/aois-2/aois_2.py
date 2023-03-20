# БГУИР, гр 121701, Макаренко А.И. 
# Лаборатораная работа №2 (АОИС) 
# Описание: преобразование вводимой логической формулы в СКНФ и СДНФ 
# Примеры вводимых формул: 
                    #      ((!A)v(B>C))
                    #      ((A~B)&C)
                    #      (((A&(!B))v(!A))>C) 

import subformula as sub

function:str = input("Input tne formula\n")

sub.get_list_of_atoms(function)
sub.create_interpretation()
sub.transform_formula(function)
sub.solution()

print("\nResult is\n")
sub.get_info()

print("\nSDNF is\n")
sub.SDNF()

print("\nSKNF is\n")
sub.SKNF()