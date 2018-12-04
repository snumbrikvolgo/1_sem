#define dL Diff(node -> left)
#define dR Diff(node -> right)
#define cL CopyNode(node -> left)
#define cR CopyNode(node -> right)

#define ISNUM(node) node -> key == NUM
#define ISVAR(node) node -> key == VAR

enum type
{
  NUM = 1,
  VAR = 2,
  OP = 3,
};

enum ops
{
  ADD = 32,
  SUB = 33,
  MUL = 34,
  DIV = 35,
  SIN = 36,
  COS = 37,
  TAN = 38,
  SQRT = 39,
  POW = 40,
};

enum vars
{
  X = 31,
  Y = 30,
};
