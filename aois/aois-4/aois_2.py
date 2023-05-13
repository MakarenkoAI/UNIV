import subformula as sub
import cutting as cut
import karno_4 as k
import trying as tr
# Task 1
#(AvBvC)&(AvBv!C)&(Av!BvC)&(!AvBvC)
#(AvBvC)&(Av!Bv!C)&(!Av!BvC)&(!AvBv!C)
# Task 2
#(AvBvC)&(AvBv!C)&(Av!BvC)&(!AvBvC)
#(AvBvC)&(Av!Bv!C)&(!Av!BvC)&(!AvBv!C)
#table, q, s = cut.truth_first()
#sknf:str = sub.SKNF(table, q)
#sknf:str = sub.SKNF(table, s)
#AvB,Av!B,
def func1():
    table, q, s = cut.truth_first()
    sknf:str = sub.SKNF(table, q)

    print('\nСКНФ(Q):',sknf)
    b= cut.separate(sknf)
    t=cut.step_three(cut.bonding(b, '&','v'),'&')
    print(t)
   
    sknf:str = sub.SKNF(table, s)
    print('\nСКНФ(S):',sknf)
    b= cut.separate(sknf)
    print(cut.step_three(cut.bonding(b, '&','v'),'&'))
    
def func2():
    print('\nТаблица истинности:')
    table, y1,y2,y3,y4 = cut.truth_second()
    loop = [y1,y2,y3,y4]

    for i in range(len(loop)):
        sknf:str = k.SKNF(table, loop[i], 4)
        print('\nСКНФ'+ str(i+1),sknf)
        sep_sknf = cut.separate(sknf)
        k.find_pairs(k.create_table(sep_sknf))
        t=tr.step_three(sep_sknf,'v')
        print(t)
 
func1()
func2()