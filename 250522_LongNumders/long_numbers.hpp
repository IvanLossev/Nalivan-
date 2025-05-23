#ifndef LONG_NUMBER_HPP
#define LONG_NUMBER_HPP

#include <iostream>
#include <cstring>
#include <stdexcept>

namespace biv {

class LongNumber {
public:
    // Конструкторы и деструктор
    LongNumber();
    LongNumber(const char* const str);
    LongNumber(const LongNumber& x);
    LongNumber(LongNumber&& x);
    ~LongNumber();

    // Операторы присваивания
    LongNumber& operator=(const char* const str);
    LongNumber& operator=(const LongNumber& x);
    LongNumber& operator=(LongNumber&& x);

    // Операторы сравнения
    bool operator==(const LongNumber& x) const;
    bool operator!=(const LongNumber& x) const;
    bool operator>(const LongNumber& x) const;
    bool operator<(const LongNumber& x) const;
    bool operator>=(const LongNumber& x) const;

    // Арифметические операторы
    LongNumber operator+(const LongNumber& x) const;
    LongNumber operator-(const LongNumber& x) const;
    LongNumber operator*(const LongNumber& x) const;
    LongNumber operator/(const LongNumber& x) const;
    LongNumber operator%(const LongNumber& x) const;

    // Вспомогательные методы
    int get_digits_number() const noexcept;
    int get_rank_number(int rank) const;
    bool is_negative() const noexcept;

    // Дружественный оператор вывода
    friend std::ostream& operator<<(std::ostream& os, const LongNumber& x);

private:
    int length;
    int sign;
    int* numbers;
};

} // namespace biv

#endif // LONG_NUMBER_HPP
