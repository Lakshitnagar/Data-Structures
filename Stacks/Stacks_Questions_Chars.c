#include<stdio.h>
#include<stdlib.h>

struct StackNode{
    char data;
    struct StackNode *next;
};

struct StackNode *createNewNode(){
    struct StackNode *newNode = (struct StackNode *)malloc(sizeof(struct StackNode));
    if(!newNode) return NULL;
    else return newNode;
}

struct StackNode *createNewStack(){
    return NULL;
}

void iterateStack(struct StackNode *head){
    struct StackNode *currNode, *nextNode;
    printf("iterate stack\n");

    if(!head) {
        printf("empty head\n");
        return;
    };
    
    currNode = head;
    nextNode = currNode->next;

    int i=0;
    while(nextNode){
        printf("Data at %dth location : %c \n", i, currNode->data);
        currNode = nextNode;
        nextNode = nextNode->next;
        i++;
    }
    printf("Data at %dth location : %c \n \n", i, currNode->data);

}

int ListLength(struct StackNode *head){
    if(!head) return 0;

    int count = 0;
    struct StackNode *currNode = head;

    while(currNode!=NULL){
        count++;
        currNode = currNode->next;
    }

    return count;
}

void push(struct StackNode **top, int data){
    struct StackNode *newStackNode = createNewNode();
    if(!newStackNode) return;

    newStackNode->data = data;
    newStackNode->next = *top;
    *top = newStackNode;
}

int isEmptyStack(struct StackNode *top){
    return top == NULL;
}

int pop(struct StackNode **top){
    if(isEmptyStack(*top)) return INT_MIN;

    int data;
    struct StackNode *temp = *top;
    data = temp->data;
    *top = temp->next;
    free(temp);

    return data;
}


int isSymbolsBalanced(char *s){
    if(!s) return 0;

    struct StackNode *stack = createNewStack();
    struct StackNode **top = &stack;
    char poppedItem;

    while(*s){
        printf("%c\n", *s);
        if(*s=='(' || *s=='[' || *s=='{'){
            push(top, *s);
        }

        if(*s==')' || *s==']' || *s=='}'){
            if(!isEmptyStack(*top))
                poppedItem = pop(top); 
            else
                return 0;
            
            if((poppedItem=='('&&*s==')') || (poppedItem=='['&&*s==']') || (poppedItem=='{'&&*s=='}')){
                s++;
                continue;
            }
            else
                return 0;
        }
        
        s++;
    }

    iterateStack(*top);

    if(isEmptyStack(*top))
        return 1;
    else
        return 0;
}

int main(){
    char *string = "(((a+b)/(a-b))+c)*d)";
    int balanceFlag = isSymbolsBalanced(string);
    printf("is '%s' balanced? : %d\n", string, balanceFlag);

    return 0;
}