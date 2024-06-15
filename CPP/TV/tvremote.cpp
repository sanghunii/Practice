#include "tvremote.h"
#include <iostream>

bool Tv::volup() {
    if (volume < MaxVal)
    {
        volume++;
        return true;
    }
    else
        return false;
}

bool Tv::voldown() {
    if (volume > MinVal)
    {
        volume--;
        return true;
    }   
    else
        return false;
}

void Tv::chanup() {
    if (channel < maxchannel)
        channel++;
    else
        channel = 1;
}

void Tv::chandown() {
    if (channel > 1)
        channel--;
    else
        channel = maxchannel;
}


//Tv class instance의 현재 setting값 출력.9
void Tv::settings() const {
    using std::cout;
    using std::endl;
    cout << "TV = " << (state == Off ? "OFF" : "ON") << endl;       //현재 TV의 상태에 따라 선택적인 출력을 함.
    if (state == On)        //현재 Tv가 켜진 상태라면
    {
        cout << "볼륨 = " << volume << endl;
        cout << "채널 = " << channel << endl;
        cout << "모드 = "
            << (mode == Antenna ?  "지상파 방송" : "케이블 방송") << endl;
        cout << "입력 = " << (input == TV ? "TV" : "DVD") << endl;
    }
}

void Tv::set_r_mode(Remote & rr) {
    if (state == On) {
        rr.remote_mode = (rr.remote_mode == rr.Normal) ? rr.Conversation : rr.Normal;
    }
    else {
        std::cout << "현재 Tv가 꺼져있습니다.\n";
    }
}



void Remote::show_rm() {
    std::cout << "현재 리모콘 모드: ";
    if (remote_mode == Normal)
        std::cout << "Normal\n";
    else
        std::cout << "Conversation\n";
}



//Conversation Mode
void Tv::ask_to_remote(Remote & rr) {
    if(state == On) {
        std::cout << "Question: ";
        std::getline(std::cin, rr.ask);
    }
    else
        std::cout << "Tv가 꺼져 있습니다.\n";
}



void Remote::answer_to_tv(Tv & rt) {
    using std::cout;
    using std::cin;
    using std::endl;

    cout << "Tv: " << ask << endl << "Me: ";
    getline(cin, rt.answer);
}