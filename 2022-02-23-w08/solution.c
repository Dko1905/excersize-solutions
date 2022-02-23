#include <stdio.h>
/* Allow custom locale, technically breaks the rules. */
#include <locale.h>

const char *progname = "";
/* Custom pow because we can't use math.h, called pow1 to stop possible conflict. */
double pow1(double n, unsigned p);

int main(int argc, const char **argv)
{
    int ret = 0;
    progname = argv[0];
    setlocale(LC_ALL, ""); /* Technically breaks the rules. */

    /* argc:
     * [0] = progname
     * [1] = x
     * [2] = n1
     * [x] = nx
     */
    if (argc < 3) {
        fprintf(stderr, "%s: Not enough arguments\n", progname);
        return 1;
    }

    double x = 0, n = 0, r = 0;

    ret = sscanf(argv[1], "%lf", &x);
    if (ret != 1) {
        fprintf(stderr, "%s: Invalid double\n", progname);
        return 1;
    }

    /* n1 is a special case. */
    ret = sscanf(argv[2], "%lf", &n);
    if (ret != 1) {
        fprintf(stderr, "%s: Invalid double\n", progname);
        return 1;
    }
    r = n; /* x ^ 0 is 1, y * 1 is y. */

    for (int i = 3; i < argc; i++) {
        ret = sscanf(argv[i], "%lf", &n);
        if (ret != 1) {
            fprintf(stderr, "%s: Invalid double\n", progname);
            return 1;
        }

        /* Change -x to 1 if you follow rules, and to 2 if you follow example. */
        r += n * pow1(x, i - 2);
    }

    printf("%.2lf\n", r);

    return 0;
}

double pow1(double n, unsigned p)
{
    double result = n;
    while (--p > 0) {
        result *= n;
    }
    return result;
}
