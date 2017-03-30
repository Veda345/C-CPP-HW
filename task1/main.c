#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char* argv[]) {
    int n;
    scanf("%d", &n);
    int **table = (int **) malloc(n * sizeof(int *));
    for (int i = 0; i < n; ++i)
        table[i] = (int *) malloc(n * sizeof(int));

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            table[i][j] = (i + 1) * (j + 1);

    int x1, y1, x2, y2;
    while (1) {
        scanf("%d", &x1);
        if (x1 == 0) {
            break;
        }
        scanf("%d %d %d", &y1, &x2, &y2);

        for (int i = x1 - 1; i < x2; i++) {
            for (int j = y1 - 1; j < y2; j++)
                printf("%d ", table[i][j]);
            printf("\n");
        }
    }

    for (int i = 0; i < n; ++i)
        free(table[i]);
    free(table);

    return 0;
}