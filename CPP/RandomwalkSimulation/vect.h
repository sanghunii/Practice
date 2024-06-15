#ifndef VECT_H_
#define VECT_H_
#include <iostream>

namespace VECTOR {
    class Vector {
        public :
            enum Mode {RECT, POL};                       //RECT = 0, POL = 1        //객체의 상태멤버는 RECT or POL 둘 중에 하나의 값을 갖는다.
        private :
            double x;
            double y;     
            double mag;             //magnitude
            double ang;             //angle
            Mode mode;              //객체의 상태멤버
        //값을 세팅하는 private 메서드들
            void set_mag();
            void set_ang();
            void set_x();
            void set_y();
        public :
            Vector();
            Vector(double n1, double n2, Mode form = RECT);
            void reset(double n1, double n2, Mode form = RECT);             //destructor를 해당 메서드 보다 더 빠른 순서로 선언하는게 더 깔끔하지 않나..?
            ~Vector();
            double xval() const {return x;}
            double yval() const {return y;}
            double magval() const{return mag;}
            double angval() const {return ang;}
            void polar_mode();
            void rect_mode();
        //연산자 오버로딩
            Vector operator+(const Vector & b) const;
            Vector operator-(const Vector & b) const;
            Vector operator-() const;
            Vector operator*(double n) const;
        //프렌드 함수
            friend Vector operator*(double n, const Vector & a);
            friend std::ostream &
                operator<<(std::ostream & os, const Vector & v);
        //변환함수 - no have ret_val & argument list
            explicit operator double();
    };

    // namespace VECTOR의 끝
}

#endif