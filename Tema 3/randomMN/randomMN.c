#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "args.c"

int main(int argc, const char *argv[])
{
    void **args;
    args=arghandler(argc,argv);
    int i;
    int min, max;
    min=*(int *)args[0];
    max=*(int *)args[1];
    srand(time(NULL));
    for(i = 0; i < 100; i++)
    {
        printf("%i\n",min+(int)((max-min)*((float)rand()/RAND_MAX)));
    }
    return 0;
}
