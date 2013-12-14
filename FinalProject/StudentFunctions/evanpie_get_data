void evanPieGetData(int dim, struct Fill fill[], struct Stroke stroke[], struct Rect rect[])
{
    int i;
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
}
