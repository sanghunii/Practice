#include "list01.h"
#include <iostream>


List::List() {
    items = new int[MAX];                        
    ct = 0;                         //항목 갯수 0
    std::cout << "크기 " << MAX << "개 짜리 리스트 생성\n"
            << "현재 항목 수 : " << ct << std::endl;
}


List::~List() {
    delete [] items;
    std::cout << "List를 삭제했습니다.\n";
}


bool List::List_isempty () const {
    if (ct == 0)
        return true;
    return false;
}


bool List::List_isfull () const {
    if (ct == MAX)
        return true;
    return false;
}


bool List::List_add() {
    using std::cout;
    using std::cin;
    using std::endl;
    
    if (List_isfull()) 
    {
        cout << "리스트가 가득 찼습니다.\n";
        return false;
    }
    else {
        cout << "Item입력 : ";
        int temp_item;
        while(true) {
            if (cin >> temp_item)
            {
                while (cin.get() != '\n')
                    continue;
                break;
            }
            else 
            {
                cout << "잘못된 입력. 다시 입력 하시오\n";
                continue;
            }   
        }
        items[ct++] = temp_item;
        cout << items[ct - 1] << "이 리스트에 추가되었습니다.\n";
        cout << "현재 저장된 항목 수 : " << ct << "개\n";
        
        return true;
    }
}


bool List::List_delete() {
    using std::cin;
    using std::cout;
    using std::endl;

    Item delete_item;
    cout << "삭제할 Item을 입력 : ";
    cin >> delete_item;
    if (List_Search(delete_item))
    {
        int count;
        for (count = 0; count < ct; count++)
            if (delete_item == items[count])
            {
                if (count == MAX - 1)                   //tail item 이면 걍 삭제
                {
                    items[MAX - 1] = 0;
                    ct--;
                }
                else                                    //아니면 리스트를 갱신해줘야 한다.
                {    
                for (int i = count; i < ct - 1; i++)
                    items[i] = items[i + 1];
                ct--;
                }
            }
        return true;
    }

    return false;
}


void List::List_show() {
    for (int count = 0; count < ct; count++)
        std::cout << count + 1 << "번째 항목 : " << items[count] << std::endl;
}


bool List::List_Search(const Item & i) const {
    int count;
    if (List_isempty())
        std::cout << "리스트가 텅 비었습니다\n";
    else
    {
        for (count = 0; count < ct; count++)
            if (i == items[count])
            {
                std::cout << count + 1 << "번째 항목에 해당 데이터가 저장되어 있습니다.\n";
                return true;
            }
            else
                continue;
    }
    if (count >= ct)
        std::cout << "해당 항목이 리스트에 존재하지 않습니다.\n";
    return false;
}

void List::visit(void (*pf)(Item & i)) {
    for (int count = 0; count < ct; count++)
        pf(items[count]);
}