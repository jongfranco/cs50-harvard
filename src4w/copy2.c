/****************************************************************************
 * copy2.c
 *
 * David J. Malan
 * malan@harvard.edu
 *
 * Copies a string.
 *
 * Demonstrates strings as pointers to arrays.
 ***************************************************************************/
       
#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    // get line of text
    printf("Say something: ");
    char* s = GetString();
    if (s == NULL)
        return 1;
 
    // allocate enough space for copy
    char* t = malloc((strlen(s) + 1) * sizeof(char));
    if (t == NULL)
        return 1;

    // copy string
    int n = strlen(s);
    for (int i = 0; i < n; i++)
        t[i] = s[i];
    t[n] = '\0';

    // change copy
    printf("Capitalizing copy...\n");
    if (strlen(t) > 0)
        t[0] = toupper(t[0]);

    // print original and copy
    printf("Original: %s\n", s);
    printf("Copy:     %s\n", t);

    // free memory
    free(s);
    free(t);

    return 0;
}
