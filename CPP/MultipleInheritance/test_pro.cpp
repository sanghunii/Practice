#include <iostream>
#include "emp.h"
using namespace std;

int main() {
    employee em("Trip", "Harris", "Thumper");
    cout << em << endl;
    em.ShowAll();

    manager ma("Amorphia", "Spindragon", "Nuancer", 5);
    cout << ma << endl;
    ma.ShowAll();

    fink fi("Matt", "Oggs", "Oiler", "Juno Barr");
    cout << fi << endl;
    fi.ShowAll();
    highfink hf(ma, "Curly Kew");
    hf.ShowAll();
    cout << "다음 출력을 위해 아무 키나 누르십쇼:\n";
    cin.get();
    highfink hf2;
    hf2.SetAll();

    cout << "abstr_emp * 포인터 사용:\n";
    abstr_emp * tri[4] = {&em , &fi, &hf, &hf2};
    for (int i = 0; i < 4; i++)
        tri[i]->ShowAll();
    
    return 0;
}


/* #Question#
1. 대입 연산자를 정의하지 않은 이유는 무엇인가
2. abstr_emp가 가상 기초 클래스인 이유는 무엇인가?
3. ShowAll()과 SetAll()이 가상인 이유는 무엇인가?
4. highfink 클래스에 데이터 부분이 없는 이유는 무엇인가?
5. operator<()의 한가지 버전만 필요한 이유는 무엇인가?
6. 프로그램 끝 부분 코드를 다음으로 대체하면 어떤일이 벌어지는가?

abstr_emp tri[4] = {em ,fi, hf,hf2}
for (int i = 0;i <4; i ++)
    tri[i].ShowAll();
*/

/* #Answer
1. 
*/