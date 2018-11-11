#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct StackNode{
    struct BinaryTreeNode *BTNode;
    struct StackNode *next;
};

struct StackNode *createNewStackNode(){
    struct StackNode *newNode = (struct StackNode *)malloc(sizeof(struct StackNode));
    if(!newNode) return NULL;
    else return newNode;
}

struct StackNode *createNewStack(){
    return NULL;
}

void iterateStack(struct StackNode *head){
    struct StackNode *currNode, *nextNode;

    if(!head) return;
    
    currNode = head;
    nextNode = currNode->next;

    int i=0;
    while(nextNode){
        printf("Data at %dth location : %d \n", i, currNode->BTNode);
        currNode = nextNode;
        nextNode = nextNode->next;
        i++;
    }
    printf("Data at %dth location : %d \n \n", i, currNode->BTNode);

}

int StackLength(struct StackNode *head){
    if(!head) return 0;

    int count = 0;
    struct StackNode *currNode = head;

    while(currNode!=NULL){
        count++;
        currNode = currNode->next;
    }

    return count;
}

void push(struct StackNode **top, struct BinaryTreeNode *BTNode){
    struct StackNode *newStackNode = createNewStackNode();
    if(!newStackNode) return;

    newStackNode->BTNode = BTNode;
    newStackNode->next = *top;
    *top = newStackNode;
}

int isEmptyStack(struct StackNode *top){
    return top == NULL;
}

struct BinaryTreeNode *pop(struct StackNode **top){
    if(isEmptyStack(*top)) return NULL;

    struct BinaryTreeNode *data;
    struct StackNode *temp = *top;
    data = temp->BTNode;
    *top = temp->next;
    free(temp);

    return data;
}

struct BinaryTreeNode{
    int data;
    struct BinaryTreeNode *left;
    struct BinaryTreeNode *right;
};

struct BinaryTreeNode *createNewBTNode(){
    struct BinaryTreeNode *BTNode;
    BTNode = (struct BinaryTreeNode *)malloc(sizeof(struct BinaryTreeNode));
    if(!BTNode) return NULL;

    BTNode->left = NULL;
    BTNode->right = NULL;

    return BTNode;
}

struct BinaryTreeNode *createFullBinaryTree_recursive(int depth){
    static int data = 1;
    struct BinaryTreeNode *BTNode;
    BTNode = createNewBTNode();

    if(depth == 0){
        BTNode->data = data++;
        return BTNode;
    }
    BTNode->left = createFullBinaryTree_recursive(depth-1);
    BTNode->right = createFullBinaryTree_recursive(depth-1);
    BTNode->data = data++;

    return BTNode;
}

void postOrderTraversal_recursive(struct BinaryTreeNode *root){
    if(root){
        postOrderTraversal_recursive(root->left);
        postOrderTraversal_recursive(root->right);
        printf("Node : %d\n", root->data);
    }
}

struct BinaryTreeNode *peek(struct StackNode *stack) 
{ 
    if (isEmptyStack(stack)) 
        return NULL; 
    return stack->BTNode; 
}
// An iterative function to do postorder traversal of a given binary tree 
void postOrderTraversal_iterative(struct BinaryTreeNode *root) 
{ 
    // Check for empty tree 
    if (root == NULL) 
        return; 
      
    struct StackNode *stk = createNewStack(); 
    struct StackNode **stack = &stk;
    do
    { 
        // Move to leftmost node 
        while (root) 
        { 
            // Push root's right child and then root to stack. 
            if (root->right) 
                push(stack, root->right); 
            push(stack, root); 
  
            // Set root as root's left child   
            root = root->left; 
        } 
  
        // Pop an item from stack and set it as root     
        root = pop(stack); 
  
        // If the popped item has a right child and the right child is not 
        // processed yet, then make sure right child is processed before root 
        if (root->right && peek(stk) == root->right) 
        { 
            pop(stack);  // remove right child from stack 
            push(stack, root);  // push root back to stack 
            root = root->right; // change root so that the right  
                                // child is processed next 
        } 
        else  // Else print root's data and set root as NULL 
        { 
            printf("Node : %d\n", root->data); 
            root = NULL; 
        } 
    } while (!isEmptyStack(stk)); 
} 

int main(){
    struct BinaryTreeNode *BTRoot;
    BTRoot = createFullBinaryTree_recursive(3);

    postOrderTraversal_iterative(BTRoot);

    return 0;
}