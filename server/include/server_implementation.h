/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** Header for server app
*/

#ifndef MYTEAMS_SERVER_IMPLEMENTATION_H
    #define MYTEAMS_SERVER_IMPLEMENTATION_H

    #include "server_core.h"

    #define MAX_NAME_LENGTH 32
    #define MAX_DESCRIPTION_LENGTH 255
    #define MAX_BODY_LENGTH 512

    typedef struct user_info_s {
        char *uuid;
        char *name;
        int status;
    } user_info_t;

    typedef struct thread_s {
        char *uuid;
        char *name;
        char *first_reply;
        char *author_uuid;
        char creation_date[11];
    } thread_t;

    typedef struct reply_s {
        char *author_uuid;
        char *thread_uuid;
        char *message;
        char creation_date[11];
    } reply_t;

    int parse_instruction(data_t *data);
    int help(data_t *data, char **args);
    int login(data_t *data, char **args);
    int create_user(char *name, char **uuid);
    int load_user(char *name, char **uuid);
    int does_user_exist(char *name);
    int logout(data_t *data, char **args);
    void broadcast_logout_response(client_t *cli, client_t **clients);
    int messages_cmd(data_t *data, char **args);
    int user(data_t *data, char **args);
    int users(data_t *data, char **args);
    int send_cmd(data_t *data, char **args);
    int info(data_t *data, char **args);
    int create(data_t *data, char **args);
    int create_team(data_t *data, char **args);
    int create_channel(data_t *data, char **args);
    int create_thread(data_t *data, char **args);
    int create_reply(data_t *data, char **args);
    int use(data_t *data, char **args);
    int subscribed(data_t *data, char **args);
    int team_exists(char *team_uuid);
    int channel_exists(char *team_uuid, char *channel_uuid);
    int thread_exists(char *team_uuid, char *channel_uuid, char *thread_uuid);
    int list(data_t *data, char **args);
    void list_teams(data_t *data);
    void list_channels(data_t *data);
    void list_threads(data_t *data);
    void list_replies(data_t *data);
    int subscribe(data_t *data, char **args);
    int unsubscribe(data_t *data, char **args);
    void list_users_subscribed(data_t *data, const char *team_uuid);
    void list_subscribed_teams(data_t *data);
    int does_team_exist(char *team_name);
    int does_channel_exist(char *team_uuid, char *channel_name);
    int does_thread_exist(char *team_uuid, char *channel_uuid,
        char *thread_name);

    void init_save_dirs(void);
    void get_team_details(const char *uuid, char **name, char **desc);
    void get_channel_details(const char *team_uuid, const char *uuid,
        char **name, char **desc);
    void get_thread_details(const char *path, char **name, char ***details);
    int is_user_subscribed(char *uuid, char *team_uuid);
    int broadcast_team(client_t **clients, const char *team_uuid,
    const char *msg);

    int get_users_nbr(void);
    user_info_t *get_users_info(int usr_nbr);
    void set_users_status(client_t **clients, user_info_t *users_info,
    int usr_nbr);
    char *get_offline_user_name(char *uuid);

#endif /* MYTEAMS_SERVER_IMPLEMENTATION_H */
