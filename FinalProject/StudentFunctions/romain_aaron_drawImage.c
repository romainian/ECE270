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
