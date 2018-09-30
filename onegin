#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <assert.h>
#include <string.h>
#include <locale.h>

/**
    \brief The function calculates size of file
    @param [in] filename

    @return number of bytes
*/

int sizeoffile(FILE * text);

/**
    \brief The function reads the text into buffer
    @param [in] -

    @return filled buffer
*/

char* readfile();

/**
    \brief The function counts number of lines in the text
    @param [in] pointer to the first element of buffer

    @return number of lines
*/

int number_of_lines(char* buffer);

/**
    \brief The function creates a new massive of pointers
    @param [in] pointer to the first element of buffer

    @return a new massive
*/

char** creationofpointers(char* buffer);

/**
    \brief The function compares any elements
    @param [in] a void input
    @param [in] b void output

    @return a result of comparison: True or False
*/

int comparator(const void* a, const void* b);

/**
    \brief The function prints sorted text
    @param [in] pointer to the pointer of the beginning of the line
    @param [in] number of lines

    @return printed text
*/

void write_str(char** string, const int number_of_lines);
//-------------------------------------------------------------------------------------------------------

int main()
 {
  setlocale (LC_ALL, "Russian");

  char* buffer = readfile();

  int num_of_str = number_of_lines(buffer);

  char** pointers = creationofpointers(buffer);

  qsort(pointers, num_of_str, sizeof(char*), comparator);

  write_str(pointers, num_of_str);

  return 0;
 }

//-------------------------------------------------------------------------------------------------------
int sizeoffile(FILE * text)
 {
  fseek(text, 0, SEEK_END);

  int number_of_symbols = 0;

  number_of_symbols = ftell(text);
  rewind(text);

  return number_of_symbols;
 }

//-------------------------------------------------------------------------------------------------------
char* readfile()
 {
  FILE* onegin = fopen("onegin.txt", "rb");
  assert(onegin);

  int number_of_symbols = sizeoffile(onegin);

  char* buffer = (char*) calloc (number_of_symbols+1, sizeof(*buffer));
  assert(buffer);

  fread(buffer, number_of_symbols, sizeof(*buffer), onegin);
  fclose(onegin);
  return buffer;

 }
//-------------------------------------------------------------------------------------------------------
int number_of_lines(char* buffer)
 {
  int counter = 0;
  int index = 0;

  while (buffer[index++] != '\0')
   {

    if (buffer[index] == '\n')
    counter++;
   }
  return counter;
 }

//-------------------------------------------------------------------------------------------------------

char** creationofpointers(char* buffer)
 {
  int index = 0;
  int number_lines = number_of_lines(buffer);

  char** memory = (char**) calloc(number_lines, sizeof(char*));
  memory[0] = &buffer[0];

  int line = 1;

  while (buffer[index] != '\0')
   {
    if (buffer[index] == '\n')
     {
      buffer[index] = '\0';
      memory[line++] = buffer+index+1;
     }
    index++;
    }

   return memory;
 }

int comparator(const void* a, const void* b)
 {
     char* str1 = *(char**) a;
     char* str2 = *(char**) b;

     while (isspace(*str1)||ispunct(*str1))
        str1++;

     while (isspace(*str2)||ispunct(*str2))
        str2++;
     return strcmp(str1, str2);
 }

void write_str(char** string, const int number_of_lines)
 {
     for (int i = 0; i< number_of_lines; i++)
      {
       printf("%s\n", string[i]);
      }
 }







