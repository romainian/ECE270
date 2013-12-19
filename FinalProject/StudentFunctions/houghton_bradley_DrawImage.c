void houghton_bradley_drawImage(struct Circle myCircle[], struct Fill myFill[], struct Stroke myStroke[])
{
    int i;
    for(i=0;i<5;i++)
    {
        drawCircle(myCircle[i].cx, myCircle[i].cy, myCircle[i].r, myFill[i].r, myFill[i].g, myFill[i].b, myFill[i].opacity, myStroke[i].r, myStroke[i].g, myStroke[i].b, myStroke[i].opacity, myStroke[i].width)
    }
}
