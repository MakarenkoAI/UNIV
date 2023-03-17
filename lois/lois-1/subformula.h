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
			if ((input[i] == '(') && (helping[i] == 0)) {//���� �� ������� ����� (

				if (!check_for_open_bracket(i, input, helping)) {//��������� ���� �� ��� �������� ( �����
					int new_index_close = check_for_close_bracket(i, input, helping);//���� �� ����� (, �� ���� )
					int level = define_level(input, i, new_index_close);//���������� ������� ����������
					helping[i] = 1;//��������, ��� ���������� ���� �������
					helping[new_index_close] = 1;

					if (uniqueness(data, i, new_index_close, input))//�������� �� ������������
						data.push_back({ level, {i, new_index_close} });//��������� ������� � ������� ����������
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
		if ((input[i] == '(') && (helping[i] == 0))//���� ����� ������� (
			return true;
		if ((input[i] == ')') && (helping[i] == 0))//���� ����� ������� )
			return false;
	}
	cout << "Error";
	return 0;
}

int check_for_close_bracket(int index, string input, vector<int> helping) {

	for (int i = index + 1; i < input.size(); i++) {
		if ((input[i] == ')') && (helping[i] == 0))//���� ����� ������� )
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
		if (equality_abc(formula, input[i]) && uniqueness(data, i, i, input)) {//���� ��������� ������� ������������ �������� � �������� �� ������������
			data.push_back({ level, {i, i} });//��������� ��������� ������� � �� �������
		}
	}
}

bool equality_abc(vector<char> abc, char symbol)
{
	for (int i = 0; i < abc.size(); i++) {//���� ������ ����������� ��������
		if (abc[i] == symbol)
			return true;
	}
	return false;
}

void print_data(vector<pair<int, index>> data, string input, int level) {

	if (level == -1) {//���� �������� ���� ������
		for (int i = 0; i < data.size(); i++) {
			cout << "Level: " << data[i].first << "   ";
			print(data[i].second.first, data[i].second.second, input);
		}
	}
	else {//���� ������� ������ ���������� � ������������ �������
		for (int i = 0; i < data.size(); i++) {
			if (data[i].first == level) {//���� ������� ���������
				cout << "Level: " << data[level].first << "   ";
				print(data[i].second.first, data[i].second.second, input);
			}
		}
	}
}

bool uniqueness(vector<pair<int, index>> data, int begin, int end, string formula) {

	string subformula = get_subformula(formula, begin, end);//�������� ������ ����������
	for (int i = 0; i < data.size(); i++) {
		if (subformula == get_subformula(formula, data[i].second.first, data[i].second.second))//�������� �� ������������
			return false;
	}
	return true;
}

string get_subformula(string formula, int begin, int end) {

	string subformula = "";
	for (int i = begin; i <= end; i++) {
		subformula += formula[i];//��������� ���������� �� �������� ������ ( � )
	}
	return subformula;
}

int get_number_of_brackets(string formula)
{
	int result = 0;
	for (int i = 0; i < formula.size(); i++)
		if (formula[i] == '(' || formula[i] == ')')//������� ���������� ���� ������
			result++;
	return result;
}

int define_level(string input, int begin, int end)
{
	string subformula = get_subformula(input, begin, end);//�������� ����������
	string brackets = get_str_brackets(subformula);//�������� ������� ��������� ������ �� ������
	int level = 0;

	while (brackets.size()) {
		for (int i = 0; i < brackets.size(); i++) {
			if (brackets[i] == '(' && brackets[i + 1] == ')') {//������� ��� ���������� ����������� ����������� ������
				brackets[i] = ' ';
				brackets[i + 1] = ' ';//�������� ���������
			}
		}
		brackets.erase(remove_if(brackets.begin(), brackets.end(), ::isspace), brackets.end());//������� �������
		level++;//����������� �������
	}
	return level;

}

string get_str_brackets(string subformula) {

	string brackets = "";
	for (int i = 0; i < subformula.size(); i++) {
		if (subformula[i] == '(' || subformula[i] == ')') {
			brackets += subformula[i];//��������� � ������ ���� ������
		}
	}
	return brackets;
}