#include <cmath>
#include "vect.h"
using std::sqrt;
using std::sin;
using std::cos;
using std::atan;                //return value of arctan() : radian.
using std::atan2;
using std::cout;


//namespace의 개방성을 이용해서 Vector클래스의 메서드들을 정의
//namespcae is always open!!
namespace VECTOR {
    //1 라디안 내의 각도를 계산하여라(1 라디안에 대한 degree 값을 계산)
    //1라디안 == 180(도)/pi(라디안)      1도 = pi(라디안)/180;
    const double Rad_To_Deg = 45.0 / atan(1.0);        //atan(1.0)은 pi/4를 라디안 값으로 리턴.             
    //반드시 약 57.29577930823값이 되어야 함.
    //1라디안 == 57.2957.... 도 (degree)

    //private메서드들
    //x값과 y값으로 크기를 계산한다
    void Vector::set_mag() {
        mag = sqrt(x * x + y * y);
    }

    void Vector::set_ang() {
        if (x == 0 && y == 0)
            ang = 0.0;
        else
            ang = atan2(y, x);              //atan(y/x)를 리턴함. 리턴값은 항상 라디안 단위
    }

    //극 좌표를 사용하여 x를 설정한다.
    void Vector::set_x() {
        x = mag * cos(ang);                 //cos(ang) = x / mag
    }

    //극 좌표를 이용하여 y를 설정한다.
    void Vector::set_y() {
        y = mag * sin(ang);                 //sin(ang) = y / mag;
    }

    
    //public 메서드들
    Vector::Vector() {                          //default constructor
        x = y = mag = ang = 0.0;
        mode = RECT;
    }

    //form이 r이면 지각 좌표로부터 벡터를 구성
    //직각 좌표 : (x, y)
    //극 좌표 : (mag, ang)
    //form이 p이면 극 좌표로붙터 벡터를 구성 
    Vector::Vector(double n1, double n2, Mode form) {                   //constructor
        mode = form;                                                    //mode 지정.
        if (form == RECT)                       
        {
            x = n1;
            y = n2;
            set_mag();
            set_ang();
        }
        else if (form == POL)
        {
            mag = n1;
            ang = n2 / Rad_To_Deg;
            set_x();
            set_y();
        }
        else
        {
            cout << "Vector()에 전달된 제 3의 매개변수가 잘못되었다.\n";
            cout << "그래서 벡터를 0으로 설정\n";
            x = y = ang = mag = 0;
            mode = RECT;
        }
    }

    //form이 RECT이면 지각 좌표로부터 벡터를 구성 (디폴트)
        //즉 세번째 매개변수가 따로 주어지지 않으면 set메서드는 직각좌표라 파단함.
    //form이 POL이면 극 좌표로붙터 벡터를 구성
    void Vector::reset(double n1, double n2, Mode form)
    {
        mode = form;
        if (form == RECT)
        {
            x = n1;
            y = n2;
            set_mag();
            set_ang();
        }
        else if (form == POL)
        {
            mag = n1;
            ang = n2 / Rad_To_Deg;
            set_x();
            set_y();
        }
        else
        {
            cout << "Vector()에 전달된 제 3의 매개변수가 잘못되었다.\n";
            cout << "그래서 벡터를 0으로 설정\n";
            x = y = ang = mag = 0;
            mode = RECT;
        }
    }

    Vector::~Vector() {                 //destructor

    }

    void Vector::polar_mode() {
        mode = POL;
    }

    void Vector::rect_mode() {
        mode = RECT;
    }


    //연산자 오버로딩
    //두 Vector 객체를 더한다
    Vector Vector::operator+(const Vector & b) const {
        return Vector(x + b.x, y + b.y);            
        //이때 x와 y는 암시적으로 호출된 객체의 private data (즉 메서드를 호출한 객체의 x, y)
    }

    Vector Vector::operator-(const Vector & b) const {
        return Vector(x - b.x, y - b.y);
    }
    
    //Vector객체의 부호를 바꾼다.
    // *** (Vector object) - 이렇게 사용하는 건가..?
    Vector Vector::operator-() const {
        return Vector(-x, -y);
    }

    Vector Vector::operator*(double n) const {
        return Vector(n * x, n * y);
    }

    //프렌드 메서드들
    //n에 Vector객체 a를 곱한다.
    Vector operator*(double n, const Vector & a) {
        return n * a;                   
    }

    //mode가 RECT이면 직각 좌표를 출력
    //mode가 POL이면 극 좌표를 출력
    std::ostream & operator<<(std::ostream & os, const Vector & v) {
        if (v.mode == Vector::RECT)   
        {
            os << "(x,y) = (" << v.x << ", " << v.y << ")";
        }
        else if (v.mode == Vector::POL) 
        {
            os << "(m,a) = (" << v.mag << ", " 
                << v.ang * Rad_To_Deg << ")";
        }
        else
            os << "Vector객체의 모드 지정이 틀렸습니다.";
        return os;
    }

    Vector::operator double() {
        std::cout << "using transfer function\n";
        return mag;
    }
    //operator 뒤에 붙어있는 typename이 리턴값의 데이터형을 알려준다. 따라서 함수 리턴형이 필요없다.
    //객체의 멤버함수이므로 호출시 객체의 정보를 받는다. 따라서 arguments list가 필요가 아리마셍
}//namespace VECTOR의 끝.           