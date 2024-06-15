#ifndef TV_H_
#define TV_H_
#include <iostream>
#include <string>

class Remote;

class Tv {
    friend class Remote;    
    public:
    
        enum {Off, On};
        enum {MinVal, MaxVal = 20};
        enum {Antenna, Cable};
        enum {TV, DVD}; 
    
    //Conversation Mode일때 사용.
        enum {Answer_Len = 50};
        enum {Ask_Len = 50};
        std::string answer;
    
    
        Tv(int s = Off, int mc = 15) : state(s), volume(5),
            maxchannel(mc), channel(2), mode(Cable), input(TV) {}
        
        void onoff() { state = (state == On) ?  Off : On; }
        bool ison() const { return state == On; }
        bool volup();
        bool voldown();
        void chanup();
        void chandown();
        void set_mode() { mode = (mode == Antenna) ? Cable : Antenna; }         //toggle
        void set_input() { input = (input == TV) ? DVD : TV; }                  //toggle
        void settings() const;
    
        void set_r_mode(Remote & rr);
        void show() {std::cout << state;}


        void ask_to_remote(Remote & rr);              //시청자에게 질문을 던진다.
        void show_answer() { std::cout << "yoru answer: " << answer << std::endl; }         //시청자가 내놓은 답을 화면에 출력한다.

    private:
        int state;                      
        int volume;
        int maxchannel;
        int channel;
        int mode;
        int input;
};



class Remote {
    friend class Tv;
    private:
        enum {Normal, Conversation};

        int mode;
        int remote_mode;
        
        //Conversation mode일때 사용
        enum {Answer_Len = 50};
        enum {Ask_Len = 50};
        std::string ask;
        
    public:
        Remote(int m = Tv::TV) : mode(m), remote_mode(Normal) {}

        bool volup(Tv & t) { return t.volup(); }
        bool voldown(Tv & t) { return t.voldown(); }
        void onoff(Tv & t) { return t.onoff(); }
        void chanup(Tv & t) { return t.chandown(); }
        void chandown(Tv & t) {return t.chandown(); }
        void set_chan(Tv & t, int c) { t.channel = c; }     
        void set_mode(Tv & t) { t.set_mode(); }
        void set_input(Tv & t) { t.set_input(); }
        void show_rm();

        //Conversation Mode
        void answer_to_tv(Tv & rt);

};


#endif


//Remote는 Tv로부터 받은 질문을 저장할 수 있고
//Tv는 Remote로부터 받은 답변을 저장할 수 있다.