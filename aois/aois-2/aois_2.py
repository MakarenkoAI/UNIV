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

#((!A)v(B>C))
#((A~B)&C)
#(((A&B)v(!Q))>C)