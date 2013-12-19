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
}
