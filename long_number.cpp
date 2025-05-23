#include "long_numbers.hpp"

using biv::LongNumbers;
		
LongNumbers::LongNumbers() {
	length = 0;
    sign = 1;
    numbers = nullptr;
}

LongNumbers::LongNumbers(const char* const str) {
    length = strlen(str);
    
    if (str[0] == "-") {
        sign = -1;
        length--;
    }
    else {
        sign = 1;
    }

    numbers = new int[length];
    for (int i = 0; i < length; i++) {
        numbers[i] = (str[i + (sign == -1)] - "0");
    }
    
    for (int i = 0; i < length / 2; ++i) {
        swap(numbers[i], numbers[length - i - 1]);
    }


}

LongNumbers::LongNumbers(const LongNumbers& x) {
	length = x.length;
    sign = x.sign;
    numbers = new int[length];
    for (int i = 0; i < length; i++) {
        numbers[i] = x.numbers[i];
    }
}

LongNumbers::LongNumbers(LongNumbers&& x) {
    length = x.length;
    sign = x.sign;
    numbers = x.numbers;
}

LongNumbers::~LongNumbers() {
    delete[] numbers;
}

LongNumbers& LongNumbers::operator = (const char* const str) {
        delete[] numbers;

        if (str[0] == "0" && str[1] == "\0") {
            length = 1;
            sign = 1;
            numbers = new int[length];
            numbers[0] = 0;
            return *this;
        }
        
        length = strlen(str);
        if (str[0] == "-") {
            sign = -1;
            length--;
        }else{
            sign = 1;
        }
        numbers = new int[length];
        for (int i = 0; i < length; i++) {
            numbers[i] = (str[i + (sign == -1)] - '0');
        }

        for (int i = 0; i < length / 2; ++i) {
            swap(numbers[i], numbers[length - i - 1]);
        }

        return *this;
    
}

LongNumbers& LongNumbers::operator = (const LongNumbers& x ){
        delete[] numbers;
        length = x.length;
        sign = x.sign;
        numbers = new int[length];
        for (int i = 0; i < length; i++) {
            numbers[i] = x.numbers[i];
        }
    return *this;
}

LongNumbers& LongNumbers::operator = (LongNumbers&& x) {
        length = x.length;
        sign = x.sign;
        numbers = x.numbers;
        x.numbers = nullptr;
        return *this;
}

bool LongNumbers::operator == (const LongNumbers& x) const {
        if (length != x.length || sign != x.sign) {
            return false;
        }
        for (int i = 0; i < length; i++) {
            if (numbers[i] != x.numbers[i]) {
                return false;
            }
        }
        return true;
    

}

bool LongNumbers::operator != (const LongNumbers& x) const {
        return !(*this == x);
}

bool LongNumbers::operator > (const LongNumbers& x) const {
    if (sign != x.sign) {
        return sign > x.sign;
    }

    if (length != x.length) {
        return (sign == 1) ? (length > x.length) : (length < x.length);
    }

    for (int i = length-1; i >= 0; --i) {
        if (numbers[i] != x.numbers[i]) {
            return (sign == 1) ? (numbers[i] > x.numbers[i]) : (numbers[i] < x.numbers[i]);
        }
    }
    return false;

}

bool LongNumbers::operator < (const LongNumbers& x) const {
    bool isgreater = *this > x;
    bool isequal = *this == x;
    return !(isgreater || isequal);
}

bool LongNumbers::operator >= (const LongNumbers& x) const {
    return !(*this < x);
}

LongNumbers LongNumbers::operator + (const LongNumbers& x) const {
    LongNumbers result;

    if (sign == x.sign) {
        result.length = max(length, x.length) + 1;
        result.numbers = new int[result.length];
        int save = 0;
        for (int i = 0; i < result.length; ++i) {
            int sum = (i < length ? numbers[i] : 0) +
                    (i < x.length ? x.numbers[i] : 0) +
                    save;
            result.numbers[i] = sum % 10;
            save = sum / 10;
        }
        result.sign = sign;

        while (result.length > 1 && result.numbers[result.length - 1] == 0) {
            result.length--;
        }

        return result;
    }
    else {
        LongNumbers positive, negative, reduced, substructed;
        if (*this > x) {
            positive = *this;
            negative = x;
        } else {
            positive = x;
            negative = *this;
        }
        
        negative.sign = 1;

        if (positive > negative) {
            reduced = positive;
            substructed = negative;
            result.sign = 1;
        } else {
            reduced = negative;
            substructed = positive;
            result.sign = -1;
        }

        result.length = reduced.length;
        result.numbers = new int[result.length];
        
        int category_sub = 0;
        for (int i = 0; i < result.length || category_sub; ++i) {
            int diff = reduced.numbers[i] - category_sub - ((i < substructed.length) ? substructed.numbers[i] : 0);
            if (diff < 0) {
                diff += 10;
                category_sub = 1;
            } else {
                category_sub = 0;
            }
            result.numbers[i] = diff;
        }

        while (result.length > 1 && result.numbers[result.length - 1] == 0) {
            result.length--;
        }

        if (result.length == 1 && result.numbers[0] == 0) {
            result.sign = 1;
        }
        return result;
    }
}

LongNumbers LongNumbers::operator - (const LongNumbers& x) const {
    LongNumbers redused = *this;
    LongNumbers substructed = x;
    substructed.sign *=-1;

    return redused + substructed;

}

LongNumbers LongNumbers::operator * (const LongNumbers& x) const {
    LongNumbers result;
    result.length = length + x.length;
    result.numbers = new int[result.length]{0};

    for (int i = 0; i < length; ++i) {
        int save = 0;
        for (int j = 0; j < x.length || save; ++j) {
            long long current = result.numbers[i + j] +
                numbers[i] * (j < x.length ? x.numbers[j] : 0) + save;
            result.numbers[i + j] = current % 10;
            save = current / 10;
        }
    }

    while (result.length > 1 && result.numbers[result.length - 1] == 0) {
        result.length--;
    }

    result.sign = (sign == x.sign) ? 1 : -1;
    return result;
}

LongNumbers LongNumbers::operator / (const LongNumbers& x) const {
    LongNumbers result;
    result.length = length;
    result.numbers = new int[result.length];
    result.sign = (sign == x.sign) ? 1 : -1;

    LongNumbers dividend = *this;
    dividend.sign = 1;
    LongNumbers divisor = x;
    divisor.sign = 1;

    if (dividend < divisor) {
        result = "0";
        return result;
    }

    LongNumbers current("0");
    LongNumbers ten("10");
    for (int i = dividend.length - 1; i >= 0; --i) {

        current = (current * ten) + LongNumbers(to_string(dividend.numbers[i]).c_str());
        int digit = 0;
        while (current >= divisor) {
            current = (current - divisor);
            ++digit;
        }

        result.numbers[i] = digit;
    }

    while (result.length > 1 && result.numbers[result.length - 1] == 0) {
        --result.length;
    }

    return result;

}

LongNumbers LongNumbers::operator % (const LongNumbers& x) const {
    LongNumbers copy = *this;
    LongNumbers copyx = x;
    LongNumbers integer_part, quotient, result;
    if (sign == 1 && x.sign == 1) {
        integer_part = copy / x;
        quotient = integer_part * x;
        result = copy - quotient;
        return result;
    }

    else if (sign == -1 && x.sign == 1) {
        integer_part = (copy / x) - LongNumbers("1");
        quotient = integer_part * x;
        result = copy - quotient;
        return result;
    }

    else if(sign == 1 && x.sign == -1) {
        integer_part = copy / x;
        quotient = integer_part * x;
        result = copy - quotient;
        return result;
    }

    else {
        integer_part = (copy / x) + LongNumbers("1");
        quotient = integer_part * x;
        result = copy - quotient;
        return result;
    }
}

int LongNumbers::get_digits_number() const noexcept {
    return length;
}

int LongNumbers::get_rank_number(int rank) const {
    if (rank < 1 || rank > length) {
        throw out_of_range("Specified rank is out of range");
    }
    return numbers[length - rank];
}

bool LongNumbers::is_negative() const noexcept {
    return sign == -1;
}

int LongNumbers::get_length(const char* const str) const noexcept {
    return length;
}

namespace biv {
	ostream& operator << (ostream &os, const LongNumbers& x) {
		if (x.sign == -1) {
			os << "-";
		}
		for (int i = x.length - 1; i >= 0; --i) {
			os << x.numbers[i];
		}
		return os;
	}
}