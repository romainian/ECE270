//
//  main.c
//  FinalProc273
//
//  Created by Evan Pietraniec on 12/14/13.
//  Copyright (c) 2013 Evan Pietraniec. All rights reserved.
//


#include <stdio.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>
#define imWidth 1000
#define imHeight 1000
#define matWidth 10
#define matHeight 10
#define classSize 5

FILE *fp;
char fileName[] = "poster.svg";

float cellSize = imWidth/matWidth;

float rand_float()
{
    return (rand()/RAND_MAX);
}

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
void setStroke(struct Stroke *myStroke, int red, int green, int blue, int width, float op)
{
    myStroke->r=red;
    myStroke->g=green;
    myStroke->b=blue;
    myStroke->width=width;
    myStroke->opacity=op;
}

void setCircle(struct Circle *myCircle, float cx, float cy, float r)
{
    
    myCircle->x=cx;
    myCircle->y=cy;
    myCircle->r=r;
}
void setLine(struct Line *myLine, float x1, float y1, float x2, float y2)
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
                int fill_r, int fill_g, int fill_b, float fill_opacity,
                int stroke_r, int stroke_g, int stroke_b, float stroke_opacity, int stroke_width)
{
    fprintf(fp,"\n    <circle cx = '%f' cy = '%f' r = '%f'", cx, cy, r);
    fprintf(fp," fill = 'rgb(%d, %d, %d)' fill-opacity = '%f'",
            fill_r, fill_g, fill_b, fill_opacity);
    fprintf(fp," stroke = 'rgb(%d, %d, %d)' stroke-opacity = '%f'",
            stroke_r, stroke_g, stroke_b, stroke_opacity);
    fprintf(fp," stroke-width = '%d' />", stroke_width);
}
void drawLine(float x1, float y1, float x2, float y2,
              int stroke_r, int stroke_g, int stroke_b, float stroke_opacity, int stroke_width)
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


/// ----------STUDENT FUNCTIONS---------------- ///

// Student   0
//  Get Data
void romain_aaron_getData(struct Line *myLines, struct Circle *myCircles,
                          float cx_in, float cy_in, float r_in,
                          int steps, int rings)
{
    float v[2][1] = {0,r_in};
    float v2[2][1] = {v[0][0],v[1][0]};
    float theta = 2*M_PI/steps;
    float R[2][2] = {{cos(theta),-sin(theta)},{sin(theta),cos(theta)}};
    int i;
    for (i=0;i<steps;i++)
    {
        myLines[i].x1 = cx_in;
        myLines[i].y1 = cy_in;
        v2[0][0] = v[0][0];
        v2[1][0] = v[1][0];
        myLines[i].x2 = v[0][0]+cx_in;
        myLines[i].y2 = v[1][0]+cy_in;
        v[0][0] = R[0][0]*v2[0][0]+R[0][1]*v2[1][0];
        v[1][0] = R[1][0]*v2[0][0]+R[1][1]*v2[1][0];
    }
    for (i=0;i<rings;i++)
    {
        myCircles[i].x = cx_in;
        myCircles[i].y = cy_in;
        myCircles[i].r = r_in*powf(.8,i);
    }
}
//  Draw Image
void romain_aaron_drawImage(struct Line myLines[], struct Circle myCircles[],
                            struct Stroke myStroke, struct Fill myFill,
                            int steps, int rings)
{
    int i;
    for (i=0;i<steps;i++)
    {
        drawLine(myLines[i].x1, myLines[i].y1, myLines[i].x2,
                 myLines[i].y2, myStroke.r, myStroke.g,
                 myStroke.b, myStroke.opacity, myStroke.width);
    }
    for (i=0;i<rings;i++)
    {
        drawCircle(myCircles[i].x, myCircles[i].y, myCircles[i].r,
                   myFill.r, myFill.g, myFill.b, myFill.opacity,
                   myStroke.r, myStroke.g, myStroke.b, myStroke.opacity,
                   myStroke.width);
    }
}
//  Student Main
void student0(float cx_in, float cy_in, float cr_in, float rx_in, float ry_in, float rWidth_in, float rHeight_in)
{
    int steps = 50;
    int rings = 8;
    struct Line myLines[steps];
    struct Circle myCircles[rings];
    struct Fill myFill;
    struct Stroke myStroke;
    setStroke(&myStroke, 0, 0, 0, 2, 1.0);
    setFill(&myFill, 0, 0, 0, 0);
    romain_aaron_getData(&myLines[0], &myCircles[0], cx_in, cy_in, cr_in, steps, rings);
    romain_aaron_drawImage(myLines, myCircles, myStroke, myFill, steps, rings);
}

// Student   1
//  Get Data
void houghton_bradley_getData(float cx_in, float cy_in, float r_in, struct Circle *smiley, struct Fill *smileyFill, struct Stroke *smileyStroke)
{
    smiley[0].x=cx_in;
    smiley[1].x=cx_in-(r_in/2);
    smiley[2].x=cx_in+(r_in/2);
    smiley[3].x=cx_in;
    smiley[4].x=cx_in;
    smiley[0].y=cy_in;
    smiley[1].y=cy_in-(r_in/2);
    smiley[2].y=cy_in-(r_in/2);
    smiley[3].y=cy_in+(r_in/3);
    smiley[4].y=cy_in;
    smiley[0].r=r_in;
    smiley[1].r=r_in/6;
    smiley[2].r=r_in/6;
    smiley[3].r=r_in/2;
    smiley[4].r=r_in/2;
    
    smileyFill[0].r=255;
    smileyFill[1].r=0;
    smileyFill[2].r=0;
    smileyFill[3].r=255;
    smileyFill[4].r=255;
    smileyFill[0].g=255;
    smileyFill[1].g=0;
    smileyFill[2].g=0;
    smileyFill[3].g=255;
    smileyFill[4].g=255;
    smileyFill[0].b=0;
    smileyFill[1].b=0;
    smileyFill[2].b=0;
    smileyFill[3].b=255;
    smileyFill[4].b=0;
    smileyFill[0].opacity=1.0;
    smileyFill[1].opacity=1.0;
    smileyFill[2].opacity=1.0;
    smileyFill[3].opacity=1.0;
    smileyFill[4].opacity=1.0;
    
    smileyStroke[0].r=0;
    smileyStroke[1].r=0;
    smileyStroke[2].r=0;
    smileyStroke[3].r=0;
    smileyStroke[4].r=255;
    smileyStroke[0].g=0;
    smileyStroke[1].g=0;
    smileyStroke[2].g=0;
    smileyStroke[3].g=0;
    smileyStroke[4].g=255;
    smileyStroke[0].b=0;
    smileyStroke[1].b=0;
    smileyStroke[2].b=0;
    smileyStroke[3].b=0;
    smileyStroke[4].b=0;
    smileyStroke[0].width=5;
    smileyStroke[1].width=2;
    smileyStroke[2].width=2;
    smileyStroke[3].width=1;
    smileyStroke[4].width=1;
    smileyStroke[0].opacity=1.0;
    smileyStroke[1].opacity=1.0;
    smileyStroke[2].opacity=1.0;
    smileyStroke[3].opacity=1.0;
    smileyStroke[4].opacity=1.0;
}
//  Draw Image
void houghton_bradley_drawImage(struct Circle myCircle[], struct Fill myFill[], struct Stroke myStroke[])
{
    int i;
    for(i=0;i<5;i++)
    {
        drawCircle(myCircle[i].x, myCircle[i].y, myCircle[i].r, myFill[i].r, myFill[i].g, myFill[i].b, myFill[i].opacity, myStroke[i].r, myStroke[i].g, myStroke[i].b, myStroke[i].opacity, myStroke[i].width);
    }
}
//  Student Main
void student1(float cx_in, float cy_in, float cr_in, float rx_in, float ry_in, float rWidth_in, float rHeight_in)
{
    struct Circle smiley[5];
    struct Fill smileyFill[5];
    struct Stroke smileyStroke[5];
    
    
    houghton_bradley_getData(cx_in, cy_in, cr_in, &smiley, &smileyFill, &smileyStroke);
    houghton_bradley_drawImage(smiley, smileyFill, smileyStroke);
}

// Student   2
//  Get Data
void evan_pietraniec_getData(struct Fill fill[], struct Stroke stroke[], struct Rect rect[], float rx_in, float ry_in, float rWidth_in, float rHeight_in)
{
    int i;
    for(i=0;i<100;i++)
    {
        fill[i].r = rand()%256;
        fill[i].g = rand()%256;
        fill[i].b = rand()%256;
        fill[i].opacity = 1;
    }
    for(i=0;i<100;i++)
    {
        stroke[i].r = rand()%256;
        stroke[i].g = rand()%256;
        stroke[i].b = rand()%256;
        stroke[i].width = 1 + rand()%3;
        stroke[i].opacity = 1;
    }
    int j,k;
    for(i=0;i<100;i++)
    {
        for(j=0;j<10;j++)
        {
            for(k=0;k<10;k++)
            {
                rect[i].x = rx_in + ((rWidth_in/10)*j);
                rect[i].y = ry_in + ((rHeight_in/10)*k);
                rect[i].height = (rHeight_in/10);
                rect[i].width = (rWidth_in/10);
                i++;
            }
        }
    }
}
//  Draw Image
void evan_pietraniec_drawImage(struct Fill fill[], struct Stroke stroke[], struct Rect rect[])
{
    int i;
    for (i=0; i<100; i++)
    {
        fprintf(fp,"\n    <rect x = '%f' y = '%f' width = '%f' height = '%f'", rect[i].x, rect[i].y, rect[i].width, rect[i].height);
        fprintf(fp," fill = 'rgb(%d, %d, %d)' fill-opacity = '%f'", fill[i].r, fill[i].g, fill[i].b, fill[i].opacity);
        fprintf(fp," stroke = 'rgb(%d, %d, %d)' stroke-opacity = '%f'", stroke[i].r, stroke[i].g, stroke[i].b, stroke[i].opacity);
        fprintf(fp," stroke-width = '%d' />", stroke[i].width);
    }
}
//  Student Main
void student2(float cx_in, float cy_in, float cr_in, float rx_in, float ry_in, float rWidth_in, float rHeight_in)
{
    struct Fill evFill[100];
    struct Stroke evStroke[100];
    struct Rect evRect[100];
    
    evan_pietraniec_getData(evFill, evStroke, evRect, rx_in, ry_in, rWidth_in, rHeight_in);
    evan_pietraniec_drawImage(evFill, evStroke, evRect);
}

// Student   3
//  Get Data
void rachel_simms_getData(struct Circle mycircle[], struct Fill myfill[], int Dim1, int cx, int cy, int radius, int Dim2, int r, int b, int g)
{
    int i;
    int j;
    for (i=0;i<Dim1;i++)
    {
        myfill[i].r = r;
        myfill[i].g = g;
        myfill[i].b = b;
        myfill[i].opacity = 1;
    }
    for (j=0; j<Dim2; j++)
    {
        mycircle[j].x = cx;
        mycircle[j].y = cy;
        mycircle[j].r = radius;
    }
}
//  Draw Image
void rachel_simms_drawImage(struct Circle mycircle[], struct Fill myFill[], struct Stroke mystroke)
{
    int i;
    for(i=0; i <100; i++)
    {
        
        fprintf(fp,"\n    <circle cx = '%f' cy = '%f' r = '%f'", mycircle[1].x, mycircle[2].y, mycircle[3].r);
        fprintf(fp," fill = 'rgb(%d, %d, %d)' fill-opacity = '%f'", myFill[1].r, myFill[2].g, myFill[3].b, myFill[4].opacity);
        fprintf(fp," stroke = 'rgb(%d, %d, %d)' stroke-opacity = '%f'", mystroke.r, mystroke.g, mystroke.b, mystroke.opacity);
        fprintf(fp," stroke-width = '%d' />", mystroke.width);
        
        mycircle[3].r -= 10;
        myFill[2].g += 10;
        myFill[3].b +=20;
        
    }
    
}
//  Student Main
void student3(float cx_in, float cy_in, float cr_in, float rx_in, float ry_in, float rWidth_in, float rHeight_in)
{
    float radius, cx, cy;
    int g, b, r;
    
    struct Circle mycircle[4];
    struct Fill myFill[4];
    struct Stroke mystroke;
    
    radius = cr_in; //radius
    cx = cx_in; //x-coordinate
    cy = cy_in; //y-coordinate
    g = 25; //green fill
    b = 0; //blue fill
    r = 255; //red fill
    
    rachel_simms_getData(mycircle, myFill, 4, cx, cy, radius, 4, r, b, g);
    rachel_simms_drawImage(mycircle, myFill, mystroke);
}

// Student   4
//  Get Data

void chadGetData(float cx_in, float cy_in, float r_in, struct Circle *myCircle, struct Fill *myFill, struct Stroke myStroke)
{
    int i;
    
    for(i = 0; i < 10; i++)
    {
        myCircle[i].r = r_in;
        myCircle[i].x = cx_in;
        myCircle[i].y = cy_in;
        myFill[i].r = 0;
        myFill[i].g = rand() % 256;
        myFill[i].b = 0;
        myFill[i].opacity = 1.0;
        myStroke.r = 0;
        myStroke.g = 0;
        myStroke.b = 0;
        myStroke.opacity = 1.0;
        myStroke.width = 2.0;
        
        
        r_in -= 5;
        cy_in -= 5;
        myFill[i + 1].r = myFill[i].r + rand() % 31;
        myFill[i + 1].b = myFill[i].r + rand() % 31;
        
    }
}
//  Draw Image

void drawChadCircle(struct Circle myCircle[], struct Fill myFill[], struct Stroke myStroke)
{
    int i;
    
    for(i = 0; i < 10; i++)
    {
        fprintf(fp,"\n    <circle cx = '%f' cy = '%f' r = '%f'", myCircle[i].x, myCircle[i].y, myCircle[i].r);
        fprintf(fp," fill = 'rgb(%d, %d, %d)' fill-opacity = '%f'",
                myFill[i].r, myFill[i].g, myFill[i].b, myFill[i].opacity);
        fprintf(fp," stroke = 'rgb(%d, %d, %d)' stroke-opacity = '%f'",
                myStroke.r, myStroke.g, myStroke.b, myStroke.opacity);
        fprintf(fp," stroke-width = '%d' />", myStroke.width);
    }
}

//  Student Main
void student4(float cx_in, float cy_in, float cr_in, float rx_in, float ry_in, float rWidth_in, float rHeight_in)
{
    struct Circle myCircle[10];
    struct Fill myFill[10];
    struct Stroke myStroke;
    
    chadGetData(cx_in, cy_in, cr_in, myCircle, myFill, myStroke);
    drawChadCircle(myCircle, myFill, myStroke);
    
}

// Student   5
//  Get Data
void student5_getData()
{
    
}
//  Draw Image
void student5_drawImage()
{
    
}
//  Student Main
void student5(float cx_in, float cy_in, float cr_in, float rx_in, float ry_in, float rWidth_in, float rHeight_in)
{
    
}

// Student   6
//  Get Data
void student6_getData()
{
    
}
//  Draw Image
void student6_drawImage()
{
    
}
//  Student Main
void student6(float cx_in, float cy_in, float cr_in, float rx_in, float ry_in, float rWidth_in, float rHeight_in)
{
    
}

// Student   7
//  Get Data
void student7_getData()
{
    
}
//  Draw Image
void student7_drawImage()
{
    
}
//  Student Main
void student7(float cx_in, float cy_in, float cr_in, float rx_in, float ry_in, float rWidth_in, float rHeight_in)
{
    
}

// Student   8
//  Get Data
void student8_getData()
{
    
}
//  Draw Image
void student8_drawImage()
{
    
}
//  Student Main
void student8(float cx_in, float cy_in, float cr_in, float rx_in, float ry_in, float rWidth_in, float rHeight_in)
{
    
}

// Student   9
//  Get Data
void student9_getData()
{
    
}
//  Draw Image
void student9_drawImage()
{
    
}
//  Student Main
void student9(float cx_in, float cy_in, float cr_in, float rx_in, float ry_in, float rWidth_in, float rHeight_in)
{
    
}

// Student  10
//  Get Data
void student10_getData()
{
    
}
//  Draw Image
void student10_drawImage()
{
    
}
//  Student Main
void student10(float cx_in, float cy_in, float cr_in, float rx_in, float ry_in, float rWidth_in, float rHeight_in)
{
    
}

// Student  11
//  Get Data
void student11_getData()
{
    
}
//  Draw Image
void student11_drawImage()
{
    
}
//  Student Main
void student11(float cx_in, float cy_in, float cr_in, float rx_in, float ry_in, float rWidth_in, float rHeight_in)
{
    
}

// Student  12
//  Get Data
void student12_getData()
{
    
}
//  Draw Image
void student12_drawImage()
{
    
}
//  Student Main
void student12(float cx_in, float cy_in, float cr_in, float rx_in, float ry_in, float rWidth_in, float rHeight_in)
{
    
}

// Student  13
//  Get Data
void student13_getData()
{
    
}
//  Draw Image
void student13_drawImage()
{
    
}
//  Student Main
void student13(float cx_in, float cy_in, float cr_in, float rx_in, float ry_in, float rWidth_in, float rHeight_in)
{
    
}

// Student  14
//  Get Data
void student14_getData()
{
    
}
//  Draw Image
void student14_drawImage()
{
    
}
//  Student Main
void student14(float cx_in, float cy_in, float cr_in, float rx_in, float ry_in, float rWidth_in, float rHeight_in)
{
    
}

// Student  15
//  Get Data
void student15_getData()
{
    
}
//  Draw Image
void student15_drawImage()
{
    
}
//  Student Main
void student15(float cx_in, float cy_in, float cr_in, float rx_in, float ry_in, float rWidth_in, float rHeight_in)
{
    
}

// Student  16
//  Get Data
void student16_getData()
{
    
}
//  Draw Image
void student16_drawImage()
{
    
}
//  Student Main
void student16(float cx_in, float cy_in, float cr_in, float rx_in, float ry_in, float rWidth_in, float rHeight_in)
{
    
}

// Student  17
//  Get Data
void student17_getData()
{
    
}
//  Draw Image
void student17_drawImage()
{
    
}
//  Student Main
void student17(float cx_in, float cy_in, float cr_in, float rx_in, float ry_in, float rWidth_in, float rHeight_in)
{
    
}

// Student  18
//  Get Data
void student18_getData()
{
    
}
//  Draw Image
void student18_drawImage()
{
    
}
//  Student Main
void student18(float cx_in, float cy_in, float cr_in, float rx_in, float ry_in, float rWidth_in, float rHeight_in)
{
    
}

// Student  19
//  Get Data
void student19_getData()
{
    
}
//  Draw Image
void student19_drawImage()
{
    
}
//  Student Main
void student19(float cx_in, float cy_in, float cr_in, float rx_in, float ry_in, float rWidth_in, float rHeight_in)
{
    
}

// Student  20
//  Get Data
void student20_getData()
{
    
}
//  Draw Image
void student20_drawImage()
{
    
}
//  Student Main
void student20(float cx_in, float cy_in, float cr_in, float rx_in, float ry_in, float rWidth_in, float rHeight_in)
{
    
}

// Student  21
//  Get Data
void student21_getData()
{
    
}
//  Draw Image
void student21_drawImage()
{
    
}
//  Student Main
void student21(float cx_in, float cy_in, float cr_in, float rx_in, float ry_in, float rWidth_in, float rHeight_in)
{
    
}

// Student  22
//  Get Data
void student22_getData()
{
    
}
//  Draw Image
void student22_drawImage()
{
    
}
//  Student Main
void student22(float cx_in, float cy_in, float cr_in, float rx_in, float ry_in, float rWidth_in, float rHeight_in)
{
    
}

// Student  23
//  Get Data
void student23_getData()
{
    
}
//  Draw Image
void student23_drawImage()
{
    
}
//  Student Main
void student23(float cx_in, float cy_in, float cr_in, float rx_in, float ry_in, float rWidth_in, float rHeight_in)
{
    
}

// Student  24
//  Get Data
void student24_getData()
{
    
}
//  Draw Image
void student24_drawImage()
{
    
}
//  Student Main
void student24(float cx_in, float cy_in, float cr_in, float rx_in, float ry_in, float rWidth_in, float rHeight_in)
{
    
}

// Student  25
//  Get Data
void student25_getData()
{
    
}
//  Draw Image
void student25_drawImage()
{
    
}
//  Student Main
void student25(float cx_in, float cy_in, float cr_in, float rx_in, float ry_in, float rWidth_in, float rHeight_in)
{
    
}

// Student  26
//  Get Data
void student26_getData()
{
    
}
//  Draw Image
void student26_drawImage()
{
    
}
//  Student Main
void student26(float cx_in, float cy_in, float cr_in, float rx_in, float ry_in, float rWidth_in, float rHeight_in)
{
    
}

// Student  27
//  Get Data
void student27_getData()
{
    
}
//  Draw Image
void student27_drawImage()
{
    
}
//  Student Main
void student27(float cx_in, float cy_in, float cr_in, float rx_in, float ry_in, float rWidth_in, float rHeight_in)
{
    
}

// Student  28
//  Get Data
void student28_getData()
{
    
}
//  Draw Image
void student28_drawImage()
{
    
}
//  Student Main
void student28(float cx_in, float cy_in, float cr_in, float rx_in, float ry_in, float rWidth_in, float rHeight_in)
{
    
}

// Student  29
//  Get Data
void student29_getData()
{
    
}
//  Draw Image
void student29_drawImage()
{
    
}
//  Student Main
void student29(float cx_in, float cy_in, float cr_in, float rx_in, float ry_in, float rWidth_in, float rHeight_in)
{
    
}

// Student  30
//  Get Data
void student30_getData()
{
    
}
//  Draw Image
void student30_drawImage()
{
    
}
//  Student Main
void student30(float cx_in, float cy_in, float cr_in, float rx_in, float ry_in, float rWidth_in, float rHeight_in)
{
    
}

// Student  31
//  Get Data
void student31_getData()
{
    
}
//  Draw Image
void student31_drawImage()
{
    
}
//  Student Main
void student31(float cx_in, float cy_in, float cr_in, float rx_in, float ry_in, float rWidth_in, float rHeight_in)
{
    
}

// Student  32
//  Get Data
void student32_getData()
{
    
}
//  Draw Image
void student32_drawImage()
{
    
}
//  Student Main
void student32(float cx_in, float cy_in, float cr_in, float rx_in, float ry_in, float rWidth_in, float rHeight_in)
{
    
}

// Student  33
//  Get Data
void student33_getData()
{
    
}
//  Draw Image
void student33_drawImage()
{
    
}
//  Student Main
void student33(float cx_in, float cy_in, float cr_in, float rx_in, float ry_in, float rWidth_in, float rHeight_in)
{
    
}

// Student  34
//  Get Data
void student34_getData()
{
    
}
//  Draw Image
void student34_drawImage()
{
    
}
//  Student Main
void student34(float cx_in, float cy_in, float cr_in, float rx_in, float ry_in, float rWidth_in, float rHeight_in)
{
    
}

// Student  35
//  Get Data
void student35_getData()
{
    
}
//  Draw Image
void student35_drawImage()
{
    
}
//  Student Main
void student35(float cx_in, float cy_in, float cr_in, float rx_in, float ry_in, float rWidth_in, float rHeight_in)
{
    
}

// Student  36
//  Get Data
void student36_getData()
{
    
}
//  Draw Image
void student36_drawImage()
{
    
}
//  Student Main
void student36(float cx_in, float cy_in, float cr_in, float rx_in, float ry_in, float rWidth_in, float rHeight_in)
{
    
}

// Student  37
//  Get Data
void student37_getData()
{
    
}
//  Draw Image
void student37_drawImage()
{
    
}
//  Student Main
void student37(float cx_in, float cy_in, float cr_in, float rx_in, float ry_in, float rWidth_in, float rHeight_in)
{
    
}

// Student  38
//  Get Data
void student38_getData()
{
    
}
//  Draw Image
void student38_drawImage()
{
    
}
//  Student Main
void student38(float cx_in, float cy_in, float cr_in, float rx_in, float ry_in, float rWidth_in, float rHeight_in)
{
    
}

// Student  39
//  Get Data
void student39_getData()
{
    
}
//  Draw Image
void student39_drawImage()
{
    
}
//  Student Main
void student39(float cx_in, float cy_in, float cr_in, float rx_in, float ry_in, float rWidth_in, float rHeight_in)
{
    
}

// Student  40
//  Get Data
void student40_getData()
{
    
}
//  Draw Image
void student40_drawImage()
{
    
}
//  Student Main
void student40(float cx_in, float cy_in, float cr_in, float rx_in, float ry_in, float rWidth_in, float rHeight_in)
{
    
}

// Student  41
//  Get Data
void student41_getData()
{
    
}
//  Draw Image
void student41_drawImage()
{
    
}
//  Student Main
void student41(float cx_in, float cy_in, float cr_in, float rx_in, float ry_in, float rWidth_in, float rHeight_in)
{
    
}

// Student  42
//  Get Data
void student42_getData()
{
    
}
//  Draw Image
void student42_drawImage()
{
    
}
//  Student Main
void student42(float cx_in, float cy_in, float cr_in, float rx_in, float ry_in, float rWidth_in, float rHeight_in)
{
    
}

// Student  43
//  Get Data
void student43_getData()
{
    
}
//  Draw Image
void student43_drawImage()
{
    
}
//  Student Main
void student43(float cx_in, float cy_in, float cr_in, float rx_in, float ry_in, float rWidth_in, float rHeight_in)
{
    
}

// Student  44
//  Get Data
void student44_getData()
{
    
}
//  Draw Image
void student44_drawImage()
{
    
}
//  Student Main
void student44(float cx_in, float cy_in, float cr_in, float rx_in, float ry_in, float rWidth_in, float rHeight_in)
{
    
}

// Student  45
//  Get Data
void student45_getData()
{
    
}
//  Draw Image
void student45_drawImage()
{
    
}
//  Student Main
void student45(float cx_in, float cy_in, float cr_in, float rx_in, float ry_in, float rWidth_in, float rHeight_in)
{
    
}

// Student  46
//  Get Data
void student46_getData()
{
    
}
//  Draw Image
void student46_drawImage()
{
    
}
//  Student Main
void student46(float cx_in, float cy_in, float cr_in, float rx_in, float ry_in, float rWidth_in, float rHeight_in)
{
    
}

// Student  47
//  Get Data
void student47_getData()
{
    
}
//  Draw Image
void student47_drawImage()
{
    
}
//  Student Main
void student47(float cx_in, float cy_in, float cr_in, float rx_in, float ry_in, float rWidth_in, float rHeight_in)
{
    
}

// Student  48
//  Get Data
void student48_getData()
{
    
}
//  Draw Image
void student48_drawImage()
{
    
}
//  Student Main
void student48(float cx_in, float cy_in, float cr_in, float rx_in, float ry_in, float rWidth_in, float rHeight_in)
{
    
}

// Student  49
//  Get Data
void student49_getData()
{
    
}
//  Draw Image
void student49_drawImage()
{
    
}
//  Student Main
void student49(float cx_in, float cy_in, float cr_in, float rx_in, float ry_in, float rWidth_in, float rHeight_in)
{
    
}

// Student  50
//  Get Data
void student50_getData()
{
    
}
//  Draw Image
void student50_drawImage()
{
    
}
//  Student Main
void student50(float cx_in, float cy_in, float cr_in, float rx_in, float ry_in, float rWidth_in, float rHeight_in)
{
    
}

// Student  51
//  Get Data
void student51_getData()
{
    
}
//  Draw Image
void student51_drawImage()
{
    
}
//  Student Main
void student51(float cx_in, float cy_in, float cr_in, float rx_in, float ry_in, float rWidth_in, float rHeight_in)
{
    
}

// Student  52
//  Get Data
void student52_getData()
{
    
}
//  Draw Image
void student52_drawImage()
{
    
}
//  Student Main
void student52(float cx_in, float cy_in, float cr_in, float rx_in, float ry_in, float rWidth_in, float rHeight_in)
{
    
}

// Student  53
//  Get Data
void student53_getData()
{
    
}
//  Draw Image
void student53_drawImage()
{
    
}
//  Student Main
void student53(float cx_in, float cy_in, float cr_in, float rx_in, float ry_in, float rWidth_in, float rHeight_in)
{
    
}

// Student  54
//  Get Data
void student54_getData()
{
    
}
//  Draw Image
void student54_drawImage()
{
    
}
//  Student Main
void student54(float cx_in, float cy_in, float cr_in, float rx_in, float ry_in, float rWidth_in, float rHeight_in)
{
    
}

// Student  55
//  Get Data
void student55_getData()
{
    
}
//  Draw Image
void student55_drawImage()
{
    
}
//  Student Main
void student55(float cx_in, float cy_in, float cr_in, float rx_in, float ry_in, float rWidth_in, float rHeight_in)
{
    
}

// Student  56
//  Get Data
void student56_getData()
{
    
}
//  Draw Image
void student56_drawImage()
{
    
}
//  Student Main
void student56(float cx_in, float cy_in, float cr_in, float rx_in, float ry_in, float rWidth_in, float rHeight_in)
{
    
}

// Student  57
//  Get Data
void student57_getData()
{
    
}
//  Draw Image
void student57_drawImage()
{
    
}
//  Student Main
void student57(float cx_in, float cy_in, float cr_in, float rx_in, float ry_in, float rWidth_in, float rHeight_in)
{
    
}

// Student  58
//  Get Data
void student58_getData()
{
    
}
//  Draw Image
void student58_drawImage()
{
    
}
//  Student Main
void student58(float cx_in, float cy_in, float cr_in, float rx_in, float ry_in, float rWidth_in, float rHeight_in)
{
    
}

// Student  59
//  Get Data
void student59_getData()
{
    
}
//  Draw Image
void student59_drawImage()
{
    
}
//  Student Main
void student59(float cx_in, float cy_in, float cr_in, float rx_in, float ry_in, float rWidth_in, float rHeight_in)
{
    
}

// Student  60
//  Get Data
void student60_getData()
{
    
}
//  Draw Image
void student60_drawImage()
{
    
}
//  Student Main
void student60(float cx_in, float cy_in, float cr_in, float rx_in, float ry_in, float rWidth_in, float rHeight_in)
{
    
}

// Student  61
//  Get Data
void student61_getData()
{
    
}
//  Draw Image
void student61_drawImage()
{
    
}
//  Student Main
void student61(float cx_in, float cy_in, float cr_in, float rx_in, float ry_in, float rWidth_in, float rHeight_in)
{
    
}

// Student  62
//  Get Data
void student62_getData()
{
    
}
//  Draw Image
void student62_drawImage()
{
    
}
//  Student Main
void student62(float cx_in, float cy_in, float cr_in, float rx_in, float ry_in, float rWidth_in, float rHeight_in)
{
    
}

// Student  63
//  Get Data
void student63_getData()
{
    
}
//  Draw Image
void student63_drawImage()
{
    
}
//  Student Main
void student63(float cx_in, float cy_in, float cr_in, float rx_in, float ry_in, float rWidth_in, float rHeight_in)
{
    
}

// Student  64
//  Get Data
void student64_getData()
{
    
}
//  Draw Image
void student64_drawImage()
{
    
}
//  Student Main
void student64(float cx_in, float cy_in, float cr_in, float rx_in, float ry_in, float rWidth_in, float rHeight_in)
{
    
}

// Student  65
//  Get Data
void student65_getData()
{
    
}
//  Draw Image
void student65_drawImage()
{
    
}
//  Student Main
void student65(float cx_in, float cy_in, float cr_in, float rx_in, float ry_in, float rWidth_in, float rHeight_in)
{
    
}

// Student  66
//  Get Data
void student66_getData()
{
    
}
//  Draw Image
void student66_drawImage()
{
    
}
//  Student Main
void student66(float cx_in, float cy_in, float cr_in, float rx_in, float ry_in, float rWidth_in, float rHeight_in)
{
    
}

// Student  67
//  Get Data
void student67_getData()
{
    
}
//  Draw Image
void student67_drawImage()
{
    
}
//  Student Main
void student67(float cx_in, float cy_in, float cr_in, float rx_in, float ry_in, float rWidth_in, float rHeight_in)
{
    
}

// Student  68
//  Get Data
void student68_getData()
{
    
}
//  Draw Image
void student68_drawImage()
{
    
}
//  Student Main
void student68(float cx_in, float cy_in, float cr_in, float rx_in, float ry_in, float rWidth_in, float rHeight_in)
{
    
}

// Student  69
//  Get Data
void student69_getData()
{
    
}
//  Draw Image
void student69_drawImage()
{
    
}
//  Student Main
void student69(float cx_in, float cy_in, float cr_in, float rx_in, float ry_in, float rWidth_in, float rHeight_in)
{
    
}

// Student  70
//  Get Data
void student70_getData()
{
    
}
//  Draw Image
void student70_drawImage()
{
    
}
//  Student Main
void student70(float cx_in, float cy_in, float cr_in, float rx_in, float ry_in, float rWidth_in, float rHeight_in)
{
    
}

// Student  71
//  Get Data
void student71_getData()
{
    
}
//  Draw Image
void student71_drawImage()
{
    
}
//  Student Main
void student71(float cx_in, float cy_in, float cr_in, float rx_in, float ry_in, float rWidth_in, float rHeight_in)
{
    
}

// Student  72
//  Get Data
void student72_getData()
{
    
}
//  Draw Image
void student72_drawImage()
{
    
}
//  Student Main
void student72(float cx_in, float cy_in, float cr_in, float rx_in, float ry_in, float rWidth_in, float rHeight_in)
{
    
}

// Student  73
//  Get Data
void student73_getData()
{
    
}
//  Draw Image
void student73_drawImage()
{
    
}
//  Student Main
void student73(float cx_in, float cy_in, float cr_in, float rx_in, float ry_in, float rWidth_in, float rHeight_in)
{
    
}

// Student  74
//  Get Data
void student74_getData()
{
    
}
//  Draw Image
void student74_drawImage()
{
    
}
//  Student Main
void student74(float cx_in, float cy_in, float cr_in, float rx_in, float ry_in, float rWidth_in, float rHeight_in)
{
    
}

// Student  75
//  Get Data
void student75_getData()
{
    
}
//  Draw Image
void student75_drawImage()
{
    
}
//  Student Main
void student75(float cx_in, float cy_in, float cr_in, float rx_in, float ry_in, float rWidth_in, float rHeight_in)
{
    
}

// Student  76
//  Get Data
void student76_getData()
{
    
}
//  Draw Image
void student76_drawImage()
{
    
}
//  Student Main
void student76(float cx_in, float cy_in, float cr_in, float rx_in, float ry_in, float rWidth_in, float rHeight_in)
{
    
}

// Student  77
//  Get Data
void student77_getData()
{
    
}
//  Draw Image
void student77_drawImage()
{
    
}
//  Student Main
void student77(float cx_in, float cy_in, float cr_in, float rx_in, float ry_in, float rWidth_in, float rHeight_in)
{
    
}

// Student  78
//  Get Data
void student78_getData()
{
    
}
//  Draw Image
void student78_drawImage()
{
    
}
//  Student Main
void student78(float cx_in, float cy_in, float cr_in, float rx_in, float ry_in, float rWidth_in, float rHeight_in)
{
    
}

// Student  79
//  Get Data
void student79_getData()
{
    
}
//  Draw Image
void student79_drawImage()
{
    
}
//  Student Main
void student79(float cx_in, float cy_in, float cr_in, float rx_in, float ry_in, float rWidth_in, float rHeight_in)
{
    
}

// Student  80
//  Get Data
void student80_getData()
{
    
}
//  Draw Image
void student80_drawImage()
{
    
}
//  Student Main
void student80(float cx_in, float cy_in, float cr_in, float rx_in, float ry_in, float rWidth_in, float rHeight_in)
{
    
}

// Student  81
//  Get Data
void student81_getData()
{
    
}
//  Draw Image
void student81_drawImage()
{
    
}
//  Student Main
void student81(float cx_in, float cy_in, float cr_in, float rx_in, float ry_in, float rWidth_in, float rHeight_in)
{
    
}

// Student  82
//  Get Data
void student82_getData()
{
    
}
//  Draw Image
void student82_drawImage()
{
    
}
//  Student Main
void student82(float cx_in, float cy_in, float cr_in, float rx_in, float ry_in, float rWidth_in, float rHeight_in)
{
    
}

// Student  83
//  Get Data
void student83_getData()
{
    
}
//  Draw Image
void student83_drawImage()
{
    
}
//  Student Main
void student83(float cx_in, float cy_in, float cr_in, float rx_in, float ry_in, float rWidth_in, float rHeight_in)
{
    
}

// Student  84
//  Get Data
void student84_getData()
{
    
}
//  Draw Image
void student84_drawImage()
{
    
}
//  Student Main
void student84(float cx_in, float cy_in, float cr_in, float rx_in, float ry_in, float rWidth_in, float rHeight_in)
{
    
}

// Student  85
//  Get Data
void student85_getData()
{
    
}
//  Draw Image
void student85_drawImage()
{
    
}
//  Student Main
void student85(float cx_in, float cy_in, float cr_in, float rx_in, float ry_in, float rWidth_in, float rHeight_in)
{
    
}

// Student  86
//  Get Data
void student86_getData()
{
    
}
//  Draw Image
void student86_drawImage()
{
    
}
//  Student Main
void student86(float cx_in, float cy_in, float cr_in, float rx_in, float ry_in, float rWidth_in, float rHeight_in)
{
    
}

// Student  87
//  Get Data
void student87_getData()
{
    
}
//  Draw Image
void student87_drawImage()
{
    
}
//  Student Main
void student87(float cx_in, float cy_in, float cr_in, float rx_in, float ry_in, float rWidth_in, float rHeight_in)
{
    
}

// Student  88
//  Get Data
void student88_getData()
{
    
}
//  Draw Image
void student88_drawImage()
{
    
}
//  Student Main
void student88(float cx_in, float cy_in, float cr_in, float rx_in, float ry_in, float rWidth_in, float rHeight_in)
{
    
}

// Student  89
//  Get Data
void student89_getData()
{
    
}
//  Draw Image
void student89_drawImage()
{
    
}
//  Student Main
void student89(float cx_in, float cy_in, float cr_in, float rx_in, float ry_in, float rWidth_in, float rHeight_in)
{
    
}

// Student  90
//  Get Data
void student90_getData()
{
    
}
//  Draw Image
void student90_drawImage()
{
    
}
//  Student Main
void student90(float cx_in, float cy_in, float cr_in, float rx_in, float ry_in, float rWidth_in, float rHeight_in)
{
    
}

// Student  91
//  Get Data
void student91_getData()
{
    
}
//  Draw Image
void student91_drawImage()
{
    
}
//  Student Main
void student91(float cx_in, float cy_in, float cr_in, float rx_in, float ry_in, float rWidth_in, float rHeight_in)
{
    
}

// Student  92
//  Get Data
void student92_getData()
{
    
}
//  Draw Image
void student92_drawImage()
{
    
}
//  Student Main
void student92(float cx_in, float cy_in, float cr_in, float rx_in, float ry_in, float rWidth_in, float rHeight_in)
{
    
}

// Student  93
//  Get Data
void student93_getData()
{
    
}
//  Draw Image
void student93_drawImage()
{
    
}
//  Student Main
void student93(float cx_in, float cy_in, float cr_in, float rx_in, float ry_in, float rWidth_in, float rHeight_in)
{
    
}

// Student  94
//  Get Data
void student94_getData()
{
    
}
//  Draw Image
void student94_drawImage()
{
    
}
//  Student Main
void student94(float cx_in, float cy_in, float cr_in, float rx_in, float ry_in, float rWidth_in, float rHeight_in)
{
    
}

// Student  95
//  Get Data
void student95_getData()
{
    
}
//  Draw Image
void student95_drawImage()
{
    
}
//  Student Main
void student95(float cx_in, float cy_in, float cr_in, float rx_in, float ry_in, float rWidth_in, float rHeight_in)
{
    
}

// Student  96
//  Get Data
void student96_getData()
{
    
}
//  Draw Image
void student96_drawImage()
{
    
}
//  Student Main
void student96(float cx_in, float cy_in, float cr_in, float rx_in, float ry_in, float rWidth_in, float rHeight_in)
{
    
}

// Student  97
//  Get Data
void student97_getData()
{
    
}
//  Draw Image
void student97_drawImage()
{
    
}
//  Student Main
void student97(float cx_in, float cy_in, float cr_in, float rx_in, float ry_in, float rWidth_in, float rHeight_in)
{
    
}

// Student  98
//  Get Data
void student98_getData()
{
    
}
//  Draw Image
void student98_drawImage()
{
    
}
//  Student Main
void student98(float cx_in, float cy_in, float cr_in, float rx_in, float ry_in, float rWidth_in, float rHeight_in)
{
    
}

// Student  99
//  Get Data
void student99_getData()
{
    
}
//  Draw Image
void student99_drawImage()
{
    
}
//  Student Main
void student99(float cx_in, float cy_in, float cr_in, float rx_in, float ry_in, float rWidth_in, float rHeight_in)
{
    
}

// MAIN FUNCTIONS //
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
    
        case   0:
        {
            student0(cx_in, cy_in, cr_in, rx_in, ry_in, rWidth_in, rHeight_in);
            break;
        }
        case   1:
        {
            student1(cx_in, cy_in, cr_in, rx_in, ry_in, rWidth_in, rHeight_in);
            break;
        }
        case   2:
        {
            student2(cx_in, cy_in, cr_in, rx_in, ry_in, rWidth_in, rHeight_in);
            break;
        }
        case   3:
        {
            student3(cx_in, cy_in, cr_in, rx_in, ry_in, rWidth_in, rHeight_in);
            break;
        }
        case   4:
        {
            student4(cx_in, cy_in, cr_in, rx_in, ry_in, rWidth_in, rHeight_in);
            break;
        }
        case   5:
        {
            student5(cx_in, cy_in, cr_in, rx_in, ry_in, rWidth_in, rHeight_in);
            break;
        }
        case   6:
        {
            student6(cx_in, cy_in, cr_in, rx_in, ry_in, rWidth_in, rHeight_in);
            break;
        }
        case   7:
        {
            student7(cx_in, cy_in, cr_in, rx_in, ry_in, rWidth_in, rHeight_in);
            break;
        }
        case   8:
        {
            student8(cx_in, cy_in, cr_in, rx_in, ry_in, rWidth_in, rHeight_in);
            break;
        }
        case   9:
        {
            student9(cx_in, cy_in, cr_in, rx_in, ry_in, rWidth_in, rHeight_in);
            break;
        }
        case  10:
        {
            student10(cx_in, cy_in, cr_in, rx_in, ry_in, rWidth_in, rHeight_in);
            break;
        }
        case  11:
        {
            student11(cx_in, cy_in, cr_in, rx_in, ry_in, rWidth_in, rHeight_in);
            break;
        }
        case  12:
        {
            student12(cx_in, cy_in, cr_in, rx_in, ry_in, rWidth_in, rHeight_in);
            break;
        }
        case  13:
        {
            student13(cx_in, cy_in, cr_in, rx_in, ry_in, rWidth_in, rHeight_in);
            break;
        }
        case  14:
        {
            student14(cx_in, cy_in, cr_in, rx_in, ry_in, rWidth_in, rHeight_in);
            break;
        }
        case  15:
        {
            student15(cx_in, cy_in, cr_in, rx_in, ry_in, rWidth_in, rHeight_in);
            break;
        }
        case  16:
        {
            student16(cx_in, cy_in, cr_in, rx_in, ry_in, rWidth_in, rHeight_in);
            break;
        }
        case  17:
        {
            student17(cx_in, cy_in, cr_in, rx_in, ry_in, rWidth_in, rHeight_in);
            break;
        }
        case  18:
        {
            student18(cx_in, cy_in, cr_in, rx_in, ry_in, rWidth_in, rHeight_in);
            break;
        }
        case  19:
        {
            student19(cx_in, cy_in, cr_in, rx_in, ry_in, rWidth_in, rHeight_in);
            break;
        }
        case  20:
        {
            student20(cx_in, cy_in, cr_in, rx_in, ry_in, rWidth_in, rHeight_in);
            break;
        }
        case  21:
        {
            student21(cx_in, cy_in, cr_in, rx_in, ry_in, rWidth_in, rHeight_in);
            break;
        }
        case  22:
        {
            student22(cx_in, cy_in, cr_in, rx_in, ry_in, rWidth_in, rHeight_in);
            break;
        }
        case  23:
        {
            student23(cx_in, cy_in, cr_in, rx_in, ry_in, rWidth_in, rHeight_in);
            break;
        }
        case  24:
        {
            student24(cx_in, cy_in, cr_in, rx_in, ry_in, rWidth_in, rHeight_in);
            break;
        }
        case  25:
        {
            student25(cx_in, cy_in, cr_in, rx_in, ry_in, rWidth_in, rHeight_in);
            break;
        }
        case  26:
        {
            student26(cx_in, cy_in, cr_in, rx_in, ry_in, rWidth_in, rHeight_in);
            break;
        }
        case  27:
        {
            student27(cx_in, cy_in, cr_in, rx_in, ry_in, rWidth_in, rHeight_in);
            break;
        }
        case  28:
        {
            student28(cx_in, cy_in, cr_in, rx_in, ry_in, rWidth_in, rHeight_in);
            break;
        }
        case  29:
        {
            student29(cx_in, cy_in, cr_in, rx_in, ry_in, rWidth_in, rHeight_in);
            break;
        }
        case  30:
        {
            student30(cx_in, cy_in, cr_in, rx_in, ry_in, rWidth_in, rHeight_in);
            break;
        }
        case  31:
        {
            student31(cx_in, cy_in, cr_in, rx_in, ry_in, rWidth_in, rHeight_in);
            break;
        }
        case  32:
        {
            student32(cx_in, cy_in, cr_in, rx_in, ry_in, rWidth_in, rHeight_in);
            break;
        }
        case  33:
        {
            student33(cx_in, cy_in, cr_in, rx_in, ry_in, rWidth_in, rHeight_in);
            break;
        }
        case  34:
        {
            student34(cx_in, cy_in, cr_in, rx_in, ry_in, rWidth_in, rHeight_in);
            break;
        }
        case  35:
        {
            student35(cx_in, cy_in, cr_in, rx_in, ry_in, rWidth_in, rHeight_in);
            break;
        }
        case  36:
        {
            student36(cx_in, cy_in, cr_in, rx_in, ry_in, rWidth_in, rHeight_in);
            break;
        }
        case  37:
        {
            student37(cx_in, cy_in, cr_in, rx_in, ry_in, rWidth_in, rHeight_in);
            break;
        }
        case  38:
        {
            student38(cx_in, cy_in, cr_in, rx_in, ry_in, rWidth_in, rHeight_in);
            break;
        }
        case  39:
        {
            student39(cx_in, cy_in, cr_in, rx_in, ry_in, rWidth_in, rHeight_in);
            break;
        }
        case  40:
        {
            student40(cx_in, cy_in, cr_in, rx_in, ry_in, rWidth_in, rHeight_in);
            break;
        }
        case  41:
        {
            student41(cx_in, cy_in, cr_in, rx_in, ry_in, rWidth_in, rHeight_in);
            break;
        }
        case  42:
        {
            student42(cx_in, cy_in, cr_in, rx_in, ry_in, rWidth_in, rHeight_in);
            break;
        }
        case  43:
        {
            student43(cx_in, cy_in, cr_in, rx_in, ry_in, rWidth_in, rHeight_in);
            break;
        }
        case  44:
        {
            student44(cx_in, cy_in, cr_in, rx_in, ry_in, rWidth_in, rHeight_in);
            break;
        }
        case  45:
        {
            student45(cx_in, cy_in, cr_in, rx_in, ry_in, rWidth_in, rHeight_in);
            break;
        }
        case  46:
        {
            student46(cx_in, cy_in, cr_in, rx_in, ry_in, rWidth_in, rHeight_in);
            break;
        }
        case  47:
        {
            student47(cx_in, cy_in, cr_in, rx_in, ry_in, rWidth_in, rHeight_in);
            break;
        }
        case  48:
        {
            student48(cx_in, cy_in, cr_in, rx_in, ry_in, rWidth_in, rHeight_in);
            break;
        }
        case  49:
        {
            student49(cx_in, cy_in, cr_in, rx_in, ry_in, rWidth_in, rHeight_in);
            break;
        }
        case  50:
        {
            student50(cx_in, cy_in, cr_in, rx_in, ry_in, rWidth_in, rHeight_in);
            break;
        }
        case  51:
        {
            student51(cx_in, cy_in, cr_in, rx_in, ry_in, rWidth_in, rHeight_in);
            break;
        }
        case  52:
        {
            student52(cx_in, cy_in, cr_in, rx_in, ry_in, rWidth_in, rHeight_in);
            break;
        }
        case  53:
        {
            student53(cx_in, cy_in, cr_in, rx_in, ry_in, rWidth_in, rHeight_in);
            break;
        }
        case  54:
        {
            student54(cx_in, cy_in, cr_in, rx_in, ry_in, rWidth_in, rHeight_in);
            break;
        }
        case  55:
        {
            student55(cx_in, cy_in, cr_in, rx_in, ry_in, rWidth_in, rHeight_in);
            break;
        }
        case  56:
        {
            student56(cx_in, cy_in, cr_in, rx_in, ry_in, rWidth_in, rHeight_in);
            break;
        }
        case  57:
        {
            student57(cx_in, cy_in, cr_in, rx_in, ry_in, rWidth_in, rHeight_in);
            break;
        }
        case  58:
        {
            student58(cx_in, cy_in, cr_in, rx_in, ry_in, rWidth_in, rHeight_in);
            break;
        }
        case  59:
        {
            student59(cx_in, cy_in, cr_in, rx_in, ry_in, rWidth_in, rHeight_in);
            break;
        }
        case  60:
        {
            student60(cx_in, cy_in, cr_in, rx_in, ry_in, rWidth_in, rHeight_in);
            break;
        }
        case  61:
        {
            student61(cx_in, cy_in, cr_in, rx_in, ry_in, rWidth_in, rHeight_in);
            break;
        }
        case  62:
        {
            student62(cx_in, cy_in, cr_in, rx_in, ry_in, rWidth_in, rHeight_in);
            break;
        }
        case  63:
        {
            student63(cx_in, cy_in, cr_in, rx_in, ry_in, rWidth_in, rHeight_in);
            break;
        }
        case  64:
        {
            student64(cx_in, cy_in, cr_in, rx_in, ry_in, rWidth_in, rHeight_in);
            break;
        }
        case  65:
        {
            student65(cx_in, cy_in, cr_in, rx_in, ry_in, rWidth_in, rHeight_in);
            break;
        }
        case  66:
        {
            student66(cx_in, cy_in, cr_in, rx_in, ry_in, rWidth_in, rHeight_in);
            break;
        }
        case  67:
        {
            student67(cx_in, cy_in, cr_in, rx_in, ry_in, rWidth_in, rHeight_in);
            break;
        }
        case  68:
        {
            student68(cx_in, cy_in, cr_in, rx_in, ry_in, rWidth_in, rHeight_in);
            break;
        }
        case  69:
        {
            student69(cx_in, cy_in, cr_in, rx_in, ry_in, rWidth_in, rHeight_in);
            break;
        }
        case  70:
        {
            student70(cx_in, cy_in, cr_in, rx_in, ry_in, rWidth_in, rHeight_in);
            break;
        }
        case  71:
        {
            student71(cx_in, cy_in, cr_in, rx_in, ry_in, rWidth_in, rHeight_in);
            break;
        }
        case  72:
        {
            student72(cx_in, cy_in, cr_in, rx_in, ry_in, rWidth_in, rHeight_in);
            break;
        }
        case  73:
        {
            student73(cx_in, cy_in, cr_in, rx_in, ry_in, rWidth_in, rHeight_in);
            break;
        }
        case  74:
        {
            student74(cx_in, cy_in, cr_in, rx_in, ry_in, rWidth_in, rHeight_in);
            break;
        }
        case  75:
        {
            student75(cx_in, cy_in, cr_in, rx_in, ry_in, rWidth_in, rHeight_in);
            break;
        }
        case  76:
        {
            student76(cx_in, cy_in, cr_in, rx_in, ry_in, rWidth_in, rHeight_in);
            break;
        }
        case  77:
        {
            student77(cx_in, cy_in, cr_in, rx_in, ry_in, rWidth_in, rHeight_in);
            break;
        }
        case  78:
        {
            student78(cx_in, cy_in, cr_in, rx_in, ry_in, rWidth_in, rHeight_in);
            break;
        }
        case  79:
        {
            student79(cx_in, cy_in, cr_in, rx_in, ry_in, rWidth_in, rHeight_in);
            break;
        }
        case  80:
        {
            student80(cx_in, cy_in, cr_in, rx_in, ry_in, rWidth_in, rHeight_in);
            break;
        }
        case  81:
        {
            student81(cx_in, cy_in, cr_in, rx_in, ry_in, rWidth_in, rHeight_in);
            break;
        }
        case  82:
        {
            student82(cx_in, cy_in, cr_in, rx_in, ry_in, rWidth_in, rHeight_in);
            break;
        }
        case  83:
        {
            student83(cx_in, cy_in, cr_in, rx_in, ry_in, rWidth_in, rHeight_in);
            break;
        }
        case  84:
        {
            student84(cx_in, cy_in, cr_in, rx_in, ry_in, rWidth_in, rHeight_in);
            break;
        }
        case  85:
        {
            student85(cx_in, cy_in, cr_in, rx_in, ry_in, rWidth_in, rHeight_in);
            break;
        }
        case  86:
        {
            student86(cx_in, cy_in, cr_in, rx_in, ry_in, rWidth_in, rHeight_in);
            break;
        }
        case  87:
        {
            student87(cx_in, cy_in, cr_in, rx_in, ry_in, rWidth_in, rHeight_in);
            break;
        }
        case  88:
        {
            student88(cx_in, cy_in, cr_in, rx_in, ry_in, rWidth_in, rHeight_in);
            break;
        }
        case  89:
        {
            student89(cx_in, cy_in, cr_in, rx_in, ry_in, rWidth_in, rHeight_in);
            break;
        }
        case  90:
        {
            student90(cx_in, cy_in, cr_in, rx_in, ry_in, rWidth_in, rHeight_in);
            break;
        }
        case  91:
        {
            student91(cx_in, cy_in, cr_in, rx_in, ry_in, rWidth_in, rHeight_in);
            break;
        }
        case  92:
        {
            student92(cx_in, cy_in, cr_in, rx_in, ry_in, rWidth_in, rHeight_in);
            break;
        }
        case  93:
        {
            student93(cx_in, cy_in, cr_in, rx_in, ry_in, rWidth_in, rHeight_in);
            break;
        }
        case  94:
        {
            student94(cx_in, cy_in, cr_in, rx_in, ry_in, rWidth_in, rHeight_in);
            break;
        }
        case  95:
        {
            student95(cx_in, cy_in, cr_in, rx_in, ry_in, rWidth_in, rHeight_in);
            break;
        }
        case  96:
        {
            student96(cx_in, cy_in, cr_in, rx_in, ry_in, rWidth_in, rHeight_in);
            break;
        }
        case  97:
        {
            student97(cx_in, cy_in, cr_in, rx_in, ry_in, rWidth_in, rHeight_in);
            break;
        }
        case  98:
        {
            student98(cx_in, cy_in, cr_in, rx_in, ry_in, rWidth_in, rHeight_in);
            break;
        }
        case  99:
        {
            student99(cx_in, cy_in, cr_in, rx_in, ry_in, rWidth_in, rHeight_in);
            break;
        }    }
}

void main()
{
    int i, j, test, x;
    srand(time(NULL));
    struct Student myStudent[classSize];
    struct Fill myFill[classSize];
    struct Stroke myStroke[classSize];
    int placeMatrix[matHeight][matWidth];
    
    x=0;
    writeSVGHeader(fileName, imWidth, imHeight);
    setupZeroMatrix(matHeight, matWidth, placeMatrix);  //SVG
    for(i=0;i<5;i++)
    {
        setStudent(&myStudent[i], 0, 1);
    }
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
                x=x%classSize;
            }
        }
    }
    printIntMatrix(matHeight, matWidth, placeMatrix);   //SVG
    writeSVGFooter();
}
