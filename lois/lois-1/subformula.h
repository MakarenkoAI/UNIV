#pragma once

#include <iostream>
#include <vector>
#include <string>

using namespace std;

typedef pair <int, int> index;

const vector<char> formula{ '0', '1', 'A', 'B', 'C', 'D','E', 'F', 'G', 'H', 'I', 'J', 'K', 'L',
							'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };

bool check_for_open_bracket(int, string, vector<int>);
int check_for_close_bracket(int, string, vector<int>);
void print(int, int, string);
void added_zero_level(vector<pair<int, index>>&, string);
bool equality_abc(vector<char>, char);
void print_data(vector<pair<int, index>>, string, int level = -1);
bool uniqueness(vector<pair<int, index>>, int, int, string);
string get_subformula(string, int, int);
int get_number_of_brackets(string);
int define_level(string, int, int);
string get_str_brackets(string);
vector<pair<int, index>> fulfill_data(vector<pair<int, index>>&, int, string, vector<int>&);
int get_number_of_subformulas(int, vector<pair<int, index>>);



int get_number_of_subformulas(int key, vector<pair<int, index>> data) {

	int number = 0;
	for (int i = 0; i < data.size(); i++) {
		if (data[i].first == key)
			number++;
	}
	return number;
}

vector<pair<int, index>> fulfill_data(vector<pair<int, index>>& data, int number_of_brackets, string input, vector<int>& helping) {

	while (number_of_brackets) {
		for (int i = 0; i < input.size(); i++) {
			if ((input[i] == '(') && (helping[i] == 0)) {//если мы впервые нашли (

				if (!check_for_open_bracket(i, input, helping)) {//проверяем есть ли еще открытая ( после
					int new_index_close = check_for_close_bracket(i, input, helping);//если не нашли (, то ищем )
					int level = define_level(input, i, new_index_close);//определяем уровень подформулы
					helping[i] = 1;//помечаем, что подформула была найдена
					helping[new_index_close] = 1;

					if (uniqueness(data, i, new_index_close, input))//проверка на дублирование
						data.push_back({ level, {i, new_index_close} });//сохраняем индексы и уровень подформулы
				}
			}
		}
		number_of_brackets--;
	}
	return data;

}

bool check_for_open_bracket(int index, string input, vector<int> helping)
{
	for (int i = index + 1; i < input.size(); i++) {
		if ((input[i] == '(') && (helping[i] == 0))//если нашли впервые (
			return true;
		if ((input[i] == ')') && (helping[i] == 0))//если нашли впервые )
			return false;
	}
	cout << "Error";
	return 0;
}

int check_for_close_bracket(int index, string input, vector<int> helping) {

	for (int i = index + 1; i < input.size(); i++) {
		if ((input[i] == ')') && (helping[i] == 0))//если нашли впервые )
			return i;
	}
	cout << "Error";
	return 0;
}

void print(int begin, int end, string input) {

	for (int i = begin; i <= end; i++) {
		cout << input[i];
	}
	cout << "\n";
}

void added_zero_level(vector<pair<int, index>>& data, string input)
{
	int level = 0;
	for (int i = 0; i < input.size(); i++) {
		if (equality_abc(formula, input[i]) && uniqueness(data, i, i, input)) {//если атомарная формула соответсвует алфавиту и проверка на дублирование
			data.push_back({ level, {i, i} });//сохраняем атомарную формулу и ее уровень
		}
	}
}

bool equality_abc(vector<char> abc, char symbol)
{
	for (int i = 0; i < abc.size(); i++) {//если символ принадлежит алфавиту
		if (abc[i] == symbol)
			return true;
	}
	return false;
}

void print_data(vector<pair<int, index>> data, string input, int level) {

	if (level == -1) {//если выводить весь вектор
		for (int i = 0; i < data.size(); i++) {
			cout << "Level: " << data[i].first << "   ";
			print(data[i].second.first, data[i].second.second, input);
		}
	}
	else {//если вывести только подформулы с определенным уровнем
		for (int i = 0; i < data.size(); i++) {
			if (data[i].first == level) {//если уровень совпадает
				cout << "Level: " << data[level].first << "   ";
				print(data[i].second.first, data[i].second.second, input);
			}
		}
	}
}

bool uniqueness(vector<pair<int, index>> data, int begin, int end, string formula) {

	string subformula = get_subformula(formula, begin, end);//получаем строку подформулы
	for (int i = 0; i < data.size(); i++) {
		if (subformula == get_subformula(formula, data[i].second.first, data[i].second.second))//проверка на дублирование
			return false;
	}
	return true;
}

string get_subformula(string formula, int begin, int end) {

	string subformula = "";
	for (int i = begin; i <= end; i++) {
		subformula += formula[i];//получание подформулы по индексам скобок ( и )
	}
	return subformula;
}

int get_number_of_brackets(string formula)
{
	int result = 0;
	for (int i = 0; i < formula.size(); i++)
		if (formula[i] == '(' || formula[i] == ')')//считаем количество всех скобок
			result++;
	return result;
}

int define_level(string input, int begin, int end)
{
	string subformula = get_subformula(input, begin, end);//получаем подформулу
	string brackets = get_str_brackets(subformula);//получаем формулу состоящую только из скобок
	int level = 0;

	while (brackets.size()) {
		for (int i = 0; i < brackets.size(); i++) {
			if (brackets[i] == '(' && brackets[i + 1] == ')') {//находим все подформулы одинакового наименьшего уровня
				brackets[i] = ' ';
				brackets[i + 1] = ' ';//заменяем пробелами
			}
		}
		brackets.erase(remove_if(brackets.begin(), brackets.end(), ::isspace), brackets.end());//удаляем пробелы
		level++;//увеличиваем уровень
	}
	return level;

}

string get_str_brackets(string subformula) {

	string brackets = "";
	for (int i = 0; i < subformula.size(); i++) {
		if (subformula[i] == '(' || subformula[i] == ')') {
			brackets += subformula[i];//сохраняем в строку лишь скобки
		}
	}
	return brackets;
}