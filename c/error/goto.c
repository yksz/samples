#include <stdio.h>
#include <stdlib.h>

static void copy(FILE* src, FILE* dst)
{
    int c;
    while ((c = getc(src)) != EOF) {
        putc(c, dst);
    }
}

int main(int argc, char* argv[])
{
    if (argc <= 2) {
        fprintf(stderr, "usage: %s <src> <dst>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    char* src_name = argv[1];
    char* dst_name = argv[2];

    int result = EXIT_FAILURE;
    FILE *src, *dst;
    if ((src = fopen(src_name, "r")) == NULL) {
        goto SRC_ERROR;
    }
    if ((dst = fopen(dst_name, "w")) == NULL) {
        goto DST_ERROR;
    }

    copy(src, dst);
    result = EXIT_SUCCESS;

    fclose(dst);
DST_ERROR:
    fclose(src);
SRC_ERROR:
    return result;
}
