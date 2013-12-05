#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
/*  Aaron Romain's head spinner  */
/*  Enter how large you'd like the image,
    how many iterations to make, and what to name the file  */

FILE *fp;
int imWidth = 700;
int imHeight = 900;
int n = 1;
char fileName[] = "agromain.svg";
int step = 30;
int ring = 10;
float xc = 400;
float yc = 600;
float radius = 200;
int i;

struct Stroke
{
    int r;
    int g;
    int b;
    int width;
    float opacity;
};

struct Fill
{
    int r;
    int g;
    int b;
    float opacity;
};

struct Lines
{
    float x1[1000];
    float x2[1000];
    float y1[1000];
    float y2[1000];
};

struct Circles
{
    float x[100];
    float y[100];
    float r[100];
};

void setStroke(struct Stroke *myStroke)
{
    myStroke->r = 0;
    myStroke->g = 0;
    myStroke->b = 0;
    myStroke->width = 1;
    myStroke->opacity = 1;
}

void setFill(struct Fill *myFill)
{
    myFill->r = 0;
    myFill->g = 0;
    myFill->b = 0;
    myFill->opacity = 0;
}

void romain_aaron_getData(struct Lines *myLines, struct Circles *myCircle,
                          float cx_in, float cy_in, float r_in,
                          int steps, int rings)
{
    float v[2][1] = {0,r_in};
    float v2[2][1] = {v[0][0],v[1][0]};
    float theta = 2*M_PI/steps;
    float R[2][2] = {{cos(theta),-sin(theta)},{sin(theta),cos(theta)}};
    int i;
    myLines->x1[0] = cx_in;
    myLines->y1[0] = cy_in;
    for (i=0;i<steps;i++)
    {
        v2[0][0] = v[0][0];
        v2[1][0] = v[1][0];
        myLines->x2[i] = v[0][0]+cx_in;
        myLines->y2[i] = v[1][0]+cy_in;
        v[0][0] = R[0][0]*v2[0][0]+R[0][1]*v2[1][0];
        v[1][0] = R[1][0]*v2[0][0]+R[1][1]*v2[1][0];
    }
    myCircle->x[0] = cx_in;
    myCircle->y[0] = cy_in;
    for (i=0;i<rings;i++)
    {
        myCircle->r[i] = r_in*powf(.8,i);
    }
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

void romain_aaron_drawImage(struct Lines myLines, struct Circles myCircle,
                            struct Stroke myStroke, struct Fill myFill,
                            int steps, int rings)
{
    int i;
    for (i=0;i<steps;i++)
    {
        drawLine(myLines.x1[0], myLines.y1[0], myLines.x2[i],
                myLines.y2[i], myStroke.r, myStroke.g,
                myStroke.b, myStroke.opacity, myStroke.width);
    }
    for (i=0;i<rings;i++)
    {
        drawCircle(myCircle.x[0], myCircle.y[0], myCircle.r[i],
                myFill.r, myFill.g, myFill.b, myFill.opacity,
                myStroke.r, myStroke.g, myStroke.b, myStroke.opacity,
                myStroke.width);
    }
}

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

int main()
{
    int i, j, k;
    srand(time(NULL));
    writeSVGHeader(fileName, imWidth, imHeight);
    struct Lines myLines;
    struct Circles myCircle;
    struct Fill myFill;
    struct Stroke myStroke;
    for (j=0;j<n;j++)
    {
        setStroke(&myStroke);
        setFill(&myFill);
        float cx_in = xc;
        float cy_in = yc;
        float r_in = radius;
        int steps = step;
        int rings = ring;
        romain_aaron_getData(&myLines, &myCircle,
                             cx_in, cy_in, r_in, steps, rings);
        romain_aaron_drawImage(myLines, myCircle,
                               myStroke, myFill, steps, rings);
    }
    writeSVGFooter();
    return 0;
}
