#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STR_ENCODE "encode"
#define STR_DECODE "decode"

#define ASCII_0 48
#define ASCII_9 57
#define ASCII_A 65
#define ASCII_Z 90

#define BUF_SIZE 8

/* util */

bool is_number(char c) { return (c >= ASCII_0 && c <= ASCII_9); }
bool is_letter(char c) { return (c >= ASCII_A && c <= ASCII_Z); }

/* encode */

void rl_encode(FILE *fin, FILE *fout)
{
    assert(fin != NULL);
    assert(fout != NULL);

    char curr, last;

    size_t count = 0;

    while ((curr = fgetc(fin)) != EOF) {
        if (!is_letter(curr)) continue;

        if (count > 0 && curr != last) {
            if (count == 1) fprintf(fout, "%c", last);
            else fprintf(fout, "%zu%c", count, last);

            count = 1;
        }
        else {
            count++;
        }

        last = curr;
    }

    if (count > 0) {
        if (count == 1) fprintf(fout, "%c\n", last);
        else fprintf(fout, "%zu%c\n", count, last);
    }

}

/* decode */

void close_and_exit(FILE *fin, FILE *fout, char *s)
{
    fclose(fin);
    fclose(fout);

    printf("%s\n", s);

    exit(1);
}

void rl_decode(FILE *fin, FILE *fout)
{
    assert(fin != NULL);
    assert(fout != NULL);

    char curr, last;

    char buf[BUF_SIZE] = {0};
    size_t buf_idx = 0;

    while ((curr = fgetc(fin)) != EOF) {
        if (!is_letter(curr) && !is_number(curr)) continue;

        if (is_letter(curr) && !is_number(last)) {
            fprintf(fout, "%c", curr);
        }
        else if (is_letter(curr) && is_number(last)) {
            for (size_t i = 0; i < atoi(buf); i++) fprintf(fout, "%c", curr);

            memset(&buf, 0, BUF_SIZE);
            buf_idx = 0;
        }
        else {
            if (buf_idx + 1 == BUF_SIZE) {
                close_and_exit(fin, fout, "multiplier exceeds buffer size");
            }

            buf[buf_idx] = curr;
            buf_idx++;
        }

        last = curr;
    }

    if (is_number(last)) {
        close_and_exit(fin, fout, "malformed input file ends with number");
    }

    fprintf(fout, "\n");
}

/* main */

int usage(char *s)
{
    printf("usage: %s ["STR_ENCODE"|"STR_DECODE"] <file_in> <file_out>\n", s);

    return 1;
}

int main(int argc, char *argv[])
{
    if (argc != 4) return usage(argv[0]);

    bool f_encode = (strncmp(argv[1], STR_ENCODE, strlen(STR_ENCODE)) == 0);
    bool f_decode = (strncmp(argv[1], STR_DECODE, strlen(STR_DECODE)) == 0);

    if (!f_encode && !f_decode) return usage(argv[0]);
    if (f_encode && f_decode) assert(0 && "not reached");

    FILE *fin = fopen(argv[2], "r");
    if (!fin) {
        printf("error opening file %s for input\n", argv[2]);
        return 1;
    }

    FILE *fout = fopen(argv[3], "w");
    if (!fout) {
        fclose(fin);

        printf("error opening file %s for output\n", argv[3]);
        return 1;
    }

    if (f_encode) rl_encode(fin, fout);
    else if (f_decode) rl_decode(fin, fout);
    else assert(0 && "not reached");

    fclose(fin);
    fclose(fout);

    return 0;
}
