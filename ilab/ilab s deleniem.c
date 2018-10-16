#include <stdio.h>
#include <math.h>
#include <assert.h>
#define SIZE 100
#define EPS 1e-6
#define UMAX 400
#define UMIN 200
#define IMAX 200
#define IMIN 100
#define DMIN 0.01
#define DMAX 0.5
#define RMAX 4
#define RMIN 1


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
    @param [in] d, mm
    @param [in] quantity of measures of the wire

    @return TRUE OR FALSE

*/

int ReadData (double* I, double* U, double* d, int *dsize, int* rsize);

/**
    \brief The function reads data in the text file

    @param [in] array of measurements
    @param [in] quantity of measures of the wire


    @return average number

*/

double Average(double* s, int size);

/**
    \brief The function reads data in the text file
    @param [in] I, mA
    @param [in] U, V

    @return accuracy of measurements

*/

double Accuracy (double *s, int size);

//-------------------------------------------------------------------------------------------------------

int main()
{
    int line = 0, measures = 5;
    //printf("How many measurements of the wire did you take?\n");
    //scanf("%d", &measures);
    double I[SIZE] = {}, U[SIZE] = {}, d[SIZE] = {};
    assert(ReadData(I, U, d, &measures, &line));
    CalculateLaba(I, U, line, d, measures);

    return 0;
}

//-------------------------------------------------------------------------------------------------------


int ReadData (double* I, double* U, double* d, int *dsize, int* rsize)
{
    FILE * file = fopen("laba 1.1.1 UI.txt", "r");
    //*dsize = 0;
    //rsize = 0;
    printf("%d", *rsize);
    if (!file)
    {
            printf("Cannot open laba 1.1.1 UI.txt");
            return 0;
    }

    while (1)
    {
        printf("%lg", U[*rsize]);
       if (fscanf(file, "%lg %lg", I + (*rsize),  U + (*rsize)) == EOF) break;
       (*rsize)++;
    }
    fclose(file);

    file = fopen("laba 1.1.1 d.txt", "r");
    {
            printf("Cannot open laba 1.1.1 d.txt");
            return 0;
    }

    while(1)
    {
        if  (fscanf(file, "%lf", d[*dsize] == EOF)) break;
        (*dsize)++;
    }

    fclose(file);

    return 1;
}

//-------------------------------------------------------------------------------------------------------

void CalculateLaba(double I[], double U[], int line, double* d, int measures)
{    int index = 0;
     FILE * file = fopen("rezy 1.1.1.txt", "w");
     double R[line];
     while (index < line)
     {
          if (I[index] < IMIN || I[index] > IMAX)
        {
           printf("ERROR: I[%d] IS OUT OF MEASURE\n", index);
           return;
        }
        if (I[index] < fabs(I[index] - EPS))
        {
            printf("ERROR: WRONG DATA, DIVISION BY ZERO I[%d]\n", index);
        return;
        }

        if (U[index] < UMIN || U[index] >UMAX)
        {
           printf("ERROR: U[%d] IS OUT OF MEASURE\n", index);
           return;
        }
        fprintf(file, "R[%d] = %lf kOM\n", index,  U[index]/I[index]);
        R[index] = U[index]/I[index];
        index++;
     }

       if (Average(R, measures) > RMAX || Average(R, measures) < RMIN)
           printf("ERROR: R IS OUT OF MEASURE\n");
       else
           fprintf(file, "R(average) = %lg kOM\n", Average(R, line));

       fprintf(file, "delta_R = %lg kOM\n", Accuracy(R, line));

       if (Average(d, measures) > DMAX || Average(d, measures) < DMIN)
           printf("ERROR: d IS OUT OF MEASURE\n");
       else
           fprintf(file, "d(average) = %lg mm \n", Average(d, measures));

       double delta_d = Accuracy(d, measures);
       fprintf(file, "delta_d = %lg mm\n", delta_d);



     fclose(file);

}

double Average(double* s, int size)
{
    double sum = 0;
    for (int i =0; i < size; i++)

         sum += s[i];

    return sum/size;
}

double Accuracy (double *s, int size)
{
    double d_av = Average(s, size);
    double sum = 0;
    for (int i = 0; i < size; i++)
        sum = (s[0] - d_av) * (s[0] - d_av);

    return sqrt(sum/size);
}
