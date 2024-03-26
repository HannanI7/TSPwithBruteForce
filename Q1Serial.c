//K214934 Hannan Irfan 6E

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define NUM_CITIES 6

int graph[NUM_CITIES][NUM_CITIES] = 
{
    {0, 12, 8, 19, 15, 21},
    {12, 0, 17, 11, 14, 9},
    {8, 17, 0, 20, 23, 13},
    {19, 11, 20, 0, 18, 16},
    {15, 14, 23, 18, 0, 25},
    {21, 9, 13, 16, 25, 0}
};

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void reverse(int arr[], int start, int end)
{
    while(start < end)
    {
        swap(&arr[start], &arr[end]);
        start++;
        end--;
    }
}

int next_permutation(int arr[], int n)
{
    int i = n - 2;
    while(i >= 0 && arr[i] >= arr[i + 1])
    {
        i--;
    }
 
    if(i < 0)
    {
        return 0;
    }
 
    int j = n - 1;
    while(arr[j] <= arr[i])
    {
        j--;
    }
 
    swap(&arr[i], &arr[j]);
    reverse(arr, i + 1, n - 1);
 
    return 1;
}

int search(int cities[], int num_cities, int start)
{
    int mindist = INT_MAX;
    int *permutation = (int *)malloc(num_cities * sizeof(int));
 
    for(int i = 0; i < num_cities; i++)
    {
        permutation[i] = cities[i];
    }
 
    do
    {
        if(permutation[0] == start)
        {
            int total_distance = 0;
            for(int i = 0; i < num_cities - 1; i++)
            {
                total_distance += graph[permutation[i]][permutation[i + 1]];
            }
            total_distance += graph[permutation[num_cities - 1]][permutation[0]];
            if(total_distance < mindist)
            {
                mindist = total_distance;
            }
        }
    } while(next_permutation(permutation, num_cities));
 
    free(permutation);

    return mindist;
}

int main()
{
    int overall_min_dist = INT_MAX;

    for(int start_city = 0; start_city < NUM_CITIES; start_city++)
    {
        int* cities = (int*)malloc(NUM_CITIES * sizeof(int));
        for (int i = 0; i < NUM_CITIES; i++) {
            cities[i] = i;
        }

        int mindist = search(cities, NUM_CITIES, start_city);
        printf("Process with start city %d has shortest path: %d\n", start_city, mindist);
        if (mindist < overall_min_dist) {
            overall_min_dist = mindist;
        }

        free(cities);
    }

    printf("Overall Shortest Path: %d\n", overall_min_dist);

    return 0;
}

