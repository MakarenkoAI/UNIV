//////////////////////////////////////////////////////////////////////////////////////////////////////
// 
// Лабораторная работа №1 по дисциплине ЛОИС
// Выполнена студентами гр. 121701 БГУИР Макаренко А. И., Корсаковой С. К.
// Определяет количество подформул заданного уровня в формуле сокращенного языка логики высказываний.
// 11.03.2023
// 
//////////////////////////////////////////////////////////////////////////////////////////////////////
// 
// Шаблоны для ввода:
//
// ((A/\A)~(B\/B))
// (((A\/A)~(!B))/\D)
// ((A/\A)~B)
// ((((A\/B)~(!C))/\((C/\D)~(A/\B)))/\((F/\A)~(!C)))
// ((((A/\B)\/(B\/C))/\((!C)\/((1\/A)\/(B->C))))/\((!D)->(Q/\A)))
// 
/////////////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <vector>
#include <string>
#include "subformula.h"
#include "verification_of_formula.h"
using namespace std;

typedef pair <int, int> index;

int main()
{
	vector<pair<int, index>> data; //хранит в себе 1) уровень формулы 2) индекс ( в строке формулы 3) индекс )
	string input;//для строки формулы

	cout << "\nInput the formula\n";
	cin >> input;
	cout << '\n';

	if (verify(input)) {
		vector<int> helping(input.size());//вспомогательный вектор, соответсвует длине строки формулы
		for (int i = 0; i < input.size(); i++)
			helping[i] = 0;

		added_zero_level(data, input); //добавляет все атомарные формулы

		int number_of_brackets = get_number_of_brackets(input);//получаем количество скобок в строке формулы

		fulfill_data(data, number_of_brackets, input, helping);//ищем все подформулы в строке формулы, кроме атомарных

		print_data(data, input);//выводим все подформулы и их уровни

		int level;//вводим необходимый уровень
		cout << "\nInput the nessesary level of subformula: ";
		cin >> level;

		int number_of_subformulas = get_number_of_subformulas(level, data);//считает количество подформул с необходимым уровнем
		cout << "Number of subformulas with the " << level << " level is " << number_of_subformulas << "\n ";

	}
	else cout << "Try again\n";
}