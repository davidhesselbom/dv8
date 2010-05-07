#include "utils.h"

/*
 * ---------------------------------------------------------------------------
 * Functions.
 * ---------------------------------------------------------------------------
 */

/*
 * XXXXXXXX
 */
void *
memcpy(void *dst, const void *src, size_t num_bytes)
{
    uint8_t       *dst_byte = dst;
    const uint8_t *src_byte = src;
    size_t i = 0;

    for (i = 0; i < num_bytes; ++i)
    {
        *dst_byte++ = *src_byte++;
    }

    return dst;
}

/*
 * XXXXX
 */
void *
memset(void *dst, int value, size_t num_bytes)
{
    uint8_t *dst_byte = dst;
    uint8_t byte_value = (uint8_t)value;
    size_t i = 0;

    for (i = 0; i < num_bytes; ++i)
    {
        dst_byte[i] = byte_value;
    }

    return dst;
}

/*
 * XXXXXXX
 */
size_t
strlen(const char *s)
{
    size_t len = 0;

    while (*s++)
    {
        ++len;
    }

    return len;
}

/*
 * XXXXXXXXX
 */
int
strcmp(const char *a, const char *b)
{
    while (*a && *b && (*a == *b))
    {
        ++a;
        ++b;
    }

    return *a - *b;
}

/*
 * XXXXXX
 */
char *
strcpy(char *dst, const char *src)
{
    char *dst_orig = dst;

    while (*src)
    {
        *dst++ = *src++;
    }
    *dst = '\0';

    return dst_orig;
}

/*
 * ---------------------------------------------------------------------------
 * Main for module testing.
 * ---------------------------------------------------------------------------
 */

/*
 * Define this constant and compile this and required modules, e.g.:
 *   gcc <this_module>.c <other_modules>.c -D<THIS_MODULE>_MAIN -Iinclude
 *   ./a.out
 */
#ifdef UTILS_MAIN

#include <stdio.h>

struct stuff
{
    double d[2];
    char str[10];
    int x;
};

int
main(void)
{
    /* Zero an array. */
    {
        double d[2];
        d[0] = 1.0;
        d[1] = 2.0;
        ZERO_ARRAY(d); /* Pass pointer to array. */
        printf("d[0]    = %f\n", d[0]);
        printf("d[1]    = %f\n", d[1]);
        printf("\n");
    }

    /* Zero a struct. */
    {
        struct stuff st;
        st.d[0]   = 1.0;
        st.d[1]   = 2.0;
        st.str[0] = 'O';
        st.str[1] = 'K';
        st.str[2] = '\n';
        st.str[3] = '\0';
        st.x      = -5;
        ZERO_STRUCT(&st); /* Pass pointer to struct. */
        printf("st.d[0] = %f\n",     st.d[0]);
        printf("st.d[1] = %f\n",     st.d[1]);
        printf("st.str  = \"%s\"\n", st.str);
        printf("st.x    = %d\n",     st.x);
        printf("\n");
    }

    /* Count array length. */
    {
        double d[3];
        printf("length  = %d\n", COUNT_ARRAY(d));
        printf("\n");
    }

    /* Test maximum. */
    {
        int a = 4;
        int b = 5;
        printf("max     = %d\n", MAX(a, b));
        printf("max     = %d\n", MAX(b, a));
        printf("\n");
    }

    /* Test strcmp. */
    {
        char a[] = "ab";
        char b[] = "abd";
        printf("strcmp  = %d\n", strcmp(a, b));
        printf("\n");
    }

    /* Test strlen. */
    {
        char a[] = "ab\n";
        char b[] = "";
        printf("strlen  = %d\n", strlen(a)); /* = 3 */
        printf("strlen  = %d\n", strlen(b)); /* = 0 */
        printf("\n");
    }

    /* Test strcpy. */
    {
        char dst[20] = "";
        char src[20] = "baba";
        printf("strcpy  = %s\n", strcpy(dst, src));
        printf("\n");
    }

    /* Test memset. */
    {
        char dst[20] = "";
        printf("memset  = %s\n", (char *)memset(dst, 97, sizeof(dst)-1));
        printf("\n");
    }

    /* Test FILL_ARRAY. */
    {
        int arr[2];
        size_t i = 0;
        uint8_t *byte = (uint8_t *)arr;
        FILL_ARRAY(arr, 0xba);
        printf("arr[0]  = %d\n", arr[0]);
        printf("arr[1]  = %d\n", arr[1]);
        for (i = 0; i < sizeof(arr); ++i)
        {
            printf("arr as byte[%d]  = 0x%x\n", i, *byte++);
        }
        printf("\n");
    }

    return 0;
}

#endif
