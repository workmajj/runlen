#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_CHARS 8192 // size of output file

#define ASCII_A 65
#define ASCII_Z 90

#define RUN_LEN_MAX 16

int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "usage: %s <file_out>\n", argv[0]);
        exit(1);
    }

    FILE *fp = fopen(argv[1], "w");
    if (!fp) {
        fprintf(stderr, "error opening file %s for output\n", argv[1]);
        exit(1);
    }

    srandom(time(NULL));

    int num = 0;

    while (num < NUM_CHARS) {
        int run_len = 1 + (random() % RUN_LEN_MAX);
        char c = ASCII_A + (random() % (ASCII_Z - ASCII_A + 1));

        for (int i = 0; i < run_len && num < NUM_CHARS; i++, num++) {
            fputc(c, fp);
        }
    }

    fputc('\n', fp); // NUM_CHARS + 1
    fclose(fp);

    return 0;
}
