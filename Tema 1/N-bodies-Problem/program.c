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
#include "vector3D.h"
#include "body.h"
#include "system.h"

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
    int i;
    int method=1;

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


    struct system Earth_Moon,*s=&Earth_Moon;
    unsigned long int time=0;

    Earth_Moon.n=3;
    Earth_Moon.b=malloc(Earth_Moon.n*sizeof(struct system));
    Earth_Moon.b[0]=(struct body){1.98892e30,{0,0,0},{0,0,0},{0,0,0},{0,0,0},1};                  //Sun if it's in the centre and fixed
    Earth_Moon.b[1]=(struct body){5.9737e24,{1.5e11,0,0},{0,29.7389e3,0},{0,0,0},{0,0,0},0};      //Earth
    Earth_Moon.b[2]=(struct body){7.3477e22,{1.8384e9,0,0},{0,30.802e3,0},{0,0,0},{0,0,0},0};     //Moon
    
    //Earth_Moon.n=2;
    //Earth_Moon.b=malloc(Earth_Moon.n*sizeof(struct system));
    //Earth_Moon.b[0]=(struct body){5.9737e24,{0,0,0},{0,0,0},{0,0,0},{0,0,0},1};                     //Earth
    //Earth_Moon.b[1]=(struct body){7.3477e22,{384e6,0,0},{0,1018.865,0},{0,0,0},{0,0,0},0};          //Moon
    //print_system(Earth_Moon);

    for(time = 0; time < 2500000; time+=200)
    {
        switch(method)
        {
            case 0:
                for(i = 0; i < 200; i++)
                    temporal_evolution(s,1);
                break;
            case 1:
                for(i = 0; i < 200; i++)
                    temporal_evolution_vt(s,1);
                break;
        }

        //printf("%lu\t%Lf\t%Lf\t%Lf\t",time,Earth_Moon.b[0].r.x,Earth_Moon.b[0].r.y,Earth_Moon.b[0].r.z);
        //printf("%Lf\t%Lf\t%Lf\n",Earth_Moon.b[1].r.x,Earth_Moon.b[1].r.y,Earth_Moon.b[1].r.z);
    }
    return 0;
}
