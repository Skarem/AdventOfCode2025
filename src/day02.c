#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* read_input(FILE *file)
{
        fseek(file, 0, SEEK_END);
        long size = ftell(file);
        rewind(file);

        char *buf = malloc(size + 1);
        if (!buf) exit(1);

        fread(buf, 1, size, file);
        buf[size] = '\0';
        return buf;
}

int split(char **line, long long *a, long long *b)
{
        char *comma = strchr(*line, ',');
        if (comma) *comma = '\0';

        char *dash = strchr(*line, '-');
        if (!dash) return -1;
        *dash = '\0';

        *a = strtoll(*line, NULL, 10);
        *b = strtoll(dash + 1, NULL, 10);

        if (!comma) return 1;
        *line = comma + 1;
        return 0;
}

long long pow_10ll(int n)
{
        long long value = 1;
        while (n-- > 0) {
                value *= 10LL;
        }
        return value;
}

int len_num(long long n)
{
        int len = 1;
        while (n >= 10) {
                n /= 10;
                len++;
        }
        return len;
}

int main(void)
{
        const char file_path[] = "input/day02.txt";
        FILE *file = fopen(file_path, "r");
        if (!file) {
                perror("Failed to open input file");
                return 1;
        }

        char *line = read_input(file);
        fclose(file);

        long long sum = 0;
        
        while (*line) {
                long long a, b;
                int status = split(&line, &a, &b);
                int max_len = len_num(b);
                
                // printf("%lld %lld\n", a, b);

                for (int L = 2; L <= max_len; L += 2) {
                        int k = L / 2;
                        // printf("%d\n", k);

                        long long pow10k = pow_10ll(k);
                        long long M = pow10k + 1;

                        long long h_raw_min = pow_10ll(k - 1);
                        long long h_raw_max = pow_10ll(k) - 1;

                        long long h_min = (a + M - 1) / M;
                        long long h_max = b / M;

                        if (h_min < h_raw_min) h_min = h_raw_min;
                        if (h_max > h_raw_max) h_max = h_raw_max;
                        // printf("%lld - %lld\n", h_min, h_max);

                        if (h_min > h_max) continue;

                        for (long long h = h_min; h <= h_max; h++) {
                                long long x = pow10k * h + h;
                                // printf("%lld\n", x);
                                
                                if (x >= a && x <= b) {
                                        sum += x;
                                }
                        } 
                }
                if (status != 0) break;
        }

        printf("Sum part 1: %lld\n", sum);
        return 0;
}


