/////////////////////////////////////////////////////
// Лабораторная работа №1 по дисциплине ЛОИС
// Выполнена студентами гр. 121701 БГУИР Макаренко А. И., Корсаковой С. К.
// Определяет количество подформул заданного уровня в формуле сокращенного языка логики высказываний.
// 10.03.2023

// Шаблоны ввода
// ((A&A)~(B&B))
// (((A&A)~(!B))&D)
// ((A&A)~B)
// ((((A&B)~(!C))&((C&D)~(A&B)))&((F&A)~(!C)))
//((((A&B)v(BvC))&((!C)v((1vA)v(B->C))))&((!D)->(Q&A)))
#include <iostream>
#include <vector>
#include <string>
using namespace std;

typedef pair <int, int> index;

bool if_void_string(string input);

const vector<char> formula{ '0', '1', 'A', 'B', 'C', 'D', 'E', 'F'};

bool check_for_open_bracket(int index, string formula, vector<int> helping);

int check_for_close_bracket(int index, string formula, vector<int> helping);

void print(int begin, int end, string input);

void added_zero_level(vector<pair<int, index>>& data, string input);

bool equality(vector<char> abc, char symbol);

void print_data(vector<pair<int, index>> data, string input, int level=-1);

bool uniqueness(vector<pair<int, index>> data, int begin, int end, string formula);

string get_subformula(string formula, int begin, int end);

int get_number_of_brackets(string formula);

int define_level(string input, int begin, int end);

string get_str_brackets(string subformula);

vector<pair<int, index>> fulfill_data(vector<pair<int, index>>& data, int number_of_brackets, string input, vector<int>& helping);

int get_number_of_subformulas(int key, vector<pair<int, index>> data);


int main()
{
	vector<pair<int, index>> data; //хранит в себе 1) уровень формулы 2) индекс ( в строке формулы 3) индекс )

	string input;//для строки формулы

	cout << "Input the formula\n";
	cin >> input;

	vector<int> helping(input.size());//вспомогательный вектор, соответсвует длине строки формулы
	for (int i = 0; i < input.size(); i++)
		helping[i] = 0;

	added_zero_level(data, input); //добавляет все атомарные формулы

	int number_of_brackets = get_number_of_brackets(input);//получаем количество скобок в строке формулы

	fulfill_data(data, number_of_brackets, input, helping);//ищем все подформулы в строке формулы, кроме атомарных

	print_data(data, input);//выводим все подформулы и их уровни

	int level;//вводим необходимый уровень
	cout << "Input the nessesary level of subformula:\n";
	cin >> level;

	int number_of_subformulas = get_number_of_subformulas(level, data);//считает количество подформул с необходимым уровнем
	cout << "Number of subformulas with the " << level << " level is " << number_of_subformulas;

}


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

void print(int begin, int end, string input){

	for (int i = begin; i <= end; i++) {
		cout << input[i];
	}
	cout << "\n";
}

void added_zero_level(vector<pair<int, index>>& data, string input)
{
	int level = 0;
	for (int i = 0; i < input.size(); i++) {
		if (equality(formula, input[i]) && uniqueness(data, i, i, input)) {//если атомарная формула соответсвует алфавиту и проверка на дублирование
			data.push_back({ level, {i, i} });//сохраняем атомарную формулу и ее уровень
		}
	}
}

bool equality(vector<char> abc, char symbol)
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
	/*
	string subformula = get_subformula(input, begin, end);//получаем подформулу

	string brackets = get_str_brackets(subformula);//получаем формулу состоящую только из скобок

	vector<int> levels {1};//у всех подформул изначально уровень 1 (кроме атомарных)

	int level = 0;//переменная для значения уровня
	
	for (int i = 1; i < brackets.size() - 1; i++) {
		if (brackets[i] == '(')//считаем количество скобок ( подряд
			level++;
		else {
			levels.push_back(level + 1);//сохраняем уровни в вектор
			level = 0;
		}
	}

	int result_max_level = 0;//переменная для поиска максимального уровня
	for (int i = 0; i < levels.size(); i++) {
		if (levels[i] >= result_max_level)
			result_max_level = levels[i];
	}
	return result_max_level;
	*/
	//(()())
	string subformula = get_subformula(input, begin, end);//получаем подформулу

	string brackets = get_str_brackets(subformula);//получаем формулу состоящую только из скобок
	int level = 0;
	while (!if_void_string(brackets)) {

		for (int i = 0; i < brackets.size(); i++) {
			if (brackets[i] == '(' && brackets[i + 1] == ')') {
				brackets[i] = ' ';
				brackets[i + 1] = ' ';

			}
		}
		brackets.erase(remove_if(brackets.begin(), brackets.end(), ::isspace), brackets.end());
		level++;

	}
	return level;

}

bool if_void_string(string input) {
	bool result = 1;
	for (int i = 0; i < input.size(); i++) 
		if (input[i] != ' ')
			result = 0;
	return result;
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