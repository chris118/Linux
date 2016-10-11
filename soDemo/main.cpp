#include "Math/math.h"
#include <stdio.h>


int main(int argc, char* argv[])
{
int a = 10, b = 5;
printf("%d + %d = %d\n", a, b, Add(a, b));
printf("%d - %d = %d\n", a, b, Sub(a, b));
printf("%d * %d = %d\n", a, b, Mul(a, b));
printf("%d / %d = %d\n", a, b, Div(a, b));
return 0;
}
