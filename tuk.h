#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct pkgconfig
{
        char *name[50];
        char *giturl[100];
        char *directory[100];
};

#define BUFFER_SIZE 1000

int indexOf(FILE *fptr, const char *word, int *line, int *col)
{
    char str[BUFFER_SIZE];
    char *pos;

    *line = -1;
    *col  = -1;

    while ((fgets(str, BUFFER_SIZE, fptr)) != NULL)
    {
        *line += 1;

        // Find first occurrence of word in str
        pos = strstr(str, word);

        if (pos != NULL)
        {
            // First index of word in str is 
            // Memory address of pos - memory
            // address of str.
            *col = (pos - str);
            break;
        }
    }


    // If word is not found then set line to -1
    if (*col == -1)
        *line = -1;

    return *col;
}
