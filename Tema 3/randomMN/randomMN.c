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
    int min, max;
    long int numb;
    numb=*(long int *)args[0];
    max=*(int *)args[1];
    min=*(int *)args[2];

    for(i = 0; i < numb; i++)
        printf("%i\n",min+(int)((max-min)*((float)rand()/RAND_MAX)));
    return 0;
}
