#include <stdio.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>
#define imWidth 1000
#define imHeight 1000
#define matWidth 10
#define matHeight 10
#define classSize 100

struct Student
{
    int shape;   //0 if circle. 1 if rectangle
    int size;
};
void setStudent(struct Student *myStudent, int shape_in, int size_in)
{
    myStudent->shape=shape_in;
    myStudent->size=size_in;
}
void printIntMatrix(int n, int m, int matrix[n][m])
{
    int i,j;
    for(i=0;i<n;i++)
    {
        for(j=0;j<m;j++)
        {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}
void setupZeroMatrix(int n, int m, int matrix[n][m])
{
    int i,j;
    for(i=0;i<n;i++)
    {
        for(j=0;j<m;j++)
        {
            matrix[i][j]=0;
        }
    }
}

int checkPosition(int i, int j, int n, int m, int matrix[n][m], int sizeCheck)
{
    int k, l;
    int flag = 0;
    for (k=i;k<i+sizeCheck;k++)
    {
        for (l=j;l<j+sizeCheck;l++)
        {
            if (matrix[k][l]!=0||(matWidth-l)<sizeCheck||(matHeight-k)<sizeCheck)
            {
                flag=1;
            }
        }
    }
    return flag;
}

void updatePosition(int i, int j, int n, int m, int matrix[n][m], int sizeCheck)
{
    int k, l;
    for (k=i;k<i+sizeCheck;k++)
    {
        for (l=j;l<j+sizeCheck;l++)
        {
            matrix[k][l]=1;
        }
    }
}

void main()
{
    int test, x;
    struct Student myStudent[classSize];
    x=0;
    int placeMatrix[matHeight][matWidth];
    setupZeroMatrix(matHeight, matWidth, placeMatrix);
    placeMatrix[2][3]=0;
    test =  checkPosition(1,2,matHeight,matWidth,placeMatrix, myStudent[x].size);
    if(test==0)
    {
        updatePosition(1,2,matHeight, matWidth, placeMatrix, myStudent[x].size);
    }
    printIntMatrix(matHeight, matWidth, placeMatrix);
}

