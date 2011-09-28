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

void usage(const char *name)
{
    fprintf(stderr, "USAGE:\n");
    fprintf(stderr, "  %s [OPTIONS]\n",name);
    fprintf(stderr,"\n");
    fprintf(stderr, "  -L\tlength of the bar (default 1)\n");
    fprintf(stderr, "  -N\tnumber of divisions of the bar (default 100)\n");
    exit(1);
}

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
        if(fabs(temp_old-temp[i])>1e-5)
            flag=1;
    }
    return flag;
}

int main(int argc, const char *argv[])
{
    int i;
    unsigned int time=0;
    unsigned int N=100;
    double K, C, h, a, L;
    K=1;
    h=0.001;

    for(i = 1; i < argc; i++)
    {
        if(!strcmp(argv[i],"-h"))
            usage(argv[0]);
        else if(!strcmp(argv[i],"-L"))
        {
            if(i+1==argc)
                usage(argv[0]);
            else
            {
                i++;
                if(!sscanf(argv[i],"%lf",&L))
                    usage(argv[0]);
            }
        }
        else if(!strcmp(argv[i],"-N"))
        {
            if(i+1==argc)
                usage(argv[0]);
            else
            {
                i++;
                if(!sscanf(argv[i],"%lf",&N))
                    usage(argv[0]);
            }
        }
        else usage(argv[0]);
    }

    double *bar;
    bar=calloc(N,sizeof(double));

    bar[0]=10;
    bar[N-1]=100;
    for(i = 1; i < N-1; i++)
        bar[i]=(bar[0]+bar[N-1])/2;

    a=L/N;
    
    C=K*h/a/a;

    //for(i = 0; i < 1000000; i++)
    //    evolution(bar, L, C);
    while(evolution(bar,N,C))
    {
        time++;
        if(time%500==0)
            for(i = 0; i < N; i++)
                printf("%d\t%u\t%lf\n",i,time,bar[i]);
    }

    //for(i = 0; i < N; i++)
    //    printf("%d\t%lf\n",i,bar[i]);
    return 0;
}
