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
