#include <assert.h>
#include <stdio.h>
#include <math.h>
#define EPS  1e-6 ///< value a number for comparing
#define COMPAREWITHZERO(a) (fabs(a) < EPS)

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

int SolveSquare(double a, double b, double c, double *x1, double *x2);

/**
    \brief The function for finding the root of liner equation
    @param [in] a coefficient
    @param [in] b coefficient
    @param [in] c coefficient
    @param [out] x1 point to the root of liner equation

    @return root of equation
*/

int SolveLinear(double b, double c, double *x1);

/**
    \brief The function for finding discriminant
    @param [in] a coefficient
    @param [in] b coefficient
    @param [in] c coefficient

    @return discriminant
*/

 double Discriminant(double a, double b, double c);

///---------------------------------------------------------------------------------------------------


int main()
 {
    double a = NAN, b = NAN, c = NAN;

    printf("Enter a, b, c\n");
    int save = scanf("%lf %lf  %lf", &a, &b, &c);

    if (save < 3 )
     {
      printf("Enter the numbers, criminal scum");
      return 0;
     }

    if (isfinite(a) || (isfinite(b)) || (isfinite(c)))
     {
      printf("Check your input");
      return 0;
     }

    printf("%.3f*x2+%.3f*x+%.3f=0\n", a,b,c); ///<The full equation

    double x1 = 0, x2 = 0;

    switch (SolveSquare(a, b, c, &x1, &x2))
     {
         case   INF: printf("The equation has Infinity number of roots");          break;
         case Lin_0: printf("The equation has no roots");                          break;
         case Lin_1: printf("The equation has 1 root, x = %f", x1);                break;
         case Squ_0: printf("The equation has no roots");                          break;
         case Squ_1: printf("The equation has 1 root, x = %f", x1);                break;
         case Squ_2: printf("The equation has 2 roots, x1 = %f, x2 = %f", x1, x2); break;

     }
 }

///---------------------------------------------------------------------------------------------------

inline double Discriminant(double a, double b, double c)
 {
     assert(isfinite(a));
     assert(isfinite(b));
     assert(isfinite(c));

     double D = 0;
     D = b*b-4*c*a;
     return D;
 }

///----------------------------------------------------------------------------------------------------

int SolveSquare(double a, double b, double c, double *x1, double *x2)
 {
    assert(isfinite(a));
    assert(isfinite(b));
    assert(isfinite(c));

    if (COMPAREWITHZERO(a))

             return SolveLinear(b, c, x1);
     else
        {
         if (COMPAREWITHZERO(c))
         {
          *x1 = SolveLinear(b, a, x1);
          *x2 = 0;
             return Squ_2;
         }
        else
         {
          double D = Discriminant(a, b, c);

          if (D < 0)
             return Squ_0;

          if (COMPAREWITHZERO(D))
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

 int SolveLinear(double b, double c, double *x1)
  {
      if (COMPAREWITHZERO(b) && COMPAREWITHZERO(c))
            return INF;
      else
        {
         if (COMPAREWITHZERO(b) && !COMPAREWITHZERO(c))
            return Lin_0;
         if (!COMPAREWITHZERO(b))
          {
            *x1 = -c/b;
            return Lin_1;
          }
        }
  }

///-------------------------------------------------------------------------------------------------------
