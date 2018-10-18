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
#define RMIN 0


/**
    \brief The function calculated the Resistance in 1.1.1 laba
    @param [in] I, mA
    @param [in] U, V
    @param [in] number of measures of resistance
    @param [in] d, mm
    @param [in] number of measures of diameter
    @param [in] R, kOm
    @param [in] po, mOm
    @param [in] Square of the wire
    @param [in] length of the wire
    @return TRUE or FALSE

*/

int CalculateLaba(double* I, double* U, int line, double *d, int measures, double* R, double *po, double *S, double l);

/**
    \brief The function reads data in the text file
    @param [in] I, mA
    @param [in] U, V
    @param [in] d, mm
    @param [in] quantity of measures of the wire
    @param [in] quantity of measures of resistance

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

/**
    \brief The function prints the results of laba
    @param [in] arrays of data
    @param [in] size of arrays
    @param [in] single data

    @return TRUE or FALSE
*/

int PrintRes (double *a, double *b, int asize, int bsize, double c, double d, double e);
//-------------------------------------------------------------------------------------------------------

int main()
{
    int line = 0, measure = 0;
    double S = 0, po = 0, l = 0.3;

    double I[SIZE] = {}, U[SIZE] = {}, d[SIZE] = {}, R[SIZE] = {};

    assert(ReadData(I, U, d, &measure, &line));

    assert(CalculateLaba(I, U, line, d, measure, R, &po, &S, l));
    assert(PrintRes(R, d, line , measure, po, S, l));

    return 0;
}

//-------------------------------------------------------------------------------------------------------


int ReadData (double* I, double* U, double* d, int *dsize, int* rsize)
{
    FILE * file = fopen("laba 1.1.1 UI.txt", "r");

    if (!file)
    {
            printf("Cannot open laba 1.1.1 UI.txt");
            return 0;
    }

    while (1)
    {

       if (fscanf(file, "%lg %lg", I + (*rsize),  U + (*rsize)) == EOF) break;
       (*rsize)++;
    }
    fclose(file);

    file = fopen("laba 1.1.1 d.txt", "r");
     if (!file)
    {
            printf("Cannot open laba 1.1.1 d.txt");
            return 0;
    }

    while(1)
    {
        if  (fscanf(file, "%lf", d + (*dsize)) == EOF) break;
        (*dsize)++;
    }

    fclose(file);

    return 1;
}

//-------------------------------------------------------------------------------------------------------

int CalculateLaba(double* I, double* U, int line, double *d, int measures, double* R, double *po, double *S, double l)
{

     int index = 0;
     FILE * file = fopen("rezy 1.1.1.txt", "w");
     while (index < line)
     {
          if (I[index] < IMIN || I[index] > IMAX)
        {
           printf("ERROR: I[%d] IS OUT OF MEASURE\n", index);
        }
        if (I[index] < fabs(I[index] - EPS))
        {
            printf("ERROR: WRONG DATA, DIVISION BY ZERO I[%d]\n", index);
        }

        if (U[index] < UMIN || U[index] >UMAX)
        {
           printf("ERROR: U[%d] IS OUT OF MEASURE\n", index);
        }
        fprintf(file, "R[%d] = %lf kOM\n", index,  U[index]/I[index]);

        R[index] = U[index]/I[index];
        index++;
    }
        double dav = Average(d, measures);
        (*S) = 3.1415 * dav * dav / 4;
        *po = (*S) * Average(R, line) / l;

     fclose(file);
     return 1;

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
        sum = (s[i] - d_av) * (s[i] - d_av);

    return sqrt(sum/size);
}

int PrintRes (double *a, double *b, int asize, int bsize, double c, double d, double e)
{
    FILE * file = fopen("rezy 1.1.1.txt", "w");
    int index = 0;
    while (index < asize)
    {
        fprintf(file, "R[%d] = %lf kOM\n", index,  a[index]);
        index++;
    }
    if (Average(a, asize) > RMAX || Average(a, asize) < RMIN)
           printf("ERROR: R IS OUT OF MEASURE\n");

    else
           fprintf(file, "R(average) = %lg kOM\n", Average(a, asize));

    fprintf(file, "delta_R = %lg kOM\n", Accuracy(a, asize));

    if (Average(b, bsize) > DMAX || Average(b, bsize) < DMIN)
           printf("ERROR: d IS OUT OF MEASURE\n");

    else
           fprintf(file, "d(average) = %lg mm \n", Average(b, bsize));

    fprintf(file, "delta_d = %lg mm\n", Accuracy(b, bsize));
    fprintf(file, "S = %lg mm^2\n", d);
    fprintf(file, "l = %lg m\n", e);
    fprintf(file, "po = %lg mOm\n", c);

    fclose(file);
    return 1;
}
