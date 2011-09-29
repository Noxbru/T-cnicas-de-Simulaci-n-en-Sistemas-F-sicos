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

void usage(const char *name)
{
    fprintf(stderr, "USAGE:\n");
    fprintf(stderr, "  %s [OPTIONS]\n",name);
    fprintf(stderr,"\n");
    fprintf(stderr, "  -h\tshow this help\n");
    fprintf(stderr, "  -K\tconstant of thermal conductivity (default 0.05)\n");
    fprintf(stderr, "  -L\tlength of the bar (default 1)\n");
    fprintf(stderr, "  -N\tnumber of divisions of the bar (default 100)\n");
    fprintf(stderr, "  -T0\ttemperature of one extreme of the bar (default 10)\n");
    fprintf(stderr, "  -T1\ttemperature of the other extreme of the bar (default 100)\n");
    exit(1);
}

void *arghandler(int argc, const char *argv[])
{
    int i;
    void **a;
    a=malloc(5*sizeof(void *));
    a[0]=malloc(sizeof(double));       *(double *)a[0]=0.05;
    a[1]=malloc(sizeof(double));       *(double *)a[1]=1;
    a[2]=malloc(sizeof(unsigned int)); *(unsigned int *)a[2]=100;
    a[3]=malloc(sizeof(double));       *(double *)a[3]=10;
    a[4]=malloc(sizeof(double));       *(double *)a[4]=100;
    for(i = 1; i < argc; i++)
    {
        if(!strcmp(argv[i],"-h"))
            usage(argv[0]);
        else if(!strcmp(argv[i],"-K"))
        {
            if(i+1==argc)
                usage(argv[0]);
            else
            {
                i++;
                if(!sscanf(argv[i],"%lf",a[0]))
                    usage(argv[0]);
            }
        }
        else if(!strcmp(argv[i],"-L"))
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
        else if(!strcmp(argv[i],"-N"))
        {
            if(i+1==argc)
                usage(argv[0]);
            else
            {
                i++;
                if(!sscanf(argv[i],"%u",a[2]))
                    usage(argv[0]);
            }
        }
        else if(!strcmp(argv[i],"-T0"))
        {
            if(i+1==argc)
                usage(argv[0]);
            else
            {
                i++;
                if(!sscanf(argv[i],"%lf",a[3]))
                    usage(argv[0]);
            }
        }
        else if(!strcmp(argv[i],"-T1"))
        {
            if(i+1==argc)
                usage(argv[0]);
            else
            {
                i++;
                if(!sscanf(argv[i],"%lf",a[4]))
                    usage(argv[0]);
            }
        }
        else usage(argv[0]);
    }
    return a;
}
