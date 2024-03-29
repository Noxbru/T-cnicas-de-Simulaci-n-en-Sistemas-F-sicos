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
 * Copyright (C) Buno Jiménez, 2011
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void usage(const char *name)
{
    fprintf(stderr,"USAGE:");
    fprintf(stderr,"  %s [OPTIONS]\n",name);
    fprintf(stderr,"\n");
    fprintf(stderr,"OPTIONS:\n");
    fprintf(stderr,"  -h\tshow this help\n");
    fprintf(stderr,"  -A\tnumber of aleatory numbers (default 100000)\n");
    fprintf(stderr,"  -eps\tmaximun movement of the particle (default 1)\n");
    fprintf(stderr,"  -I\tnumber of intervals (default 10)\n");
    fprintf(stderr,"  -N\tlower random number (default 0)\n");
    fprintf(stderr,"  -M\thigher random number (default 100)\n");
    fprintf(stderr,"\n");
    fprintf(stderr,"  -method\tmethod of handling extremes (default 1)\n");
    fprintf(stderr,"\t\t0: Reflex\n");
    fprintf(stderr,"\t\t1: Reject\n");
    fprintf(stderr,"\t\t2: Portal\n");
    exit(1);
}

void *arghandler(int argc, const char *argv[])
{
    int i;
    void **a;
    a=malloc(6*sizeof(void *));
    a[0]=malloc(sizeof(long int));  *(long int *)a[0]=100000;
    a[1]=malloc(sizeof(double));    *(double *)a[1]=1;
    a[2]=malloc(sizeof(int));       *(int *)a[2]=10;
    a[3]=malloc(sizeof(int));       *(int *)a[3]=0;
    a[4]=malloc(sizeof(int));       *(int *)a[4]=100;
    a[5]=malloc(sizeof(char));      *(char *)a[5]=100;
    for(i = 1; i < argc; i++)
    {
        if(!strcmp(argv[i],"-h"))
            usage(argv[0]);
        else if(!strcmp(argv[i],"-A"))
        {
            if(i+1==argc)
                usage(argv[0]);
            else
            {
                i++;
                if(!sscanf(argv[i],"%li",a[0]))
                    usage(argv[0]);
            }
        }
        else if(!strcmp(argv[i],"-eps"))
        {
            if(i+1==argc)
                usage(argv[0]);
            else
            {
                i++;
                if(!sscanf(argv[i],"%lf",a[1]))
                    usage(argv[0]);
            }
        }
        else if(!strcmp(argv[i],"-I"))
        {
            if(i+1==argc)
                usage(argv[0]);
            else
            {
                i++;
                if(!sscanf(argv[i],"%i",a[2]))
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
                if(!sscanf(argv[i],"%i",a[3]))
                    usage(argv[0]);
            }
        }
        else if(!strcmp(argv[i],"-M"))
        {
            if(i+1==argc)
                usage(argv[0]);
            else
            {
                i++;
                if(!sscanf(argv[i],"%i",a[4]))
                    usage(argv[0]);
            }
        }
        else if(!strcmp(argv[i],"-method"))
        {
            if(i+1==argc)
                usage(argv[0]);
            else
            {
                i++;
                if(!sscanf(argv[i],"%i",a[4]))
                    usage(argv[0]);
            }
        }
        else usage(argv[0]);
    }
    return a;
}
