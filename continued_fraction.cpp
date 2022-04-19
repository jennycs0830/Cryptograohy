#include<stdio.h>
#include<stdlib.h>

using namespace std;
#define E 2.71828182846

typedef struct{
    int top;
    int bottom;
}Frac;

//inverting a fraction just means swapping numerator/denominator
void invert(Frac*f){
    int tmp=f->bottom;
    f->bottom=f->top;
    f->top=tmp;
}

//to add int to fraction, first multiply by denominator
void add(Frac*f,int i){
    f->top+=(i*f->bottom);
}

double continued_fraction(int limit){
    double approx;
    double e=E;
    int series[50];
    Frac f;

    for(int i=0;i<limit;i++){
        series[i]=(int)e;
        e=1.0/(e-(int)e);
    }

    f.top=1;
    f.bottom=0;

    for(int i=limit;i>=0;i--){
        invert(&f);
        add(&f,series[i]);
    }

    approx=((double)f.top/(double)f.bottom);
    
}