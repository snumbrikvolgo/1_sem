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

void WriteBase(node_t* node, FILE* file);
elem_t* Question(tree_t* s, node_t* node);
void NewChar(tree_t* s, node_t* node);
char* ReadBase(tree_t* s, FILE * file);
node_t* ElemSearch(node_t* s, elem_t string);
void SearchChar(tree_t* s, char* elem);
void StartAkina(tree_t* s, FILE* file, FILE* out);
node_t* NodeConstr(tree_t* s, char* buffer, int* i);

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
    printf("Privet, GAYmer, go igratb\n");
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
                  StartAkina(s, file, out);
                  break;
                }
        case 2: {
                  treeShow(s);
                  StartAkina(s, file, out);
                  break;
                }
        case 3: {
                  WriteBase(s -> root, out);
                  printf("Saved\n");
                  StartAkina(s, file, out);
                  break;
                }
        case 4: {
                  printf("O kom rasskazat?\n");
                  char name[MAX_NAME] = {};
                  scanf("%s", name);
                  SearchChar(s, name);
                  StartAkina(s, file, out);
                  break;
                }
        case 5: {
                  break;
                }
        case 0: {
                  break;
                }
    }

}
void WriteBase(node_t* node, FILE* file)
{
  assert(file);
  fprintf(file, "{\n");
  fprintf(file, "%s\n", node -> elem);
  if (node -> left != NULL)
  WriteBase(node -> left, file);
  if (node -> right != NULL)
  WriteBase(node -> right, file);

  fprintf(file, "}\n");
  assert(file);

}


elem_t* Question(tree_t* s, node_t* node)
{
    while (1)
    {

        if (node -> left == NULL)
        {
            printf("Eto %s?\n", (node -> elem));
            printf("[y] YES - [n] NO\n");
            getchar();
            char respond = getchar();
            switch (respond)
            {

                case 'y':  {
                            printf("Ty lokh\n\n");
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
    printf("Ladno, pidor\n");
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

void SearchChar(tree_t* s, char* elem)
{
  node_t* cur = ElemSearch(s -> root, elem);

  if (!cur)  return;
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
    //printf ("\t%s\n", stackTop(&stack1));
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
}

node_t* ElemSearch(node_t* s, elem_t string)
{ printf("...\n");
  if (strcmp(s -> elem, string) == 0)
  {
        printf("nashel\n");
    return s;
  }
  node_t* cur = 0;//(node_t*) calloc (1, sizeof(*cur));
  if (s -> left)
    cur = ElemSearch(s -> left, string);
  if (!cur && s->right) cur = ElemSearch(s -> right, string);

  return cur;
}
