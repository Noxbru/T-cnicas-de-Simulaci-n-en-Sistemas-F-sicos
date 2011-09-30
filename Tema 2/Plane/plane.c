/* This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * 
 * Copyright (C) Bruno Jiménez, 2011
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "args.c"

int evolution(double **temp, unsigned int N, double C)
{
    int i, j, flag=0;
    double C_0=1-4*C;
    double temp_old;
    for(i = 1; i < N-1; i++)
        for(j = 1; j < N-1; j++)
        {
            temp_old=temp[i][j];
            temp[i][j]=C_0*temp[i][j]+C*(temp[i+1][j]+temp[i-1][j]+temp[i][j-1]+temp[i][j+1]);
            if(fabs(temp_old-temp[i][j])>1e-6)
                flag=1;
        }
    return flag;
}
int main(int argc, const char *argv[])
{
    void **args;
    int i, j;
    unsigned int N;
    double K, C, h, a, L, T0, T1;
    h=0.001;

    args=arghandler(argc, argv);
    K=*(double *)args[0];
    L=*(double *)args[1];
    N=*(unsigned int *)args[2];
    T0=*(double *)args[3];
    T1=*(double *)args[4];

    double **plane;
    plane=malloc(N*sizeof(double *));
    for(i = 0; i < N; i++)
        plane[i]=calloc(N,sizeof(double));

    for(i = 0; i < N; i++)
    {
        plane[0][i]=T0;
        plane[N-1][i]=T1;
    }

    a=L/N;

    C=K*h/a/a;
    if(C>0.5)
        fprintf(stderr,"Value of C higher than 0.5: %lf Might give wrong results\n",C);
    else if(C<5e-4)
        fprintf(stderr,"Value of C lower than 0.0005: %lf Might give wrong results\n",C);

    while(evolution(plane,N,C));
    {
        if(bar[1]==INFINITY)
        {
            C/=10;
            fprintf(stderr,"WARNING: ALGORITHM DIVERGED. TRYING WITH LOWER C: %lf\n",C);
            for(i = 1; i < N-1; i++)
                for(j = 1; j < N-1; j++)
                    plane[i][j]=0;
        }
    }

    for(i = 0; i < N; i++)
        for(j = 0; j < N; j++)
            printf("%d\t%d\t%lf\n",i,j,plane[i][j]);
    return 0;
}
