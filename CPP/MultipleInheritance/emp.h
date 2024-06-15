//##protected methods에 주목.

#include <iostream>
#include <string>


static void emptybuff() {
    while (getchar() != '\n')
        continue;
}


//# abstr_emp class (Abstract Base Class) 
class abstr_emp {
    private:
        std::string fname;          //이름
        std::string lname;          //성
        std::string job;
    public: 
        abstr_emp();
        abstr_emp(const std::string & fn, const std::string & ln, const std::string & j);
        virtual void ShowAll() const;   //show the all data member
        virtual void SetAll();  // 사용자에게 값들을 입력하라고 요구한다.
        friend std::ostream & operator<<(std::ostream & os, const abstr_emp & e);               //display firstname and lastname
        virtual ~abstr_emp() = 0;
    //destructor is 'pure virtual function' that make this class 'abstrac base class'(ABC)
};










class employee : public abstr_emp {
    public:
        employee();
        employee(const std::string & fn, const std::string & ln, const std::string & j);
        virtual void ShowAll() const;
        virtual void SetAll();
};








class manager : virtual public abstr_emp {
    private:
        int inchargeof;
    protected:
        int InChargeOf() const { return inchargeof; }               //ouput
        int & InChargeOf() { return inchargeof; }                   //input
    public:
        manager();
        manager(const std::string & fn, const std::string & ln, const std::string & j, int ico = 0);
        manager(const abstr_emp & e, int ico);
        manager(const manager & m);
        virtual void ShowAll() const;
        virtual void SetAll();
};
//##protected method
//#상속이 일어나지 않았을때는 data member와 비슷하다.   
//#상속이 일어났을때 data member와 차이점이 생긴다.
//#기초 클래스의 private멤버는 파생클래스 범위 내에서나 클래스 외부 세계에서나 data member에 직접 접근할 수 없다.
//#기초 클래스의 protected멤버는 파생클래스 범위 내부에서는 public 멤버처럼 직접적으로 접근할 수 있다.
//#하지만 외부세계에서는 private 멤버와 마찬가지로 직접 접근할 수 없고 public method를 이용해서 접근해야 한다.








//##fink class
class fink : virtual public abstr_emp {
    private:
        std::string reportsto;
    protected:
        const std::string ReportsTo() const { return reportsto; }
        std::string & ReportsTo() { return reportsto; }
    public:
        fink();
        fink(const std::string & fn, const std::string & ln, const std::string & j, const std::string & rpo);
        fink(const abstr_emp & e, const std::string & rpo);
        fink(const fink & e);
        virtual void ShowAll() const;
        virtual void SetAll();
};










class highfink : public manager, public fink {
    public:
        highfink();
        highfink(const std::string & fn, const std::string & ln, const std::string & j, const std:: string & rpo, int ico);
        highfink(const abstr_emp & e, const std::string & rpo, int ico); 
        highfink(const fink & f, int ico);                                  
        highfink(const manager & m, const std::string & rpo);               
        virtual void ShowAll() const;
        virtual void SetAll();
};


