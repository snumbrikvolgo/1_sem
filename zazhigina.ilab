#include <stdio.h>
#include <math.h>
#define SIZE 100

/**
    \brief The function calculated the Resistance
    @param [in] I, mA
    @param [in] U, V
    @param [in] number of lines

    @return void

*/

void CalculateLaba(double* I, double* U, int line);

/**
    \brief The function reads data in the text file
    @param [in] I, mA
    @param [in] U, V

    @return number of lines

*/

int ReadData (double* I, double* U);

//-------------------------------------------------------------------------------------------------------

int main()
{
    int line = 0;
    double I[SIZE] = {}, U[SIZE] = {};
    line = ReadData(I, U);
    CalculateLaba(I, U, line);
    return 0;
}

//-------------------------------------------------------------------------------------------------------

int ReadData (double* I, double* U)
{
    FILE * file = fopen("laba.txt", "r");
    if (!file)
    {
     printf("Cannot open laba.txt");
    }

    int line = 0;
    while (1)
    {
     if (fscanf(file, "%lf %lf", I + line, U + line) == EOF) break;
     line++;
    }

    fclose(file);
    return line;
}

//-------------------------------------------------------------------------------------------------------

void CalculateLaba(double I[], double U[], int line)
{    int index = 0;
     FILE * file = fopen("rezy.txt", "w");
     while (index < line)
     {
      fprintf(file, "%lf\n", U[index]/I[index]);
        index++;
     }
     fclose(file);
}
