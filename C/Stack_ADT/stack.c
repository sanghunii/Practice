/* 인터페이스 구현 파일 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"


/* 내부 지원 함수 프로토타입 */
static Node * searching(const Stack *, Item);    //Stack에서 원하는 정보를 가진 노드를 찾아서 그 노드의 주소를 리턴. (입력된 순서 역순으로 하나씩 뒤져봐야함.)
static Node * makenode(Item item);          //새로운 노드를 만들어서 그 노드에 정보(item)을 저장하고 그 노드의 주소를 리턴.
static Node * findparent(const Stack *, Item);    //그 노드를 가리키는 노드를 찾는다.
static bool AddNode(Stack * pstack, Node * new_node);                       
inline static void empty(void);              //버퍼를 비우는 인라인 함수.

/* ****caution ***** */
/* findparent()를 사용할때는 찾고자 하는 노드가 첫번째 노드가 아님을 가정한다. */





/* ****** 인터페이스 함수 구현 ****** */
void Initialize(Stack * pstack)             //초기화
{
    pstack->head = NULL;
    pstack->size = 0;
}

bool StackIsEmpty(const Stack * pstack)         //비어있는지
{
    return ((pstack->head == NULL && pstack->size == 0) ? true : false);
}

bool StackIsFull(const Stack * pstack)              //꽉찼는지
{
    return pstack->size == SSIZE;
}

int StackItemCount(const Stack * pstack)                //현재 스택에 들어있는 정보 갯수를 리턴한다. 
{
    return pstack->size;
}


bool Push(Stack * pstack, Item si)                                           //bool Push(Stack * pstack, Item si)로 이름변경    
{
    Node * new_node;
    
    if ((new_node = makenode(si)) == NULL)     //여기서 새로운 노드를 만든다.
    {
        fprintf(stderr, "노드 만들기를 실패했습니다.\n");
        return false;
    }
    if (StackIsFull(pstack))
    {
        fprintf(stderr, "스택에 빈자리가 없습니다.\n");
        free(new_node);
        return false;
    }                                            
    if (searching(pstack, si))                   
    {
        fprintf(stderr, "해당 숫자는 이미 저장되어 있습니다.\n");
        free(new_node);
        return false;
    }
    AddNode(pstack, new_node);                                                                                              

    return true;
}

void POP(Stack * pstack)
{
    Node * temp;                        

    if (StackIsEmpty(pstack))
    {   
        fpritnf(stderr, "Stack이 비어있습니다.\n");
        return;
    }
    printf("%d\n", pstack->head);
    temp = pstack->head;
    pstack->head = pstack->head->prev;
    free(temp);
}


bool DeleteNode(Stack * pstack, Item si)
{
    Node * t_node;                          //target node
    Node * parent;                          //target node가 중간에 끼어있을때 사용.
    int temp;
    
    if (!(t_node = searching(pstack, si)))
    {
        fprintf(stderr, "해당 정보를 저장하고 있는 노드가 존재하지 않습니다.\n");
        return false;
    }
    /* 해당 정보를 저장하고 있는 노드가 존재함을 확인하면 */
    if (t_node == pstack->head)   //if target node is head node
    {
        pstack->head = t_node->prev;                  
        free(t_node);                                                
        pstack->size--;
    }
    else if (t_node->prev == NULL)              //if target node is tail node
    {
        parent = findparent(pstack, si);        //tail node의 부모노드를 찾는다.
        free(t_node);                           //target node를 메모리에서 해제한다.
        parent->prev = NULL;                    //기존의 tail node의 부모노드를 tail node로 새로 지정.
        pstack->size--;
    }
    else   //target이 중간에 끼어 있으면
    {
        parent = findparent(pstack, si);
        parent->prev = t_node->prev;
        free(t_node);
        pstack->size--;
    }

    return true;
}


void DeleteAll(Stack * pstack)                  //use recursion
{
    Node * pnode = pstack->head;                //Initializing pnode = Stack's head node              
    Node * tnode;                               //target node : 메모리에서 해제시킬 노드.
    
    while (pstack->size != 0)                 //pstack->size == 0이면 모든 노드들이 삭제되었다는 뜻이므로 해당 루프문의 조건문을 이렇게 짰다.
    {
        tnode = pnode;
        pnode = pnode->prev;
        free(tnode);
        pstack->size--;
    } 
}       
/**** recursion을 이용한 DeleteAll()구현에서는 전달인자를 Stack * 으로 다른 함수 인터페이스들과 일관성을 맞추기 힘들다. 
 *      따라서 다른 함수 인터페이스들과의 일관ㅌ을 위해서 recursion이 아닌 다른 방법으로 DeleteAll()을 구현해야한다.
*/

void InStack(Stack * pstack, Item si)
{
    Node * target;

    target = searching(pstack, si);

    if (target == NULL)
        printf("%d는 저장되어 있지 않습니다.\n", si);
    else
        printf("%d는 저장되어 있습니다.\n", si);
}

void ShowAll(const Stack * pstack)
{
    Node * temp;

    temp = pstack->head;
    while (temp)    
    {
        printf("%d \n", temp->item);
        temp = temp->prev;
    }
}

void Traverse(Node * pnode, void (* pfun)(Item n))
{
    if (pnode->prev != NULL)
        Traverse(pnode->prev, pfun);
    (*pfun)(pnode->item);                   //마찬가지로 recursion을 이용해서 맨처음 추가한 노드부터 함수 적용.
}

bool GetItem(Item * si)
{
    puts("저장하고자 하는 정보를 입력하시오:");
    if (scanf("%d", si) == 1)
    {
        empty();
        return true;
    }
    else
    {
        puts("올바르지 않은 입력입니다.");
        empty();
        return false;
    }
}




/* ***** 지원 함수 ***** */
static Node * findparent(const Stack * pstack, Item si)
{
    Node * parent;
    
    parent = pstack->head;
    
    while (parent->prev)     //parent가 마지막 노드가 아니면 계속 루프 진행.
        if (parent->prev->item == si)
            break;
        else
            continue;           //if-else문은 하나의 문장으로 C가 받아들이기 때문에 중괄호 필요 없다 하지만 if문이 while()루프의 몸체라는 사실을 명확히 하기 위해 중괄홀르 씌워주자.         
    

    return parent;              //리턴값이 NULL이면 si를 가리키는 노드를 가리키는 노드가 없음.
}

static Node * searching(const Stack * pstack, Item si)
{
    Node * temp;
     
    temp = pstack->head;
    while (temp != NULL)
        if (temp->item == si)
            break;
        else
        
            temp = temp->prev;          //if - else문은 전체가 하나의 문장으로 카운트 된다.

    return temp;                    
}   //원하는 item이 들어있는 노드를 찾으면 그 노드를 리턴. Item을 못찾았으면 temp의 값은 NULL

static Node * makenode(Item si)             //si : stack item
{
    Node * new_node;
    
    if ((new_node = (Node *)malloc(sizeof(Node))) == NULL)
        return NULL;
    new_node->item = si;

    return new_node;
}

static bool AddNode(Stack * pstack, Node * new_node)
{
    if (StackIsEmpty(pstack))           //추가하는 노드가 Head node.
    {
        puts("첫번째 노드를 성공적으로 추가하였습니다.");
        pstack->head = new_node;
        pstack->size++;
    }
    else
    {
        new_node->prev = pstack->head;            //새로만들어진 노드와 기존 노드를 연결
        pstack->head = new_node;                  //Stack의 recnet멤버가 new_node를 가리키도록 갱신
        pstack->size++;                             //Stack size 갱신
        puts("노드를 성공적으로 만들었습니다.");
    } 
    
}

inline static void empty()
{
    while (getchar() != '\n')
        continue;
}
