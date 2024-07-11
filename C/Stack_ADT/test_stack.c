//Test stack.h & stack.c
//Are functions well operating

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "stack.h"


void multiply(Node * pnode) {                     //Test for Traverse()
        pnode->item *= 10;
    }

int main(void) {
    Stack t_stack;



//initialize stack
    Initialize(&t_stack);
    printf("%d\n", t_stack.size);



//Check stack is empty
    if(StackIsEmpty(&t_stack))
        printf("There is empty stack\n");



//Check Push() and StackItemCount()
    printf("현재 노드 갯수 : %d\n", StackItemCount(&t_stack));
    while(!StackIsFull(&t_stack)) 
        for(int i = 1; i <= 10; i++) {
            if(StackIsFull(&t_stack))
                break;
            Push(&t_stack, i);
            printf("현재 노드 갯수 : %d\n", StackItemCount(&t_stack));
        }


    
//Check POP()
    while (!StackIsEmpty(&t_stack)) {
        printf("POP :  ");
        POP(&t_stack);
    }
    


//Refill the value to Stack 
    while(!StackIsFull(&t_stack)) 
        for(int i = 1; i <= 10; i++) {
            if(StackIsFull(&t_stack))
                break;
            Push(&t_stack, i);
        }


//Test InStack() function
    Item valid_value = 5;
    Item invalid_value = 11;
    InStack(&t_stack, valid_value);
    InStack(&t_stack, invalid_value);



//Check DeleteNode() & ShowAll()
    Item val_target = 5;
    Item inval_target = 11;

    DeleteNode(&t_stack, inval_target);         //Delete invalid value
    printf("\n------------Form Now Show All the contents1---------\n");
    ShowAll(&t_stack);

    DeleteNode(&t_stack, val_target);           //Error Point
    printf("\n------------Form Now Show All the contents2---------\n");
    ShowAll(&t_stack);

    //check DeleteAll()
    DeleteAll(&t_stack);
    printf("\n------------Form Now Show All the contents3---------\n");
    ShowAll(&t_stack);
    printf("size : %d\n", t_stack.size);
    printf("head pointer : %p", t_stack.head);


//Refill Stack for test Traverse()
    int temp = 1;
    while (t_stack.size != SSIZE) {
        Push(&t_stack, temp);
        temp++;
    }
    printf("\n------------Form Now Show All the contents4---------\n");
    ShowAll(&t_stack);


//Check Traverse()
    Traverse(t_stack.head, multiply);
    printf("\n------------Form Now Show All the contents5---------\n");
    ShowAll(&t_stack);

    return 0;
}