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
    void **args;
    args=arghandler(argc,argv);
    int i,j;
    int min, max;
    min=*(int *)args[0];
    max=*(int *)args[1];

    int x,y,z;
    int **frecs;
    frecs=malloc((max-min)*sizeof(int *));
    for(i = 0; i < max-min; i++)
        frecs[i]=calloc(max-min,sizeof(int));

    srand(time(NULL));
    for(i = 0; i < 10000; i++)
    {
        x=min+(int)((max-min)*((float)rand()/RAND_MAX));
        y=min+(int)((max-min)*((float)rand()/RAND_MAX));
        //z=min+(int)((max-min)*((float)rand()/RAND_MAX));
        frecs[x][y]++;
        //printf("%d\t%d\n",x,y);
    }
    for(i = 0; i < max-min; i++)
        for(j = 0; j < max-min; j++)
            printf("%d\t%d\t%d\n",i,j,frecs[i][j]);

    return 0;
}
