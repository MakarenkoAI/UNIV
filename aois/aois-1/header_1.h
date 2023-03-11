#pragma once
#ifndef HEADER_1_H
#define HEADER_1_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

typedef vector<int> vect;

vect to_binary(int);

vect to_binary_direct(int);

vect to_binary_reverse(int);

vect to_binary_adding(int);

vect to_binary_fract(double);


vect search_min_part(vect, vect);

vect equalization_of_orders(vect&, vect, bool&);

vect summa(vect, vect);

vect multiplication(vect, vect);

vect division(vect, vect);

void division_integer(int&, vect&, vect&, vect, vect);

void division_fractional(vect&, vect&, vect, vect);


void print_v(vect);

void print_menu();

int get_key(int&);



double to_decimal_diff(vect);

bool is_less(vect, vect);

vect change_sign(int, vect);

void cutting(vect&);

double to_decimal(vect);

vect normal_floating(vect, int, bool);

vect floating(double);

void print_float(vect);

void adding_vect(vect&, vect);

void adding_zero(vect&);

vect from_adding_to_direct(vect);

vect floating_sum(vect, vect);

void from_float_to_dec(vect);

vect f_get_mantissa(vect);

vect f_get_order(vect);

vect f_new_mantissa(int diff, vect bigger, vect smaller, vect& order);

#endif  // HEADER_1_H