#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include "vect.h"

int main() {
    using namespace std;
    using VECTOR::Vector;
    srand(time(0));
    double direction;
    Vector step;
    Vector result(0.0, 0.0);
    unsigned long steps = 0;
    double target;
    double dstep;

    char filename[40];
    cout << "출력값을 저장할 파일명 : ";
    cin.getline(filename, 40);
    ofstream File_out;                      //output filestream객체를 하나 선언
    File_out.open(filename);        //그 객체랑 원하는 파일과 연결.
    File_out.setf(ios_base::fixed);
    File_out.precision(2);


    int test_count = 0;                             //실험 횟수를 카운팅 한다.
    cout << "목표 거리를 입력하십시오(끝내려면 q): ";
    while (cin >> target)
    {
        ++test_count;
        cout << "보폭을 입력하십시오: ";
        if (!(cin >> dstep))
            break;
        File_out << test_count <<"번째 실험\n";
        File_out << "목표 거리 : " << target << ", 보폭 : " << dstep << endl;
        File_out << steps << ": (x, y) = (" 
            << result.xval() << result.yval() << ")\n";
        while (result.magval() < target)
        {
            direction = rand() % 360;                           //0에서 359까지의 값이 무작위로 대입된다. 이때 이거는 각도임.
            step.reset(dstep, direction, Vector::POL);          //각도가 랜덤하게 결정. 보폭은 사용자가 입력한대로
            result = result + step;
            steps++;
            File_out << steps << ": (x, y) = (" 
            << result.xval() << result.yval() << ")\n";
        }
        File_out << steps << "걸음을 걸은 후 현재 위치:\n";
        File_out << result << endl;
        result.polar_mode();
        File_out << "또는\n" << result << endl;
        File_out << "걸음당 기둥에서 벗어난 평균 거리 = "
            << result.magval()/steps << endl << endl;
        steps = 0;
        result.reset(0.0, 0.0);
        cout << "목표 거리르 입력하십시오(끝내려면 q): ";
    }
    cout << "프로그램을 종료합니다\n";
    cin.clear();
    while (cin.get() != '\n')
        continue;
    File_out.close();               //연 파일 스트림 닫아줌.
    return 0;
}