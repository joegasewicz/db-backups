//
// Created by Sumi on 19/06/2026.
//

#ifndef DB_BACKUPS_CONF_H
#define DB_BACKUPS_CONF_H

#define SUCCESSFUL_RUN 0
#define EXIT_FAILED_RUN 1

struct _Config
{
    char *db_name;
    char *host;
    char *port;
    char *username;
    char *password;
    char *destination;
    char *filename;
    char *fullpath;
    char *cmd;
};

typedef struct _Config Config;

int prompt_user(char *input, const char *name);

#endif //DB_BACKUPS_CONF_H
