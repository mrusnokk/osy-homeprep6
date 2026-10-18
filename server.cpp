#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cstdarg>
#include <cerrno>
#include <unistd.h>
#include <poll.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <iostream>

constexpr int PORT = 8080;
int main()
{
    int soc;
    if ((soc = socket(AF_INET, SOCK_STREAM, 0) < 0))
    {
        exit(EXIT_FAILURE);
    }

    in_addr addr_any = {INADDR_ANY};
    sockaddr_in srv_addr;
    srv_addr.sin_family = AF_INET;
    srv_addr.sin_port = htons(PORT);
    srv_addr.sin_addr = addr_any;

    int opt = 1;
    if (setsockopt(soc, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
    {
        fprintf(stdout, "Nepodariolo se nastavit socopts!\n");
    }

    if (bind(soc, (const sockaddr *)(&srv_addr), sizeof(srv_addr)) < 0)
    {
        fprintf(stdout, "Nepodarilo se bindnout port a soc!\n");
        close(soc);
        exit(EXIT_FAILURE);
    }
    if (listen(soc, 1) < 0)
    {
        fprintf(stdout, "Nedase poslouchat! :( \n");
        close(soc);
        exit(EXIT_FAILURE);
    }

    while (1)
    {
        int cl = -1;
        pollfd read_poll[2];

        read_poll[0].fd = STDIN_FILENO;
        read_poll[0].events = POLLIN;
        read_poll[1].fd = soc;
        read_poll[1].events = POLLIN;

        while (1)
        {
            int l_poll = poll(read_poll, 2, -1)
        }
    }

    return 0;
}