//
// Created by Vedana Voronina on 30.03.17.
//

#ifndef TASK3_RATIONAL_H
#define TASK3_RATIONAL_H

class rational {
public:
    rational(int);

    rational(int, int);

    int getNum() const;

    int getDenom() const;

    rational operator+(rational const &) const;

    rational operator-(rational const &) const;

    rational operator*(rational const &) const;

    rational operator/(rational const &) const;

private:
    int num;
    int denom;

    int gcd(int x, int y) const;

    void set_sign();

    void set_sign(rational &x) const;
};

#endif //TASK3_RATIONAL_H
