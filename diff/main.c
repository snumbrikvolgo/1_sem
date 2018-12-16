#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include "diff.h"
#include "work_file_strings.h"
#define MAX_LENGTH 150
////peredaavat ukazatel na derevo v uproshalke

node_t* MakeNode(const int key, const elem_t value, node_t* left, node_t* right);
node_t* getG(const char* str);
double getN();
node_t* getE();
node_t* getT();
node_t* getP();
char* getID();
void skipSpaces();
void BeginLatex(FILE *file);
void EndTex(FILE *file);
void MiddleLatex(FILE* file);
node_t* Derivate(node_t* cur);
node_t* SimNode(tree_t* tree, node_t* cur);
node_t* SimRemote(tree_t* tree, node_t* cur);


const char* s = NULL;

int main()
{
  setbuf(stdout, NULL);
  setbuf(stderr, NULL);
  tree_t* input = (tree_t*) calloc (1, sizeof(tree_t));
  tree_t* output = (tree_t*) calloc (1, sizeof(tree_t));
  tree_t* new = (tree_t*) calloc (1, sizeof(tree_t));


  char* string = (char*) calloc (MAX_LENGTH, sizeof(*string));
  scanf("%s ", string);
  PushFirst(input, getG(string));
  treeShow(input);
  PrintConsole(input -> root);
  FILE* f = fopen("kekus.tex", "w");
  printf("%p\n", input -> root);
  PushFirst(output, Derivate(input -> root));
  treeShow(output);
  PrintConsole(output -> root);
  BeginLatex(f);
  TreeLatex((input) -> root, f);
  //treeDtor(&input);
  MiddleLatex(f);
  output -> root = SimRemote(output, output -> root);
  treeShow(output);
  TreeLatex(output -> root, f);
  EndTex(f);
  fclose(f);
  PrintConsole(output -> root);

}

node_t* Derivate(node_t* cur)
{
  node_t* new = (node_t*)calloc(1, sizeof(node_t));
  printf("%p\n", cur);
  printf("%lg\n", cur -> elem);
  if (cur -> key == NUM)
    new = NUMBER(0);
  else if (cur -> key == VAR)
      {
        new = NUMBER(1);
      }
  else
  {
    switch((int)(cur -> elem))
    {
      case ADD:
      {
        new = PLUS(dL, dR);
        break;
      }
      case SUB:
      {
        new = MINUS(dL, dR);
        break;
      }
      case MUL:
      {
        new = PLUS(MULTIP(dL, cR), MULTIP(dR, cL));
        break;
      }
      case DIV:
      {
        new = DIVIS(MINUS(MULTIP(dL, cR), MULTIP(dR, cL)), POWER(cR, NUMBER(2)));
        break;
      }
      case SIN:
      {
        new = MULTIP(COSINUS(cL), dL);
        break;
      }
      case COS:
      {
        new = MULTIP(NUMBER(-1), MULTIP(SINUS(cL), dL));
        break;
      }
      case TG:
      {
        printf("%p\n", cur);
        printf("elem1 %lg elem2 %lg, elem3 %lg", new -> elem, new -> left -> elem, new -> right -> elem);
        new = MULTIP(DIVIS(NUMBER(1), POWER(COSINUS(cL), NUMBER(2))), dL);
        assert(new);
        printf("%p\n", new);
        printf("elem1 %lg elem2 %lg, elem3 %lg", new -> elem, new -> left -> elem, new -> right -> elem);
        break;
      }
      case CTG:
      {
        node_t* one = 0;
        one -> key = NUM;
        one -> elem = 1;
        new = MULTIP(DIVIS(NUMBER(-1), POWER(SINUS(cL), NUMBER(2))), dL);


        break;
      }
      case EXP:
      {
        new = MULTIP(EPOW(cL), dL);
        break;
      }

      case LN:
      {
        new = MULTIP(DIVIS(NUMBER(1), cL), dL);
        break;
      }
      case LG:
      {
        new = MULTIP(DIVIS(NUMBER(1), MULTIP(cL, LNE(NUMBER(10)))), dL);
        break;
      }
      case LOG:
      {
        if (ISNUM(cur->right))
        new = MULTIP(DIVIS(NUMBER(1), MULTIP(cL, LNE(cR))), dL);
        else
        new = MULTIP(Derivate(DIVIS(LNE(cur->right), LNE(cur->left))), dL);
        break;
      }
      case POW:
      {
        if (ISNUM(cur->right))
        {
        new = MULTIP(MULTIP(NUMBER(cur->right->elem), POWER(cL, NUMBER(cur->right->elem - 1))), dL);

        }

        else if (ISNUM(cur->left))
        {

        new = MULTIP(MULTIP(POWER(NUMBER(cur->left->elem), cR), LNE(NUMBER(cur->left->elem))),
                       dL);
        }
        else
        {
        new = MULTIP(CopyNode(cur), PLUS(MULTIP(dL, DIVIS(cR, cL)), MULTIP(dR, LNE(cL))));
        }
        break;
      }
    }
  }
  return new;
}

node_t* SimRemote(tree_t* tree, node_t* cur)
{
    if(cur -> elem)
    printf("valueeeeee ====== %lg\n", cur -> elem);
    if (cur -> left) cur -> left = SimRemote(tree, cur -> left);
    if (cur -> right) cur -> right = SimRemote(tree, cur -> right);
    cur = SimNode(tree, cur);

    return cur;
}

node_t* SimNode(tree_t* tree, node_t* cur)
{
  printf("cur0 -> elem == %c\n", (int) cur -> elem);
  if (cur -> right)
      printf("cur0 right -> elem == %lg\n", cur -> right -> elem);
  if (cur -> left)
      printf("cur0 left -> elem == %lg\n", cur -> left -> elem);
  switch((int) cur -> elem)
  {

    case ADD:
            {
              if (ISZERO(cur -> left) && ISZERO(cur -> right))
              {
                NodeDtor(tree, cur -> left);
                NodeDtor(tree, cur -> right);
                cur -> elem = 0;
                cur -> key = NUM;
                printf("cur1 conec  -> elem == %lg\n", cur -> elem);
              }
              else if (ISNUM(cur -> left) && ISNUM(cur -> right))
              {
                 cur -> elem = cur -> left -> elem + cur -> right -> elem;
                 NodeDtor(tree, cur -> right);
                 NodeDtor(tree, cur -> left);
                 cur -> key = NUM;

                 printf("cur2 -> elem == %lg\n", cur -> elem);
              }
              else if(ISZERO(cur -> left))
              {
                cur -> elem = cur -> right -> elem;
                cur -> key = cur->right->key;

                NodeDtor(tree, cur -> right);
                NodeDtor(tree, cur -> left);

                printf("cur3 -> elem == %lg\n", cur -> elem);
              }
              else if(ISZERO(cur -> right))
              {
                cur -> elem = cur -> left -> elem;
                cur -> key = cur -> right -> key;

                NodeDtor(tree, cur -> right);
                NodeDtor(tree, cur -> left);

                printf("cur4 -> elem == %lg\n", cur -> elem);

              }
                break;
            }

      case SUB:
      {
        if (ISZERO(cur -> left) && ISZERO(cur -> right))
        {
          cur -> elem = 0;
          NodeDtor(tree, cur -> right);
          NodeDtor(tree, cur -> left);
          cur -> key = NUM;

        }
        else if (ISNUM(cur -> left) && ISNUM(cur -> right))
        {
           cur -> elem = cur -> left -> elem - cur -> right -> elem;
           NodeDtor(tree, cur -> right);
           NodeDtor(tree, cur -> left);
           cur -> key = NUM;

        }
        else if(ISZERO(cur -> left) && (ISNUM(cur -> right)))
        {
          cur -> elem = -1 * (cur -> right -> elem);
          NodeDtor(tree, cur -> right);
          NodeDtor(tree, cur -> left);
          cur -> key = NUM;

        }
        else if(ISZERO(cur -> right))
        {
            cur -> elem = cur -> left -> elem;
            cur -> key = cur -> left -> key;

            cur -> left -> parent = cur -> parent;

            NodeDtor(tree, cur -> right);
        }
          break;
      }
        case MUL:
      {
        if(ISZERO(cur -> left) || ISZERO(cur -> right))
        {
          cur -> elem = 0;
          //NodeDtor(tree, cur -> left);
          //NodeDtor(tree, cur -> right);
          cur -> key = NUM;
        }
         if(ISONE(cur -> left))
        {
          node_t* new = 0;
          new = CopyNode(cur -> right);
          printf("key = %d, elem %lg\n", new -> key, new -> elem);
          printf("key = %d, elem %lg\n", cur -> key, cur -> elem);
          NodeDtor(tree, cur -> left);
          NodeDtor(tree, cur -> right);
          cur = new;

        }
        else  if(ISONE(cur -> right))
        {
          node_t* new = 0;
          new = CopyNode(cur -> left);
          printf("key = %d, elem %lg\n", new -> key, new -> elem);
          printf("key = %d, elem %lg\n", cur -> key, cur -> elem);
          NodeDtor(tree, cur -> left);
          NodeDtor(tree, cur -> right);
          cur = new;
        }
      /*  else if (ISNUM(cur -> left) && ISVAR(cur -> right))
        {
          cur -> elem = cur -> left -> elem;
          NodeDtor(tree, cur -> left);
          NodeDtor(tree, cur -> right);
          cur -> key = NUM;

        }
        else if (ISNUM(cur -> right) && ISVAR(cur -> left))
        {
          cur -> elem = cur -> right -> elem;
          NodeDtor(tree, cur -> left);
          NodeDtor(tree, cur -> right);
          cur -> key = NUM;

        }*/
        else if (ISNUM(cur -> left) && ISNUM (cur -> right))
        {
        cur -> elem = cur -> left -> elem * cur ->right -> elem;
        NodeDtor(tree, cur -> left);
        NodeDtor(tree, cur -> right);
        cur -> key = NUM;
        }

        break;
      }

      case DIV:
      {
        if (ISZERO(cur -> left))
        {
          NodeDtor(tree, cur -> right);
          NodeDtor(tree, cur -> left);

          cur -> elem = 0;
          cur -> key = NUM;
        }
        else if(ISNUM(cur -> left) && ISNUM(cur -> right))
        {
          cur -> elem = cur -> left -> elem / cur -> right -> elem;
          NodeDtor(tree, cur -> right);
          NodeDtor(tree, cur -> left);
          cur -> key = NUM;

        }
        else if (ISONE(cur -> right))
        {
          cur -> elem = cur -> left -> elem;

          NodeDtor(tree, cur -> right);
          NodeDtor(tree, cur -> left);
          cur -> key = cur -> left -> key;

        }
        break;
      }
      /*case POW:
      {
        if (ISZERO(cur -> left))
        {
          cur -> elem = cur -> left -> elem;
          NodeDtor(tree, cur -> left);
          NodeDtor(tree, cur -> right);
          cur -> key = NUM;

        }
        else if (ISZERO(cur -> right))
        {
          cur -> elem = 1;
          NodeDtor(tree, cur -> left);
          NodeDtor(tree, cur -> right);
          cur -> key = NUM;
        }
        break;
      }*/
  }
  return cur;
}

node_t* MakeNode(const int key, const elem_t value, node_t* left, node_t* right)
{
  node_t* node = (node_t*) calloc (1, sizeof(*node));

  node -> key = key;
  node -> elem = value;

  node -> left = left;
  if (left) node -> left -> parent = node;
  node -> right = right;
  if (right) node -> right -> parent = node;
  return node;

}

node_t* getG(const char* str)
{

  s = str;
  skipSpaces();
  node_t* root = getE();
  skipSpaces();
  assert(*s == '\0');
  assert(s != str);

  s++;
  return root;
}

double getN()
{
  double val = 0;
  double point = 0;
  int rate = 0;
  skipSpaces();
  while('0' <= *s && *s <= '9')
  {
    val = val * 10 + (*s) - '0';
    s++;
  }
  if (*s == '.')
  {
    s++;
    while('0' <= *s && *s <= '9')
    {
      rate++;
      point = point * 10 + (*s) - '0';
      s++;
    }
  }
  val = val + (point)/(pow(10, rate));
  skipSpaces();
  return val;
}

node_t* getE()
{
  skipSpaces();
  char op = 0;
  node_t* val = getT();
  skipSpaces();
  while (*s == '+' || *s == '-')
  {
    op = *s;
    s++;
    skipSpaces();
    node_t* val2 = getT();
    skipSpaces();
    if (op == '+')
      {
      val =  MakeNode(OP, ADD, val, val2);
    }
    if (op == '-')
      val =  MakeNode(OP, SUB, val, val2);
  }
  return val;
}

node_t* getT()
{
  skipSpaces();
  char op = 0;
  node_t* val = getP();
  skipSpaces();
  while (*s == '*' || *s == '/')
  {
    op = *s;
    s++;
    node_t* val2 = getP();
    skipSpaces();
    if (op == '*')
      val =  MakeNode(OP, MUL, val, val2);
    if (op == '/')
      val =  MakeNode(OP, DIV, val, val2);
  }
  return val;
}

node_t* getP()

{
  node_t* val = 0;
  node_t* val2 = 0;
  skipSpaces();
  if (*s == '(')
  {
    s++;
    skipSpaces();

    val = getE();
    skipSpaces();
    assert(*s == ')');
    s++;
    if (*s == '^')
    {
    s++;
    val2 = getP();
    val =  MakeNode(OP, POW, val, val2);
   }
    return val;
  }

   else if (*s == 's' && *( s + 1) == 'i' && *(s + 2) == 'n')
   {
     s = s + 3;
     if (*s == '^')
     {
       s++;
       val2 = getP();
     }
     val =  MakeNode(OP, SIN, getP(), NULL);
     if (val2)
     val =  MakeNode(OP, POW, val, val2);
   }

   else if (*s == 'c' && *( s + 1) == 'o' && *(s + 2) == 's')
   {
     s = s + 3;
     if (*s == '^')
     {
       s++;
       val2 = getP();
     }
     val =  MakeNode(OP, COS, getP(), NULL);
     if (val2)
     val =  MakeNode(OP, POW, val, val2);
   }

   else if (*s == 't' && *( s + 1) == 'g')
   {
     s = s + 2;
     if (*s == '^')
     {
       s++;
       val2 = getP();
     }
     val =  MakeNode(OP, TG, getP(), NULL);
     if (val2)
     val =  MakeNode(OP, POW, val, val2);

   }

   else if (*s == 'c' && *( s + 1) == 't' && *(s + 2) == 'g')
   {
     s = s + 3;
     if (*s == '^')
     {
       s++;
       val2 = getP();
     }
     val =  MakeNode(OP, CTG, getP(), NULL);
     if (val2)
     val =  MakeNode(OP, POW, val, val2);
   }

   else if (*s == 'l' && *( s + 1) == 'g')
   {
     s = s + 2;
     if (*s == '^')
     {
       s++;
       val2 = getP();
     }
     val =  MakeNode(OP, LG, getP(), NULL);
     if (val2)
     val =  MakeNode(OP, POW, val, val2);

   }

   else if (*s == 'l' && *( s + 1) == 'n')
   {
     s = s + 2;
     if (*s == '^')
     {
       s++;
       val2 = getP();
     }
     val =  MakeNode(OP, LN, getP(), NULL);
     if (val2)
     val =  MakeNode(OP, POW, val, val2);

   }

   else if (*s == 'l' && *( s + 1) == 'o' && *(s + 2) == 'g')
   {
     s = s + 3;
     node_t* power = 0;

     if (*s == '^')
     {
       s++;
       power = getP();
     }
     assert(*s == '(');
     s++;
     val = getE();
     assert(*s == ',');
     s++;
     val2 = getE();
     assert(*s == ')');
     s++;
     if (power)
     val = MakeNode(OP, POW, MakeNode(OP, LOG, val2, val), power);
     else
     val =  MakeNode(OP, LOG, val2, val);

   }

   else if (*s == 'e' && *( s + 1) == '^')
   {
     s = s + 2;
     val =  MakeNode(OP, EXP, getP(), NULL);

   }

   else if (*s >= '0' && *s <= '9')
         {
           val = MakeNode(NUM, getN(), NULL, NULL);

         }
        else
        {
            s++;
            val = MakeNode(VAR, X, NULL, NULL);
        }
    if (*s == '^')
    {
      s++;
      val2 = getP();
      val = MakeNode(OP, POW, val, val2);
    }
    skipSpaces();
    return val;
}

char* getID()
{
  skipSpaces();
  char* id = (char*) calloc (MAX_LENGTH, sizeof(*id));
  char* cur = id;
  if ((*s >= 'A' && *s <= 'Z') ||
  (*s >= 'a' && *s <= 'z') ||
  (*s == '_') ||
  (*s == '$'))
  {
    *cur = *s;
    cur++;
    s++;
  }
  while ((*s >= 'A' && *s <= 'Z') ||
  (*s >= 'a' && *s <= 'z') ||
  (*s == '_') ||
  (*s == '$'))
  {
    if (cur - id < MAX_LENGTH)
    {
      *id = *cur;
      cur++;
      s++;
    }
  }
  *id = '\0';
  skipSpaces();
  return cur;

}

void skipSpaces()
{
  while(*s == ' ' || *s == '\n')
    s++;
  return;
}
void BeginLatex(FILE *tex)
{
    assert (tex);

    fprintf (tex, "\\documentclass[a4paper,12pt]{article}\n\n");
    fprintf (tex, "\\usepackage[T2A]{fontenc}\n");
    fprintf (tex, "\\usepackage[utf8]{inputenc}\n");
    fprintf (tex, "\\usepackage[english]{babel}\n");
    fprintf(tex, "\\usepackage[dvips]{graphicx}\n");
    fprintf(tex, "\\graphicspath{{noiseimages/}}\n");
    fprintf (tex, "\\usepackage{amsmath,amsfonts,amssymb,amsthm,mathtools}\n");
    fprintf (tex, "\\usepackage{wasysym}\n");
    fprintf (tex, "\\author{snumbrikvolgo}\n");
    fprintf (tex, "\\title{Derivatives in \\LaTeX{}}\n");
    fprintf (tex, "\\begin{document}\n\n");
    fprintf (tex, "\\maketitle\n");
    fprintf (tex, "\\newpage\n\n");
    fprintf (tex, "\\What the derivative is?\n It's of a function of a real variable measures"
    "the sensitivity to change of the function value (output value) with respect"
    "to a change in its argument (input value). Derivatives are a fundamental tool"
    "of calculus. For example, the derivative of the position of a moving object"
    "with respect to time is the object's velocity: this measures how quickly"
    "the position of the object changes when time advances.\n\n");
    fprintf (tex, "At first, we have this:\n");
    fprintf(tex, "\\begin{equation}\n");
}
void EndTex (FILE *tex)
{
    assert (tex);

    fprintf(tex, "\n\\end{equation}\n");
    fprintf (tex, "\n\n");
    fprintf(tex, "Finally, we can go sleeping\n");
    fprintf (tex, "\\end{document}\n");

    fclose (tex);
    //system("latex kekus.tex -o lol.png");
}

void MiddleLatex(FILE* tex)
{
    assert(tex);

    fprintf(tex, "\n\\end{equation}");
    fprintf(tex, "\nDoing some easy simplifyings we got:\n\n");
    fprintf(tex, "\\begin{equation}\n");

}
