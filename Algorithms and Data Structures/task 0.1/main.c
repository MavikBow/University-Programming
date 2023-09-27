#include <stdio.h>
#include <stdlib.h>

int size;
int* array;
int requests;
int target;

int i = 0;

int answers[3];

int binary_search(int target)
{
    int left = 0;
    int right = size;

    int middle;

    while(left < right)
    {
        middle = (left + right) >> 1;

        if (array[middle] == target)
        {
            return 1;
        }
        if (array[middle] > target)
        {
            right = middle;
        }
        else
        {
            left = middle + 1;
        }
    }

    return 0;
}

int lower_bound(int target)
{
    int left = 0;
    int right = size;

    int middle;

    while(left < right)
    {
        middle = (left + right) >> 1;

        if (array[middle] >= target)
        {
            right = middle;
        }
        else
        {
            left = middle + 1;
        }
    }

    return left;
}

int upper_bound(int target)
{
    int left = 0;
    int right = size;

    int middle;

    while(left < right)
    {
        middle = (left + right) >> 1;

        if (array[middle] > target)
        {
            right = middle;
        }
        else
        {
            left = middle + 1;
        }
    }

    return left;
}

void search(int target)
{
    answers[0] = binary_search(target);
    answers[1] = lower_bound(target);
    answers[2] = upper_bound(target);

    printf("%d %d %d\n", answers[0], answers[1], answers[2]);
}

int main()
{
    scanf("%d ", &size);

    array = (int*) malloc(size * sizeof(int));

    for(i = 0; i < size; i++)
    {
        scanf("%d", &array[i]);
    }

    scanf("%d ", &requests);

    for(i = 0; i < requests; i++)
    {
        scanf("%d", &target);
        search(target);
    }

    free(array);

    return 0;
}