#ifndef COMMON_H
#define COMMON_H
 
#include <iostream>
#include <string>
#include <list>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 34876
#define EPOLL_SIZE 500
#define BUF_SIZE 10000
#define SERVER_MESSAGE "ClientID#%d say: %s"
#define SERVER_PRIVATE_ERROR_MESSAGE "Client %d is not in the chat room yet~"
#define EXIT "EXIT"
#define CAUTION "Here is only you"
 
static void addfd(int epollfd, int fd, bool enable_et) {
    struct epoll_event ev;
    ev.data.fd = fd;
    ev.events = EPOLLIN;
    if(enable_et) ev.events = EPOLLIN | EPOLLET;
    epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &ev);
    fcntl(fd, F_SETFL, fcntl(fd, F_GETFD, 0) | O_NONBLOCK);
}
 
struct Msg {
    int fromID;
    char content[BUF_SIZE];
};

#endif
