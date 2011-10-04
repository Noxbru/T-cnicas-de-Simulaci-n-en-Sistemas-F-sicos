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
#include <time.h>
#include "args.c"

int main(int argc, const char *argv[])
{
    srand(time(NULL));
    void **args;
    args=arghandler(argc,argv);
    int i;
    int min, max, ints;
    long int numb;
    numb=*(long int *)args[0];
    ints=*(int *)args[1];
    min=*(int *)args[2];
    max=*(int *)args[3];

    int r;
    int *frecs;
    frecs=calloc(ints,sizeof(int));

    float del=(max-min)/ints;
    float x, dx;
    x=min+(max-min)*((float)rand()/RAND_MAX);

    for(i = 0; i < numb; i++)
    {
        dx=-del+(2*del*((float)rand()/RAND_MAX));
        if(x+dx<min||x+dx>max)
        {
            if(x+dx<min)
                x=max+(dx+x-min);
            else
                x=min+(dx+x-max);
            frecs[(int)((x-min)/del)]++;
        }
        else
        {
            x+=dx;
            frecs[(int)((x-min)/del)]++;
        }
    }

    for(i = 0; i < ints; i++)
        printf("%d\t%d\n",i,frecs[i]);

    return 0;
}
