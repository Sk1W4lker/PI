#include <stdio.h>
#include <math.h>

void robot(void) {

long x = 28;
long y = 2;
char d = 'w';
int v = 1;

long distAtual = 0;
long maxDist = 0;

for(int t = 1; t < 10000; t++) { //10000 segundos

if (t % 3 == 0 && t % 5 == 0) {

    if(distAtual > maxDist)
        maxDist = distAtual;

    distAtual = 0;

    if (d == 'n')
        d = 'e';
    else if (d == 'e')
        d = 's';
    else if (d == 's')
        d = 'w';
    else
        d = 'n';

} 
else if (t % 3 == 0)
    v += 2;

else if (t % 5 == 0)
    v -= 1;

else {

    if (d == 'n')
        y += v;
    else if (d == 'e')
        x += v;
    else if (d == 's')
        y -= v;
    else
        x -= v;

    distAtual += v;
}

}

if(distAtual > maxDist)
    maxDist = distAtual;

printf("%ld\n", x);
printf("%ld\n", maxDist);
}

int main() {
    robot();
}