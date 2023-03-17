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
	if (check_symbols(formula) && syntax(formula))//���� ��������� � ����� ����������
		return true;
	return false;
}

bool check_atom(string formula, int index) {
	for (int i = 0; i < atom_formula.size(); i++)
		if (formula[index] == atom_formula[i])//���� ���������
			return true;
	return false;
}

pair<bool, bool> check_connective(string formula, int index) {
	if ((index + 1) < formula.size()) {//��������� ������� �� ����� ������ � ����� ����� ������
		if (formula[index] == '/' && formula[index + 1] == '\\')//��� ���������, �������� ��� �������
			return { true, 1 };
		if (formula[index] == '\\' && formula[index + 1] == '/')//��� ����������, �������� ��� �������
			return { true, 1 };
		if (formula[index] == '-' && formula[index + 1] == '>')//��� ����������, �������� ��� �������
			return { true, 1 };
		if (formula[index] == '~' || formula[index] == '(' || formula[index] == '!')//��� ������ �� (, ���������� ���� ������
			return { true, 0 };
	}
	if (formula[index] == ')')//������, ������� ����� ���� � ����� ������
		return { true, 0 };//�������� ���� ������
	return { false, 0 };//������������ ������
}

bool check_symbols(string formula) {
	for (int i = 0; i < formula.size(); i++) {

		pair< bool, bool> connective = check_connective(formula, i);//��������� ������ � ������ (���� ��� ����������, 1 - �������� 2 ������� ; 0 - ���� ������

		if (!check_atom(formula, i) && !connective.first) {//���� ������ �� ���� � �� ������
			cout << "Incorrect symbols\n";
			return false;
		}
		if (connective.second)//���� ������ �������� ��� �������, ���������
			i++;
	}
	return true;
}

bool syntax(string formula) {
	int number = get_number_of_brackets(formula);
	while (number) {
		for (int i = 0; i < formula.size(); i++) {
			if (formula[i] == '(') {//���� ������ ( ... ), ����� ������ �� ���� ������ ������
				for (int j = i + 1; j < formula.size(); j++) {
					if (formula[j] == '(')
						break;
					if (formula[j] == ')') {
						if ((check_atom(formula, i + 1) && check_atom(formula, j - 1) && check_connective(formula, i + 2).first)||//���� �������� �������
							(check_atom(formula, j - 1) && check_connective(formula, i + 1).first))	{//���� ������� �������
							if ((check_connective(formula, i + 2).second == 1 && j == i + 5) ||//���� �������� � ������ �������� ��� �������
								(check_connective(formula, i + 2).second == 0 && j == i + 4) ||//���� �������� � ������ �������� ���� ������
								(check_connective(formula, i + 1).second == 0 && j == i + 3)) {//���� �������
								while (i != j) {
									formula[i] = ' ';//������ ���������� �� �������
									i++;
								}
							}
							formula[j] = const_atom;//�������� ���������� �� ���������
							formula.erase(remove_if(formula.begin(), formula.end(), ::isspace), formula.end());//������� ��������
						}
						break;
					}
				}
			}
		}
		number--;
	}
	if (formula.size() == 1)//���� ������ ������������ �������, �� ��� ���������
		return true;
	else {//����� ���� ������
		cout << "Syntax error\n";
		return false;
	}
}