#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void mergeSort(int*, int, int*);

int main(int argc, char **argv)
{
    int size = atoi(argv[1]);
    int* array = malloc(sizeof(int)*size);
    int* temp = malloc(sizeof(int)*size);
    int i;
    int rnd;

    printf("Unsorted numbers: ");
    srand(time(NULL));

    for(i = 0; i < size; i++)
    {
        rnd = rand() % size;
        array[i] = rnd;
    
        if (argc == 2)
            printf("%d, ", rnd);
    }
    printf("\n\n ... Starting to Sort ... \n\n");

    mergeSort(array, size, temp);

    if (argc == 2)
    {
        printf("Sorted numbers: ");
        for(i = 0; i < size; i++)
        {
            printf("%d, ", array[i]);
        }
        putchar('\n');
    }
    
    return 0;
}

void mergeSort(int* array, int size, int* temp)
{
    if (size <= 1) return;

    mergeSort(array, size/2, temp);
    mergeSort(array + size/2, size - size/2, temp);

    int i = 0, j = size/2;
    int t = 0;

    while (i < size/2 && j < size)
    {
        if (array[i] <= array[j])
        {
            temp[t] = array[i];
            i++;
        }
        else
        {
            temp[t] = array[j];
            j++;
        }
        t++;
    }

    while (i < size/2)
    {
        temp[t++] = array[i++];
    }

    while (j < size)
    {
        temp[t++] = array[j++];
    }

    memcpy(array, temp, size*sizeof(int));
}
