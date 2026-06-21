#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "conf.h"


int main(void)
{
    char confirm[4];
    /* Postgres details */
    char *db_name = malloc(sizeof(char) * 100);
    char *host = malloc(sizeof(char) * 253);
    char *port = malloc(sizeof(char) * 6);
    char *username = malloc(sizeof(char) * 300);
    char *password = malloc(sizeof(char) * 300);
    /* File details */
    char *destination = malloc(sizeof(char) * 1000);
    char *filename = malloc(sizeof(char) * 300);
    char *fullpath = malloc(sizeof(char) * 1000);
    char *cmd = malloc(sizeof(char) * 2000);

    int failed_run = 0;

    printf("==========\n");
    printf("DB Backups\n");
    printf("==========\n");

    int err = 0;
    err = prompt_user(db_name, "Database name");
    if (err)
    {
        failed_run = EXIT_FAILED_RUN;
        goto clean;
    }
    err = prompt_user(host, "Database host");
    if (err)
    {
        failed_run = EXIT_FAILED_RUN;
        goto clean;
    }
    err = prompt_user(port, "Database port");
    if (err)
    {
        failed_run = EXIT_FAILED_RUN;
        goto clean;
    }
    err = prompt_user(username, "Database username");
    if (err)
    {
        failed_run = EXIT_FAILED_RUN;
        goto clean;
    }
    err = prompt_user(password, "Database password");
    if (err)
    {
        failed_run = EXIT_FAILED_RUN;
        goto clean;
    }

    printf("Destination path of backup: \n");
    scanf("%s", destination);
    strcpy(filename, db_name);
    strcat(filename, ".sql");
    strcpy(fullpath, destination);
    strcat(fullpath, "/");
    strcat(fullpath, filename);

    printf("Dump will be stored in the following file: \n\t%s\n", fullpath);
    printf("Continue dump? (y/n)\n");
    scanf("%s", confirm);
    if (strcmp(confirm, "y") != 0)
    {
        printf("Aborting dump!\n");
        failed_run = EXIT_FAILED_RUN;
        goto clean;
    }

    // Start dump
    Config config = {
        .db_name = db_name,
        .host = host,
        .port = port,
        .username = username,
        .password = password,
        .destination = destination,
        .filename = filename,
        .fullpath = fullpath,
    };

    sprintf(
        cmd,
        "PGPASSWORD=%s pg_dump "
        "-h %s "
        "-p %s "
        "-U %s "
        "-d %s "
        "-f %s",
        config.password,
        config.host,
        config.port,
        config.username,
        config.db_name,
        config.fullpath
    );

    printf("Command: %s\n", cmd);

    config.cmd = cmd;

    printf("Starting dump...\n");

    int sys_err = system(config.cmd);
    if (sys_err < 0)
    {
        printf("Error running pg_dump!\n");
        failed_run = EXIT_FAILED_RUN;
    }


clean:
    free(db_name);
    free(host);
    free(port);
    free(username);
    free(password);
    free(destination);
    free(filename);
    free(fullpath);
    free(cmd);

    if (failed_run == EXIT_FAILED_RUN)
        return EXIT_FAILED_RUN;
    return 0;
}
