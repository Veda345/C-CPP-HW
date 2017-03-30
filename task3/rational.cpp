//
// Created by Vedana Voronina on 30.03.17.
//
#include "rational.h"

int rational::gcd(int x, int y) const {
    if (x < 0)
        x = -x;
    if (y < 0)
        y = -y;
    while (y) {
        x %= y;
        int t = x;
        x = y;
        y = t;
    }
    return x;
}

void rational::set_sign() {
    if (denom < 0) {
        num *= -1;
        denom *= -1;
    }
}

void rational::set_sign(rational &x) const {
    if (x.denom < 0) {
        x.num *= -1;
        x.denom *= -1;
    }
}

rational::rational(int n) {
    num = n;
    denom = 1;
    set_sign();
}

rational::rational(int n, int d) {
    int divisor = gcd(n, d);
    num = n / divisor;
    denom = d / divisor;
    set_sign();
}

int rational::getNum() const {
    return num;
}

int rational::getDenom() const {
    return denom;
}

rational rational::operator+(const rational &x) const {
    int resN = num * x.denom + x.num * denom;
    int divisor = gcd(resN, denom * x.denom);
    rational res = rational(resN / divisor, denom * x.denom / divisor);
    set_sign(res);
    return res;
}

rational rational::operator-(const rational &x) const {
    int resN = num * x.denom - x.num * denom;
    int divisor = gcd(resN, denom * x.denom);
    rational res = rational(resN / divisor, denom * x.denom / divisor);
    set_sign(res);
    return res;
}

rational rational::operator*(const rational &x) const {
    int divisor = gcd(num * x.num, denom * x.denom);
    rational res = rational(num * x.num / divisor, denom * x.denom / divisor);
    set_sign(res);
    return res;
}

rational rational::operator/(const rational &x) const {
    int divisor = gcd(num * x.denom, denom * x.num);
    rational res = rational(num * x.denom / divisor, denom * x.num / divisor);
    set_sign(res);
    return res;
}