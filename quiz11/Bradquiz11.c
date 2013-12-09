//
//  main.c
//  quiz #11.2
//
//  Created by Bradley Houghton on 11/10/2013.
//  Copyright (c) 2013 Bradley Houghton. All rights reserved.
//

#include <stdio.h>
FILE *fp;
int imHeight=1000;
int imWidth=1000;

//HEADERS//
void writeSVGHeader(char fileName[], int width, int height)
{
    fp = fopen(fileName,"w");
    
    fprintf(fp,"<?xml version='1.0' standalone='no'?>");
    fprintf(fp,"\n<svg xmlns='http://www.w3.org/2000/svg' xmlns:xlink='http://www.w3.org/1999/xlink' version='1.1' width = '%d' height = '%d'>", width, height);
}
void writeSVGFooter()
{
    fprintf(fp,"\n</svg>");
    fclose(fp);
}
//STRUCTURES//
struct Circle
{
    float cx;
    float cy;
    float r;
};
struct Fill
{
    int red;
    int green;
    int blue;
    float opacity;
};
struct Stroke
{
    int red;
    int green;
    int blue;
    int size;
    int width;
    float opacity;
};
//SET ARRAY//
void setCircle(struct Circle *myCircle,float cx,float cy, float r)
{
    
    myCircle->cx=cx;
    myCircle->cy=cy;
    myCircle->r=r;
}
void setCircleArray(int Dim, struct Circle myCircle[],float cx[],float cy[], float r[])
{
    int i;
    for(i=0;i<Dim;i++)
    {
        setCircle(&myCircle[i], cx[i], cy[i], r[i]);
    }
    
}
void setFill(struct Fill *myFill,int r, int g, int b, float op)
{
    myFill->red=r;
    myFill->green=g;
    myFill->blue=b;
    myFill->opacity=op;
}
void setFillArray(int Dim, struct Fill myFill[], int red[], int green[], int blue[], float opacity[])
{
    int i;
    for(i=0;i<Dim;i++)
    {
        setFill(&myFill[i], red[i], green[i], blue[i], opacity[i]);
    }
}
void setStroke(struct Stroke *myStroke, int red,int green,int blue,int width,float op)
{
    myStroke->red=red;
    myStroke->green=green;
    myStroke->blue=blue;
    myStroke->width=width;
    myStroke->opacity=op;
}
void setStrokeArray(int Dim, struct Stroke myStroke[], int red[], int green[], int blue[], int width[], float opacity[])
{
    int i;
    for(i=0;i<Dim;i++)
    {
        setStroke(&myStroke[i], red[i], green[i], blue[i], width[i], opacity[i]);
    }
}
//DRAW//
void drawCircles(int n, struct Circle circle[], struct Fill fill[], struct Stroke stroke[])
{
    int i;
    for(i=0;i<n;i++)
    {
        fprintf(fp,"\n  <circle cx = '%f' cy = '%f' r = '%f'", circle[i].cx, circle[i].cy, circle[i].r);
        fprintf(fp," fill = 'rgb(%d, %d, %d)' fill-opacity = '%f'", fill[i].red, fill[i].green, fill[i].blue, fill[i].opacity);
        fprintf(fp," stroke = 'rgb(%d, %d, %d)' stroke-opacity = '%f'", stroke[i].red, stroke[i].green, stroke[i].blue, stroke[i].opacity);
        fprintf(fp," stroke-width = '%d' />", stroke[i].width);
    }
    
}
//GET DATA & DRAW IMAGE//
void houghton_bradley_getData(float cx_in, float cy_in, float r_in, struct Circle smiley[], struct Fill smileyFill[], struct Stroke smileyStroke[])
{
    float cx[]={cx_in,cx_in-(r_in/2),cx_in+(r_in/2),cx_in,cx_in};
    float cy[]={cy_in,cy_in-(r_in/2),cy_in-(r_in/2),cy_in+(r_in/3),cy_in};
    float r[]={r_in,r_in/6,r_in/6,r_in/2,r_in/2};
    
    int redFill[]={255,0,0,255,255};
    int greenFill[]={255,0,0,255,255};
    int blueFill[]={0,0,0,255,0};
    float opacityFill[]={1.0,1.0,1.0,1.0,1.0};
    
    int redStroke[]={0,0,0,0,255};
    int greenStroke[]={0,0,0,0,255};
    int blueStroke[]={0,0,0,0,0};
    int widthStroke[]={5,2,2,1,1};
    float opacityStroke[]={1.0,1.0,1.0,1.0,1.0};
    
    //struct Circle smiley[5];
    //struct Fill smileyFill[5];
    //struct Stroke smileyStroke[5];
    
    setCircleArray(5, smiley, cx, cy, r);
    setFillArray(5, smileyFill, redFill, greenFill, blueFill, opacityFill);
    setStrokeArray(5, smileyStroke, redStroke, greenStroke, blueStroke, widthStroke, opacityStroke);
}
void houghton_bradley_drawImage(struct Circle myCircle[], struct Fill myFill[], struct Stroke myStroke[])
{
    drawCircles(5,myCircle, myFill, myStroke);
}
//MAIN//


int main(int argc, const char * argv[])
{
    writeSVGHeader("Smiley.SVG",imWidth, imHeight);
    
    struct Circle smiley[5];
    struct Fill smileyFill[5];
    struct Stroke smileyStroke[5];
    
    
    houghton_bradley_getData(700, 700, 90, smiley, smileyFill, smileyStroke);
    houghton_bradley_drawImage(smiley, smileyFill, smileyStroke);
    
    
    
    
    
    
    writeSVGFooter();
    
    return 0;
}

