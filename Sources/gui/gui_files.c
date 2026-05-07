#include "gui_files.h"
#include "../alloc.h"
#include <string.h>

void print_lines_tab(char **lines, int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%s\n", lines[i]);
    }
}

static void remove_spaces(char *line)
{
    int i = 0, j = 0;
    while (line[i] != '\0')
    {
        if (line[i] != ' ' && line[i] != '\n' && line[i] != '\t')
        {
            line[j++] = line[i];
        }
        i++;
    }
    line[j] = '\0';
}

char **read_lines(const char *filename, int *size)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        fprintf(stderr, "Error opening file: %s\n", filename);
        return NULL;
    }

    char **lines;
    int lines_size = 1;
    int nb_lines = 0;
    MALLOC(lines, 1);

    char buffer[256];
    while (fscanf(file, "%255[^;]; ", buffer) == 1)
    {
        remove_spaces(buffer);
        if (nb_lines >= lines_size)
        {
            lines_size <<= 1; // Double the size of the array
            REALLOC(lines, lines_size);
        }
        MALLOC(lines[nb_lines], strlen(buffer) + 1);
        strcpy(lines[nb_lines], buffer); // Copy the line into the allocated memory
        nb_lines++;
    }
    REALLOC(lines, nb_lines); // Resize the array to the actual number of lines read
    *size = nb_lines;
    fclose(file);
    return lines;
}

void free_lines_tab(char **lines, int size)
{
    for (int i = 0; i < size; i++)
    {
        free(lines[i]);
    }
    free(lines);
}

bool write_lines(char **lines, int size, const char *filename)
{
    if (lines == NULL || size < 0 || filename == NULL)
    {
        fprintf(stderr, "Invalid input to write_lines.\n");
        return false;
    }

    FILE *file = fopen(filename, "w");
    if (file == NULL)
    {
        fprintf(stderr, "Error opening file: %s\n", filename);
        return false;
    }

    for (int i = 0; i < size; i++)
    {
        fprintf(file, "%s;\n", lines[i]);
    }
    fclose(file);
    return true;
}
