#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

static const char *next_token(const char *q,  int sep) {
    if (q)
        q = strchr(q, sep);
    if (q)
        q++;

    return q;
}

static int next_num(const char *str, char **end, int *result) {
    if (!str || *str == '\0' || !isdigit(*str))
        return -1;

    *result = strtoul(str, end, 10);
    if (str == *end)
        return -1;

    return 0;
}

/* set current thread cpu affinity to cpu list, this function works like
 * taskset command (actually cpulist parsing logic reference to util-linux).
 * example of this function: "0,2,3", "0,2-3", "0-20:2". */
void setcpuaffinity(const char *cpulist) {
    const char *p, *q;
    char *end = NULL;

    q = cpulist;
    while (p = q, q = next_token(q, ','), p) {
        int a, b, s;
        const char *c1, *c2;

        if (next_num(p, &end, &a) != 0)
            return;

        b = a;
        s = 1;
        p = end;

        c1 = next_token(p, '-');
        c2 = next_token(p, ',');

        if (c1 != NULL && (c2 == NULL || c1 < c2)) {
            if (next_num(c1, &end, &b) != 0)
                return;

            c1 = end && *end ? next_token(end, ':') : NULL;
            if (c1 != NULL && (c2 == NULL || c1 < c2)) {
                if (next_num(c1, &end, &s) != 0)
                    return;

                if (s == 0)
                    return;
            }
        }

        if ((a > b))
            return;

        while (a <= b) {
            a += s;
            printf("%d ", a);
        }
    }

    if (end && *end)
        return;

}

int main () {
    setcpuaffinity("0-20:2");
}
