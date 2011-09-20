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

#include <stdio.h>

double h=0.001;
double k=1;
double l=1;
double s=0;
double m=1;


void evoluciona(double *x, double *v)
{
    double v_old=*v;
    *v+=h*(-k*(*x-l-s));
    *x+=h*v_old;
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

int main(int argc, const char *argv[])
{
    long int i;
    long int j;
    long int time=0;
    int inter = 100;
    double x, v;
    x=0;
    v=0;

    for(i=0;i<800;i++)
    {
        for(j=0;j<inter;j++)
            evoluciona(&x,&v);
        time+=inter;
        escribe_res(time,x,v);
    }

    h=-h;

    for(i=0;i<800;i++)
    {
        for(j=0;j<inter;j++)
            evoluciona(&x,&v);
        time+=inter;
        escribe_res(time,x,v);
    }
    return 0;
}
