/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** Header for server app
*/

#ifndef ZAPPY_SERVER_IMPLEMENTATION_H
    #define ZAPPY_SERVER_IMPLEMENTATION_H

    #include "server_core.h"

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
    char *get_offline_user_name(char *uuid);

#endif /* ZAPPY_SERVER_IMPLEMENTATION_H */
