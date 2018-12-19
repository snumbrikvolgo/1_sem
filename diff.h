#include <stdlib.h>
#include <errno.h>

#define dL Derivate(cur->left)
#define dR Derivate(cur->right)
#define cL CopyNode(cur->left)
#define cR CopyNode(cur->right)

#define NUMBER(number)          MakeNode (NUM, number, NULL, NULL)
#define VARIABLE()              MakeNode (VAR, 1, NULL, NULL)

#define      PLUS(left, right) MakeNode (OP, ADD, left, right)
#define     MINUS(left, right) MakeNode (OP, SUB, left, right)
#define    MULTIP(left, right) MakeNode (OP, MUL, left, right)
#define     DIVIS(left, right) MakeNode (OP, DIV, left, right)
#define     POWER(left, right) MakeNode (OP, POW, left, right)
#define LOGARITHM(left, right) MakeNode (OP, LOG, left, right)
#define     SINUS(cur)         MakeNode (OP, SIN, cur, NULL)
#define   COSINUS(cur)         MakeNode (OP, COS, cur, NULL)
#define   TANGENT(cur)         MakeNode (OP, TG, cur, NULL)
#define COTANGENT(cur)         MakeNode (OP, CTG, cur, NULL)
#define      EPOW(cur)         MakeNode (OP, EXP, cur, NULL)
#define       LNE(cur)         MakeNode (OP, LN , cur, NULL)
#define       L10(cur)         MakeNode (OP, LG , cur, NULL)

#define ISZERO(cur) cur -> elem == 0
#define ISONE(cur) cur -> elem == 1
#define ISLEAF(cur) cur  -> left == NULL
#define ISNUM(node) node ->key == NUM
#define ISVAR(node) node ->key == VAR
#define ISPLUS(node) node -> elem == ADD
#define ISMINUS(node) node -> elem == SUB
#define ISMUL(node) node -> elem == MUL
#define ISDIV(node) node -> elem == DIV
#define ISPOW(node) node -> elem == POW

enum type
{
  NUM = 1,
  VAR = 2,
  OP = 3,
};

enum ops
{
  ADD = 43,
  SUB = 45,
  MUL = 42,
  DIV = 47,
  SIN = 115,
  COS = 99,
  TG = 74,
  SQRT = 50,
  POW = 94,
  CTG = 52,
  LG = 108,
  LOG = 111,
  LN = 110,
  EXP = 65,
};

enum vars
{
  X = 31,
  Y = 30,
};
enum error
{
    NULLPTR = 10001001,
    BRKN = 10001100,
    EMPTY = 10001011,

};
enum side
{
    Left = 1,
    Right = 2,
    NONE = 3,
};
typedef double elem_t;
typedef struct node node_t;

struct node
{
    elem_t elem;
    int key;
    node_t* parent;
    node_t* left;
    node_t* right;
};

typedef struct tree
{
    node_t* root;
    int size;

} tree_t;


node_t* nodeCtor(tree_t* s, node_t* parent, elem_t value, int type);
int nodeOK(node_t* node, node_t* parent);
int treeOK(tree_t *s);
int treeDump (int value, tree_t *s);
int nodeDelete(tree_t* s, node_t* parent);
int treeDtor(tree_t** s);
tree_t* treeCtor(tree_t* s);
node_t* nodeCopy(node_t* s);
node_t* nodePushRoot(tree_t* s, elem_t value, int type);
node_t* nodePush(tree_t* s, node_t* parent, int side, elem_t value, int type);
node_t* nodeValChange(tree_t* s, node_t* node, elem_t value, int type);
node_t* nodeNext(node_t* node, int side);
node_t* nodeParent(node_t* node, int side);
node_t* nodeRoot(tree_t* s);
node_t* nodeLeft(tree_t* s);
node_t* nodeRight(tree_t* s);
void nodeShow(FILE* out, const node_t* cur, const int parent, int* number, int side);
void treeShow(tree_t* s);
void PushLeft(tree_t* s, node_t* node, const int key, const elem_t value);
void PushRight(tree_t* s, node_t* node, const int key, const elem_t value);
void PushRoot(tree_t* s, const int key, const elem_t value);
void PushFirst(tree_t* s, node_t* root);
node_t* CopyNode(const node_t* node);
int CountNodes(node_t* node);
void PrintConsole (node_t* s);
int NodeDtor(tree_t* tree, node_t* node);
void Shorten(node_t* node, double side1, double side2);
void TreeLatex(node_t* node, FILE *file);
