#pragma once

#pragma once

#include <iostream>
#include <vector>
#include <string>
#include "subformula.h"
using namespace std;

const char const_atom = 'A';

const vector<char> atom_formula{ '0', '1', 'A', 'B', 'C', 'D','E', 'F', 'G', 'H', 'I', 'J', 'K', 'L',
							'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };

const vector<string> connective{ "/\\", "\\/", "->", "(", ")", "~", "!" };

bool check_symbols(string formula);
bool syntax(string formula);

bool verify(string formula) {
	if (check_symbols(formula) && syntax(formula))//если синтаксис и атомы корректные
		return true;
	return false;
}

bool check_atom(string formula, int index) {
	for (int i = 0; i < atom_formula.size(); i++)
		if (formula[index] == atom_formula[i])//если совпадает
			return true;
	return false;
}

pair<bool, bool> check_connective(string formula, int index) {
	if ((index + 1) < formula.size()) {//следующие символы не могут стоять в самом конце строки
		if (formula[index] == '/' && formula[index + 1] == '\\')//для конъюкции, занимает два символа
			return { true, 1 };
		if (formula[index] == '\\' && formula[index + 1] == '/')//для дизъюнкции, занимает два символа
			return { true, 1 };
		if (formula[index] == '-' && formula[index + 1] == '>')//для импликации, занимает два символа
			return { true, 1 };
		if (formula[index] == '~' || formula[index] == '(' || formula[index] == '!')//для связок ии (, занимающих один символ
			return { true, 0 };
	}
	if (formula[index] == ')')//символ, которые может быть в конце строки
		return { true, 0 };//занимает один символ
	return { false, 0 };//неккоректная связка
}

bool check_symbols(string formula) {
	for (int i = 0; i < formula.size(); i++) {

		pair< bool, bool> connective = check_connective(formula, i);//сохраняем данные о связке (если она существует, 1 - занимает 2 символа ; 0 - один символ

		if (!check_atom(formula, i) && !connective.first) {//если символ не атом и не связка
			cout << "Incorrect symbols\n";
			return false;
		}
		if (connective.second)//если связка занимает два символа, инкремент
			i++;
	}
	return true;
}

bool syntax(string formula) {
	int number = get_number_of_brackets(formula);
	while (number) {
		for (int i = 0; i < formula.size(); i++) {
			if (formula[i] == '(') {//ищем паттер ( ... ), чтобы внутри не было скобок лишних
				for (int j = i + 1; j < formula.size(); j++) {
					if (formula[j] == '(')
						break;
					if (formula[j] == ')') {
						if ((check_atom(formula, i + 1) && check_atom(formula, j - 1) && check_connective(formula, i + 2).first)||//если бинарная формула
							(check_atom(formula, j - 1) && check_connective(formula, i + 1).first))	{//если унарная формула
							if ((check_connective(formula, i + 2).second == 1 && j == i + 5) ||//если бинарная и связка занимает два символа
								(check_connective(formula, i + 2).second == 0 && j == i + 4) ||//если бинарная и связка занимает один символ
								(check_connective(formula, i + 1).second == 0 && j == i + 3)) {//если унарная
								while (i != j) {
									formula[i] = ' ';//замена подформулы на пробелы
									i++;
								}
							}
							formula[j] = const_atom;//заменяем подформулу на атомарную
							formula.erase(remove_if(formula.begin(), formula.end(), ::isspace), formula.end());//удаляем проблемы
						}
						break;
					}
				}
			}
		}
		number--;
	}
	if (formula.size() == 1)//если смогли видоизменить формулу, то она корректна
		return true;
	else {//иначе есть ошибки
		cout << "Syntax error\n";
		return false;
	}
}