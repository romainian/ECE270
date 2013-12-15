#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

int main(void)
{
FILE *fp;
fp = fopen("studentfunctions.txt", "w");
int i;
for (i=1;i<100;i++)
{
    fprintf(fp, "\n\n// Student %3d", i);
    fprintf(fp, "\n//  Get Data");
    fprintf(fp, "\nvoid student%d_getData()", i);
    fprintf(fp, "\n{");
    fprintf(fp, "\n");
    fprintf(fp, "\n}");
    fprintf(fp, "\n//  Draw Image");
    fprintf(fp, "\nvoid student%d_drawImage()", i);
    fprintf(fp, "\n{");
    fprintf(fp, "\n");
    fprintf(fp, "\n}");
    fprintf(fp, "\n//  Student Main");
    fprintf(fp, "\nvoid student%d(float cx_in, float cy_in, float cr_in, float rx_in, float ry_in, float rWidth_in, float rHeight_in)", i);
    fprintf(fp, "\n{");
    fprintf(fp, "\n");
    fprintf(fp, "\n}");
}
return 0;
}
