#include <stdlib.h>
#include <errno.h>
#define MAX_LENGTH 50
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
    int type;
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
int nodeDelete(tree_t* s, node_t** parent);
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
node_t* CopyNode(const node_t* node);
