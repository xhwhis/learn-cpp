/*************************************************************************
	> File Name: master.c
	> Author: Yu_dong
	> Mail: 1124250973@qq.com 
	> Created Time: 2018年06月13日 星期三 19时23分51秒
 ************************************************************************/

#include "common.h"
#include "master.h"

int connect_to_client(char *host, int port) {
    // connect to client
    int sockfd = 0;
    if ((sockfd = socket_connect(port, host)) == -1) {
        perror("master --> socket_connect(port, host)");
        return -1;
    }
    return sockfd;
}

int create_master_server(int port) {
    int sockfd = 0;
    if ((sockfd = socket_create(port)) == -1) {
        perror("create_master_server ");
        return -1;
    }
    return sockfd;
}

int master_server_warning(int port) {
    int sockfd = 0;
    if ((sockfd = socket_create(port)) == -1) {
        return -1;
    }
    return sockfd;
}

int send_SYN(int SYN, int soocket) {
    if ( send(soocket, &SYN, sizeof(SYN), 0) < 0 ) {
        perror("send SYN failed");
        return -1;
    }
    return 1;
}

int recv_ACK(int socket) {
    int ACK = 0;
    if ( recv(socket, &ACK, sizeof(ACK), 0) < 0 ) {
        perror("recv ACK failed");
        return -1;
    }
    return ACK;
}

int recv_data(char *data, int socket) {
    if ( recv(socket, data, strlen(data), 0) < 0 ) {
        perror("recv data failed");
        return -1;
    }
    return 1;
}
int recv_warning(char *data, int socket) {
    if ( recv(socket, data, 1024, 0) < 0 ) {
        perror("recv data failed");
        return -1;
    }
    return 1;
}

int get_port(char *port_type) {
    char port_str[10] = {'\0'};
    int port = 0;
    if (get_conf_value("./master.conf", port_type, port_str) < 0) {
        return -1;
    }
    port = atoi(port_str);
    return port;
}

void get_time(char *now_time) {
    char *wday[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
    time_t now;
    struct tm *tm_now;
    time(&now);
    tm_now = localtime(&now);
    sprintf(now_time, "%d-%d-%d %s %d:%d:%d\t", (1900+tm_now->tm_year), (1+tm_now->tm_mon), tm_now->tm_mday, wday[tm_now->tm_wday], tm_now->tm_hour, tm_now->tm_min, tm_now->tm_sec);
}

void write_log(char *operate) {
    
    FILE *log = fopen("/var/log/pihealthd.log", "a+");
    flock(log->_fileno, LOCK_EX);
    char now_time[100] = {'\0'};
    get_time(now_time);
    // DBG("start time : %s\n", now_time);
    // if (log == NULL) {
    //     DBG("????\n");
    //     return ;
    // }
    fwrite(now_time, 1, strlen(now_time), log);
    fwrite(operate, 1, strlen(operate), log);
    flock(log->_fileno, LOCK_UN);
    fclose(log);
    return ;
}

void warning_log(char *operate) {
    // DBG("WTF\n");
    FILE *log = fopen("/var/log/warning.log", "a+");
    char now_time[100] = {'\0'};
    get_time(now_time);
    fwrite(now_time, 1, strlen(now_time), log);
    fwrite(operate, 1, strlen(operate), log);
    fputs("\n", log);
    fclose(log);
    return ;
}

void ip_to_pi(char *ip, char *pi) {
    switch (ip[strlen(ip) - 1]) {
        case '0' : strcat(pi, "pi1"); break;
        case '1' : strcat(pi, "pi2"); break;
        case '2' : strcat(pi, "pi3"); break;
        case '3' : strcat(pi, "pi4"); break;
        case '4' : strcat(pi, "pi5"); break;
        case '5' : strcat(pi, "pi6"); break;
        case '6' : strcat(pi, "pi7"); break;
        case '7' : strcat(pi, "pi8"); break;
        case '8' : strcat(pi, "pi9"); break;
        case '9' : strcat(pi, "pi10"); break;
    }
}

void warning() {
    DBG("Warning checking is Starting!\n");
    int warning_port = get_port("warning");
    int warning_sockfd = create_master_server(warning_port);
    int sockfd = 0;
    while (1) {
        if ((sockfd = accept(warning_sockfd, (struct sockaddr *)NULL, NULL)) < 0) {
            perror("client_server_sock error");
            write_log("master warning log create failed!\n");
            // fflush(stdout);
            exit(1);
            // return;
        }
        // DBG("\n\n666\n");
        char data[2048] = {'\0'};
        recv_warning(data, sockfd);
        // DBG("????%d\n", flag);
        // DBG("%s\n", data);

        struct sockaddr_in peer;
        socklen_t peer_len = sizeof(struct sockaddr_in);
        bzero(&peer, sizeof(struct sockaddr_in));
        if ( getpeername(sockfd, (struct sockaddr *)&peer, &peer_len) < 0) {
            perror("getpeername");
            continue;
        }
        char buff_peer[64] = {'\0'};
        char peer_name[5] = {0};
        inet_ntop(AF_INET, (void *)&peer.sin_addr, buff_peer, 63);
        // printf("[%s : %d]===>", buff_peer, ntohs(peer.sin_port));
        ip_to_pi(buff_peer, peer_name);
        DBG("%s\n%s\n", buff_peer, peer_name);
        char operate[2048] = {'\0'};
        switch (data[0]) {
            case 'c': {
                strcat(operate, peer_name);
                strcat(operate, " CPU Warning");
                warning_log(operate);
                break;
            }
            case 'm': {
                strcat(operate, peer_name);
                strcat(operate, " MEM Warning");
                warning_log(operate);
                break;
            }
            case 'd': {
                strcat(operate, peer_name);
                strcat(operate, " Disk Warning");
                warning_log(operate);
                break;
            }
            case 'p': {
                strcat(operate, peer_name);
                strcat(operate, " Proc Warning");
                warning_log(operate);
                break;
            }
        }
        warning_log(data);
        // write_log("Find a warning! ")
        close(sockfd);
    }
}

int generate_name(int code, char *logname, char *log_dir) {
    strcpy(logname, log_dir);
    code -= 100;
    switch (code) {
        case 100: 
            strcat(logname, "/Cpu.log");
            break;
        case 101:
            strcat(logname, "/Mem.log");
            break;
        case 102:
            strcat(logname, "/Disk.log");
            break;
        case 103: 
            strcat(logname, "/Pro.log");
            break;
        case 104:
            strcat(logname, "/SysInfo.log");
            break;
        case 105:
            strcat(logname, "/UsrInfo.log");
            break;
        default:
            break;
    }
    return 0;
}

int master_get(int data_sock, int reqcode, char *client) {
    
    char data[4096];
    int size;
    char arg[1024] = {0};
    char logdir[100] = {0};
    strcpy(logdir, data_dir);
    strcat(logdir, "/");
    strcat(logdir, client);

    mkdir(logdir, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    
    generate_name(reqcode, arg, logdir);

    FILE *fd = fopen(arg, "a+");
    flock(fd->_fileno, LOCK_EX);
    // DBG("<----%d --- %s\n", reqcode, arg);
    while ((size = recv(data_sock, data, sizeof(data), 0)) > 0) {
        fwrite(data, 1, size, fd);
        // DBG("==%d---->%s==\n", size, data);
    }
    fclose(fd);
    DBG("Write massage to File %s\n", arg);
    char log_msg[50] = {0};
    sprintf(log_msg, "Write massage to File %s\n", arg);
    write_log(log_msg);
    return 0;
}

int master_create_connect(int socket) {
    int data_sock = 0;
    if ((data_sock = accept(socket, (struct sockaddr *)NULL, NULL)) < 0) {
        perror("data_sock error");
    }
    return data_sock;
}

int recv_response(int syn, int socket, int sockfd, char *client) {
    int ack = recv_ACK(socket);
    int data_sock = 0;
    if (ack == syn + 100) {
        // DBG("Start to recv  %d\n", sockfd);
        data_sock = master_create_connect(sockfd);   
        master_get(data_sock, ack, client);
        close(data_sock);
    }
    // else if (ack == syn + 300) {
    //     // char log_msg[32] = {0};
    //     // DBG("%d is error\n", ack);
    //     // sprintf(log_msg, "%d is error\n", ack);
    //     // write_log("The client has no bash info file!\n");
    //     // write_log(log_msg);
        
    // }
}
int recv_bak(int syn, int socket, int sockfd, char *client) {
    int ack = recv_ACK(socket);
    int data_sock = 0;
    if (ack == syn - 100) {
        // DBG("Start to recv  %d\n", sockfd);
        data_sock = master_create_connect(sockfd);   
        master_get(data_sock, ack, client);
        close(data_sock);
    }
}

void run(int socket, int sockfd, char *client) {
    for (int j = 300; j < 306; ++j) {
        send_SYN(j, socket);
        recv_bak(j, socket, sockfd, client);
    }
    // send_SYN(18313, socket);
    for (int i = 100; i < 106; ++i) {
        send_SYN(i, socket);
        recv_response(i, socket, sockfd, client);
    }   
    send_SYN(18312, socket);
    // int ret = recv_ACK(socket);
    // DBG("Finished %d\n", socket);
    // DBG("res: %d\n", close(socket));
    // DBG("After %d\n", socket);  
    write_log("Finished send SYNs to client\n");
}

int get_ip(char *ip_str) {
    if (get_conf_value("./master.conf", "ip", ip_str) < 0) {
        return -1;
    }
    return 1;
}

int master_connect_clients(int sockfd) {
    int master_port = get_port("port");
    // DBG("Begin  %d\n", master_port);
    // char log_msg[50] = {0};
    // sprintf(log_msg, "Begin  %d\n", master_port);
    // write_log(log_msg);
    char ip[32] = {'\0'};
    // int master_ctrl_sock = 0;
    for (int i = 1; i < 11; i++) {
    // for (int i = 1; i < 4; i++) {
        stats = fork();
        x = i;
        if (stats == 0) break;
    }
    if (stats == 0) {
        char pi[10] = {'\0'};
        sprintf(pi, "%d", x + 39);
        // itoa(i, pi, 3);
        get_ip(ip);
        char ip_str[32] = {0};
        strncat(ip_str, ip, strlen(ip) - 1);
        strcat(ip_str, pi);
        // DBG("%s : \n", ip_str);
        // char log_msg[50] = {0};
        // sprintf(log_msg, "Begin : %s\n", ip_str);
        // write_log(log_msg);

        int master_ctrl_sock = connect_to_client(ip_str, master_port);
        if (master_ctrl_sock < 0) {
            // DBG("pi%d is closed\n", x);
            char log_msg[50] = {0};
            sprintf(log_msg, "pi%d is closed\n", x);
            write_log(log_msg);
            close(master_ctrl_sock);
            exit(1);
        }
        char client[50] = {'\0'};
        strcat(client, ip_str);
        run(master_ctrl_sock, sockfd, client); 
        close(sockfd);
        close(master_ctrl_sock);
        // master_ctrl_sock = -1;
        exit(1);
    }
    signal(SIGCHLD, SIG_IGN);
    // while (wait(&stats) > 0);
}

int main(int argc, char const *argv[]) {
    int pid = fork();
    if (pid == 0) {
        warning();
        exit(0);
    }
    DBG("Start:\n");
    write_log("Start to running master\n");
    // sleep(10);
    int data_port = get_port("data_port");
    int master_data_sock = create_master_server(data_port);
    // int tmp = 20;
    while (1) {
        master_connect_clients(master_data_sock);
        sleep(3);
    }
    return 0;
}

