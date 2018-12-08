#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include "tree.h"
#include "stack.h"
#include "work_file_strings.h"

#define MAX_QUESTION 150
#define MAX_NAME 100

enum commands
{
    START = 1,
    LOAD = 2,
    SAVE = 3,
    TELL = 4,
    COMP = 5,
    EXIT = 0,
};



int WriteBase(node_t* node, FILE* file);
elem_t* Question(tree_t* s, node_t* node);
void NewChar(tree_t* s, node_t* node);
char* ReadBase(tree_t* s, FILE * file);
node_t* ElemSearch(node_t* s, elem_t string);
int SearchChar(tree_t* s, char* elem);
void StartAkina(tree_t* s, FILE* file, FILE* out);
node_t* NodeConstr(tree_t* s, char* buffer, int* i);
void CompareChar(tree_t* s);


int main()
{

    tree_t* tree = (tree_t*) calloc(1, sizeof(*tree));
    treeCtor(tree);

    FILE* file = fopen("ak", "rw");
    FILE* out = fopen("base", "w");
    ReadBase(tree, file);
    StartAkina(tree, file, out);
    fclose(file);
    fclose(out);

    return 0;
}

void StartAkina(tree_t* s, FILE* file, FILE* out)
{

    while (1)
    {
      printf("Privet, go igratb\n");
      printf("Press [1] to START\n");
      printf("Press [2] to SHOW BASE\n");
      printf("Press [3] to SAVE\n");
      printf("Press [4] to TELL\n");
      printf("Press [5] to COMP\n");
      printf("Press [0] to EXIT\n");
      int answ = 0;

      scanf("%d", &answ);
      switch(answ)
      {
        case 1: {
                  Question(s ,s -> root);
                  break;
                }
        case 2: {
                  treeShow(s);
                  break;
                }
        case 3: {
                  int res = WriteBase(s -> root, out);
                  if (res == 1)
                  printf("Saved\n");
                  break;
                }
        case 4: {
                  printf("O kom rasskazat?\n");
                  char name[MAX_NAME] = {};
                  scanf("%s", name);
                  SearchChar(s, name);
                  break;
                }
        case 5: {
                  CompareChar(s);
                  break;
                }
        case 0: {
                  return;
                  break;
                }
      }
    }

}
int WriteBase(node_t* node, FILE* file)
{
  assert(file);
  fprintf(file, "{\n");
  fprintf(file, "%s\n", node -> elem);
  if (node -> left != NULL)
  WriteBase(node -> left, file);
  if (node -> right != NULL)
  WriteBase(node -> right, file);

  fprintf(file, "}\n");
    if(file)
    {
      return 1;
    }
    else
    {
      errno = SAVEERR;
      fprintf(stderr, "Error while saving file\n");
      return 0;
    }

}


elem_t* Question(tree_t* s, node_t* node)
{
    while (1)
    {

        if (node -> left == NULL)
        {
            printf("Eto %s?\n", (node -> elem));
            printf("[y] YES - [n] NO\n");

            char respond = 0;
            scanf("%*[^yn]");
            scanf("%c", &respond);
/*
              getchar();
            char respond = getchar();
*/
            switch (respond)
            {

                case 'y':  {
                            printf("Tebe menya ne POBEDITB\n\n");
                            return NULL;
                         }
                case 'n': {
                            printf("Y kto zhe eto?\n");
                            NewChar(s, node);
                            break;
                          }
                default: {
                            printf("Unknown command\n");
                            break;
                          }

            }

         }

        printf("%s?\n", (node -> elem));
        printf("[y] YES - [n] NO\n");

        getchar();
        char answer = getchar();


        switch (answer)
        {

            case 'y':  {
                        node = node -> right;
                        break;
                     }
            case 'n': {
                        node = node -> left;
                        break;
                     }
            default: {
                        printf("Unknown command\n");
                        break;
                      }
        }
    }
}

void NewChar(tree_t* s, node_t* node)
{
    char name[MAX_NAME] = "";
    scanf("%s", name);
    char* person = strdup(name);

    printf("Y kak zhe %s otlichaetsa ot %s?\n", person, node -> elem);
    char differ[MAX_QUESTION] = "";
    scanf("%s", differ);
    char* pregunta = strdup(differ);

    char* previous = node -> elem;
    node -> elem = pregunta;

    nodePush(s, node, LEFT, previous);
    nodePush(s, node, RIGHT, person);
    printf("Ponyal, prinyal\n");
    return;
}


char* ReadBase(tree_t* s, FILE * file)
{
    char* buffer = read_file(file);

    int i = 0;

    s -> root = NodeConstr(s, buffer, &i);
    return buffer;
 }

node_t* NodeConstr(tree_t* s, char* buffer, int* i)
{
    if (buffer[*i] == '{')
    {
        node_t* node = (node_t*) calloc(1, sizeof(*node));
        *i += (sizeof(char) * 2);
        s -> size++;
        node -> elem = &buffer[*i];
        while(!(buffer[*i] == '{' || buffer[*i] == '}'))
        (*i)++;
        buffer[*i - 1] = '\0';
        node -> elem = strdup(node -> elem);

        if (buffer[*i] == '{')
        {
            node -> left = NodeConstr(s, buffer, i);
            node -> left -> parent = node;
        }

        if (buffer[*i] == '{')
        {
            node -> right = NodeConstr(s, buffer, i);
            node -> right -> parent = node;
        }
        if (buffer[*i] !='}')
        {
            printf("Invalid buffer\n");
            exit(-1);
        }

        (*i) += (2 * sizeof(char));

        return node;
    }

    else
    {
        printf("Check your file\n");
        exit(-1);
    }
}

int SearchChar(tree_t* s, char* elem)
{
  node_t* cur = ElemSearch(s -> root, elem);

  if (!cur)
  {
    errno = NOCHAR;
    fprintf(stderr, "No such character\n");
    return 0;
  }

  stack_t stack1 = {};
  stackCtor(&(stack1));

  stackPush(&stack1, NULL);

  while(cur)
  {
      stackPush(&stack1, cur -> elem);
      if (cur -> parent == NULL) break;
        cur = cur -> parent;

  }

  cur = s -> root;


  printf("Eto \n");
  while(stackTop(&stack1) && cur->left)
  {
    stackPop(&stack1);
    stackTop(&stack1);

    if (strcmp(cur -> left -> elem, stackTop(&stack1)) == 0)
    {
      printf(" ne %s,\n", cur -> elem);
      if (cur -> left != NULL)
      cur = cur -> left;
      else break;
    }
    else
    {
      printf(" %s,\n", cur -> elem);
      if (cur -> right != NULL)
      cur = cur -> right;
      else break;
    }
  }
  printf(".\n");
  stackDtor(&stack1);
  return 1;
}

node_t* ElemSearch(node_t* s, elem_t string)
{
  if (strcmp(s -> elem, string) == 0)
  {
    return s;
  }
  node_t* cur = 0;
  if (s -> left)
    cur = ElemSearch(s -> left, string);
  if (!cur && s->right) cur = ElemSearch(s -> right, string);

  return cur;
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wincompatible-pointer-types"
void CompareChar(tree_t* s)
{
  printf("Kogo nuzhno sravnit?\n");
  printf("V ochered:\n");

  char char1[MAX_NAME] = "";
  scanf("%s", char1);
  node_t* node1 = ElemSearch(s -> root, char1);

  char char2[MAX_NAME] = "";
  scanf("%s", char2);
  node_t* node2 = ElemSearch(s -> root, char2);

  if (strcmp(char1, char2) == 0)
  {
    printf("Eto odno i to zhe\n");
    return;
  }
  stack_t stack1 = {};
  stack_t stack2 = {};
  stackCtor(&stack1);
  stackCtor(&stack2);
  stackPush(&stack1, NULL);
  stackPush(&stack2, NULL);

  while(node1)
  {
      stackPush(&stack1, node1);
      if (node1 -> parent == NULL) break;
        node1 = node1 -> parent;

  }
  while(node2)
  {
      stackPush(&stack2, node2);
      if (node2 -> parent == NULL) break;
        node2 = node2 -> parent;

  }
/*  printf("pop2 -- %s\n", stackPop(&stack2));
  printf("pop2 -- %s\n", stackPop(&stack2));
  printf("pop2 -- %s\n", stackPop(&stack2));
  printf("pop1 -- %s\n", stackPop(&stack1));
  printf("pop1 -- %s\n", stackPop(&stack1));
  printf("pop1 -- %s\n", stackPop(&stack1));
*/
  stackPop(&stack1);
  stackPop(&stack2);

  node_t* cur1 = s -> root;
  node_t* next1 = stackPop(&stack1);

  node_t* cur2 = s -> root;
  node_t* next2 = stackPop(&stack2);

  printf("Pro nih mozhno skazat\n");
  while(next1 == next2)
  {
      if(next1 == cur1 -> left)
          printf("not ");
      printf("%s ", cur1 -> elem);

      cur1 = next1;
      cur2 = next2;

      next1 = stackPop(&stack1);
      next2 = stackPop(&stack2);
  }
  printf("\nODNAKO\n%s ", char1);

  while(next1 != NULL) {
      if(next1 == cur1 -> left)
          printf("ne ");
      printf("%s ", cur1 -> elem);

      cur1 = next1;
      next1 = stackPop(&stack1);
  }
  printf("\npoka\n%s ", char2);
  while(next2 != NULL) {
      if(next2 == cur2 -> left)
          printf("ne ");
      printf("%s ", cur2 -> elem);

      cur2 = next2;
      next2 = stackPop(&stack2);
  }
  printf("\n");
  /*
  while (stackTop(&stack1) == stackTop(&stack2) && cur2 -> left && cur1 -> left)
  //if (node1 -> elem == node2 -> elem)
  {
    printf("top 1 = %s\n top 2 = %s\n", stackTop(&stack1), stackTop(&stack2));
    printf("cur1 %s\n", cur1 -> left -> elem);
    if (cur1 -> left  -> elem == stackTop(&stack1))
    {
      printf("ne %s, \n", cur1 -> elem);
      if (cur1 -> left != NULL && cur2 -> left != NULL)
      {
        cur1 -> left -> elem = stackPop(&stack1);
        cur2 -> left -> elem = stackPop(&stack2);
        printf("top 1 = %s\n top 2 = %s\n", stackTop(&stack1), stackTop(&stack2));

        printf("cur 1 after pop %s\n cur2 afterpop %s\n", cur1 -> left -> elem, cur2 -> left-> elem);

        //cur2 -> elem == stackPop(&stack2);
      }

      else break;
    }
    else
    {
      //stackPop(&stack1);
      //stackPop(&stack2);
      printf("%s\n", cur1 -> elem);
      if (cur1 -> right != NULL && cur2 -> right != NULL)
      {
        cur1 == cur1 -> right;
        cur2 == cur2 -> right;
      }
      else break;

    }
  }
  */
//  printf("top2 == %s", stackPop(&stack2));

/*
    printf("No pervy\n");

    while(stackTop(&stack1) && node1 ->left)
    {   char* cur = stackPop(&stack1);
        if (strcmp(node1 -> left -> left -> elem, cur) == 0)
      {
        printf(" ne %s,\n", node1 -> left -> elem);
        if (node1 -> left != NULL)
        node1 = node1 -> left;

      }
      else
      {
        printf(" %s,\n", node1 -> elem);
        if (node1 -> right != NULL)
        node1 = node1 -> right;
      }
    }
    printf("A vtoroy\n");

    while(stackTop(&stack2) && node2 -> left)
    {
          if (strcmp(node2 -> left -> left -> elem, stackTop(&stack2)) == 0)
        {
          printf(" ne %s,\n", node2 -> left -> elem);
          if (node2 -> left != NULL)
          node2 = node2 -> left;

        }
        else
        {
          printf(" %s,\n", node2 -> elem);
          if (node2 -> right != NULL)
          node2 = node2 -> right;

        }
    }
*/
  stackDtor(&stack1);
  stackDtor(&stack2);
}
#pragma GCC diagnostic pop
