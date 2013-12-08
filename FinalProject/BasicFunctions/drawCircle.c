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
