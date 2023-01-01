#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>

typedef struct {
    int tcp_sock;
    int udp_sock;
} IRCAPI;

void *listen(void *arg) {
    IRCAPI *api = (IRCAPI *)arg;

    while (1) {
        char buf[1024];
        struct sockaddr_in addr;
        socklen_t addr_len = sizeof(addr);
        int n = recvfrom(api->udp_sock, buf, sizeof(buf), 0, (struct sockaddr *)&addr, &addr_len);
        if (n < 0) {
            perror("recvfrom");
            break;
        }

        printf("%.*s", n, buf);
    }

    return NULL;
}

int login(IRCAPI *api, const char *nick, const char
