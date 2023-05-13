import generation as g
import sdnf
import cutting as cut

def min(formula:str, number:int):
    rez = cut.separate(formula)
    rez = cut.bonding(rez, '&')
    rez = cut.step_three(rez,'&')
    print('TSDNF H'+str(number),rez,sep=' ')
    return rez

def all_min(formula:list):
    for i in range(len(formula)):   min(formula[i], int(i)+1)

content = g.generate(4,1)

interpret = sdnf.plus_lists(content[0], content[4])
result = content[6]
formula:list = sdnf.make_sdnf(interpret,result)
all_min(formula)




