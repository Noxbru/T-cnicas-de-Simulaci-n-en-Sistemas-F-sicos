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
    fprintf(stderr,"  -A\tnumber of aleatory numbers to generate (default 100000)\n");
    fprintf(stderr,"  -M\thigher random number (default 100)\n");
    fprintf(stderr,"  -N\tlower random number (default 0)\n");
    fprintf(stderr,"\n");
    fprintf(stderr,"NOTES:\n");
    fprintf(stderr,"  The number of intervals CAN'T be higher\n");
    fprintf(stderr,"  than the maximun number minus the minimun.\n");
    exit(1);
}

void *arghandler(int argc, const char *argv[])
{
    int i;
    void **a;
    a=malloc(3*sizeof(void *));
    a[0]=malloc(sizeof(long int));  *(long int *)a[0]=100000;
    a[1]=malloc(sizeof(int));       *(int *)a[1]=100;
    a[2]=malloc(sizeof(int));       *(int *)a[2]=0;
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
        else if(!strcmp(argv[i],"-M"))
        {
            if(i+1==argc)
                usage(argv[0]);
            else
            {
                i++;
                if(!sscanf(argv[i],"%i",a[1]))
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
                if(!sscanf(argv[i],"%i",a[2]))
                    usage(argv[0]);
            }
        }
        else usage(argv[0]);
    }
    if(*(int *)a[3]>*(int *)a[2])
        usage(argv[0]);
    return a;
}
