/*************************************************************************
	> File Name: client.c
	> Author: Yu_dong
	> Mail: 1124250973@qq.com
	> Created Time: 2018年06月13日 星期三 20时05分56秒
 ************************************************************************/

#include "common.h"
#include "client.h"

int create_client_server(int port) {
    int sockfd = 0;
    if ((sockfd = socket_create(port)) == -1) {
        return -1;
    }
    return sockfd;
}

int recv_SYN(int soocket) {
    int SYN = 0;
    if ( recv(soocket, &SYN, sizeof(SYN), 0) < 0 ) {
        perror("recv SYN failed");
        return -1;
    }
    return SYN;
}

int send_ACK(int ACK, int socket) {
    if ( send(socket, &ACK, sizeof(ACK), 0) < 0 ) {
        perror("send ACK failed");
        return -1;
    }
    return 1;
}

int data_create_connect(int socket) {
    int data_sock = 0;
    if ((data_sock = accept(socket, (struct sockaddr *)NULL, NULL)) < 0) {
        perror("data_sock error");
    }
    return data_sock;
}

int send_data(char *data, int socket) {
    if ( send(socket, data, strlen(data), 0) < 0 ) {
        perror("send data failed");
        return -1;
    }
    return 1;
}

int get_port(char *port_type) {
    char port_str[10] = {'\0'};
    int port = 0;
    if (get_conf_value("./client.conf", port_type, port_str) < 0) {
        return -1;
    }
    port = atoi(port_str);
    return port;
}

void server(int socket) {
    int server_pid = fork();
    if (server_pid != 0) return;
}

int switch_ack(int ACK, char *path) {
    FILE *fp;
    if ((fp = fopen(path, "r")) != NULL) {
        fclose(fp);
        return ACK + 100;
    } else {
        return ACK + 300;
    }
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
    FILE *log = fopen("/tmp/log/client.log", "a+");
    flock(log->_fileno, LOCK_EX);
    char now_time[100] = {'\0'};
    get_time(now_time);
    fwrite(now_time, 1, strlen(now_time), log);
    fwrite(operate, 1, strlen(operate), log);
    fclose(log);
    flock(log->_fileno, LOCK_UN);

    return ;
}

int switch_bak(int syn, char *path) {
    switch(syn) {
        case 300: {
            if (system("ls ./log/bak/*cpu* 1>/dev/null 2>&1") != 0) return syn + 300;
            system("tar -zxvf ./log/bak/`ls ./log/bak | grep cpu | head -n 1`");
            system("rm ./log/bak/`ls ./log/bak | grep cpu | head -n 1`");
            path = strdup("/home/Sniex/PiSystem/log/bak/cpu.log");
            break;
        }
        case 301: {
            if (system("ls ./log/bak/*mem* 1>/dev/null 2>&1") != 0) return syn + 300;
            system("tar -zxvf ./log/bak/`ls ./log/bak | grep mem | head -n 1`");
            system("rm ./log/bak/`ls ./log/bak | grep mem | head -n 1`");
            path = strdup("/home/Sniex/PiSystem/log/bak/mem.log");
            break;
        }
        case 302: {
            if (system("ls ./log/bak/*disk* 1>/dev/null 2>&1") != 0) return syn + 300;
            system("tar -zxvf ./log/bak/`ls ./log/bak | grep disk | head -n 1`");
            system("rm ./log/bak/`ls ./log/bak | grep disk | head -n 1`");
            path = strdup("/home/Sniex/PiSystem/log/bak/disk.log");
            break;
        }
        case 303: {
            if (system("ls ./log/bak/*pro* 1>/dev/null 2>&1") != 0) return syn + 300;
            system("tar -zxvf ./log/bak/`ls ./log/bak | grep pro | head -n 1`");
            system("rm ./log/bak/`ls ./log/bak | grep pro | head -n 1`");
            path = strdup("/home/Sniex/PiSystem/log/bak/pro.log");
            break;
        }
        case 304: {
            if (system("ls ./log/bak/*sys* 1>/dev/null 2>&1") != 0) return syn + 300;
            system("tar -zxvf ./log/bak/`ls ./log/bak | grep sys | head -n 1`");
            system("rm ./log/bak/`ls ./log/bak | grep sys | head -n 1`");
            path = strdup("/home/Sniex/PiSystem/log/bak/sys.log");
            break;
        }
        case 305: {
            if (system("ls ./log/bak/*usr* 1>/dev/null 2>&1") != 0) return syn + 300;
            system("tar -zxvf ./log/bak/`ls ./log/bak | grep usr | head -n 1`");
            system("rm ./log/bak/`ls ./log/bak | grep usr | head -n 1`");
            path = strdup("/home/Sniex/PiSystem/log/bak/usr.log");
            break;
        }
    }
    return syn - 100;
}

void run() {
    int client_server_port = get_port("port");
    int client_sock = create_client_server(client_server_port);
    int client_server_sock = 0;
    struct sockaddr_in client_addr;
    socklen_t len = sizeof(client_addr);
    char ip[64] = {0};
    DBG("=====Waiting conntct=====\n");
    while (1) {
        write_log("client start running\n");
        if ((client_server_sock = accept(client_sock, (struct sockaddr *)&client_addr, &len)) < 0) {
            perror("client_server_sock error");
            write_log("client sockfd create error\n");
            return ;
        }
        write_log("master connect succeed!\n");
        inet_ntop(AF_INET, (void *)&client_addr.sin_addr, ip, sizeof(ip));
        while (1) {
            int retcode = recv_SYN(client_server_sock);
            if (retcode == 18312) {
                close(client_server_sock);
                write_log("client send info over with no problems;\n");
                break;
            }
            DBG("recive retcode = %d\n", retcode);
            char log_msg[32] = {0};
            DBG("log_msg = %p\n", log_msg);
            sprintf(log_msg, "recive retcode = %d\n", retcode);
            write_log(log_msg);
            int ACK = 0;
            retcode -= 100;
            char *path = (char *)malloc(200);
            switch (retcode) {
                case 0: {
                    ACK = switch_ack(100, "/home/Sniex/PiSystem/log/cpu.log");
                    path = strdup("/home/Sniex/PiSystem/log/cpu.log");
                    break;
                }
                case 1: {
                    ACK = switch_ack(101, "/home/Sniex/PiSystem/log/mem.log");
                    path = strdup("/home/Sniex/PiSystem/log/mem.log");
                    break;
                }
                case 2: {
                    ACK = switch_ack(102, "/home/Sniex/PiSystem/log/disk.log");
                    path = strdup("/home/Sniex/PiSystem/log/disk.log");
                    break;
                }
                case 3: {
                    ACK = switch_ack(103, "/home/Sniex/PiSystem/log/pro.log");
                    path = strdup("/home/Sniex/PiSystem/log/pro.log");
                    break;
                }
                case 4: {
                    ACK = switch_ack(104, "/home/Sniex/PiSystem/log/sys.log");
                    path = strdup("/home/Sniex/PiSystem/log/sys.log");
                    break;
                }
                case 5: {
                    ACK = switch_ack(105, "/home/Sniex/PiSystem/log/usr.log");
                    path = strdup("/home/Sniex/PiSystem/log/usr.log");
                    break;
                }
                default: {
                    retcode += 100;
                    ACK = switch_bak(retcode, path);
                    break;
                }
            }
            fflush(stdout);
            send_ACK(ACK, client_server_sock);
            if (ACK < 400 && ACK != 0) {
                int data_port = get_port("data_port");
                int data_sockfd = socket_connect(data_port, ip);
                char buf[1024] = {'\0'};
                FILE *fp = fopen(path, "r");
                flock(fp->_fileno, LOCK_EX);
                while (fgets(buf, sizeof(buf), fp) != NULL) {
                    send_data(buf, data_sockfd);
                }
                close(data_sockfd);
                fclose(fp);
                fp = fopen(path, "w");
                flock(fp->_fileno, LOCK_EX);
                fclose(fp);
                write_log("send bash info success!\n");
            } else if (ACK >= 400 && ACK < 600) {
                write_log("The client cannot find the info of the Pi;\n");
            }
            memset(path, 0, sizeof(path));
            free(path);
        }
    }
}

int get_ip(char *ip_str) {
    if (get_conf_value("./client.conf", "master_ip", ip_str) < 0) {
        return -1;
    }
    return 1;
}

int connect_to_master(char *host, int port) {
    // connect to master
    int sockfd = 0;
    if ((sockfd = socket_connect(port, host)) == -1) {
        perror("socket_connect(port, host)");
        return -1;
    }
    return sockfd;
}

void warning_deal(char *type, char *warning_info) {
    DBG("Deal with the warning info %s\n", type);
    char log_msg[64] = {0};
    sprintf(log_msg, "Deal with the warning info %s\n", type);
    write_log(log_msg);
    char ip_str[32] = {0};
    char message[2048] = {0};
    get_ip(ip_str);
    int warning_port = get_port("warning");
    
    int warning_sock = connect_to_master(ip_str, warning_port);
    strcat(message, type);
    strcat(message, warning_info);
    int flag = send_data(message, warning_sock);
    DBG("%d\n", flag);
    DBG("Deal finished\n");
    write_log("Deal finished\n");
}

int get_file_size(char* filename) {
    struct stat statbuf;
    stat(filename,&statbuf);
    int size=statbuf.st_size;
    return size;
}

void gz(char *filename) {
    char order[100] = {0};
    sprintf(order, "tar -zcvf `date +\"%Y%m%H%M\"`%s.tar.gz %s.log", filename, filename);
    system(order);
    system("mv *.tar.gz ./bak");
}

void info(char *type, char *popen_order, char *log_locate) {
    static int flag = 0;
    static char last_temp[5] = "0";
    char buf[1024] = {0};
    static char info[10240] = {0};
    FILE *res = popen(popen_order, "r");
    while (fgets(buf, sizeof(buf), res) != NULL) {
        strcat(info, buf);
        if (buf[strlen(buf) - 2] == '2') {
            int warning = fork();
            if (warning == 0) {
                warning_deal(type, buf);
                exit(0);
            }
            signal(SIGCHLD, SIG_IGN);
        }
    }
    flag += 1;
    if (flag % 10 == 0) {
        FILE *fp = fopen(log_locate, "a+");
        fprintf(fp, "%s", info);
        fclose(fp);
        flag = 0;
        memset(info, 0, 10240);
        if (get_file_size(log_locate) >= 31457280) {
            gz(type);
            fp = fopen(log_locate, "w");
            flock(fp->_fileno, LOCK_EX);
            fclose(fp);
        }
    }
    pclose(res);

}

void bash_info(void (*func)(char *, char *, char *), char *type, char *popen_order, char *log_locate, int times) {
    while (1) {
        func(type, popen_order, log_locate);
        sleep(times);
    }
}

void ready_file() {
    for (int i = 1; i < 7; i++) {
        stats = fork();
        x = i;
        if (stats == 0) break;
    }
    if (stats == 0) {
        switch (x) {
            case 1: bash_info(info, "cpu", "bash cpu.sh", "./log/cpu.log", 5);
            case 2: bash_info(info, "mem", "bash mem.sh 17", "./log/mem.log", 5);
            case 3: bash_info(info, "disk", "bash disk.sh", "./log/disk.log", 60);
            case 4: bash_info(info, "pro", "bash pro.sh", "./log/pro.log", 30);
            case 5: bash_info(info, "sys", "bash sys.sh", "./log/sys.log", 60);
            case 6: bash_info(info, "usr", "bash usr.sh", "./log/usr.log", 60);
        }
    } 
}

int main(int argc, char const *argv[]) {
    int fork_t = fork();
    if (fork_t == 0) {
        sleep(5);
        run();
    } else {
        ready_file();
    } 
    signal(SIGCHLD, SIG_IGN);
    return 0;
}
