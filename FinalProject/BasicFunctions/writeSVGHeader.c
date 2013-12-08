void writeSVGHeader(char fileName[], int width, int height)
{
    fp = fopen(fileName,"w");
    fprintf(fp,"<?xml version='1.0' standalone='no'?>");
    fprintf(fp,"\n<svg xmlns='http://www.w3.org/2000/svg' ");
    fprintf(fp,"xmlns:xlink='http://www.w3.org/1999/xlink' ");
    fprintf(fp,"version='1.1' width = '%d' height = '%d'>", width, height);
}
