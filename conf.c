//
// Created by Joe G on 19/06/2026.
//
#include <stdio.h>
#include <string.h>
#include "conf.h"


int prompt_user(char *input, const char *name)
{
    char confirm[4];
    printf("Enter %s:\n", name);
    scanf("%s", input);
    printf("%s:\n\t%s\nIs this correct? (y/n)\n", name, input);
    scanf("%s", confirm);
    if (strcmp(confirm, "y") != 0)
    {
        printf("Aborting dump!\n");
        return EXIT_FAILED_RUN;
    }
    return SUCCESSFUL_RUN;
}