#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_BATTERIES_PART1     2
#define NUM_BATTERIES_PART2     12
#define MAX_LINE_LEN            128

static size_t line_length(const char *line)
{
        size_t len = strlen(line);
        if (len > 0 && line[len - 1] == '\n') {
                len--;
        }
        return len;
}

static long long digits_to_value(const int *best_n, const int count)
{
        long long value = 0;
        for (int i = 0; i < count; i++) {
                value = value * 10 + best_n[i];
        }
        return value;
}

static void reset_from_depth(int *best_n, const int depth, const int count)
{
        for (size_t i = depth; i < count; i++) {
                best_n[i] = 0;
        }
}

// Try to place digit 'n' at depth if improving current best_n[depth] value
static void biggest_number(
        int n,
        int *best_n,
        size_t pos,
        size_t len,
        int count,
        int depth)
{
        int remaining_positions = len - pos;
        int remaining_needed    = count - depth;

        // If n can be placed and is better than current at this depth
        if (n > best_n[depth] && remaining_positions >= remaining_needed) {
                best_n[depth] = n;
                reset_from_depth(best_n, depth + 1, count);
        }
        // Try deeper depth if remaining
        else if (depth < count - 1) {
                biggest_number(n, best_n, pos, len, count, depth + 1);
        }
}

long long max_bank_joltage(const char *line, size_t len, int count)
{
        int best_n[NUM_BATTERIES_PART2] = {0};

        for (size_t i = 0; i < len; i++) {
                int n = line[i] - '0';
                biggest_number(n, best_n, i, len, count, 0);        
        }

        return digits_to_value(best_n, count);
}

int main()
{
        const char *file_path = "input/day03.txt";

        FILE *file = fopen(file_path, "r");
        if (!file) {
                perror("Failed to open input file");
                return 1;
        }

        char line_buffer[MAX_LINE_LEN];
        long long sum_part1 = 0;
        long long sum_part2 = 0;

        while (fgets(line_buffer, sizeof(line_buffer), file) != NULL) {
                size_t len = line_length(line_buffer);
                
                sum_part1 += max_bank_joltage(line_buffer, len, NUM_BATTERIES_PART1);
                sum_part2 += max_bank_joltage(line_buffer, len, NUM_BATTERIES_PART2);
        }
        
        fclose(file);

        printf("Part 1: %lld\n", sum_part1);
        printf("Part 2: %lld\n", sum_part2);

        return 0;
}