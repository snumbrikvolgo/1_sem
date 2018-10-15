#include <stdio.h>
#include <math.h>
#define SIZE 100
#define EPS 1e-6
#define UMAX 400
#define UMIN 200
#define IMAX 200
#define IMIN 100
#define DMIN 0.01
#define DMAX 0.5

/**
    \brief The function calculated the Resistance in 1.1.1 laba
    @param [in] I, mA
    @param [in] U, V
    @param [in] number of lines

    @return void

*/

void CalculateLaba(double* I, double* U, int line, double *d, int measures);

/**
    \brief The function reads data in the text file
    @param [in] I, mA
    @param [in] U, V

    @return number of lines

*/

int ReadData (double* I, double* U, double* d, int measures);
double average(double* s, int size);

//-------------------------------------------------------------------------------------------------------

int main()
{
    int line = 0, measures = 0;
    printf("How many measurements of the wire did you take?\n");
    scanf("%d", &measures);
    double I[SIZE] = {}, U[SIZE] = {}, d[SIZE] = {};
    line = ReadData(I, U, d, measures);
    CalculateLaba(I, U, line, d, measures);
    return 0;
}

//-------------------------------------------------------------------------------------------------------

int ReadData (double* I, double* U, double* d, int measures)
{
    FILE * file = fopen("laba 1.1.1 UI.txt", "r");
    if (!file) printf("Cannot open laba 1.1.1 UI.txt");

    int line = 0;
    int number = 0;

    while (1)
    {
     if (fscanf(file, "%lf %lf", I + line, U + line) == EOF) break;
     //printf("%lf", I[line]);
     line++;
    }
    fclose(file);

    file = fopen("laba 1.1.1 d.txt", "r");
    if (!file) printf("Cannot open laba 1.1.1 d.txt");

    while(number  < measures)
    {
        if  (fscanf(file, "%lf", d + number) == EOF) break;
        //printf("%lf", d[number]);
        number++;
    }

    fclose(file);

    return line;
}

//-------------------------------------------------------------------------------------------------------

void CalculateLaba(double I[], double U[], int line, double* d, int measures)
{    int index = 0;
     FILE * file = fopen("rezy 1.1.1.txt", "w");
     while (index < line)
     {
          if (I[index] < IMIN || I[index] > IMAX)
        {
           printf("ERROR: I[%d] IS OUT OF MEASURE", index);
           return;
        }
        if (I[index] < fabs(I[index] - EPS))
        {
            printf("ERROR: WRONG DATA, DIVISION BY ZERO I[%d]", index);
        return;
        }

        if (U[index] < UMIN || U[index] >UMAX)
        {
           printf("ERROR: U[%d] IS OUT OF MEASURE", index);
           return;
        }
        fprintf(file, "R[%d] = %lf kOM\n", index,  U[index]/I[index]);
        index++;
     }
       fprintf(file, "d(average) = %f mm^2 \n", average(d, measures));
     fclose(file);
}

double average(double* s, int size)
{

    double sum = 0;
    for (int i =0; i < size; i++)
    {
        if (s[i] > DMAX || s[i] < DMIN)
        {
            printf("ERROR: d IS OUT OF MEASURE");
            return -100000000;
        }
         sum += s[i];
    }

    return sum/size;
}
