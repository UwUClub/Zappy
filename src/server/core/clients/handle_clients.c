/*
** EPITECH PROJECT, 2023
** zappy_server
** File description:
** handle_clients
*/

#include <errno.h>
#include <signal.h>
#include <sys/time.h>
#include <sys/select.h>
#include "implementation.h"
#include "utils.h"
#include "ranges.h"

static int keep_running = 1;

void detect_ctrl_c(int dummy)
{
    keep_running = 0;
}

static void get_fd_set(client_t **clients, fd_set *read_fd_set,
    fd_set *write_fd_set)
{
    FD_ZERO(read_fd_set);
    for (int i = 0; clients[i]; i++) {
        if (clients[i]->fd >= 0) {
            FD_SET(clients[i]->fd, read_fd_set);
        }
    }
    FD_ZERO(write_fd_set);
    for (int i = 0; clients[i]; i++) {
        if (clients[i]->fd >= 0 && strlen(clients[i]->output) > 0) {
            FD_SET(clients[i]->fd, write_fd_set);
        }
    }
}

static void run_client_flow(data_t *data, unsigned long long elapsed_time_ms,
    fd_set read_fd_set, fd_set write_fd_set)
{
    client_t *cli = data->clients[data->curr_cli_index];
    int player_left = 0;

    if (cli->player && cli->is_registered) {
        if (cli->player->pending_cmd_queue[0]) {
            handle_pending_cmd(data, elapsed_time_ms);
        }
        handle_player_digestion(data, elapsed_time_ms);
    }
    if (FD_ISSET(cli->fd, &write_fd_set)) {
        player_left = write_to_selected_client(data,
            &(data->clients)[data->curr_cli_index]);
    }
    if (!player_left && FD_ISSET(cli->fd, &read_fd_set)) {
        read_selected_client(data);
    }
}

static void handle_clients(data_t *data, fd_set read_fd_set,
    fd_set write_fd_set)
{
    unsigned long long elapsed_time_ms = 0;

    elapsed_time_ms = get_ms_since_epoch() - data->last_select_ms;
    handle_resource_spawn(data, elapsed_time_ms);
    handle_eggs_digestion(data, elapsed_time_ms);
    data->curr_cli_index = 0;
    while (data->clients[data->curr_cli_index]) {
        if (data->clients[data->curr_cli_index]->fd > 0) {
            run_client_flow(data, elapsed_time_ms, read_fd_set, write_fd_set);
        }
        data->curr_cli_index++;
    }
}

int select_clients(struct sockaddr_in *addr, int server_fd, data_t *data,
    struct timeval *timeout)
{
    fd_set read_fd_set;
    fd_set write_fd_set;

    get_fd_set(data->clients, &read_fd_set, &write_fd_set);
    FD_SET(server_fd, &read_fd_set);
    select(FD_SETSIZE, &read_fd_set, &write_fd_set, NULL, timeout);
    if (!keep_running)
        return 1;
    if (FD_ISSET(server_fd, &read_fd_set) && data->nb_clients < MAX_CLIENTS) {
        welcome_selected_client((struct sockaddr *) addr, server_fd, data);
    }
    handle_clients(data, read_fd_set, write_fd_set);
    return SUCCESS_STATUS;
}
