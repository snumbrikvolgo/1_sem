enum side
{
    LEFT = 1,
    RIGHT = 2,
    NONE = 3,
};

enum type
{
  CONST = 1,
  VAR = 2,
  OP = 3,
};

enum ops
{
  PLUS = 32,
  MINUS = 33,
  MUL = 34,
  DIV = 35,
  SIN = 36,
  COS = 37,
  TAN = 38,
  SQRT = 39,
};

enum vars
{
  X = 31,
  Y = 30,
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
