#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include <errno.h>
#define POISON 1488
#define CANARY 1337
#define MAX_SIZE 50


enum error
{
    DEADCANARY = 10001000,
    NULLPTR = 10001001,
    OVERFLOW = 10001010,
    EMPTY = 10001011,
    BRKN = 10001100,
};

typedef int element_t;


typedef struct elem  elem_t;
struct elem
{
        int canary1;       
        
        element_t value;
        elem_t* next;
        elem_t* prev;

        int canary2;

};

typedef struct list
{   
    int canary1;
    
    int size;
    elem_t* tail;
    elem_t* head;

    int canary2;
    
} list_t;

list_t* listCtor(list_t *s);
int listOK(list_t *s);
int listDump (int value, list_t *s);
elem_t* PushHead(list_t* s ,const element_t number);
elem_t* PushBack(list_t* s ,const element_t number);
elem_t* deleteElem(list_t* t,elem_t* s);
elem_t* PopBack(list_t* s);
elem_t* PopHead(list_t* s);
elem_t* listInsert(list_t *s, elem_t* p, element_t value);
list_t* Erase (list_t* s);
int listDtor(list_t *s);
void Illustrate(list_t *s);
element_t* listShow(list_t *s);

