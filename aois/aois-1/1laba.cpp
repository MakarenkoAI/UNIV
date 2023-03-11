#include <iostream>
#include <vector>
#include <algorithm>
#include "header_1.h"

using namespace std;

//cl /EHsc hello.cpp
//.\laba.exe

int main(){

    int key;
    int x1, x2;

    cout << "Input x1: ";
    cin >> x1;

    cout << "Input x2: ";
    cin >> x2;

    pair<int, int> signs (0,0);
    if (x1 < 0) signs.first = 1;
    if (x2 < 0) signs.second = 1;

    vect arg1 = to_binary_adding(x1);
    vect arg2 = to_binary_adding(x2);

    vect arg1_min = to_binary_adding(x2 * (-1));
    vect arg2_min = to_binary_adding(x1 * (-1));

    vect arg1_bi = to_binary(x1);
    vect arg2_bi = to_binary(x2);
    
    print_menu();
    do {
        switch (get_key(key)) {
        case 0: {
            vect temp = summa(arg1, arg2);
            print_v(from_adding_to_direct(temp));
            cout << to_decimal_diff(from_adding_to_direct(temp)) << "\n";
            break;
        }
        case 1: {
            vect temp = summa(arg1, arg1_min);
            print_v(from_adding_to_direct(temp));
            cout << to_decimal_diff(from_adding_to_direct(temp)) << '\n';
            break;
        }
        case 2: {
            vect temp = multiplication(to_binary_direct(abs(x1)), to_binary_direct(abs(x2)));
            print_v(temp);
            if (signs.first + signs.second == 1) 
                cout << '-';
            else  
                cout << '+';
            cout << to_decimal(temp) << "\n";
            break;

        }
        case 3: {
            if (signs.first + signs.second == 1) 
                cout << "-";
            else 
                cout << "+";
       
            vect temp = division(arg1_bi, arg2_bi);
            print_v(temp);
            cout << to_decimal(temp) << "\n";
            break;
        }
        case 4: {            
            double x, y;
            cin >> x;
            cin >> y;
            print_float(floating(x));
            from_float_to_dec(floating(x));
            print_float(floating(y));
            from_float_to_dec(floating(y));
            print_float(floating_sum(floating(x), floating(y)));
            from_float_to_dec((floating_sum(floating(x), floating(y))));
            break;
        }
        }
    } while (key != -1);
}



