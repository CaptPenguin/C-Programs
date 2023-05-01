#include <stdio.h>
#include <stdlib.h>


/*Basic Structs - Program to showcase using structs*/
//Traditional definition of a struct
struct Point
{
    int x;
    int y;
};
typedef struct Point Point; //It can be annoying to type out struct Point everytime, so we rename it to just Point

//We can typedef the struct in the definition as well!
//Structs can be made from other structs!
typedef struct Triangle
{
    Point p1, p2, p3;
} Triangle;
//Structs can also refer to themselves
typedef struct Node{
    int val;
    struct Node* next;
} Node;

void addNode(Node*, Node*);

int main(){
    //different ways of assigning struct values
    Point newPoint;
    newPoint.x = 3;
    newPoint.y = 4;

    Point vectPoint = {7,8};
    Point OtherVect = {.y = 1, .x = 5};

    Triangle myTriangle = {newPoint, vectPoint, OtherVect};

    Node root = {2,NULL}; //Note: NULL is just a placeholder for 0, its defined in stdlib
    Node next,third,fourth;
    next.val = 7;
    third.val = 9;
    fourth.val = 0;
    addNode(&root, &next);
    addNode(&next, &third);
    addNode(&third, &fourth);
    addNode(&fourth,NULL);

    printf("[*]My Triangle has points at {%d,%d}, {%d,%d}, and {%d,%d}\n", myTriangle.p1.x, myTriangle.p1.y, myTriangle.p2.x, myTriangle.p2.y, myTriangle.p3.x,myTriangle.p3.y);
    printf("[*]A Point is %ld bytes, and a Triangle is %ld bytes\n", sizeof(Point), sizeof(Triangle));

    printf("[*]The list is constructed as follows, starting at %p:\n", &root);
    //Note: Normally when accessing a struct we do struct.member
    //However, a Node* is a POINTER, not a struct, so . notation does not work!
    //We would have to deference it then use . notation, as follows:
    // *(base).next to access next
    //This notation is hard to read, so the shorthand -> is used to deference then access a member
    for(Node * base = &root; base->next != NULL; base = base->next){
        printf("[*]val: %d, addr of next is %p\n", base->val, base->next);
    }

    printf("[*]The size of a Node is %ld, and the size of the list would be %ld\n", sizeof(Node), sizeof(Node) * 4);
}


void addNode(Node* original, Node* add){

    original->next = add;
}