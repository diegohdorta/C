#include <stdio.h>

#include "global.h"

static char reverse[64];

int main(void)
{
    unsigned i, x, y;
    Generate6BitTable();

    for (i = 0; i < 64; i++)
        reverse[LFSR6bits[i]] = i;

    printf("const static char REVERSE_LFSR_6BITS[64] = {\n");
    printf("\t%d%n", reverse[0], &x);

    for (i = 1; i < 64; i++) {
        if (x > 67) {
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
