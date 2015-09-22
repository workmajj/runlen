#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ENCODE "encode"
#define DECODE "decode"

#define ASCII_0 48
#define ASCII_9 57
#define ASCII_A 65
#define ASCII_Z 90

#define BUF_SIZE 8

void encode(FILE *fin, FILE *fout)
{
    assert(fin != NULL);
    assert(fout != NULL);

    char curr, last;

    int count = 0;

    while ((curr = fgetc(fin)) != EOF) {
        if (!isupper(curr)) continue;

        if (count > 0 && curr != last) {
            if (count > 1) fprintf(fout, "%d", count);

            fputc(last, fout);
            count = 1;
        }
        else {
            count++;
        }

        last = curr;
    }

    if (count > 0) {
        if (count > 1) fprintf(fout, "%d", count);

        fputc(last, fout);
        fputc('\n', fout);
    }
}

void decode(FILE *fin, FILE *fout)
{
    assert(fin != NULL);
    assert(fout != NULL);

    char curr, last;

    char buf[BUF_SIZE] = {0};
    int buf_idx = 0;

    while ((curr = fgetc(fin)) != EOF) {
        if (!isupper(curr) && !isdigit(curr)) continue;

        if (isupper(curr) && !isdigit(last)) {
            fputc(curr, fout);
        }
        else if (isupper(curr) && isdigit(last)) {
            for (int i = 0; i < strtol(buf, NULL, 10); i++) {
                fputc(curr, fout);
            }

            memset(&buf, 0, BUF_SIZE);
            buf_idx = 0;
        }
        else {
            if (buf_idx + 1 == BUF_SIZE) {
                fprintf(stderr, "multiplier exceeds buffer\n");
                exit(1);
            }

            buf[buf_idx] = curr;
            buf_idx++;
        }

        last = curr;
    }

    fputc('\n', fout);

    if (isdigit(last)) {
        fprintf(stderr, "malformed input ends with number\n");
        exit(1);
    }
}

void usage(const char *s)
{
    fprintf(stderr, "usage: %s ["ENCODE"|"DECODE"] <file_in> <file_out>\n", s);
    exit(1);
}

int main(int argc, char *argv[])
{
    if (argc != 4) usage(argv[0]);

    bool f_encode = (strncmp(argv[1], ENCODE, strlen(ENCODE)) == 0);
    bool f_decode = (strncmp(argv[1], DECODE, strlen(DECODE)) == 0);

    if (!f_encode && !f_decode) usage(argv[0]);
    if (f_encode && f_decode) assert(0 && "not reached");

    FILE *fin = fopen(argv[2], "r");
    if (!fin) {
        fprintf(stderr, "error opening file %s for input\n", argv[2]);
        exit(1);
    }

    FILE *fout = fopen(argv[3], "w");
    if (!fout) {
        fprintf(stderr, "error opening file %s for output\n", argv[3]);
        exit(1);
    }

    if (f_encode) {
        encode(fin, fout);
    }
    else if (f_decode){
        decode(fin, fout);
    }
    else {
        assert(0 && "not reached");
    }

    fclose(fin);
    fclose(fout);

    return 0;
}
