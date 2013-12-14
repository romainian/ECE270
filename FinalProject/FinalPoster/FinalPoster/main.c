#include <stdio.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>
#define imWidth 1000
#define imHeight 1000
#define matWidth 10
#define matHeight 10
#define classSize 100
FILE *fp;

// SVG HEADER AND FOOTER //
void writeSVGHeader(char fileName[], int width, int height)
{
    fp = fopen(fileName,"w");
    fprintf(fp,"<?xml version='1.0' standalone='no'?>");
    fprintf(fp,"\n<svg xmlns='http://www.w3.org/2000/svg' ");
    fprintf(fp,"xmlns:xlink='http://www.w3.org/1999/xlink' ");
    fprintf(fp,"version='1.1' width = '%d' height = '%d'>", width, height);
}
void writeSVGFooter()
{
    fprintf(fp,"\n</svg>");
    fclose(fp);
}
// STRUCTURES //


struct Fill
{
    int r;
    int g;
    int b;
    float opacity;
};
struct Stroke
{
    int r;
    int g;
    int b;
    int width;
    float opacity;
};
struct Circle
{
    float x;
    float y;
    float r;
};
struct Line
{
    float x1;
    float x2;
    float y1;
    float y2;
};
struct Rect
{
    float x;
    float y;
    float width;
    float height;
};
struct Student
{
    int shape;   //0 if circle. 1 if rectangle
    int size;
};
// MATRIX //
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
void drawImage(int i, int j, struct Student myStudent, int x)
{
    switch(x)
    {
        case 0:
        {
            /*int i;                          //Get_Data function and Draw_Data function
            for(i=0;i<dim;i++)
            {
                fill[i].r = rand()%256;
                fill[i].g = rand()%256;
                fill[i].b = rand()%256;
                fill[i].opacity = rand_float();
            }
            for(i=0;i<dim;i++)
            {
                stroke[i].r = rand()%256;
                stroke[i].g = rand()%256;
                stroke[i].b = rand()%256;
                stroke[i].width = 1 + rand()%3;
                stroke[i].opacity = rand_float();
            }
            int j,k;
            for(i=0;i<dim;i++)
            {
                for(j=0;j<10;j++)
                {
                    for(k=0;k<10;k++)
                    {
                        rect[i].x = (imHeight/10)*j;
                        rect[i].y = (imWidth/10)*k;
                        rect[i].height = (imHeight/10);
                        rect[i].width = (imWidth/10);
                        i++;
                    }
                }
            }
            int i;
            for (i=0; i<Dim; i++)
            {
                fprintf(fp,"\n    <rect x = '%f' y = '%f' width = '%f' height = '%f'", rect[i].x, rect[i].y, rect[i].width, rect[i].height);
                fprintf(fp," fill = 'rgb(%d, %d, %d)' fill-opacity = '%f'", fill[i].r, fill[i].g, fill[i].b, fill[i].opacity);
                fprintf(fp," stroke = 'rgb(%d, %d, %d)' stroke-opacity = '%f'", stroke[i].r, stroke[i].g, stroke[i].b, stroke[i].opacity);
                fprintf(fp," stroke-width = '%d' />", stroke[i].width);
            }     */    //Get_Data function and Draw_Data function
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
    setStudent(&myStudent[x], 0, 2);
    test =  checkPosition(1,2,matHeight,matWidth,placeMatrix, myStudent[x].size);
    if(test==0)
    {
        updatePosition(1,2,matHeight, matWidth, placeMatrix, myStudent[x].size);
        x++;
    }
    printIntMatrix(matHeight, matWidth, placeMatrix);
}

