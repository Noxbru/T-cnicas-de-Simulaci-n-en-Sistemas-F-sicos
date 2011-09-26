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
#include <math.h>

#define BODY

#ifndef VECTOR3D
    #include "vector3D.h"
#endif

#ifndef TRUE
    #define TRUE 1
#endif
#ifndef FALSE
    #define FALSE 0
#endif

struct body
{
    long double m;          //Mass of the body
    struct vector3D r,v;    //Position and velocity vectors
    struct vector3D dr,dv;  //Increments in position and velocity vectors
    char fixed;             //Check if a body is fixed in space or not (1 fixed, 0 not fixed)
    FILE *fout;
};

/* Gets a body from keyboard */
void get_body(struct body *v)
{
    struct vector3D *r1=&v->r;
    struct vector3D *v1=&v->v;
    v->dv=(struct vector3D){0,0,0};
    printf("Imput the mass of the body\n");
    scanf("%Lf",&v->m);
    printf("Imput its position vector\n");
    get_vector(r1);
    printf("Imput its velocity vector\n");
    get_vector(v1);
    printf("Is the body fixed in space?(Y/N)\n");
    scanf(" %c",&v->fixed);
    
    switch(v->fixed)
    {
        case 'Y':
        case 'y':   v->fixed=TRUE; break;
        default:    v->fixed=FALSE;break;
    }
}

/* Prints a body with the following format
 * Mass:
 * Its position vector
 * Its velocity vector
 * Wheter is fixed or not                   */
void print_body(struct body c)
{
    printf("Mass:\t%Lf\n",c.m);
    printf("Position vector\n");
    print_vector(c.r);
    printf("Velocity vector\n");
    print_vector(c.v);
    if (c.fixed)
        printf("Body fixed in space\n");
    else
        printf("Body not fixed in space\n");
}

/* Linear moment of a body: mass times velocity vector */
struct vector3D linear_moment(struct body a)
{
    return (struct vector3D){a.m*a.v.x,a.m*a.v.y,a.m*a.v.z};
}

/* Returns a vector which is the angular moment of the body
 * with respect of the origin of coordinates                */
struct vector3D angular_moment(struct body a)
{
    return vectorial_product(a.r,linear_moment(a));
}

/* Returns a vector which is the force between two bodies */
struct vector3D force(struct body a, struct body b)
{
    long double aux1=distancia(a.r,b.r);
    long double aux2=6.67e-11*a.m*b.m/aux1/aux1/aux1;
    struct vector3D r=resta(b.r,a.r);
    return (struct vector3D){r.x*aux2,r.y*aux2,r.z*aux2};
}

/* Returns a vector which is the force between two bodies
 * in a diferent point according to the dr vector           */
struct vector3D force_dr(struct body a, struct body b)
{
    long double aux1 = distancia(suma(a.r, a.dr), b.r);
    long double aux2=6.67e-11*a.m*b.m/aux1/aux1/aux1;
    struct vector3D r=resta(b.r, suma(a.r, a.dr));
    return (struct vector3D){r.x*aux2,r.y*aux2,r.z*aux2};
}

/* Returns the potential energy of a body with respect another */
long double potential_energy(struct body a,struct body b)
{
    return 6.67e-11*a.m*b.m/distancia(a.r,b.r);
}

/* Returns the kinetic energy of a body */
long double kinetic_energy(struct body a)
{
    return 0.5*a.m*distancia(a.v,a.dv)*distancia(a.v,a.dv);
}
