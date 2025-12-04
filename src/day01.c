#include <stdio.h>
#include <stdlib.h>

int main()
{
        const char *file_path = "input/day01.txt";
        FILE *file = fopen(file_path, "r");
        if (!file) {
                perror("Failed to open input file");
                return 1;
        }

        char line_buffer[32];

        enum { LEFT = -1, RIGHT = 1 };
        static const int DIAL_MOD = 100;

        int dial = 50;
        int password_part1 = 0;
        int password_part2 = 0;

        while (fgets(line_buffer, sizeof(line_buffer), file)) {
                char dirChar;
                int distance;

                if (sscanf(line_buffer, " %c%d", &dirChar, &distance) != 2) {
                        fprintf(stderr, "Invalid line: %s\n", line_buffer);
                        continue;
                }

                int direction = (dirChar == 'L') ? LEFT : RIGHT;

                for (int i = 0; i < distance; i++) {
                        dial = (dial + direction + DIAL_MOD) % DIAL_MOD;
                        if (dial == 0) {
                                password_part2++;
                        }
                }
                
                if (dial == 0) {
                        password_part1++;
                }
        }

        printf("Password for part 1: %d\n", password_part1);
        printf("Password for part 2: %d\n", password_part2);

        fclose(file);
        return 0;
}