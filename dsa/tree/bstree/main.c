#include <stdio.h>
#include <stdlib.h>

// Define a node structure
typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

// Stack structure for storing tree nodes
typedef struct Stack {
    Node** items;
    int top;
    int capacity;
} Stack;

// Stack functions
Stack* createStack(int capacity) {
    Stack* stack = (Stack*) malloc(sizeof(Stack));
    stack->items = (Node**) malloc(sizeof(Node*) * capacity);
    stack->top = -1;
    stack->capacity = capacity;
    return stack;
}

int isEmpty(Stack* stack) {
    return stack->top == -1;
}

int stackSize(Stack* stack) {
    return stack->top + 1;
}

void push(Stack* stack, Node* node) {
    if (stack->top + 1 >= stack->capacity) {
        // Resize if needed
        stack->capacity *= 2;
        stack->items = realloc(stack->items, sizeof(Node*) * stack->capacity);
    }
    stack->items[++stack->top] = node;
}

Node* pop(Stack* stack) {
    if (isEmpty(stack)) return NULL;
    return stack->items[stack->top--];
}

Node* peek(Stack* stack) {
    if (isEmpty(stack)) return NULL;
    return stack->items[stack->top];
}

// Function to create a new node
Node* createNode(int data) {
    Node* newNode = (Node*) malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Insert into a binary search tree
Node* insert(Node* root, int data) {
    if (root == NULL) return createNode(data);
    if (data < root->data)
        root->left = insert(root->left, data);
    else
        root->right = insert(root->right, data);
    return root;
}

// TODO: Implement this using stack
void postOrder(Node* root) {
    // Your iterative post-order implementation here
    Stack* treeStack = createStack(100);
    Node* currNode = root;
    Node* prevPrintedNode = NULL;
    while (!isEmpty(treeStack) || currNode != NULL) {
        if (currNode != NULL) {
            push(treeStack, currNode);
            currNode = currNode->left;
        } else {
            Node* prevRootNode = peek(treeStack);
            if (prevRootNode->right != NULL && prevRootNode->right != prevPrintedNode) {
                currNode = prevRootNode->right;
            } else {
                printf("%d ", prevRootNode->data);
                prevPrintedNode = pop(treeStack); //prevRootNode
            }
        }
    }
}

// Test it
int main() {
    Node* root = NULL;
    root = insert(root, 50);
    insert(root, 30);
    insert(root, 70);
    insert(root, 20);
    insert(root, 40);
    insert(root, 60);
    insert(root, 80);

    printf("Post-order traversal: ");
    postOrder(root);
    printf("\n");

    return 0;
}
