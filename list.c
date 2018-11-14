#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include <errno.h>
#define POISON_FREE 1488
#define CANARY 1337
#define MAX_SIZE 50
enum error
{
    DEADCANARY = 10001000,
    NULLPTR = 10001001,
    OVERFLOW = 10001010,
    EMPTY = 10001011,
};

typedef int element_t;


typedef struct elem  elem_t;                           //Insert, pushhead, pushtail, pophead, poptail, showelem,  
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

list_t listCtor(list_t *s)
{
    s -> canary1 = CANARY;
    s -> canary2 = CANARY;

    s -> tail = NULL;
    s -> head = NULL;
    s -> size = 0;
    
    return *s;
}

int listOK(list_t *s)
{
    if (s == NULL) 
        {
        errno = NULLPTR;
        perror("List ptr is NULL\n");
        return 0;
        }
    if (s -> canary1 != CANARY || s -> canary2 != CANARY)
        {
        errno = DEADCANARY;
        perror("Canary is dead, sorry!\n");
        return 0;
        }
     /*if (s -> tail -> canary1 != CANARY || s -> tail -> canary2 != CANARY)
        {
        errno = DEADCANARY;
        perror("Canary is dead, sorry!\n");
        return 0;
        }
    if (s -> head -> canary1 != CANARY || s -> head -> canary2 != CANARY)
        {
        errno = DEADCANARY;
        perror("Canary is dead, sorry!\n");
        return 0;
        }*/


     return 1;

}

int elemOK(elem_t *s)
{
    if (s == NULL) 
        {
        errno = NULLPTR;
        perror("Elem ptr is NULL\n");
        return 0;
        }
    if (s -> canary1 != CANARY || s -> canary2 != CANARY)
        {
        errno = DEADCANARY;
        perror("Canary is dead, sorry!\n");
        return 0;
        }

    return 1;
}

int listDump (int value, list_t *s)
{
    if (value == 0)
        {
            printf("list ptr == %p\n", s);
            printf("list canary1 == %d\n", s -> canary1);
            printf("list canary2 == %d\n", s -> canary2);
            printf("head ptr == %p\n", s -> head);
            printf("tail ptr == %p\n", s -> tail);
            printf("head canary 1 == %d\nhead canary2 == %d\n", (s -> head) -> canary1, (s -> head) -> canary2);
            printf("tail canary 1 == %d\ntail canary2 == %d\n", (s -> tail) -> canary1, (s -> tail) -> canary2);
            return 0;
        }

    return 1;
}



void PushHead(list_t* s ,const element_t number)
{
    if (s -> size >= MAX_SIZE) 
        {
            errno = OVERFLOW;
            perror("There is no memory\n");
        }

    elem_t* cur = (elem_t*) calloc(1, sizeof(*cur));

    cur -> canary1 = CANARY;
    cur -> canary2 = CANARY;

    if (s -> size == 0)
        {
            s -> head = cur;
           
            cur -> next = NULL;
            cur -> prev = NULL;
            cur -> value = number;

            s -> tail = cur;
        }

    if (s -> size > 0)
        {
            s -> head -> prev = cur;

            cur -> next = s -> head;
            cur -> prev = NULL;
            cur -> value = number;

            s -> head = cur;
              
        }

    (s -> size)++;
}



void PushBack(list_t* s ,const element_t number)
{
    if (s -> size >= MAX_SIZE) 
        {
            errno = OVERFLOW;
            perror("There is no memory\n");
        }

    elem_t* cur = (elem_t*) calloc(1, sizeof(*cur));

    cur -> canary1 = CANARY;
    cur -> canary2 = CANARY;

    if (s -> size == 0)
        {
            s -> head = cur;
            
            cur -> next = NULL;
            cur -> prev = NULL;
            cur -> value = number;

            s -> tail = cur;
        }

    if (s -> size > 0)
        {
            s -> tail -> next = cur;

            cur -> next = NULL;
            cur -> prev = s -> tail;
            cur -> value = number;

            s -> tail = cur;
        } 

    (s -> size)++;

}

int deleteElem(elem_t* s)
{   
    if (s == NULL) 
        {
        errno = NULLPTR;
        perror("Elem ptr is NULL\n");
        return 0;
        }
    free(s);
    s = NULL;

    return 1;
}

element_t PopBack(list_t* s)
{

    if(s -> size == 0)
            {
                errno = EMPTY;
                perror("List is empty\n");
            }

    element_t data = s -> tail -> value;
    elem_t* cur = s -> tail;
    
    if(s -> size == 1) 
            {
                s -> head = NULL;
                s -> tail = NULL;
            }

    if(s -> size > 0)
            {
                s -> tail -> next = NULL;
                s -> tail = s -> tail -> prev;
            }

    (s -> size)--;

    deleteElem(cur);
    
    
    return data;

}

element_t PopHead(list_t* s)
{
    if(s -> size == 0)
        {
            errno = EMPTY;
            perror("List is empty\n");
        }
    element_t data = s -> head -> value;
    elem_t* cur = s -> head;
    
    if(s -> size == 1)
        {
            s -> head = NULL;
            s -> tail = NULL;
        }

    if(s -> size > 0)
        {
            s -> head -> prev = NULL;
            s -> head = s -> head -> next;
        }
    (s -> size)--;

    deleteElem(cur);
    
    return data;
}

list_t listInsert(list_t *s)
{
    /*if(listdump(listOK(s), s) == 0) return 0;*/  
   
}

list_t listDtor(list_t *s)
{
   
}

void Illustrate(list_t *s)
{
    FILE * output = fopen("debug.dot", "w");
    fprintf(output, "digraph G{\nrankdir = LR;\n\tnode[shape = \"box\", color=\"black\", fontsize=14];\n\tedge[color=\"black\"];\n");
    if (s -> canary1 == CANARY)
        fprintf(output, "\tcanary1 [label = \"Canary1 = %d\"]\n", s -> canary1);
    if (s -> canary2 == CANARY)
        fprintf(output, "\tcanary2 [label = \"Canary2 = %d\"]\n", s -> canary2);
    if (s -> size >= 0)
        fprintf(output, "size [label =\"Size = %d\"]\n", s -> size);

    elem_t* cur = s -> head;
    int counter = 1;
    while (cur != NULL)
        {
            fprintf(output, "\telem_%d [shape = box , label = \"<ptr>%d\n", counter, counter);
            
            if(cur == s -> head)
                fprintf(output, "HEAD\n");
            if (cur == s -> tail)
                fprintf(output, "TAIL\n");
            
            fprintf(output, "%p | {<prev> prev\n%p\n", cur, cur -> prev);
            fprintf(output, "| <next> next\n %p} |{canary1\n %d | canary2\n %d}\"]", cur -> next, cur -> canary1, cur -> canary2);
            counter++;
            cur = cur -> next;
        }
       fprintf(output, "\n");
        cur = s -> head;
        
        counter = 1;

    while (cur != NULL)
        {
            if (cur -> prev != NULL)
                fprintf(output, "\telem_%d:<prev> -> elem_%d:<ptr>\n", counter, counter -1);
            if (cur -> next != NULL)
                fprintf(output, "\telem_%d:<next> -> elem_%d:<ptr>\n", counter, counter +1);
            counter++;
            cur = cur -> next;
        }
     fprintf(output, "}");
     fclose(output);
    
                                        
}   

int main()
{
    list_t list = {0};
    listCtor(&list);
    PushHead(&list, 5);
    PushBack(&list, 7);
    PushHead(&list, 6);
    PushHead(&list, 3);
    printf("popped = %d\n", PopBack(&list));
    printf("popped = %d\n", PopHead(&list));
    printf("size = %d\n", list.size);
    printf("done\n");
    printf("adress = %p", &list);
    Illustrate(&list);
}
