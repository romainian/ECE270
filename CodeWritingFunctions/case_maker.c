#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

int main(void)
{
FILE *fp;
fp = fopen("cases.txt", "w");
int i;
for (i=0;i<100;i++)
{
    fprintf(fp, "\n        case %3d:", i);
    fprintf(fp, "\n            {");
    fprintf(fp, "\n                student%d(cx_in, cy_in, cr_in, rx_in, ry_in, rWidth_in, rHeight_in);", i);
    fprintf(fp, "\n                break;");
    fprintf(fp, "\n            }");
}
return 0;
}
