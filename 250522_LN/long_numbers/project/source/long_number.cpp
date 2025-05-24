#include "long_number.hpp"

namespace mmh {
    LongNumber::LongNumber() : len(1), sign(1) {
        numbers = new int[len];
        numbers[0] = 0;
    }

    LongNumber::LongNumber(int len, int sign) : len(len), sign(sign) {
        numbers = new int[len];
        for (int i = 0; i < len; i++) numbers[i] = 0;
    }

    LongNumber::LongNumber(const char* const str) {
        int str_len = get_length(str);
        if (str[0] == '-') {
            sign = -1;
            len = str_len - 1;
        } else {
            sign = 1;
            len = str_len;
        }
        numbers = new int[len];
        for (int i = 0; i < len; i++)
            numbers[i] = str[str_len - i - 1] - '0';
    }

    LongNumber::LongNumber(const LongNumber& x) {
        len = x.len;
        sign = x.sign;
        numbers = new int[len];
        for (int i = 0; i < len; i++)
            numbers[i] = x.numbers[i];
    }

    LongNumber::LongNumber(LongNumber&& x) {
        len = x.len;
        sign = x.sign;
        numbers = x.numbers;
        x.numbers = nullptr;
    }

    LongNumber::~LongNumber() {
        len = 0;
        delete[] numbers;
        numbers = nullptr;
    }

    LongNumber& LongNumber::operator=(const char* const str) {
        int str_len = get_length(str);
        if (str[0] == '-') {
            sign = -1;
            len = str_len - 1;
        } else {
            sign = 1;
            len = str_len;
        }
        delete[] numbers;
        numbers = new int[len];
        for (int i = 0; i < len; i++)
            numbers[i] = str[str_len - i - 1] - '0';
        return *this;
    }

    LongNumber& LongNumber::operator=(const LongNumber& x) {
        if (this == &x) return *this;
        len = x.len;
        sign = x.sign;
        delete[] numbers;
        numbers = new int[len];
        for (int i = 0; i < len; i++)
            numbers[i] = x.numbers[i];
        return *this;
    }

    LongNumber& LongNumber::operator=(LongNumber&& x) {
        if (this != &x) {
            delete[] numbers;
            len = x.len;
            sign = x.sign;
            numbers = x.numbers;
            x.numbers = nullptr;
        }
        return *this;
    }

    bool LongNumber::operator==(const LongNumber& x) const {
        if (this == &x) return true;
        if (len != x.len || sign != x.sign) return false;
        for (int i = 0; i < len; i++)
            if (numbers[i] != x.numbers[i]) return false;
        return true;
    }

    bool LongNumber::operator!=(const LongNumber& x) const {
        return !(*this == x);
    }

    bool LongNumber::operator>(const LongNumber& x) const {
        if (sign != x.sign) return sign > x.sign;
        if (len != x.len) return sign == 1 ? len > x.len : len < x.len;
        for (int i = len - 1; i >= 0; --i)
            if (numbers[i] != x.numbers[i])
                return sign == 1 ? numbers[i] > x.numbers[i] : numbers[i] < x.numbers[i];
        return false;
    }

    bool LongNumber::operator<(const LongNumber& x) const {
        return !(*this > x) && (*this != x);
    }

    LongNumber LongNumber::operator+(const LongNumber& x) const {
        LongNumber sum, min, max;
        if (sign * x.sign > 0) {
            sum = LongNumber(std::max(len, x.len) + 1, sign);
            max = (len >= x.len ? *this : x);
            min = (len >= x.len ? x : *this);
            for (int i = 0; i < min.len; i++)
                sum.numbers[i] = min.numbers[i] + max.numbers[i];
            for (int i = min.len; i < max.len; i++)
                sum.numbers[i] = max.numbers[i];
            for (int i = 0; i < sum.len - 1; i++)
                if (sum.numbers[i] > 9) {
                    sum.numbers[i + 1] += sum.numbers[i] / 10;
                    sum.numbers[i] %= 10;
                }
            if (sum.numbers[sum.len - 1] == 0) sum.len--;
        } else {
            LongNumber a = *this, b = x;
            a.sign = b.sign = 1;
            if (b < a) {
                sum = LongNumber(len + 1, sign);
                max = *this;
                min = x;
            } else {
                sum = LongNumber(x.len + 1, x.sign);
                max = x;
                min = *this;
            }
            for (int i = 0; i < max.len; i++)
                sum.numbers[i] = max.numbers[i];
            for (int i = 0; i < min.len; i++)
                sum.numbers[i] -= min.numbers[i];
            for (int i = 0; i < sum.len - 1; i++)
                if (sum.numbers[i] < 0) {
                    sum.numbers[i + 1]--;
                    sum.numbers[i] += 10;
                }
            while (sum.len > 1 && sum.numbers[sum.len - 1] == 0) sum.len--;
        }
        if (sum.len == 1 && sum.numbers[0] == 0) sum.sign = 1;
        return sum;
    }

    LongNumber LongNumber::operator-(const LongNumber& x) const {
        LongNumber inv = x;
        inv.sign = -inv.sign;
        return *this + inv;
    }

    LongNumber LongNumber::operator*(const LongNumber& x) const {
        LongNumber product(len + x.len, sign * x.sign);
        for (int i = 0; i < x.len; i++)
            for (int j = 0; j < len; j++) {
                product.numbers[i + j] += x.numbers[i] * numbers[j];
                if (product.numbers[i + j] > 9) {
                    int carry = product.numbers[i + j] / 10;
                    product.numbers[i + j + 1] += carry;
                    product.numbers[i + j] %= 10;
                }
            }
        while (product.len > 1 && product.numbers[product.len - 1] == 0) product.len--;
        return product;
    }

    LongNumber LongNumber::operator/(const LongNumber& x) const {
        if (x.len == 1 && x.numbers[0] == 0) return LongNumber("0");
        if (len == 1 && numbers[0] == 0) return LongNumber("0");
        LongNumber abs_a(*this), abs_b(x);
        abs_a.sign = abs_b.sign = 1;
        LongNumber q;
        if (abs_a < abs_b) {
            q = LongNumber("0");
        } else {
            int n = abs_a.len, m = abs_b.len;
            q = LongNumber(n - m + 1, 1);
            for (int i = n - m; i >= 0; --i) {
                LongNumber cur(m + i, 1);
                for (int j = 0; j < m; ++j) cur.numbers[j + i] = abs_b.numbers[j];
                int cnt = 0;
                while (!(abs_a < cur)) {
                    abs_a = abs_a - cur;
                    cnt++;
                }
                q.numbers[i] = cnt;
            }
            while (q.len > 1 && q.numbers[q.len - 1] == 0) q.len--;
        }
        LongNumber rem = abs_a;
        if (is_negative() && !(rem.len == 1 && rem.numbers[0] == 0)) {
            rem = abs_b - rem;
            q = q + LongNumber("1");
        }
        q.sign = sign * x.sign;
        return q;
    }

    LongNumber LongNumber::operator%(const LongNumber& x) const {
        LongNumber q = *this / x;
        LongNumber prod = q * x;
        LongNumber r = *this - prod;
        r.sign = 1;
        return r;
    }

    int LongNumber::get_digits_number() const noexcept { return len; }

    int LongNumber::get_rank_number(int rank) const { return rank > 0 && rank <= len ? numbers[rank - 1] : 0; }

    bool LongNumber::is_negative() const noexcept { return sign == -1; }

    int LongNumber::get_length(const char* const str) const noexcept { int l = 0; while (str[l] != '\0') ++l; return l; }

    std::ostream& operator<<(std::ostream& os, const LongNumber& x) {
        if (x.sign < 0) os << '-';
        for (int i = x.len - 1; i >= 0; --i) os << x.numbers[i];
        return os;
    }
}
