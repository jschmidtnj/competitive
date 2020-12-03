#include <bits/stdc++.h>

using namespace std;

size_t count_trees(size_t slope_x, size_t slope_y, size_t length, char *data)
{
    size_t count = 0;
    size_t x = 0;
    size_t y = 0;

    while (x % 31 + y * 32 <= length)
    {
        if ('#' == data[(x % 31 + y * 32)])
            count++;
        x += slope_x;
        y += slope_y;
    }

    return count;
}

int main(int argc, char *args[])
{
    FILE *file = fopen("input.txt", "r");
    if (!file)
    {
        cout << "File could not be found" << endl;
        return -1;
    }

    fseek(file, 0L, SEEK_END);
    int length = ftell(file);
    rewind(file);

    char *data = (char *)calloc(length, sizeof(char));

    // read file into data
    if (fread(data, sizeof(char), length, file) == 0)
    {
        cout << "problem with reading file" << endl;
        return -1;
    }

    size_t part1 = count_trees(3, 1, length, data);
    size_t p2a = count_trees(1, 1, length, data);
    size_t p2b = count_trees(5, 1, length, data);
    size_t p2c = count_trees(7, 1, length, data);
    size_t p2d = count_trees(1, 2, length, data);

    printf("part 1: %ld\n%ld\n%ld\n%ld\n%ld\npart 2: %ld\n", part1, p2a, p2b, p2c, p2d, part1 * p2a * p2b * p2c * p2d);

    free(data);
    fclose(file);
}
