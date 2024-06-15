/*
리스트에 특정 데이터형의 항목을 0개 또는 그 이상을 저장할 수 있다.
비어 있는 리스트를 생성할 수 있다.
리스트에 항목들을 추가할 수 있다.
리스트에 있는 항목을 삭제할 수 있다. 
리스트가 비어 있는지 결정할 수 있다.
리스트가 가득 차 있는지 결정할 수 있다. 
리스트에 원하는 데이터가 저장되어 있는지 확인해 볼 수 있다.
리스트의 각 항목에 대해 몇가지 원하는 동작을 수행할 수 있다.
    - 이때 원하는 동작(을 하는 함수)은 private 멤버에 정의한다.
        * public인터페이스를 구성하지 않는 클래스 기능의 세부적인 구현은 private멤버에 넣는다.
    - 해당 리스트를 링크드 리스트로 구현해 보자.

*/

#ifndef LIST01_H_
#define LIST01_H_


typedef int Item;             


class List {              
    private :
        enum {MAX = 10};
        Item * items;                            //Head 추적
        int ct;                                 //리스트에 추가된 항목 갯수 추적
        void apply(Item & I) {I += 20;}        //visit()인터페이스에서 호출되어 각 항목에 적용되는 함수, 그때그때 필요에 따라 수정해서 사용
    public :
        List();         //default constructor        이것 외에 별도의 생정자는 가지지 않는다.
        ~List();        //destructor
        bool List_isempty() const;                    //비었으면 true, 아니면 false
        bool List_isfull() const;                     //꽉찼으면 true, 아니면 false
        bool List_add();
        bool List_delete();                 
        bool List_Search(const Item &) const ;         //원하는 정보가 있는지 확인한다, 있으면 true, 없으면 false      
        void List_show();
        void visit(void (*pf)(Item &));         //각 항목을 방문하여 원하는 조작을 가한다. 적용할 조작의 내용은 private : apply()가 결정.
};


#endif


//사용자는 public interface의 사용법만 숙지하면 되게끔.


//추후에 template functior과 explicit specialization을 이용해서 좀 더 일반적인 클래스 (generic class)를 만들어보자