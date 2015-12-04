#include <stdio.h>

#include "global.h"

static unsigned reverse[4096];

int main(void)
{
    unsigned i, x, y;
    Generate12BitTable();

    for (i = 0; i < 4096; i++)
        reverse[LFSR12bits[i]] = i;

    printf("const static int32_t REVERSE_LFSR_12BITS[4096] = {\n");
    printf("\t%d%n", reverse[0], &x);

    for (i = 1; i < 4096; i++) {
        if (x > 65) {
            printf(",\n");
            printf("\t%d%n", reverse[i], &x);
        }
        else {
            printf(", %d%n", reverse[i], &y);
            x += y;
        }
    }

    printf("\n};\n");

    return 0;
}
