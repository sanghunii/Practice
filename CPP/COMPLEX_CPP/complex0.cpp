#include "complex0.h"
//constructor - all functions are inline function


//operator overloading
Complex Complex::operator+(const Complex & c) const {
    Complex temp(real + c.real, imaginary + c.imaginary);
    return temp;
}

Complex Complex::operator-(const Complex & c) const {
    Complex temp(real - c.real, imaginary - c.imaginary);
    return temp;
}

Complex Complex::operator*(const Complex & c) const {
    Complex temp;
    temp.real = (real * c.real) - (imaginary * c.imaginary);
    temp.imaginary = (real * c.imaginary) + (imaginary * c.real);

    return temp;
}

//conjugate
Complex Complex::operator~() const {
    Complex temp;
    temp.real = -real;
    temp.imaginary = -imaginary;

    return temp;
}



//from now friend function
Complex operator*(double r, Complex c) {
    Complex temp;
    temp.real = c.real * r;
    temp.imaginary = c.imaginary * r;

    return temp;
}

std::ostream & operator<<(std::ostream & os, const Complex & c) {
    os << "(" << c.real << "," << c.imaginary << "i)";
    return os;
}

std::istream & operator >> (std::istream & is, Complex & c) {
    using std::cout;
    
    cout << "하나의 복소수를 입력하십시오(끝내려면 q): \n";
    cout << "실수부: ";
    while (!(is >> c.real))
        return is;
    cout << "허수부: ";
    while (!(is >> c.imaginary))
        return is;
    return is;
}