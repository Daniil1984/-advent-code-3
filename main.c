#include <stdio.h>
#include <stdlib.h>
int compare(const void *x, const void *y);
int sum_distances(int point, int *array, int size, int (*distance)(const int, const int));
int min(int a, int b);
int module(int a, int b);
int arithmetic_dist(int a, int b);

int main(int argc, char *argv[argc])
{   
    if (argc != 2) {
        return -1;
    }
    FILE *input = fopen(argv[1], "r");
    if (input == NULL) {
        return -1;
    }
    int number;
    int size = 0;
    while (fscanf(input, "%d", &number) == 1) {
        char c;
        fscanf(input, "%c", &c);
        size++;
    }
    rewind(input);
    int *array = malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) {
        fscanf(input, "%d", &number);
        char c;
        fscanf(input, "%c", &c);
        array[i] = number;
    }
    qsort(array, size, sizeof(int), compare);
    int res1 = sum_distances(array[size / 2], array, size, module);
    int res2 = sum_distances(array[size / 2] - 1, array, size, module);
    int res3 = sum_distances(array[size / 2] + 1, array, size, module);
    printf("%d\n", min(res1, min(res2, res3)));
    int min_dist = sum_distances(array[size / 2], array, size, arithmetic_dist);
    // слева от середины искать нет смысла
    for (int i = array[size / 2] + 1; i < array[size - 1]; i++) {
        int res = sum_distances(i, array, size, arithmetic_dist);
        if (res <= min_dist) {
            min_dist = res;
        } else {
            break;
        }
    }
    printf("%d\n", min_dist);
    fclose(input);
    free(array);
    return 0;
}

int compare(const void *x, const void *y)
{
    return *(int *)x - *(int *)y;
}

int sum_distances(int point, int *array, int size, int (*distance)(const int, const int))
{
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += distance(point, array[i]);
    }
    return sum;
}

int min(int a, int b)
{
    if (a >= b) {
        return b;
    }
    return a;
}

int module(int a, int b)
{
    return abs(a - b);
}

int arithmetic_dist(int a, int b)
{
    return ((1 + abs(a - b)) * (abs(a - b))) / 2;
}
