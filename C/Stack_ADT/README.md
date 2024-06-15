/* ***** 코드 개선 일지 ***** */
/*
2023년 10/15 : DeleteNode()코드 오류 발견 --> 11.6 오류 수정함
2023년 11/8 : AddNode() 전면 수정 필요함. 

    Item 입력과 AddNode 작업 분리해야함
        1. 전달인자를 2개로 (사용할 스택, 저장할 Item)
        2. Item즉 노드에 저장할 정보를 입력받는 도움함수를 헤더파일과 인터페이스 구현파일에 추가하자  Node * additem(Item) : Item을 입력받아서 새로운 노드를 만든다.
        3. AddNode는 새로 만들어진 노드를 전달인자로 받아서 Stack에 추가하는 역할만 한다.
        
        --> 이렇게 짜야지 stack.h에 있는 Item의 데이터형만 바꿔가면서 여러 프로그램에 적용 가능함. (for utility)
    
2023년 11/10 : Traverse()의 pfun함수포인터 전달인자를 int형에서 Item형으로 바꿈
        ..     다음 입력을 위해 버퍼를 비우는 인라인 함수 empty()추가.

2023년 11/11 : 정보 입력, 노드 생성, 생성한 노드 Stack에 추가. 각 단계를 분리
                get_item() : 저장할 정보를 받음.
                makenode() : 입력받은 정보를 토대로 노드를 만듦.
                AddNode() : Stack에 노드 추가 

2023년 11/11 : DeleteAll() 연산자 오류 발견. 
                1. 다른 연산자와 마찬가지로 Stack의 주소를 전달인자로 받게하여서 다른 연산자들의 전달인자의 데이터형과 일관성을 띄게 한다.
                2. 재귀 과정에 할당된 메모리를 해제함과 동시에 Stack size또한 갱신해야한다.
..     11/12 : DeleteAll() 수정 완료

2023년 12/28 : Stack ADT연산 이름 변경 및 모듈화 수정사안.
                1. 기존의 AddNode()를 Push()로 이름을 바꾸고 AddNode()를 내부지원 함수로 돌린다.
                2. 이후에 POP연산을 구현한다. (맨 위의 것만 POP하는 것과 Stack 전체를 POP하는 연산 둘 다 구현한다.)
                3. line 68 ~ line 79까지 하나로 묶어서 AddNode()내부지원 함수를 새로 만들어서 그걸로 대체
                4. ShowNode()를 InStack()으로 이름변경
                5. fprintf()이용해서 오류가 났을때 어디서 어떤 오류가 발생했는지 standard error stream을 이용해서 디스플레이에 표시하도록 함.
*/




/*
재귀를 이용한 DeleteNode()구현
단, recursion을 이용해서 구현할때는 전달인자를 Stack *이 아닌 Node * 형 이어야 한다. --> 다른 인터페이스 구현 함수들과 통일성이 떨어짐. 그에따라 사용자가 신경써야할 점이 하나 는다.

void DeleteAll(Stack * pstack)                  //use recursion
{
    Node * pnode = pstack->head;                //Initializing pnode = Stack's head node              
    
    if(pnode->prev != NULL)
        DeleteAll(pnode->prev);                 //recursion
    free(pnode);   
    pstack->size--;                             
}   //recursion 이용. --> recursion은 순서의 역전이 필요할때 유용하게 사용할 수 있다.
        //제일 처음 입력된 노드까지 갔다가 재귀를 종료하고 원래의 차원으로 돌아오면서 맨 처음(스택의 맨 밑에 있는 노드)부터 차례대로 메모리를 해제한다.
     recursion을 이용한 DeleteAll()구현에서는 전달인자를 Stack * 으로 다른 함수 인터페이스들과 일관성을 맞추기 힘들다. 
    따라서 다른 함수 인터페이스들과의 일관성을 위해서 recursion이 아닌 다른 방법으로 DeleteAll()을 구현해야한다.
*/
