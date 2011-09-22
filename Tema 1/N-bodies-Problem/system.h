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

/* Temporal evolution based on Euler's Algorithm */
void temporal_evolution(struct system *s, double h)
{
    int i,j;
    struct vector3D f;
    for (i = 0; i < s->n; i++)
        if(!s->b[i].fixed)
            s->b[i].r = suma(s->b[i].r, s->b[i].dr); 

    for (i = 0; i < s->n; i++)
        for (j = i+1; j < s->n; j++)
        {
            f=force(s->b[i],s->b[j]);
            s->b[i].dr=multiply_vector_by(s->b[i].v,h);
            s->b[i].dv=multiply_vector_by(f,h/s->b[i].m);
            s->b[i].v=suma(s->b[i].v,s->b[i].dv);

            f=force(s->b[j],s->b[i]);
            s->b[j].dr=multiply_vector_by(s->b[j].v,h);
            s->b[j].dv=multiply_vector_by(f,h/s->b[j].m);
            s->b[j].v=suma(s->b[j].v,s->b[j].dv);
        }
}

/* Temporal evolution based on Verlet's Algorithm */
void temporal_evolution_vt(struct system *s, double h)
{
    int i,j;
    struct vector3D f;
    struct vector3D dv;
    for (i = 0; i < s->n; i++)
        if(!s->b[i].fixed)
            s->b[i].r = suma(s->b[i].r, s->b[i].dr); 

    for(i = 0; i < s->n; i++)
        for(j = i+1; j < s->n; j++)
        {
            if(!s->b[i].fixed)
            {
                f = force(s->b[i],s->b[j]);
                k1 = multiply_vector_by(f,h/s->b[i].m/2);
                dv = suma(s->b[i].v,k1);

                s->b[i].dr = multiply_vector_by(dv,h);

                f = force_rk(s->b[i],s->b[j]);
                k2 = multiply_vector_by(f,h/s->b[i].m/2);

                s->b[i].dv = suma(k1+k2);
                s->b[i].v=suma(s->b[i].v,s->b[i].dv);
            }
            if(!s->b[j].fixed)
            {
                f = force(s->b[j],s->b[i]);
                k1 = multiply_vector_by(f,h/s->b[j].m/2);
                dv = suma(s->b[j].v,k1);

                s->b[j].dr = multiply_vector_by(dv,h);

                f = force_rk(s->b[j],s->b[i]);
                k2 = multiply_vector_by(f,h/s->b[j].m/2);

                s->b[j].dv = suma(k1+k2);
                s->b[j].v=suma(s->b[j].v,s->b[j].dv);
            }
        }
}
