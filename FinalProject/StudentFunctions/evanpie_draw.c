void printRectangles(int Dim, struct Rect rect[], struct Fill fill[], struct Stroke stroke[])
{
    int i;
    for (i=0; i<Dim; i++)
    {
        fprintf(fp,"\n    <rect x = '%f' y = '%f' width = '%f' height = '%f'", rect[i].x, rect[i].y, rect[i].width, rect[i].height);
        fprintf(fp," fill = 'rgb(%d, %d, %d)' fill-opacity = '%f'", fill[i].r, fill[i].g, fill[i].b, fill[i].opacity);
        fprintf(fp," stroke = 'rgb(%d, %d, %d)' stroke-opacity = '%f'", stroke[i].r, stroke[i].g, stroke[i].b, stroke[i].opacity);
        fprintf(fp," stroke-width = '%d' />", stroke[i].width);
    }
}
