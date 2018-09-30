#include <assert.h>
#include <stdio.h>
#include <math.h>
#define EPS  0.00001 ///< value a number for comparing

enum Cases_Of_Equation
 {
      INF, ///< The case of an infinite number of roots
    Lin_0, ///< The case of a linear equation with no roots
    Lin_1, ///< The case of a linear equation with one root
    Squ_0, ///< The case of a quadratic equation with no roots
    Squ_1, ///< The case of a quadratic equation with one root
    Squ_2, ///< The case of a quadratic equation with two roots
 };

/**
    \brief The function for finding the roots of the quadratic equation
    @param [in] a coefficient
    @param [in] b coefficient
    @param [in] c coefficient
    @param [out] x1 point to the first root of the equation
    @param [out] x2 point to the second root of the equation

    @return roots of equation

*/

int SolveEqual(double a, double b, double c, double *x1, double *x2);

/**
    \brief The function for finding the root of liner equation
    @param [in] a coefficient
    @param [in] b coefficient
    @param [in] c coefficient
    @param [out] x1 point to the root of liner equation

    @return root of equation
*/

int SolveLiner(double b, double c, double *x1);

/**
    \brief The function for finding discriminant
    @param [in] a coefficient
    @param [in] b coefficient
    @param [in] c coefficient

    @return discriminant
*/

int Discriminant(double a, double b, double c);

/**
    \brief The function for comparison number with EPS
    @param [in] a number

    @return TRUE or FALSE
*/

int Comparison(double a);


int main()
 {
    double a = 0, b = 0, c = 0;

    printf("Enter a, b, c\n");
    scanf("%lf %lf  %lf", &a, &b, &c);

    assert(isfinite(a));
    assert(isfinite(b));
    assert(isfinite(c));

    printf("%.3f*x2+%.3f*x+%.3f=0\n", a,b,c); ///<The full equation

    double x1 = 0, x2 = 0;

    switch (SolveEqual(a, b, c, &x1, &x2))
     {
         case   INF: printf("The equation has Infinity number of roots");          break;
         case Lin_0: printf("The equation has no roots");                          break;
         case Lin_1: printf("The equation has 1 root, x = %f", x1);                break;
         case Squ_0: printf("The equation has 0 roots");                           break;
         case Squ_1: printf("The equation has 1 root, x = %f", x1);                break;
         case Squ_2: printf("The equation has 2 roots, x1 = %f, x2 = %f", x1, x2); break;

     }
 }

///---------------------------------------------------------------------------------------------------

int Discriminant(double a, double b, double c)
 {
     double D = 0;
     D = b*b-4*c*a;
     return D;
 }

///----------------------------------------------------------------------------------------------------

int Comparison (double a)
 {
   return (fabs(a) <= EPS);
 }

///----------------------------------------------------------------------------------------------------

int SolveEqual(double a, double b, double c, double *x1, double *x2)
 {
    if (Comparison(a))

             return SolveLiner(b, c, x1);
     else
        {
         if (Comparison(c))
         {
          *x1 = SolveLiner(b, a, &x1);
          *x2 = 0;
             return Squ_2;
         }
        else
         {
          double D = Discriminant(a, b, c);

          if (D < 0)
             return Squ_0;

          if (Comparison(D))
           {
             *x1 = -b/2/a;
             return Squ_1;
           }
          else
           {
              D = sqrt(D);
              *x1 = (-b + D/2/a);
              *x2 = (-b - D/2/a);
             return Squ_2;
           }
         }
        }
 }

///----------------------------------------------------------------------------------------------------

 int SolveLiner(double b, double c, double *x1)
  {
      if ((fabs(b) <= EPS) && (fabs(c) <= EPS))
            return INF;
      else
        {
         if ((fabs(b) <= EPS && fabs(c) > EPS))
            return Lin_0;
         if (fabs(b) >= EPS)
          {
            *x1 = -c/b;
            return Lin_1;
          }
        }
  }

///-------------------------------------------------------------------------------------------------------
