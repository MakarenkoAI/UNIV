#include "header_1.h"
#include <cmath>
#include <iterator>
#include <algorithm>

vect to_binary(int value)
{
    value = abs(value);

    vect result = { div(value, 2).rem }; 

    while (div(value, 2).quot > 0) {
        value = div(value, 2).quot;
        result.push_back(div(value, 2).rem);
    }

    reverse(result.begin(), result.end());

    return result;
}

double to_decimal(vect x) {

    float result = 0;
    int index_comma = x.size();

    for (int i = 0; i < x.size(); i++) 
        if (x[i] == -1) {
            index_comma = i;
            break;
        }
    
    for (int i = index_comma - 1, j = 0; i > -1; i--, j++) 
        result += x[i] * pow(2, j);
    
    for (int i = index_comma + 1, j = -1; i < x.size(); i++, j--) 
        result += x[i] * pow(2, j);
    
    return result;
}

double to_decimal_diff(vect x) {
    const int base = 2;
    const int comma = -1;
    double result = 0;
    int index_comma = x.size();

    for (int i = 0; i < x.size(); i++) {
        if (x[i] == comma) {
            index_comma = i;
            break;
        }
    }

    for (int i = index_comma - 1, power = 0; i > 0; i--, power++) {
        result += x[i] * pow(base, power);
    }
    for (int i = index_comma + 1, j = -1; i < x.size(); i++, j--) {
        result += x[i] * pow(base, j);
    }

    if (x[0] == 1)
        result = result * (-1);

    return result;


}

vect  to_binary_direct(int value) {
    const int size = 7;
    bool sign = 1;
    if (value > 0) {
        sign = 0;
    }

    vect result = to_binary(value);

    while (result.size() != size) {
        result.insert(result.begin(), 0);
    }
        
    if (sign == 0) {
        result.insert(result.begin(), 0);
    }else {
        result.insert(result.begin(), 1);
    }

    return result;
}

vect to_binary_reverse(int value)
{
    vect result = to_binary_direct(value);

    if (value < 0) {
        for (int i = 1; i < result.size(); i++) {
            if (result[i] == 1) {
                result[i] = 0;
            }else {
                result[i] = 1;
            }
        }
    }
    return result;
}

vect to_binary_adding(int value)
{
    vect result;

    if (value < 0) {
        result = summa(to_binary_reverse(value), { 0,0,0,0,0,0,0,1 });
    } else {
        result = to_binary_direct(value);
    }
    return result;
}

vect search_min_part(vect X1, vect X2) {
    vect result;

    for (int i = 0; i < X1.size(); i++) {

        result.push_back(X1[i]);

        if (!is_less(result, X2)) 
            return result;
    }
}

vect multiplication(vect X1, vect X2) {

    vector<vect> set;
    vect result;
    int size = X2.size();
    for (int i = size - 1; i > -1; i--)
        if (X2[i] == 1) {
            int dif = size - i - 1;

            vect summand = X1;

            while (dif) {
                summand.push_back(0);
                dif--;
            }

            set.push_back(summand);
        }
    result = set[0];
    for (int i = 1; i < set.size(); i++) {
       result = summa(result, set[i]);
    }
    return result;
}

vect summa(vect X1, vect X2)
{
    int size1 = X1.size();
    int size2 = X2.size();

    if (size1 > size2) {
        while (X1.size() != X2.size())
            X2.insert(X2.begin(), 0);
    }
    if (size2 > size1) {
        while (X1.size() != X2.size())
            X1.insert(X1.begin(), 0);
    }

    vect result;
    result.resize(X1.size());
    bool add_one = 1;

    for (int i = X1.size() - 1; i >= 0; i--) {
        if (X1[i] + X2[i] == 2) {
            if (add_one) 
                result[i] = 0;
            else 
                result[i] = 1;
                
            add_one = 0;
        }
        if (X1[i] + X2[i] == 1) {
            if (add_one)
                result[i] = 1;
            else
                result[i] = 0;
        }
        if (X1[i] + X2[i] == 0) {
            if (add_one)
                result[i] = 0;
            else {
                result[i] = 1;
                add_one = 1;
            }
        }
    }

    return result;
}

vect equalization_of_orders(vect& X1, vect X2, bool& comma) {

    vect result;

    int zero_numbers = 0;

    while (is_less(X1, X2)) {
        X1.push_back(0);
        zero_numbers++;
    }

    result.push_back(0);
    result.push_back(-1);
    comma = 1;

    while (zero_numbers - 1) {
        result.push_back(0);
        zero_numbers--;
    }

    return result;
}

void division_integer(int& index_of_last_symbol, vect& result, vect& part_of_divider, vect X1, vect X2) {

    vect arg1 = to_binary_adding(to_decimal(part_of_divider));
    vect arg2 = to_binary_adding(to_decimal(X2) * (-1));

    part_of_divider = summa(arg1, arg2);
    cutting(part_of_divider);
    result.push_back(1);

    while (index_of_last_symbol < X1.size()) {

        part_of_divider.push_back(X1[index_of_last_symbol]);
        cutting(part_of_divider);

        if (!is_less(part_of_divider, X2)) {
            arg1 = to_binary_adding(to_decimal(part_of_divider));
            arg2 = to_binary_adding(to_decimal(X2) * (-1));
            part_of_divider = summa(arg1, arg2);
            result.push_back(1);
            index_of_last_symbol++;
        }
        else result.push_back(0);
            
        index_of_last_symbol++;
    }
}

void division_fractional(vect& result, vect& part_of_divider, vect X1, vect X2) {

    int precision = 5;
    while (precision) {
        precision--;
        cutting(part_of_divider);
        part_of_divider.push_back(0);

        if (!is_less(part_of_divider, X2)) {
            vect arg1 = to_binary_adding(to_decimal(part_of_divider));
            vect arg2 = to_binary_adding(to_decimal(X2) * (-1));

            part_of_divider = summa(arg1, arg2);
            result.push_back(1);
        }
        else {
            result.push_back(0);
        }

    }
}

vect division(vect X1, vect X2) {

    vect result;
    bool comma = 0;

    if (is_less(X1, X2)) 
        result = equalization_of_orders(X1, X2, comma);
    
    vect part_of_divider = search_min_part(X1, X2);

    int index_of_last_symb = part_of_divider.size();

    division_integer(index_of_last_symb, result, part_of_divider, X1, X2);

    if (!comma) 
        result.push_back(-1);
    
    division_fractional(result, part_of_divider, X1, X2);

    return result;
}

bool is_less(vect X1, vect X2) {

    double x1 = to_decimal(X1);

    double x2 = to_decimal(X2);

    return x1 < x2;
}



void print_v(vect list)
{
    for (int i = 0; i < list.size(); i++) {
        if (list[i] == -1){
            cout << ",";
        } else{
            cout << list[i];
        }
    }
    cout << "\n";
}

void print_menu()
{
    cout << "0. + " << endl;
    cout << "1. - " << endl;
    cout << "2. * " << endl;
    cout << "3. / " << endl;
    cout << "4. e " << endl;
}

int get_key(int& key)
{
    cout << "Input the key: ";
    cin >> key;

    return key;
}



vect change_sign(int s, vect lst) {

    lst[0] = s;
    return lst;
}

void cutting(vect& list) {

    if (list.size() >= 8) {
        list.erase(list.begin());

        for (int i = 0; i < list.size(); ) {
            if (list[i] == 0) {
                list.erase(list.begin());
            } else {
                break;
            }
        }
    }


}

vect normal_floating(vect mantissa, int sign, bool zero_int) {

    int order = 0;
    int index_comma = 0;
    vect float_num;
    const int number = 127;
    const int size_mantiss = 23;
    float_num.push_back(sign);

    if (zero_int) {
        for (int i = 0; i < mantissa.size(); i++)
            if (mantissa[i] == 1) {
                index_comma = i;
                break;
            }
        order = -1 * (index_comma - 1);
        for (int i = 0; i < index_comma + 1; i++)
            mantissa.erase(mantissa.begin());
    }
    else {
        for (int i = 0; i < mantissa.size(); i++) {
            if (mantissa[i] == -1) {
                index_comma = i;
                break;
            }
        }
        order = index_comma - 1;
        mantissa.erase(mantissa.begin() + index_comma);
        mantissa.erase(mantissa.begin());
    }

    mantissa.resize(size_mantiss);

    vect b_order = to_binary(order + number);
    adding_zero(b_order);

    adding_vect(float_num, b_order);
    adding_vect(float_num, mantissa);

    return float_num;

}

vect floating(double value) {

    vect result_int, result_fract;
    double fract_part, int_part;
    int sign = 0;
    bool zero_int = 0;

    if (value < 0) 
        sign = 1;

    value = abs(value);
    
    fract_part = modf(value, &int_part);
    if (int_part == 0) 
        zero_int = 1;
    
    result_int = to_binary(int_part);
    result_int.push_back(-1);
    result_fract = to_binary_fract(fract_part);

    result_int.insert(result_int.end(), result_fract.begin(), result_fract.end());
    result_int = normal_floating(result_int, sign, zero_int);
    return result_int;
}

vect to_binary_fract(double value) {
    vect result;
    const int base = 2;
    int precision = 30;
    int power = -1;
    double try_answer = 0;
    double answer = 0;

    while (precision) {
        precision--;
        try_answer += pow(base, power);

        if (try_answer <= value) {
            result.push_back(1);
            answer += pow(base, power);
        }
        else {
            result.push_back(0);
            try_answer = answer;
        }
        power--;
    }
    return result;
}

void print_float(vect list) {
    const int first = 1;
    const int ninth = 9;
    for (int i = 0; i < list.size(); i++) {
        if (i == first || i == ninth)
            cout << " ";
        cout << list[i];
    }
    cout << "\n";
}

void adding_zero(vect& list) {
    const int size_order = 8;
    if (list.size() < size_order) {
        int num_zero = size_order - list.size();
        while (num_zero) {
            num_zero--;
            list.insert(list.begin(), 0);
        }
    }
}

void adding_vect(vect& main, vect tail) {

    for (int i = 0; i < tail.size(); i++) 
        main.push_back(tail[i]);
    
}

vect from_adding_to_direct(vect list) {

    if (list[0] == 0)
        return list;
    for (int i = 1; i < list.size(); i++) {
        if (list[i] == 0)
            list[i] = 1;
        else 
            list[i] = 0;
    }
    list = summa(list, { 0, 0, 0, 0, 0, 0, 0, 1 });
    return list;
}

vect floating_sum(vect x1, vect x2) {

    const int size_mantiss = 23;
    vect order;
    vect result{0};
    
    vect order_1 = f_get_order(x1);
    vect order_2 = f_get_order(x2);
    
    vect mantissa_1 = f_get_mantissa(x1);
    vect mantissa_2 = f_get_mantissa(x2);
    
   
    int ord_1 = to_decimal(order_1);
    int ord_2 = to_decimal(order_2);
    int diff = ord_1 - ord_2;

    if (diff != 0) {

        vect new_mantissa;

        if (ord_1 > ord_2) {
            order = order_1;
            new_mantissa = f_new_mantissa(abs(diff), mantissa_1, mantissa_2, order);
        }
        if (ord_2 > ord_1) {
            order = order_2;
            new_mantissa = f_new_mantissa(abs(diff), mantissa_2, mantissa_1, order);
        }
        
        result.insert(result.end(), order.begin(), order.end());
        result.insert(result.end(), new_mantissa.begin(), new_mantissa.end());
    }
    else {
        mantissa_2.insert(mantissa_2.begin(), 0);
        mantissa_1.insert(mantissa_1.begin(), 0);

        vect new_mantissa = summa(mantissa_2, mantissa_1);

        if (new_mantissa[0] == 1) {
            int ord = to_decimal(order);
            ord++;
            order = to_binary(ord);
        }
        else new_mantissa.erase(new_mantissa.begin());

        new_mantissa.erase(new_mantissa.begin());
        new_mantissa.resize(size_mantiss);
        result.insert(result.end(), order.begin(), order.end());
        result.insert(result.end(), new_mantissa.begin(), new_mantissa.end());
    }

    return result;
}

void from_float_to_dec(vect x)
{
    const int number = 127;
    float rez = 0;
    vect order_v;
    vect mantissa;

    for (int i = 1; i < 9; i++)
        order_v.push_back(x[i]);

    int order = to_decimal(order_v) - number;
    cout << order << " ";

    if (order < 0) {
        mantissa.push_back(0);
        mantissa.push_back(-1);
        while (order + 1) {
            mantissa.push_back(0);
            order++;
        }
        mantissa.push_back(1);
        for (int i = 9; i < 31; i++)
            mantissa.push_back(x[i]);
    }
    if (order > 0) {
        mantissa.push_back(1);
        for (int i = 9; i < 31; i++, order--){
            if (order == 0) 
                mantissa.push_back(-1);
            mantissa.push_back(x[i]);
        }
    }
    if (order == 0) {
        mantissa.push_back(1);
        mantissa.push_back(-1);
        for (int i = 9; i < 31; i++)
            mantissa.push_back(x[i]);
    }
    rez = to_decimal(mantissa);
    if (x[0] == 1) 
        rez = rez * (-1);
    cout << rez << '\n';
}

vect f_get_order(vect float_num) {

    vect order;
    for (int i = 1; i < 9; i++)
        order.push_back(float_num[i]);

    return order;
}

vect f_get_mantissa(vect float_num) {

    vect mantissa{1};

    for (int i = 9; i < 32; i++)
        mantissa.push_back(float_num[i]);

    return mantissa;
}

vect f_new_mantissa(int diff, vect bigger, vect smaller, vect& order) {

    vect new_mantissa{0, 0};

    while (diff - 1) {
        new_mantissa.push_back(0);
        diff--;
    }

    new_mantissa.insert(new_mantissa.end(), smaller.begin(), smaller.end());
    new_mantissa.resize(25);
    bigger.insert(bigger.begin(), 0);
    
    new_mantissa = summa(new_mantissa, bigger);

    if (new_mantissa[0] == 1) {
        int ord = to_decimal(order);
        ord++;
        order = to_binary(ord);
    }
    else new_mantissa.erase(new_mantissa.begin());

    new_mantissa.erase(new_mantissa.begin());

    return new_mantissa;
}
