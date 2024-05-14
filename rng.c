#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    FILE *file;
    int i;
    srand(time(NULL));

    file = fopen("requests.txt", "w");
    if (file == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    for (i = 0; i < 1000; i++) {
        int num = rand() % 5000; 
        fprintf(file, "%d\n", num);
    }

    fclose(file);
    return 0;
}