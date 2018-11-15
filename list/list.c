#include <stdio.h>
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

list_t* listCtor(list_t *s)
{   
    s -> canary1 = CANARY;
    s -> canary2 = CANARY;

    s -> tail = NULL;
    s -> head = NULL;
    s -> size = 0;
    
    return s;
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

     if (s -> size == 0 && s -> tail != NULL && s -> head != NULL)
        {
        errno = BRKN;
        perror("IT HAS HEAD AND TAIL BUT THE SOUL IS EMPTY\n");
        return 0;
        }

    if (s -> size > 0 && s -> tail == NULL && s -> head == NULL) 
        {
        errno = BRKN;
        perror("LIST IS DISABLED, ZHALKO\n");
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

elem_t* PushHead(list_t* s ,const element_t number)
{   
    listDump(listOK(s), s);
    elem_t* cur = NULL;

    if (s -> size >= MAX_SIZE) 
        {
            errno = OVERFLOW;
            perror("There is no memory\n");
            return cur;
        }

    cur = (elem_t*) calloc(1, sizeof(*cur));

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

    listDump(listOK(s), s);

    return cur;
}



elem_t* PushBack(list_t* s ,const element_t number)
{   
    listDump(listOK(s), s);

    elem_t* cur = NULL;

    if (s -> size >= MAX_SIZE) 
        {
            errno = OVERFLOW;
            perror("There is no memory\n");
            return cur;
        }

    cur = (elem_t*) calloc(1, sizeof(*cur));

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

    listDump(listOK(s), s);

    return cur;
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
    listDump(listOK(s), s);

    if(s -> size == 0)
            {
                errno = EMPTY;
                perror("List is empty\n");
                return POISON;
            }

    element_t data = s -> tail -> value;
    elem_t* cur = s -> tail;
    
    (s -> size)--;    

    if(s -> size == 0) 
            {
                s -> head = NULL;
                s -> tail = NULL;
            }

    if(s -> size > 0)
            {
                
                s -> tail = s -> tail -> prev;
                s -> tail -> next = NULL;
            }

    

    deleteElem(cur);
    
    listDump(listOK(s), s);

    return data;

}

element_t PopHead(list_t* s)
{   
    listDump(listOK(s), s);
    printf(" pop sosatb\n");
    elem_t* cur = NULL;

    if(s -> size == 0)
        {
            errno = EMPTY;
            perror("List is empty\n");
            return POISON;
        }

    element_t data = s -> head -> value;
    cur = s -> head;
    
    (s -> size)--;

    if(s -> size == 0)
        {
            s -> head = NULL;
            s -> tail = NULL;
        }

    if(s -> size > 0)
        {
            
            s -> head = s -> head -> next;
            s -> head -> prev = NULL;
        }

    deleteElem(cur);
    
    listDump(listOK(s), s);
    
    return data;
}

elem_t* listInsert(list_t *s, elem_t* p, element_t value)
{   
    listDump(listOK(s), s);
    
    elem_t* cur = NULL;

    if(s -> size >= MAX_SIZE)
        {
            errno = OVERFLOW;
            perror("List overflow");
            return cur; 
        }

    if (p == s -> tail)
        {
            PushBack(s, value);
        }
    

    else 
        {
            
            cur = (elem_t*) calloc (1, sizeof(*cur));
            cur  = p -> next;
            cur -> prev = p;
            cur -> value = value;
            
            cur -> next -> prev = cur;
            cur -> prev -> next = cur;
            
            (s -> size)++;  
        }

    listDump(listOK(s), s);

    return cur; 
}

list_t* Erase (list_t* s)
{   
    listDump(listOK(s), s);

    if (s -> size == 0)
        {
            return s;
        }

    while (s -> size > 0)
        {
            PopBack(s);
        }

    return s;
}

int listDtor(list_t *s)
{
    listDump(listOK(s), s);
    Erase(s);

    s -> canary1 = POISON;
    s -> canary2 = POISON;
   
    s -> size = -1;
    
    //free(s); !!!!!!!!!
    s = NULL;
    return 1;
    
}

void Illustrate(list_t *s)
{   
    listDump(listOK(s), s);

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
            fprintf(output, "\telem_%d [shape = \"record\"  , label = \"<ptr>%d\\n", counter, counter);
            
            if(cur == s -> head)
                fprintf(output, "HEAD\\n");
            if (cur == s -> tail)
                fprintf(output, "TAIL\\n");
            
            fprintf(output, "%p | %d | {<prev> prev\n%p\\n", cur, cur -> value, cur -> prev);
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

     system("dot -Tpng debug.dot -o ks2.png");
     system("xviewer ks2.png");

     listDump(listOK(s), s);
                                        
}   

int main()
{
    list_t list = {0};
    listCtor(&list);
    PushHead(&list, 5);
    PushBack(&list, 7);
    PushHead(&list, 5);
    PopHead(&list);
    PopBack(&list);
    PopHead(&list);//segfault
    PushHead(&list, 6);
    
    PushHead(&list, 3);
    
    /*printf("popped = %d\n", PopBack(&list));
    printf("popped = %d\n", PopHead(&list));*/
    printf("size = %d\n", list.size);
    printf("done\n");
    printf("adress = %p\n", &list);
    
    Erase(&list);
    Illustrate(&list);
    printf("size = %d\n", list.size);
    listDtor(&list);

}
