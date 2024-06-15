#ifndef COMPLEX0_H_
#define COMPLEX0_H_
#include <iostream>

class Complex {
    private :
        double real;            //실수부
        double imaginary;       //허수부
    public :
//constructors - make all constructor inline function
    Complex() : real(0.0), imaginary(0.0) {}        //default constructor
    Complex(double r, double i) : real(r), imaginary(i) {}
//public member funciton - operator overloading
    Complex operator+(const Complex &) const;
    Complex operator-(const Complex &) const;           //순서주의 !!
    Complex operator*(const Complex &) const;           // * overloading (C x C)
    Complex operator~() const;                          //conjugate - 공액
//friend function - operator overloading
    friend Complex operator*(double r, Complex c);
    friend std::ostream & operator<<(std::ostream & os, const Complex & c);
    friend std::istream & operator>>(std::istream & is, Complex & c);
};

#endif