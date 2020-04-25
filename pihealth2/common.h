#ifndef COMMON_H
#define COMMON_H 

#define MAX 1024

#include "head.h"

// int socket_create(int port);

// int socket_connect(int port, char *host);

/*
* Master Check Bak File 
* 666
*
* Master request 
* 100 Cpu
* 101 Mem
* 102 Disk
* 103 Pro
* 104 SystemInfo
* 105 UserInfo
*
* Client find file success and ready to transfer
* 200 Cpu
* 201 Mem
* 202 Disk
* 203 Pro
* 204 SystemInfo
* 205 UserInfo
*
* Client find file failed
* 400 Cpu
* 401 Mem
* 402 Disk
* 403 Pro
* 404 SystemInfo
* 405 UserInfo
*
*
*
*
*
*
*
*
*
*
*
*/

// struct linger {
//      int l_onoff;  // 0 = off, nozero = on 
//      int l_linger; // linger time 
// };

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
                // printf("%s\n", value);
                fclose(conf);
                return 1;
            }
        } 
    }
    printf("Not Found\n");
    fclose(conf);
    return -1;

}


int socket_create(int port) {
    int sockfd;
    struct linger yes;
    yes.l_onoff = 1;
    yes.l_linger = 0;
    int tmp = 1;
    struct sockaddr_in sever_addr = {0};
    if ((sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
        perror(" socket_create ");
        return -1;
    }

    sever_addr.sin_family = AF_INET;
    sever_addr.sin_port = htons(port);
    sever_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &tmp, sizeof(int)) == -1) {
        close(sockfd);
        perror("setsockopt() error");
        return -1;
    }

    if (setsockopt(sockfd, SOL_SOCKET, SO_LINGER, &yes, sizeof(struct linger)) == -1) {
        close(sockfd);
        perror("setsockopt() error");
        return -1;
    }


    if (bind(sockfd, (struct sockaddr *)&sever_addr, sizeof(sever_addr)) < 0) {
        perror(" bind ");
        return -1;
    }
    
    if (listen(sockfd, 10) < 0) {
        perror(" listen ");
        return -1;
    }
    return sockfd;
}

int socket_connect(int port, char *host) {
    int sockfd;
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



#endif
