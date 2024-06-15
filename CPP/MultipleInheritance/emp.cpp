#include <iostream>
#include <string>
#include "emp.h"







//##abstr_emp methods
abstr_emp::abstr_emp() : fname("no name"), lname("no name"), job("no job") {};

abstr_emp::abstr_emp(const std::string & fn, const std::string & ln, const std::string & j) 
            : fname(fn), lname(ln), job(j) {};

void abstr_emp::ShowAll() const {
    std::cout << lname << " " << fname << std::endl
                << "job: " << job << std::endl;
}

void abstr_emp::SetAll() {
    using namespace std;
    cout << "put the first name: ";
    getline(std::cin, fname);
    cout << "put the last name: ";
    getline(std::cin, lname);
    cout << "put the job: ";
    getline(std::cin, job);
}

//friend함수란 어떤 클래스의 멤버함수가 아님에도 불구하고 그 어떤 클래스의 데이터 멤버(private member)에 접근할 수 있는 권한을 가진 함수를 뜻한다.
std::ostream & operator<<(std::ostream & os, const abstr_emp & e) {
    os << e.lname << " " << e.fname << std::endl
         << "job: " << e.job;
    
    return os;
}

abstr_emp::~abstr_emp() {};





//##employee methods
employee::employee() : abstr_emp() {};

employee::employee(const std::string & fn, const std::string & ln, const std::string & j)
                    : abstr_emp(fn, ln, j) {};


void employee::ShowAll() const {
    abstr_emp::ShowAll();
}

void employee::SetAll() {
    abstr_emp::SetAll();
}




//##manager methods
manager::manager() : abstr_emp("no name", "no name", "no job"), inchargeof(0) {};

manager::manager(const std::string & fn, const std::string & ln, const std::string & j, int ico) 
                : abstr_emp(fn, ln, j), inchargeof(ico) {};
    
manager::manager(const abstr_emp & e, int ico) : abstr_emp(e), inchargeof(ico) {};

manager::manager(const manager & m) : abstr_emp(m) {
    inchargeof = (m.inchargeof);
}

void manager::ShowAll() const {
    abstr_emp::ShowAll();
    std::cout << "incharge of: " << inchargeof << std::endl;
}

void manager::SetAll() {
    abstr_emp::SetAll();
    std::cout << "put the inchargeof: ";
    std::cin >> inchargeof;
    emptybuff();
}






//##fink method
fink::fink() : abstr_emp("noname", "no name", "no job"), reportsto("no report") {};

fink::fink(const std::string & fn, const std::string & ln, const std::string & j, const std::string & rpo) 
            : abstr_emp(fn, ln, j), reportsto(rpo) {};

fink::fink(const abstr_emp & e, const std::string & rpo) : abstr_emp(e), reportsto(rpo) {};

fink::fink(const fink & e) : abstr_emp(e) {
    reportsto = e.reportsto;
}

void fink::ShowAll() const {
    abstr_emp::ShowAll();
    std::cout << "reports to: " << reportsto << std::endl;
}

void fink::SetAll() {
    abstr_emp::SetAll();
    std::cout << "put the who get reports: ";
    getline(std::cin, reportsto);
}






//##highfink method
highfink::highfink() : abstr_emp("no name", "no name", "no job")
                        , manager("no name", "no name", "no job", 0), fink("no name", "no name", "no job", "no reportsto") {};

highfink::highfink(const std::string & fn, const std::string & ln, const std::string & j, const std:: string & rpo, int ico) 
                : abstr_emp(fn, ln, j), manager(fn, ln, j, ico), fink(fn, ln, j, rpo) {};

highfink::highfink(const abstr_emp & e, const std::string & rpo, int ico) 
                : abstr_emp(e), manager(e, ico), fink(e, rpo) {};

highfink::highfink(const fink & f, int ico) 
                : abstr_emp((abstr_emp &)f), manager((abstr_emp &)f, ico) {}

highfink::highfink(const manager & m, const std::string & rpo)
                : abstr_emp((abstr_emp &)m), fink((abstr_emp &)m, rpo) {};

void highfink::ShowAll() const {
    abstr_emp::ShowAll();
    std::cout << "incharge of: " << manager::InChargeOf() << std::endl;
    std::cout << "reports to: " << fink::ReportsTo() << std::endl;
}

void highfink::SetAll() {
    abstr_emp::SetAll();

    abstr_emp::SetAll();
    std::cout << "put the inchargeof: ";
    std::cin >> InChargeOf();
    emptybuff();

    std::cout << "put the who get reports: ";
    getline(std::cin, ReportsTo());
}