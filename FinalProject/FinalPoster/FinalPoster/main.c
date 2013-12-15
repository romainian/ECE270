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
char fileName[] = "poster.svg";

float cellSize = imWidth/matWidth;


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


// SET STRUCTURE FUNCTIONS //
void setFill(struct Fill *myFill,int r, int g, int b, float op)
{
    myFill->r=r;
    myFill->g=g;
    myFill->b=b;
    myFill->opacity=op;
}
void setStroke(struct Stroke *myStroke, int red,int green,int blue,int width,float op)
{
    myStroke->r=red;
    myStroke->g=green;
    myStroke->b=blue;
    myStroke->width=width;
    myStroke->opacity=op;
}

void setCircle(struct Circle *myCircle,float cx,float cy, float r)
{

    myCircle->x=cx;
    myCircle->y=cy;
    myCircle->r=r;
}
void setLine(struct Line *myLine,float x1,float y1, float x2, float y2)
{
    myLine->x1=x1;
    myLine->y1=y1;
    myLine->x2=x2;
    myLine->y2=y2;
}
void setRect(struct Rect *myRect, int x, int y, int width, int height)
{
    myRect->x=x;
    myRect->y=y;
    myRect->width=width;
    myRect->height=height;
}

void setFillArray(int Dim, struct Fill myFill[], int red[], int green[], int blue[], float opacity[])
{
    int i;
    for(i=0;i<Dim;i++)
    {
        setFill(&myFill[i], red[i], green[i], blue[i], opacity[i]);
    }
}
void setStrokeArray(int Dim, struct Stroke myStroke[], int red[], int green[], int blue[], int width[], float opacity[])
{
    int i;
    for(i=0;i<Dim;i++)
    {
        setStroke(&myStroke[i], red[i], green[i], blue[i], width[i], opacity[i]);
    }
}
void setCircleArray(int Dim, struct Circle myCircle[],float cx[],float cy[], float r[])
{
    int i;
    for(i=0;i<Dim;i++)
    {
        setCircle(&myCircle[i], cx[i], cy[i], r[i]);
    }

}

void setStudent(struct Student *myStudent, int shape_in, int size_in)
{
    myStudent->shape=shape_in;
    myStudent->size=size_in;
}


// DRAWING FUNCTIONS //
void drawCircle(float cx, float cy, float r,
                int fill_r, int fill_g, int fill_b,
                float fill_opacity, int stroke_r, int stroke_g,
                int stroke_b, float stroke_opacity, int stroke_width)
{
    fprintf(fp,"\n    <circle cx = '%f' cy = '%f' r = '%f'", cx, cy, r);
    fprintf(fp," fill = 'rgb(%d, %d, %d)' fill-opacity = '%f'",
            fill_r, fill_g, fill_b, fill_opacity);
    fprintf(fp," stroke = 'rgb(%d, %d, %d)' stroke-opacity = '%f'",
            stroke_r, stroke_g, stroke_b, stroke_opacity);
    fprintf(fp," stroke-width = '%d' />", stroke_width);
}
void drawLine(float x1, float y1, float x2, float y2,
              int stroke_r, int stroke_g, int stroke_b,
              float stroke_opacity, int stroke_width)
{
    fprintf(fp,"\n    <line x1 = '%f' y1 = '%f' x2 = '%f' y2 = '%f'",
            x1, y1, x2, y2);
    fprintf(fp," stroke = 'rgb(%d, %d, %d)' stroke-opacity = '%f'",
            stroke_r, stroke_g, stroke_b, stroke_opacity);
    fprintf(fp," stroke-width = '%d' />", stroke_width);
}
void drawRectangle(float x, float y, float width, float height,
                   int fill_r, int fill_g, int fill_b, float fill_opacity,
                   int stroke_r, int stroke_g, int stroke_b, float stroke_opacity, int stroke_width)
{
    fprintf(fp,"\n    <rect x = '%f' y = '%f' width = '%f' height = '%f'", x, y, width, height);
    fprintf(fp," fill = 'rgb(%d, %d, %d)' fill-opacity = '%f'", fill_r, fill_g, fill_b, fill_opacity);
    fprintf(fp," stroke = 'rgb(%d, %d, %d)' stroke-opacity = '%f'", stroke_r, stroke_g, stroke_b, stroke_opacity);
    fprintf(fp," stroke-width = '%d' />", stroke_width);
}

// MATRIX AND POSITION //
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
            if (matrix[k][l]!=0||(matWidth+1-l)<sizeCheck||(matHeight+1-k)<sizeCheck)
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


// STUDENT FUNCTIONS //
void drawImage(int i, int j, struct Student myStudent, int x)
{
    float cx_in      = j*cellSize+myStudent.size*cellSize/2;
    float cy_in      = i*cellSize+myStudent.size*cellSize/2;
    float cr_in      = myStudent.size*cellSize/2;
    float rx_in      = j*cellSize;
    float ry_in      = i*cellSize;
    float rWidth_in  = myStudent.size*cellSize;
    float rHeight_in = myStudent.size*cellSize;

    switch(x)
    {
        case 0:
            {
                drawCircle(cx_in, cy_in, cr_in, 255, 0, 0, 1.0, 0, 0, 0, 1.0, 2); //Get_Data function and Draw_Data function
                break;
            }
        case 1:
            {
                drawCircle(cx_in, cy_in, cr_in, 0, 255, 0, 1.0, 0, 0, 0, 1.0, 2);
                break;
            }
        case 2:
            {
                drawCircle(cx_in, cy_in, cr_in, 0, 0, 255, 1.0, 0, 0, 0, 1.0, 2);
                break;
            }
        case 3:
            {
                drawRectangle(rx_in, ry_in, rWidth_in, rHeight_in, 255, 255, 0, 1.0, 0, 0, 0, 1.0, 2);
                break;
            }
    }
}

void main()
{
    int i, j, test, x;
    struct Student myStudent[classSize];
    struct Fill myFill[classSize];
    struct Stroke myStroke[classSize];
    int placeMatrix[matHeight][matWidth];

    x=0;
    writeSVGHeader(fileName, imWidth, imHeight);
    setupZeroMatrix(matHeight, matWidth, placeMatrix);  //SVG
    setStudent(&myStudent[0], 0, 2);
    setStudent(&myStudent[1], 0, 2);
    setStudent(&myStudent[2], 0, 2);
    setStudent(&myStudent[3], 0, 2);
    for(i=0;i<matHeight;i++)
    {
        for(j=0;j<matWidth;j++)
        {
            test = checkPosition(i,j,matHeight,matWidth,placeMatrix, myStudent[x].size);
            if(test==0)
            {
                drawImage(i, j, myStudent[x], x);
                updatePosition(i,j,matHeight, matWidth, placeMatrix, myStudent[x].size);
                x++;
                x=x%4;
            }
        }
    }
    printIntMatrix(matHeight, matWidth, placeMatrix);   //SVG
    writeSVGFooter();
}

