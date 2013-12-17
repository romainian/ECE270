void rachel_simms_getData(struct circle mycircle[], struct Fill myfill[], int Dim1, int cx, int cy, int radius, int Dim2, int r, int b, int g)
{
 int i;
 int j;
    for (i=0;i<Dim1;i++)
    {
        myfill[i].red = r;
        myfill[i].green = g;
        myfill[i].blue = b;
        myfill[i].opacity = 1;
    }
    for (j=0; j<Dim2; j++)
    {
        mycircle[j].cx = cx;
        mycircle[j].cy = cy;
        mycircle[j].radius = radius;
    }
}




void rachel_simms_drawImage(struct circle mycircle[], struct Fill myFill[], struct stroke mystroke)
{
    int i;
    for(i=0; i <100; i++)
    {

    fprintf(fp,"\n    <circle cx = '%f' cy = '%f' r = '%f'", mycircle[1].cx, mycircle[2].cy, mycircle[3].radius);
    fprintf(fp," fill = 'rgb(%d, %d, %d)' fill-opacity = '%f'", myFill[1].red, myFill[2].green, myFill[3].blue, myFill[4].opacity);
    fprintf(fp," stroke = 'rgb(%d, %d, %d)' stroke-opacity = '%f'", mystroke.red, mystroke.green, mystroke.blue, mystroke.opacity);
    fprintf(fp," stroke-width = '%d' />", mystroke.width);

    mycircle[3].radius -= 10;
    myFill[2].green += 10;
    myFill[3].blue +=20;

    }

}



int main()
{
   

    float radius, cx, cy;
    int g, b, r;




    struct circle mycircle[4];
    struct Fill myFill[4];
    struct stroke mystroke;

    radius = 300; //radius
    cx = 500; //x-coordinate
    cy = 500; //y-coordinate
    g = 25; //green fill
    b = 0; //blue fill
    r = 255; //red fill


    setcircle(&mycircle, cx, cy, radius);

    setFill(&myFill, r, g, b, 1.0);

    setstroke(&mystroke, 0, 0, 0, 1.0, 2);



    rachel_simms_getData(mycircle, myFill, 4, cx, cy, radius, 4, r, b, g);


    rachel_simms_drawImage(mycircle, myFill, mystroke);
    
    return(0);
}






