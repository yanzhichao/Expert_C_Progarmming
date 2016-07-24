#ifndef XP_INCLUDE
#define XP_INCLUDE

#define T XP_T

typedef unsigned char *T;

int XP_quotion(int n,T z, T x,int y);
int XP_product(int n,T z,T x, int y);
int XP_sub(int n,T z,T x,T y,int borrow);
int XP_add(int n,T z,T x, T, int carry);
int XP_length(int n,T x);
int XP_mul(T z,int n,T x,int m,T y);
int XP_div(int n,T q,T x,int m, T y,T r, T tmp);
int XP_fromstr(int n,T z,const char *str,int base,char** end);
int XP_tostr(int n, T z,char* outstr,int base, char** end);

#undef  T

#endif