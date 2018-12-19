#include <stdio.h>
#include <assert.h>
#include <ctype.h>
#include <stdlib.h>
#include <errno.h>
#include "diff.h"

node_t* nodeCtor(tree_t* s, node_t* parent, elem_t value, int key)
{
    if (s == NULL)
       {
            errno = NULLPTR;
            perror("Tree is NULLPTR\n");
            return NULL;
        }
    /*if (parent == NULL)
        {
            errno = NULLPTR;
            perror("Tree is orphan(\n");
            return nodeRoot(s, value);
        }*/

    node_t* node = (node_t*) calloc(1, sizeof(*node));
    node -> elem = value;
    node -> key = key;
    node -> parent = parent;
    node -> left = NULL;
    node -> right = NULL;

    (s -> size)++;

    return node;

}

int nodeOK(node_t* node, node_t* parent)
{


    int stat = 1;
    if (node -> left)
        stat &= nodeOK(node -> left, node);
    if (node -> right)
        stat &= nodeOK(node -> right, node);

    stat &= (node -> parent == parent);

    return stat;

}

int treeOK(tree_t *s)
{
      if (s -> root == NULL) return 1;

      return nodeOK(s -> root, NULL);
}


int treeDump (int value, tree_t *s)
{

    if (value == 0)
        {
            printf("tree ptr == %p\n", s);
            printf("root ptr == %p\n", s -> root);
            printf("tree size == %d\n", s -> size);

            return 0;
        }

    return 1;
}

int nodeDelete(tree_t* s, node_t* parent)
{
    treeDump(treeOK(s), s);

    if (parent -> parent -> left == parent)
        parent -> parent -> left = NULL;
    if (parent -> parent -> right == parent)
        parent -> parent -> right = NULL;
    if (parent -> left != NULL)
        nodeDelete(s, parent -> left);
    if (parent -> right != NULL)
        nodeDelete(s, parent -> right);
    (s -> size)--;

    treeDump(treeOK(s), s);

    return 1;

}

int treeDtor(tree_t** s)
{
    treeDump(treeOK(*s), *s);
    if ((*s) -> size > 0)
        nodeDelete(*s, (*s) -> root);
    (*s) -> size = 0;
    free(s);
    (*s) = NULL;
    return 1;
}

tree_t* treeCtor(tree_t* s)
{
    s -> size = 0;
    s -> root = NULL;



    return s;

}
node_t* nodePushRoot(tree_t* s, elem_t value, int key)
{
    if (s == NULL)
       {
            errno = NULLPTR;
            perror("Tree is NULLPTR\n");
            return NULL;
        }
    if (s -> root != NULL)
        {
            perror("It has already a root\n");
        }
    node_t* node = (node_t*) calloc(1, sizeof(*node));
    if (s -> size == 0)
    {

        s -> root = node;
        s -> root -> key = key;
        (s -> root) -> elem = value;
        s -> root -> parent = NULL;
        s -> root -> left = NULL;
        s -> root -> right = NULL;
        s -> root -> elem = 0;
        s -> size = 1;

        return s -> root;
    }


    node -> left = s -> root -> left;
    node -> right = s -> root -> right;

    s -> root = node;
    s -> root -> key = key;
    (s -> root) -> elem = value;
    s -> root -> parent = NULL;


    return s -> root;

}
node_t* nodeCopy(node_t* s)
{
  node_t* new = (node_t*) calloc (1, sizeof(*new));
  new -> left = s -> left;
  new -> right = s -> right;
  new -> parent = s -> parent;
  new -> key = s -> key;
  new -> elem = s -> elem;

  return new;
}

node_t* nodePush(tree_t* s, node_t* parent, int side, elem_t value, int key)
{
    treeDump(treeOK(s), s);
    if (s -> size == 0 && parent == NULL)
        {
             node_t* node = (node_t*) calloc(1, sizeof(*node));
             node -> elem = value;
             node -> key = key;
             node -> parent = NULL;
             node -> left = NULL;
             node -> right = NULL;
             s -> root = node;
             s -> size++;
             return node;
        }
    if (side == Left)
        {
            parent -> left = nodeCtor(s, parent, value, key);
            return parent -> left;
        }
     if (side == Right)
        {
            parent -> right = nodeCtor(s, parent, value, key);
            return parent -> right;
        }
    treeDump(treeOK(s), s);
    return NULL;
}



node_t* nodeValChange(tree_t* s, node_t* node, elem_t value, int key)
{
    treeDump(treeOK(s), s);

    node -> elem = value;

    treeDump(treeOK(s), s);

    return node;
}

node_t* nodeNext(node_t* node, int side)
{

    if (side == Left)
        return node -> left;
    if (side == Right)
        return node -> right;
    return NULL;

}
node_t* nodeParent(node_t* node, int side)
{
    if (node -> parent == NULL)
        {
            return node;
        }

    return node -> parent;

}

node_t* nodeRoot(tree_t* s)
{
    treeDump(treeOK(s), s);
    return s -> root;
}

node_t* nodeLeft(tree_t* s)
{
    treeDump(treeOK(s), s);

    node_t* tmp = nodeRoot(s);
    while (nodeNext(tmp, Left) != NULL)
        tmp = nodeNext(tmp, Left);

    treeDump(treeOK(s), s);

    return tmp;
}

node_t* nodeRight(tree_t* s)
{
    treeDump(treeOK(s), s);

    node_t* tmp = nodeRoot(s);
    while (nodeNext(tmp, Right) != NULL)
        tmp = nodeNext(tmp, Right);

    treeDump(treeOK(s), s);
    return tmp;
}

void nodeShow(FILE* out, const node_t* cur, const int parent, int* number, int side)
{
    const int number_copy = *number;
    fprintf(out, "subgraph clust_%d{\nrandir = HR;\n", *number);
    /*if (cur -> key == NUM)
    fprintf(out, "\telem_%d [ shape = \"record\", label = \"{ <pointer> %d\\n%p|"
             "  { value = %lg\\n ", *number, *number, cur, (cur -> elem));
    if (cur -> key == VAR)
    fprintf(out, "\telem_%d [ shape = \"record\", label = \"{ <pointer> %d\\n%p|"
            "  { value = X\\n ", *number, *number, cur);
    if (cur -> key == OP)*/
    fprintf(out, "\telem_%d [ shape = \"record\", label = \"{ <pointer> %d\\n%p|"
            "  { value = %d\\n ", *number, *number, cur,(int)(cur -> elem));
    fprintf(out, " | <parent> parent\\n%p } | { <left> left\\n%p | <right> right\\n%p } }\"]"
             , cur -> parent , cur -> left, cur -> right);
    fprintf (out, "}\n\n");
    if (side == Left)
         fprintf (out, "\t\telem_%d:<left> -> elem_%d\n", parent, *number);
    if (side == Right)
         fprintf (out, "\t\telem_%d:<right> -> elem_%d\n", parent, *number);
    if (cur->left)
    {
        (*number)++;
        nodeShow (out, cur -> left, number_copy, number, Left);
    }
     if (cur->right)
    {
        (*number)++;
        nodeShow (out, cur->right, number_copy, number, Right);
    }


}
void treeShow(tree_t* s)
{
    FILE* out = fopen("dump.dot", "w");
    assert(out);

    fprintf (out, "digraph Tree\n{\nrankdir=TB\n");
    fprintf (out, "\t\tnode [ shape = \"box\", color = \"black\" ]\n");
    fprintf (out, "\t\tedge [ color = \"black\" ]\n\n");

    fprintf(out, "\tsize [ label =\"size = %d\" ]\n\n", s -> size);

    int number = 1;
    if (s -> size > 0)
        {
           nodeShow (out, s -> root, 0, &number, NONE);

        }
    fprintf (out, "}");
    fclose (out);


      system("dot -Tpng dump.dot -o ks2.png");
     system("xviewer ks2.png");

}

void PushLeft(tree_t* s, node_t* node, const int key, const elem_t value)
  {
    if (s -> size == 0)
    {
      PushRoot(s, key, value);
      return;
    }
    if (node -> left)
    {
      node -> left -> key = key;
      node -> left -> elem = value;
      node -> left -> parent = node;
      node -> left -> right = NULL;
      node -> left -> left = NULL;
      return;

    }
    else
    {
    node_t* new = (node_t*) calloc(1, sizeof(new));

    new -> elem = value;
    new -> key = key;
    new -> parent = node;
    new -> left = NULL;
    new -> right = NULL;
    node -> left = new;
    (s -> size)++;
    }

  }
void PushRight(tree_t* s, node_t* node, const int key, const elem_t value)
{
  if (s -> size == 0)
  {
    PushRoot(s, key, value);
    return;
  }
  if (node -> right)
  {
    node -> right -> key = key;
    node -> right -> elem = value;
    node -> right -> parent = node;
    node -> right -> right = NULL;
    node -> right -> left = NULL;
    return;

  }
  else
  {
  node_t* new = (node_t*) calloc(1, sizeof(new));

  new -> elem = value;
  new -> key = key;
  new -> parent = node;
  new -> right = NULL;
  new -> left = NULL;
  node -> right = new;
  (s -> size)++;
  }

}
void PushRoot(tree_t* s, const int key, const elem_t value)
{
  node_t* new = (node_t*) calloc(1, sizeof(new));
  if (s -> size != 0)
  {
    new -> elem = value;
    new -> key = key;
    return;
  }
  else
  {
    node_t* new = (node_t*) calloc(1, sizeof(new));

    new -> elem = value;
    new -> key = key;
    new -> parent = NULL;
    new -> right = NULL;
    new -> left = NULL;

    (s -> size)++;
  }
}
node_t* CopyNode(const node_t* node)
{
  node_t* new = (node_t*) calloc(1, sizeof(node_t));
  //new = node;
  new -> key = node -> key;
  new -> elem = node -> elem;

  if (node -> left)
  {
    new -> left = CopyNode(node -> left);
  }
  else new -> left = NULL;
  if (node -> right)
  {
    new -> right = CopyNode(node -> right);
  }
  else new -> right = NULL;

  return new;
}
void PushFirst(tree_t* s, node_t* root)
{
  s -> root = root;
  s -> size = CountNodes(root);

}
int CountNodes(node_t* node)
{
  if (node == NULL)
  return 0;
  return 1 + CountNodes(node -> left) + CountNodes(node -> right);
}
void PrintConsole (node_t* s)
{
 assert (s);
    printf("%c", '(');
    if (s->left)
    {
        PrintConsole (s->left);
    }

    if (s->key == VAR)
        printf("x");
    else if (s -> key == NUM)
        printf("num %lg", s -> elem);
        else
        {
            printf("op %c", (int) s->elem);
        }
    if (s->right)
    {
        PrintConsole (s->right);
    }
    printf("%c", ')');

}
int NodeDtor(tree_t* tree, node_t* node)
{ if(node -> parent)
  {
  if (node -> parent -> left == node)
    node -> parent -> left = NULL;
  else node -> parent -> right = NULL;
  }
  if (node -> left) NodeDtor(tree, node -> left);
  if (node -> right) NodeDtor(tree, node -> right);
  node -> elem = 0;
  node -> key = NUM;
  (tree -> size)--;
  free(node);
  return 1;

}
void Shorten(node_t* node, double side1, double side2)
{
	node_t* new = NULL;
	node_t* re1 = NULL;
	node_t* re2 = NULL;

	if (side1 == Left)
	{
		new = node->left;
		re1 = node->right;
	}
	else if (side1 == Right)
	{
		new = node->right;
		re1 = node->left;
	}

	if (side2 == Left)
	{
		re2 = new->right;
	}
	else if (side2 == Right)
	{
		re2 = new->left;
	}

	double val = node-> elem;
	node-> elem = new-> elem;
	new-> elem = val;

	if (side1 == Left)
	{
		if (side2 == Left)
		{
			node->right = re2;
			re2->parent = node;

			new->right = re1;
			re1->parent = new;
		}
		else
		{
			node->right = re2;
			re2->parent = node;

			new->left = re1;
			re1->parent = new;
		}
	}
	else
	{
		if (side2 == Left)
		{
			node->left = re2;
			re2->parent = node;

			new->right = re1;
			re1->parent = new;
		}
		else
		{
			node->left = re2;
			re2->parent = node;

			new->left = re1;
			re1->parent = new;
		}
	}
}


#define TEXIT(_elem, atm)                                             \
    if (node -> elem == _elem && node -> key == OP)                   \
    {                                                                 \
          assert(node -> left);                                       \
          assert(node -> right);                                      \
          if(!(ISLEAF(node -> left))) {                               \
              fprintf(file, "(");                                     \
              TreeLatex(node -> left, file);                          \
              fprintf(file, ")");                                     \
          } else {                                                    \
              TreeLatex(node -> left, file);                          \
          }                                                           \
                                                                      \
          fprintf(file, atm);                                         \
                                                                      \
          if(!(ISLEAF(node -> right))) {                              \
              fprintf(file, "(");                                     \
              TreeLatex(node -> right, file);                         \
              fprintf(file, ")");                                     \
          } else                                                      \
          {                                                           \
              TreeLatex(node -> right, file);                         \
          }                                                           \
          return;                                                     \
      }
#define SINGLETEX(_elem, atm)                                         \
  if (node -> elem == _elem && node -> key == OP)                     \
  {                                                                   \
    fprintf(file, atm);                                               \
    assert(node -> left);                                             \
    if(!(ISLEAF(node -> left))) {                                     \
        fprintf(file, "(");                                           \
        TreeLatex(node -> left, file);                                \
        fprintf(file, ")");                                           \
    } else {                                                          \
        TreeLatex(node -> left, file);                                \
    }                                                                 \
    return;                                                           \
  }

void TreeLatex(node_t* node, FILE *file)
{
  //file = stdout;
  if (node == NULL) return;

  if (node -> key == OP)
  { //if (node -> key == OP)
  //fprintf(file, " OPERATOR!!!!!!!!!!!!!!!!!!\t[ shape = \"record\", label = \"{ <pointer> \\n%p|"
        //  "  { value = %c\\n ", node, X);
      if (node -> elem == DIV)
      {
        fprintf(file, "\\frac{");
        TreeLatex(node -> left, file);
        fprintf(file, "}{");
        TreeLatex(node -> right, file);
        fprintf(file, "}");

        return;
      }
      if (node -> elem == POW)
      {
        if (ISLEAF(node -> left)) TreeLatex(node -> left, file);
        else
        {
          fprintf(file, "(");
          TreeLatex(node -> left, file);
          fprintf(file, ")");
        }
        fprintf(file, "^{");
        TreeLatex(node -> right, file);
        fprintf(file, "}");

        return;
      }
      if (node -> elem == LOG)
      {
        fprintf(file, "\\log");
        fprintf(file, "_{");
        if (!ISNUM(node -> right) || !ISVAR(node -> right))
        fprintf(file, "(");
        TreeLatex(node -> right, file);
        if (!ISNUM(node->right) || !ISVAR(node->right))
        fprintf(file, ")");
        fprintf (file, " }{ ");
        fprintf(file, "(");
        TreeLatex(node -> left, file);
        fprintf(file, ")");
        fprintf(file, "}");

        return;
      }
      if (node -> elem == EXP)
      {
        fprintf(file, "e^{");
        TreeLatex(node -> left, file);
        fprintf(file, "}");

        return;
      }

      TEXIT(MUL, " \\cdot ")
      TEXIT(ADD, " + ")
      TEXIT(SUB, " - ")
      SINGLETEX(SIN, " \\sin")
      SINGLETEX(COS, "\\cos")
      SINGLETEX(TG, "\\tan")
      SINGLETEX(CTG, "\\cot")
      SINGLETEX(LN, "\\ln")
      SINGLETEX(LG, "\\lg")

  }

    if (node -> key == NUM) {
      printf("CHISLOOOOOO %lg\n", node-> elem);
      printf("ukazatel na jodu chislo %p\n", node);
      fprintf(file, "%lg", node -> elem);
    }
    if (node -> key == VAR){
        printf("PEREMENNAYA\n");
        printf("ukazatel na jodu preremennaya %p\n", node);
        fprintf(file, "x");
    }


  fflush(file);

}
