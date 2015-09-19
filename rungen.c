#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_CHARS 8192

#define ASCII_A 65
#define ASCII_Z 90

#define RUN_MAX 16

int main(int argc, char *argv[])
{
    if (argc != 2) {
        printf("usage: %s <file_out>\n", argv[0]);
        return 1;
    }

    FILE *fp = fopen(argv[1], "w");
    if (!fp) {
        printf("error opening file %s for output\n", argv[1]);
        return 1;
    }

    // N.B. (rand() % N) isn't the greatest technique

    srand(time(NULL));

    size_t num = 0;
    while (num < NUM_CHARS) {
        char c = ASCII_A + (rand() % (ASCII_Z - ASCII_A + 1));
        size_t run_len = 1 + (rand() % RUN_MAX);

        for (size_t i = 0; num < NUM_CHARS && i < run_len; i++) {
            fprintf(fp, "%c", c);
            num++;
        }
    }

    fprintf(fp, "\n"); // NUM_CHARS + 1
    fclose(fp);

    return 0;
}
