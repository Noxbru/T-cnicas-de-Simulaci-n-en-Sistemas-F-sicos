#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "args.c"

int main(int argc, const char *argv[])
{
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

    srand(time(NULL));
    for(i = 0; i < numb; i++)
    {
        r=min+(int)((max-min)*((float)rand()/RAND_MAX));
        frecs[(int)((r-min)/del)]++;
    }

    for(i = 0; i < ints; i++)
        printf("%d\t%d\n",i,frecs[i]);

    return 0;
}
