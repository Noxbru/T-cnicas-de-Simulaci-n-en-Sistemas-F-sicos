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
 */

/* Copyright 2011 Bruno Jiménez */

/* This program is the solution to the Exercise 1 and problems 1 and 2
 * of Lesson 1:
 * Program the harmonic oscilator in 1 dimension with Euler and Verlet
 * algorithms (Exercise 1)
 * Plot with gnuplot some variables (Problem 1)
 * After N steps invert time and see what happens (Problem 2)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

double h=0.001;
double k=1;
double l=1;
double s=0;
double m=1;

void evoluciona(double *x, double *v, int method)
{
    double v_old=*v;
    switch(method)
    {
        case 0:
            *v+=h*(-k*(*x-l-s));
            *x+=h*v_old;
            break;
        case 1:
            *v+=h/2*(-k*(*x-l-s));
            *x+=h*(*v);
            *v+=h/2*(-k*(*x-l-s));
            break;
    }
}

void escribe_res(double tiempo, double x, double v)
{
    double e_pot, e_cin, e_mec;
    e_pot = 0.5*k*(x-l-s)*(x-l-s);
    e_cin = 0.5*m*v*v;
    e_mec = e_pot+e_cin;
    printf("%lf\t%lf\t%lf\t",tiempo,x,v);
    printf("%lf\t%lf\t%lf\n",e_pot,e_cin,e_mec);
}

void printusage(const char *name)
{
    fprintf(stderr,"USAGE:\n");
    fprintf(stderr,"  %s [Options]\n",name);
    fprintf(stderr,"\n");
    fprintf(stderr,"Options:\n");
    fprintf(stderr,"  -m\talgorithm to use: euler or verlet (default verlet)\n");
    fprintf(stderr,"\n");
    exit(1);
}

int main(int argc, const char *argv[])
{
    long int i, j;
    long int time=0;
    int method = 1;
    int inter = 100;
    double x, v;
    x=0;
    v=0;

    for(i = 1; i < argc; i++)
    {
        if(!strcmp(argv[i],"-m"))
        {
            if(i+1==argc) printusage(argv[0]);
            else i++;
            if(!strcmp(argv[i],"euler"))       method = 0;
            else if(!strcmp(argv[i],"verlet")) method = 1;
            else printusage(argv[0]);
        }
        else printusage(argv[0]);
    }

    for(i=0;i<800;i++)
    {
        for(j=0;j<inter;j++)
            evoluciona(&x,&v,method);
        time+=inter;
        escribe_res(time,x,v);
    }

    h=-h;

    for(i=0;i<800;i++)
    {
        for(j=0;j<inter;j++)
            evoluciona(&x,&v,method);
        time+=inter;
        escribe_res(time,x,v);
    }
    return 0;
}
