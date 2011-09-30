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

int evolution(double *temp, unsigned int N, double C)
{
    int i, flag=0;
    double temp_old, temp_old_aux;
    temp_old=temp[0];
    double C_0=1-2*C;
    for(i = 1; i < N-1; i++)
    {
        temp_old_aux=temp[i];
        temp[i]=C_0*temp[i]+C*(temp_old+temp[i+1]);
        temp_old=temp_old_aux;
        if(fabs(temp_old-temp[i])>1e-6)
            flag=1;
    }
    return flag;
}

int main(int argc, const char *argv[])
{
    void **args;
    int i;
    //unsigned int time=0;
    unsigned int N;
    double K, C, h, a, L, T0, T1;
    h=0.001;

    args=arghandler(argc, argv);
    K=*(double *)args[0];
    L=*(double *)args[1];
    N=*(unsigned int *)args[2];
    T0=*(double *)args[3];
    T1=*(double *)args[4];

    double *bar;
    bar=calloc(N,sizeof(double));

    bar[0]=T0;
    bar[N-1]=T1;
    for(i = 1; i < N-1; i++)
        bar[i]=(bar[0]+bar[N-1])/2;

    a=L/N;
    
    C=K*h/a/a;
    if(C>0.5)
        fprintf(stderr,"Value of C higher than 0.5: %lf Might give wrong results\n",C);
    else if(C<5e-4)
        fprintf(stderr,"Value of C lower than 0.0005: %lf Might give wrong results\n",C);

    while(evolution(bar,N,C))
    {
        //time++;
        if(bar[1]==INFINITY)
        {
            C/=10;
            fprintf(stderr,"WARNING: ALGORITHM DIVERGED. TRYING WITH LOWER C: %lf\n",C);
            for(i = 1; i < N-1; i++)
                bar[i]=(bar[0]+bar[N-1])/2;
        }
        //if(time%500==0)
        /*{
            for(i = 0; i < N; i++)
                printf("%d\t%u\t%lf\n",i,time,bar[i]);
            getchar();
        }*/
    }

    for(i = 0; i < N; i++)
        printf("%d\t%lf\n",i,bar[i]);
    return 0;
}
