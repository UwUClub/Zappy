/*
** EPITECH PROJECT, 2023
** my_teams
** File description:
** launch_server
*/

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

struct sockaddr_in get_sockaddr(in_addr_t address, unsigned int port)
{
    struct sockaddr_in addr;

    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = address;
    memset(&(addr.sin_zero), '\0', 8);
    return addr;
}
