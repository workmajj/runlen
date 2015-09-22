#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ENCODE "encode"
#define DECODE "decode"

#define BUF_SIZE 8 // to build multiplier strs when decoding

void rl_encode(FILE *fin, FILE *fout)
{
    assert(fin != NULL);
    assert(fout != NULL);

    char curr = -1;
    char last = -1;

    int run_len = 0;

    while ((curr = fgetc(fin)) != EOF) {
        if (!isupper(curr)) continue;

        if (run_len > 0 && curr != last) {
            if (run_len > 1) fprintf(fout, "%d", run_len);
            fputc(last, fout);

            run_len = 1;
        }
        else {
            run_len++;
        }

        last = curr;
    }

    if (run_len > 0) {
        if (run_len > 1) fprintf(fout, "%d", run_len);
        fputc(last, fout);
    }

    fputc('\n', fout);
}

void rl_decode(FILE *fin, FILE *fout)
{
    assert(fin != NULL);
    assert(fout != NULL);

    char curr = -1;
    char last = -1;

    char buf[BUF_SIZE] = {0};
    int buf_idx = 0;

    while ((curr = fgetc(fin)) != EOF) {
        if (!isupper(curr) && !isdigit(curr)) continue;

        if (isupper(curr) && (isupper(last) || last == -1)) {
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
            if (buf_idx + 1 >= BUF_SIZE) {
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
}

int main(int argc, char *argv[])
{
    if (argc != 4) {
        usage(argv[0]);
        exit(1);
    }

    bool f_encode = (strncmp(argv[1], ENCODE, strlen(ENCODE)) == 0);
    bool f_decode = (strncmp(argv[1], DECODE, strlen(DECODE)) == 0);

    if (f_encode && f_decode) assert(0 && "not reached");

    if (!f_encode && !f_decode) {
        usage(argv[0]);
        exit(1);
    }

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
        rl_encode(fin, fout);
    }
    else {
        rl_decode(fin, fout);
    }

    fclose(fin);
    fclose(fout);

    return 0;
}
