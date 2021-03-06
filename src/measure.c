#include "measure.h"
#include "lattice.h"
#include <math.h>

void meas_reset(meas *p)
{
    int i, j;

    for (i = 0; i < NUM_MOMENTS; i++)
        for (j = 0; j < NUM_AVERAGES; j++)
            p->v[i][j] = 0.;
}

void meas_accum(meas *sum, wolff const *w, state const *s)
{
    meas samp;
    int i, j;
    double m = (double) s->magnetization / LT_N,
           c = (double) w->cluster_size / LT_N,
           en = (double) w->energy / LT_N;

    samp.v[0][M2] = m*m;
    samp.v[0][C] = c;
    samp.v[0][U] = en;
    samp.v[0][UM2] = en*m*m;

    for (i = 0; i < NUM_MOMENTS; i++)
        for (j = 0; j < NUM_AVERAGES; j++)
            sum->v[i][j] += pow(samp.v[0][j], i+1);
}

void meas_average(meas *sum, uint64_t t_meas)
{
    int i, j;

    for (i = 0; i < NUM_MOMENTS; i++)
        for (j = 0; j < NUM_AVERAGES; j++)
            sum->v[i][j] /= t_meas;
}
