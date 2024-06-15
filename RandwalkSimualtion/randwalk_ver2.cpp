#include "vect.h"
#include <fstream>
#include <cstdlib>
#include <ctime>

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

//파일 스트림 연결
    char filename[40];
    cout << "출력값을 저장할 파일명 : ";
    cin.getline(filename, 40);
    ofstream File_out;                      //output filestream객체를 하나 선언
    File_out.open(filename);        //그 객체랑 원하는 파일과 연결.
    File_out.setf(ios_base::fixed);
    File_out.precision(2);

    int test_ct;                //총 몇번의 실험을 할 것인지 정한다
    int ctr = 0;                    //루프 controler.
    cout << "몇번의 실험을 진행할 것인지 입력 : ";
    (cin >> test_ct).get();
    int max = 0;                    //전체 시뮬레이션의 최대값
    int min = 0;                    //전체 시물레이션의 최소값
    double average;                 //전체 시뮬레이션의 평균값
    double total_step = 0;              //전체 시뮬레이션의 총 걸음수
    //average = total_step / tset_ct;


    cout << "목표 거리를 입력하십시오(끝내려면 q): ";
    while (!(cin >> target))
    {
        cout << "잘못된 값이 입력됨\n";
        cout << "목표 거리를 입력하십시오(끝내려면 q): ";
        cin.clear();
        while (cin.get() != '\n')
            continue;
        continue;
    }
    cout << "보폭을 입력: ";
    while (!(cin >> dstep))
    {
            cout << "잘못된 값이 입력됨\n";
            cout << "보폭을 입력: ";
            cin.clear();
            while (cin.get() != '\n')
            continue;
    }
    for (int ct = 0; ct < test_ct; ct++)
    {
        while (result.magval() < target)
        {   
            direction = rand() % 360;                           //0에서 359까지의 값이 무작위로 대입된다. 이때 이거는 각도임.
            step.reset(dstep, direction, Vector::POL);          //각도가 랜덤하게 결정. 보폭은 사용자가 입력한대로
            result = result + step;
            steps++;
        }
        total_step += steps;
        if (ct == 0)
            max = min = steps;
        else 
        {
            max = max > steps ? max : steps;            //최대값 갱신
            min = min < steps ? min : steps;            //최소값 갱신
        }
        result = Vector();                  //result객체 0으로 초기화
        steps = 0;                          //steps 초기화.
    }
    average = total_step / test_ct;

    File_out << "시뮬레이션 횟수 : " << test_ct << endl
        << "maximum value : " << max << endl
        << "minimum value : " << min << endl
        << "average value : " << average << endl;

    File_out.close();
    return 0; 
}