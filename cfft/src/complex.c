#include "complex.h"
#include <math.h>

Complex add(Complex *a, Complex *b)
{
    Complex result;
    result.re = a->re + b->re;
    result.im = a->im + b->im;

    return result;
}

Complex mul(Complex *a, Complex *b)
{
    Complex result;
    result.re = a->re * b->re - a->im * b->im;
    result.im = a->re * b->im + a->im * b->re;

    return result;
}

Complex neg(Complex *a)
{
    Complex result;
    result.re = -a->re;
    result.im = -a->im;

    return result;
}

Complex conjugate(Complex *a)
{
    Complex result;
    result.re = a->re;
    result.im = -a->im;

    return result;
}

Complex cis(float theta)
{
    Complex result;
    result.re = cos(theta);
    result.im = sin(theta);

    return result;
}
