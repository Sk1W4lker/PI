#include <stdio.h>

float multInt1 (int n, float m) {
    float r = 0;

    while (n != 0) {
        r = r + m;
        n--;
    }

    return r;
}

float multInt2 (int n, float m) {
    float r = 0;

    while (n > 0) {
        if (n % 2 != 0) r+=m;
        n /= 2;
        m *= 2;
    }

    return r;
}

int mdc1(int a, int b) {
    int menor, i;
    int mdc = 1;

    if (a < b)
        menor = a;
    else
        menor = b;

    for (int i = menor; i >= 1; i--) {
        if (a % i == 0 && b % i == 0) {
            mdc = i;
        }
    }

    return mdc;
}

int mdc2(int a, int b) {
    while(a != b) {
        if (a > b) 
            a -= b;
        else
            b -= a;
    }
    return a;
}

int mdc3(int a, int b) {
    while (a != 0 && b != 0) {
        if (a > b)
            a %= b;
        else
            b %= a;
    }
    return (a == 0) ? b : a; //Se a é 0 devolve b inves de a
}

int fib1(int n) {
    return (n < 2) ? 1 : fib(n - 1) + fib(n - 2);
}

/*
int fib (int n) {
    if(n == 1 || n == 2) return 1;
    else return fib(n - 1) + fib(n - 2);
}
*/

int main() {
    float res = multInt1(81, 423);
    printf("%f\n", res);

    float res1 = multInt2(81, 423);
    printf("%f\n", res1);

    printf("%d\n", mdc1(126, 45));
    printf("%d\n", mdc2(126, 45));
    printf("%d\n", mdc3(126, 45));
    return 0;
}
void swap (int v[], int i, int j)