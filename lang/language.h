
#define NAME_SIZE 50
#define NUM_VARS 1000
const char* input = "prog.txt";

#define NUMBER(number)          MakeNode (NUM,  number, NULL, NULL)
#define VARIABLE(number)        MakeNode (VAR,  number, NULL, NULL)
#define FUNCT(number)           MakeNode (FUNC, number, NULL, NULL)


#define ISNUM(node) node -> key == NUM
#define ISVAR(node) node -> key == VAR

#define      PLUS(left, right) MakeNode (OP, ADD,   left, right)
#define     MINUS(left, right) MakeNode (OP, SUB,   left, right)
#define    MULTIP(left, right) MakeNode (OP, MUL,   left, right)
#define     DIVIS(left, right) MakeNode (OP, DIV,   left, right)
#define     ASSGN(left, right) MakeNode (OP, ASG,   left, right)
#define    OPERAT(left, right) MakeNode (OP, OPER,  left, right)
#define      MAS(left, right)  MakeNode (OP, JA,    left, right)
#define     MENOR(left, right) MakeNode (OP, JB,    left, right)
#define      EMAS(left, right) MakeNode (OP, JAE,   left, right)
#define    EMENOR(left, right) MakeNode (OP, JBE,   left, right)
#define     IGUAL(left, right) MakeNode (OP, JE,    left, right)
#define    NIGUAL(left, right) MakeNode (OP, JNE,   left, right)
#define    CONDIC(left, right) MakeNode (OP, SI,    left, right)
#define     OTROS(left, right) MakeNode (OP, OTRO,  left, right)
#define      LUPA(left, right) MakeNode (OP, MIENTRAS, left, right)
#define   PARAMET(left, right) MakeNode (OP, PARAM, left, right)
#define     SINUS(current)     MakeNode (OP, SIN,   current, NULL)
#define   COSINUS(current)     MakeNode (OP, COS,   current, NULL)
#define   RADICAL(current)     MakeNode (OP, SQRT,  current, NULL)
#define   ENTRADA(current)     MakeNode (OP, SCAN,  current, NULL)
#define    SALIDA(current)     MakeNode (OP, PRINT, current, NULL)
#define    DESPAC(left, right) MakeNode (OP, DESP,   left, right)
typedef struct vars vars_t;

  struct vars
{
    char* nombre[NUM_VARS]; //////////////////////////////////////////
    int numero;
};
vars_t funcions;
//vars_t vars;


enum lang_errors
{
  SYNTERROR = 1,
  NOFUNC = 2,
  NOVAR = 3,
};
#define COMCMD(name, command, size)                             \
{                                                               \
  s += size;                                                    \
                                                                \
  skipSpaces();                                                 \
                                                                \
  char* ptr = s;                                                \
  node_t* value2 = getE(vars);                                  \
                                                                \
  skipSpaces();                                                 \
  printf("cluasecom %c\n", *s);                                                         \
                                                          \
  assert(s != ptr);                                             \
  return command(value, value2);                                \
}

#define CONDICIONAL(name)                                       \
  skipSpaces();                                                 \
          printf("cluase %c\n", *s);                                                         \
  if (*(s++) != '(')                                         \
  {                                                             \
    errno = SYNTERROR;                                          \
    fprintf(stderr, "No braaaacket en " #name);                    \
    exit(0);                                                    \
  }                                                             \
  skipSpaces();                                                 \
  char* ptr = s;                                                \
                                                                \
  node_t* value = getExp(vars);                                 \
  assert(ptr != s);                                             \
                                                                \
  skipSpaces();                                                 \
  printf("cluase %c\n", *s);                                                         \
                                                \
  assert(*(s++) == ')');                                            \
                                                                \
  skipSpaces();                                                 \
                                                                \
  ptr = s;                                                      \
  printf("cluase222 %c\n", *s);                                                         \
\
  node_t* value2 = getOp(vars);                                 \
  printf("cluase333 %c\n", *s);                                                         \
                                                            \
  assert(s != ptr);                                             \
                                                                \
  skipSpaces();

#define RECIBE(name)                                            \
    skipSpaces();                                               \
    if (*(s++) != '(')                                          \
    {                                                           \
      errno = SYNTERROR;                                        \
      fprintf(stderr, "No '(' en" #name);                       \
      exit(0);                                                  \
    }                                                           \
    skipSpaces();                                               \
                                                                \
    if (!isalpha(*s))                                           \
    {                                                           \
      errno = SYNTERROR;                                        \
      fprintf(stderr, "no arg\n");                              \
      exit(0);                                                  \
    }                                                           \
    char* name = getV();                                        \
    int num = Existe(name, vars);                               \
                                                                \
    if (num == -1)                                              \
    {                                                           \
      errno = NOVAR;                                            \
      fprintf(stderr, "Hay no nombre de el variable\n");        \
      exit(0);                                                  \
    }                                                           \
                                                                \
    skipSpaces();                                               \
                                                                \
    if (*(s++) != ')')                                          \
    {                                                           \
      errno = SYNTERROR;                                        \
      fprintf(stderr, "No ')'" #name);                          \
      exit(0);                                                  \
    }                                                           \
    skipSpaces();                                               \
                                                                \
    if (*(s++) != ';')                                          \
    {                                                           \
      errno = SYNTERROR;                                        \
      fprintf(stderr, "No hay fin de terminacion");             \
      exit(0);                                                  \
    }                                                           \
    skipSpaces();

enum types
{
    NUM      = 1,
    VAR      = 2,
    OP       = 3,
    FUNC     = 4
};

enum ops
{
      ADD   = 1,
      SUB   = 2,
      MUL   = 3,
      DIV   = 4,
      SIN   = 5,
      COS   = 6,
      SQRT  = 7,
      OPER  = 8,
      JA    = 9,
      JB    = 10,
      JE    = 11,
      JNE   = 12,
      JAE   = 13,
      JBE   = 14,
      ASG   = 15,
      SI    = 16,
      OTRO  = 17,
   MIENTRAS = 18,
      SCAN  = 19,
      PRINT = 20,
      LLAME = 21,
      PARAM = 22,
      DESP  = 23,
};

#define CHOSEOP(name, img)                                            \
case name:                                                            \
{                                                                     \
  return #img;                                                       \
  break;                                                              \
}
