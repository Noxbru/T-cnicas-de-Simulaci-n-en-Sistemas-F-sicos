/* This code is part of N-Bodies Problem
 *
 * N-Bodies Problem is free software: you can redistribute it and/or modify
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

#ifndef BODY
    #include "body.h"
#endif

struct system
{
    struct body *b;
    unsigned int n;
};

void get_system(struct system *s)
{
    struct body *b1;
    int i;
    printf("Imput the number of bodies\n");
    scanf("%u",&s->n);
    s->b=malloc(s->n*sizeof(struct body));
    for (i = 0; i < s->n; i++)
    {
        b1=&s->b[i];
        get_body(b1);
    }
}

void print_system(struct system s)
{
    int i;
    for (i = 0; i < s.n; i++)
        print_body(s.b[i]);
}

struct vector3D force_system(struct system s, unsigned int i)
{
    int j;
    struct vector3D f = {0,0,0};
    for(j = 0; j < s->n; j++)
        if(i!=j)
            f=suma(f,force(s->b[i],s->b[j]));
    return f;
}

struct vector3D force_system_dr(struct system s, unsigned int i)
{
    int j;
    struct vector3D f = {0,0,0};
    for(j = 0; j < s->n; j++)
        if(i!=j)
            f=suma(f,force_dr(s->b[i],s->b[j]));
    return f;
}

/* Temporal evolution based on Euler's Algorithm */
void temporal_evolution(struct system *s, double h)
{
    int i,j;
    struct vector3D f;
    struct vector3D k1;

    for (i = 0; i < s->n; i++)
        if(!s->b[i].fixed)
        {
            f=force_system(s,i);
            k1=multiply_vector_by(f,1/s->b[i].m);
            s->b[i].dr=multiply_vector_by(s->b[i].v,h);
            s->b[i].dv=multiply_vector_by(k1,h);
            s->b[i].v=suma(s->b[i].v,s->b[i].dv);
            s->b[i].r = suma(s->b[i].r, s->b[i].dr); 
        }
}

/* Temporal evolution based on Verlet's Algorithm */
void temporal_evolution_vt(struct system *s, double h)
{
    int i,j;
    struct vector3D f;
    struct vector3D dv;

    for(i = 0; i < s->n; i++)
        if(!s->b[i].fixed)
        {
            f = force_system(s,i);
            k1 = multiply_vector_by(f,h/s->b[i].m/2);
            dv = suma(s->b[i].v,k1);

            s->b[i].dr = multiply_vector_by(dv,h);

            f = force_system_dr(s,i);
            k2 = multiply_vector_by(f,h/s->b[i].m/2);

            s->b[i].dv = suma(k1+k2);
            s->b[i].v=suma(s->b[i].v,s->b[i].dv);
            s->b[i].r = suma(s->b[i].r, s->b[i].dr); 
        }
}
