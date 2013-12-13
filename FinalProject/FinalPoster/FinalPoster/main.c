#include <stdio.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>
#define MATRIX_HEIGHT 10
#define MATRIX_WIDTH 10

void Image(int matrix[MATRIX_HEIGHT][MATRIX_WIDTH])
{
    int i,j,flag;
    flag=0;
    for(i=0;i<MATRIX_HEIGHT;i++)
    {
        for(j=0;j<MATRIX_WIDTH;j++)
        {
            if(flag!=1)
            {
                if(matrix[i][j]==0)
                {
                    matrix[i][j]=1;
                    flag=1;
                }
            }
        }
    }
}
void largeImage(int matrix[MATRIX_HEIGHT][MATRIX_WIDTH])
{
    int i,j,flag;
    flag=0;
    for(i=0;i<MATRIX_HEIGHT;i++)
    {
        for(j=0;j<MATRIX_WIDTH;j++)
        {
            if(flag!=1)
            {
                if(matrix[i][j]==0&&(MATRIX_WIDTH-j)>=2)
                {
                    matrix[i][j]=2;
                    matrix[i+1][j]=2;
                    matrix[i][j+1]=2;
                    matrix[i+1][j+1]=2;
                    flag=1;
                }
            }
        }
    }
}
void largestImage(int matrix[MATRIX_HEIGHT][MATRIX_WIDTH])
{
    int i,j,flag;
    flag=0;
    for(i=0;i<MATRIX_HEIGHT;i++)
    {
        for(j=0;j<MATRIX_WIDTH;j++)
        {
            if(flag!=1)
            {
                if(matrix[i][j]==0&&(MATRIX_WIDTH-j)>=3)
                {
                    matrix[i][j]=3;
                    matrix[i+1][j]=3;
                    matrix[i+2][j]=3;
                    matrix[i][j+1]=3;
                    matrix[i+1][j+1]=3;
                    matrix[i+2][j+1]=3;
                    matrix[i][j+2]=3;
                    matrix[i+1][j+2]=3;
                    matrix[i+2][j+2]=3;
                    flag=1;
                }
            }
        }
    }
}
int main(int argc, const char * argv[])
{
    srand(time(NULL));
    int i, j;
    int N=MATRIX_HEIGHT;
    int M=MATRIX_WIDTH;
    int matrix[N][M];
    //SETUP MATRIX
    printf("\n Matrix Grid");
    for(i=0;i<N;i++)
    {
        printf("\n");
        for(j=0;j<M;j++)
        {
            matrix[i][j]=0;
            printf("%d ",matrix[i][j]);
        }
    }
    //SCAN FOR SPACE AND CHANGE
    largestImage(matrix);       //
    largeImage(matrix);         //
    Image(matrix);              //  included in the main only two test the functions
    largeImage(matrix);         //  it worked!
    Image(matrix);              //
    largeImage(matrix);         //
    largestImage(matrix);       //
    Image(matrix);              //
    //PRINT NEW MATRIX
    printf("\n Matrix Grid");
    for(i=0;i<N;i++)
    {
        printf("\n");
        for(j=0;j<M;j++)
        {
            printf("%d ",matrix[i][j]);
        }
    }
    
    
    return 0;
}


