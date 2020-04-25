#ifndef COMMON_H
#define COMMON_H 

#include "head.h"
#define MAX 1024

int get_conf_value(char *pathname, char* key_name, char *value) {
    FILE *conf = NULL;
    char *line = NULL;
    int key_len = strlen(key_name);
    size_t len = 0;
    ssize_t read;
    conf = fopen(pathname, "r");
    if ( conf == NULL) {
        printf("Error: The pathname is wrong\n");
        return -1;
    }
    if ( key_name == NULL ) {
        printf("Error: The key_name is NULL\n");
        fclose(conf);
        return -1;
    }
    while ((read = getline(&line, &len, conf)) != -1) {  
        if (strncmp(key_name, line, key_len) == 0) {
            if (line[key_len] == '=') {
                strncpy(value, &line[key_len + 1], (int)read - key_len - 1);
                fclose(conf);
                return 1;
            }
        } 
    }
    printf("Not Found\n");
    fclose(conf);
    return -1;
}

class Socket {
public:
    int socketfd;

    Socket(int port) {
        struct linger yes;
        yes.l_onoff = 1;
        yes.l_linger = 0;
        int tmp = 1;
        struct sockaddr_in sever_addr = {0};
        if ((sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
            perror(" socket_create ");
            sockfd = -1;
            return ;
        }
        sever_addr.sin_family = AF_INET;
        sever_addr.sin_port = htons(port);
        sever_addr.sin_addr.s_addr = htonl(INADDR_ANY);
        if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &tmp, sizeof(int)) == -1) {
            close(sockfd);
            perror("setsockopt() error");
            sockfd = -1;
            return ;
        }
        if (setsockopt(sockfd, SOL_SOCKET, SO_LINGER, &yes, sizeof(struct linger)) == -1) {
            close(sockfd);
            perror("setsockopt() error");
            sockfd = -1;
            return ;
        }
        if (bind(sockfd, (struct sockaddr *)&sever_addr, sizeof(sever_addr)) < 0) {
            perror("bind");
            sockfd = -1;
            return ;
        }
        if (listen(sockfd, 10) < 0) {
            perror("listen");
            socketfd = -1;
            return ;
        }
    }

    void connect(int port, char *host) {
    struct sockaddr_in dest_addr = {0};
    if ((sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
        perror(" socket_connect ");
        return -1;
    }
    dest_addr.sin_family = AF_INET;
    dest_addr.sin_port = htons(port);
    dest_addr.sin_addr.s_addr = inet_addr(host);
    if (connect(sockfd, (struct sockaddr *)&dest_addr, sizeof(dest_addr)) < 0) {
        perror(" connect ");
        return -1;
    }
    return sockfd;
}

};
#endif
