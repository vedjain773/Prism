#ifndef COMPLEX_H
#define COMPLEX_H

typedef struct {
    float re;
    float im;
} Complex;

Complex add(Complex *a, Complex *b);
Complex mul(Complex *a, Complex *b);
Complex neg(Complex *a);
Complex conjugate(Complex *a);
Complex cis(float theta);

#endif
