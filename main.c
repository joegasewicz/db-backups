#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "conf.h"


int main(void)
{
    char confirm[4];
    /* Postgres details */
    char *db_name = malloc(100);
    char *host = malloc(253);
    char *port = malloc(6);
    char *username = malloc(300);
    char *password = malloc(300);
    /* File details */
    char *destination = malloc(1000);
    char *filename = malloc(300);
    char *fullpath = malloc(1000);
    char *cmd = malloc(2000);

    printf("==========\n");
    printf("DB Backups\n");
    printf("==========\n");

    // DB name
    printf("Enter db name:\n");
    scanf("%s", db_name);
    printf("Database name:\n\t%s\nIs this correct? (y/n)\n", db_name);
    scanf("%s", confirm);
    if (strcmp(confirm, "y") != 0)
    {
        printf("Aborting dump!\n");
        exit(1);
    }

    // Host
    printf("Enter host:\n");
    scanf("%s", host);
    printf("Database host:\n\t%s\nIs this correct? (y/n)\n", host);
    scanf("%s", confirm);
    if (strcmp(confirm, "y") != 0)
    {
        printf("Aborting dump!\n");
        exit(1);
    }

    // Port
    printf("Enter port:\n");
    scanf("%s", port);
    printf("Database port:\n\t%s\nIs this correct? (y/n)\n", port);
    scanf("%s", confirm);
    if (strcmp(confirm, "y") != 0)
    {
        printf("Aborting dump!\n");
        exit(1);
    }

    // DB username
    printf("Enter db username:\n");
    scanf("%s", username);
    printf("Database username:\n\t%s\nIs this correct? (y/n)\n", username);
    scanf("%s", confirm);
    if (strcmp(confirm, "y") != 0)
    {
        printf("Aborting dump!\n");
        exit(1);
    }

    // DB password
    printf("Enter db password:\n");
    scanf("%s", password);
    printf("Database password:\n\t%s\nIs this correct? (y/n)\n", password);
    scanf("%s", confirm);
    if (strcmp(confirm, "y") != 0)
    {
        printf("Aborting bump!\n");
        exit(1);
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
        printf("Aborting bump!\n");
        exit(1);
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

    int err = system(config.cmd);
    if (err < 0)
        printf("Error running pg_dump!\n");

    free(db_name);
    free(host);
    free(port);
    free(username);
    free(password);
    free(destination);
    free(filename);
    free(fullpath);
    free(cmd);

    return 0;
}
