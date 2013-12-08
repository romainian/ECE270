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
