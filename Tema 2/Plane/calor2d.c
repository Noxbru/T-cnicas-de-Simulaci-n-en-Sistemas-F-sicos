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

void printusage(const char *name)
{
    fprintf(stderr, "USAGE\n");
    fprintf(stderr, "-----\n");
    fprintf(stderr, "%s\n",name);
    fprintf(stderr, "OR\n");
    fprintf(stderr, "%s -L length\n",name);
    exit(1);
}

int evolution(double **temp, unsigned int L, double C)
{
    int i, j, flag=0;
    double C_0=1-4*C;
    double temp_old;
    for(i = 1; i < L-1; i++)
        for(j = 1; j < L-1; j++)
        {
            temp_old=temp[i][j];
            temp[i][j]=C_0*temp[i][j]+C*(temp[i+1][j]+temp[i-1][j]+temp[i][j-1]+temp[i][j+1]);
            if(fabs(temp_old-temp[i][j])>1e-5)
                flag=1;
        }
    return flag;
}
int main(int argc, const char *argv[])
{
    int i, j;
    unsigned int time=0;
    unsigned int L=100;
    double K, C, h, a;
    K=1;
    h=0.001;
    for(i = 1; i < argc; i++)
    {
        if(!strcmp(argv[i],"-h"))
            printusage(argv[0]);
        else if(!strcmp(argv[i],"-L"))
        {
            if(i++<argc)
                L=atol(argv[i]);
            else
                printusage(argv[0]);
        }
        else printusage(argv[0]);
    }

    double **bar;
    bar=malloc(L*sizeof(double *));
    for(i = 0; i < L; i++)
        bar[i]=calloc(L,sizeof(double));

    for(i = 0; i < L; i++)
    {
        bar[0][i]=100;
        bar[L-1][i]=10;
    }

    a=1./L;

    //C=K*h/a/a;
    C=K*h/a;

    while(evolution(bar,L,C));
    /*{
        time++;
        if(time%1000==0)
            for(i = 0; i < L; i++)
                printf("%d\t%u\t%lf\n",i,time,bar[i]);
    }*/

    for(i = 0; i < L; i++)
        for(j = 0; j < L; j++)
            printf("%d\t%d\t%lf\n",i,j,bar[i][j]);
    return 0;
}
