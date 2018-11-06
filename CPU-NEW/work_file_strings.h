#ifndef WORK_FILE_STRINGS_H_INCLUDED
#define WORK_FILE_STRINGS_H_INCLUDED
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <assert.h>
#include <string.h>
#include <locale.h>
#define C_FREE(p)       \
    do                  \
    {                   \
        free(p);        \
        p = NULL;       \
    } while(0)

/**
    \brief The function calculates size of file
    @param [in] filename
    @return number of bytes
*/

int size_of_file(FILE * text);

/**
    \brief The function reads the text into buffer
    @param [in] -
    @return filled buffer
*/

char* read_file();

/**
    \brief The function counts number of lines in the text and separates the strings
    @param [in] pointer to the first element of buffer
    @return number of lines
*/

int number_of_lines(char* buffer);

/**
    \brief The function creates a new massive of pointers
    @param [in] pointer to the first element of buffer
    @return a new massive
*/

char** creation_of_pointers(char* buffer);

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

/**
    \brief The function compares last letters till the string ends
    @param [in] a void input
    @param [in] b void output
    @return a result of comparison: True or False
*/

int reverse_comparator(const void* a, const void* b);

/**
    \brief The function finds the last letter in the string
    @param [in] string
    @param [in] counter of symbols
    @return -
*/
char* Remote_to_last_letter(char *str, int counter);

/**
    \brief The function remotes to the end of the line
    @param [in] string
    @param [in] counter of symbols
    @return number of the last letter in line
*/

int Remote_to_the_end(char **str, int counter);

/**
    \brief The function reads the file, creates memory and marks first letters as pointers
    @param [in] text
    @param [in] number of strings
    @param [in] pointers to the beginnings of lines
    @return -
*/

void create_text(char **buffer, int *num_of_str, char*** pointers, char* filename);

//-------------------------------------------------------------------------------------------------------

int size_of_file(FILE * text) ///current position - done
{
    int current = 0;
    current = ftell(text);

    fseek(text, 0, SEEK_END);

    int number_of_symbols = 0;

    number_of_symbols = ftell(text);
    rewind(text);

    fseek(text, current, SEEK_SET);

    return number_of_symbols;
}

//-------------------------------------------------------------------------------------------------------
char* read_file(const char * fl)
{
    FILE* onegin = fopen(fl, "rb");
    assert(onegin);

    int number_of_symbols = size_of_file(onegin);

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
    return counter+1;
}

//-------------------------------------------------------------------------------------------------------

char** creation_of_pointers(char* buffer)
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
            memory[line++] = buffer + index + 1;
        }
        index++;
    }

    return memory;
}

//-------------------------------------------------------------------------------------------------------

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
//-------------------------------------------------------------------------------------------------------
void write_str(char** string, const int number_of_lines)
{
    for (int i = 0; i< number_of_lines; i++)
    {
        printf("%s\n", string[i]);
    }
    printf("\n");
}

//-------------------------------------------------------------------------------------------------------

int reverse_comparator(const void* a, const void* b)
{
    char* str1 = *(char**) a;
    char* str2 = *(char**) b;

    int counter1 = 0;
    int counter2 = 0;

    counter1 = Remote_to_the_end(&str1, counter1);
    counter2 = Remote_to_the_end(&str2, counter2);

    str1 = Remote_to_last_letter(str1, counter1);
    str2 = Remote_to_last_letter(str2, counter2);

    while (1)
    {
        if (*str1 == '\0' && *str2 != '\0')
            return  1;
        if (*str2 == '\0' && *str1 != '\0')
            return -1;

        if (*str1 > *str2)
            return  1;
        if (*str1 < *str2)
            return -1;
        str1--;
        str2--;
    }
}

//-------------------------------------------------------------------------------------------------------

int Remote_to_the_end(char **str, int counter)
{
    while ((**str != '\0'))
    {
        (*str)++;
        counter++;
    }
    return counter;
}

//-------------------------------------------------------------------------------------------------------

char* Remote_to_last_letter(char *str, int counter)
{
    while ((!isalpha(*str)||(*str == '\0'))
          &&(counter)-- >= 0)
        (str)--;
    return str;
}

//-------------------------------------------------------------------------------------------------------

void create_text(char **buffer, int *num_of_str, char*** pointers, char* filename)
{
    *buffer = read_file(filename);

    *num_of_str = number_of_lines(*buffer);

    *pointers = creation_of_pointers(*buffer);
}

//-------------------------------------------------------------------------------------------------------

#endif
