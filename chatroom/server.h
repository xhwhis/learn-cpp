#ifndef SERVER_H
#define SERVER_H

#include "common.h"
using namespace std;
 
class Server {
 
public:
    Server() {
        serverAddr.sin_family = PF_INET;
        serverAddr.sin_port = htons(SERVER_PORT);
        serverAddr.sin_addr.s_addr = inet_addr(SERVER_IP);
        listener = 0;
        epfd = 0;
    }
    
    void Init() {
        listener = socket(PF_INET, SOCK_STREAM, 0);
        if(listener < 0) { perror("listener"); exit(-1);}
        if( bind(listener, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
            perror("bind error");
            exit(-1);
        }
        int ret = listen(listener, 5);
        if(ret < 0) {
            perror("listen error"); 
            exit(-1);
        }
        cout << "Start to server: " << SERVER_IP << endl;
        epfd = epoll_create (EPOLL_SIZE);
        if(epfd < 0) {
            perror("epfd error");
            exit(-1);
        }
        addfd(epfd, listener, true);
    }
    
    void Close() {
        close(listener);
        close(epfd);
    }

    void Start() {
        static struct epoll_event events[EPOLL_SIZE]; 
        Init();
        while(1) {
            int epoll_events_count = epoll_wait(epfd, events, EPOLL_SIZE, -1);
            if(epoll_events_count < 0) {
                perror("epoll failure");
                break;
            }
            for(int i = 0; i < epoll_events_count; ++i) {
                int sockfd = events[i].data.fd;
                if(sockfd == listener) {
                    struct sockaddr_in client_address;
                    socklen_t client_addrLength = sizeof(struct sockaddr_in);
                    int clientfd = accept( listener, ( struct sockaddr* )&client_address, &client_addrLength );
                    cout << "client connection from: " << inet_ntoa(client_address.sin_addr) << ":" << ntohs(client_address.sin_port) << ", clientfd = " << clientfd << endl;
                    addfd(epfd, clientfd, true);
                    clients_list.push_back(clientfd);
                    cout << "Now there are " << clients_list.size() << " clients int the chat room" << endl;
                    char message[BUF_SIZE];
                    bzero(message, BUF_SIZE);
                    int ret = send(clientfd, message, BUF_SIZE, 0);
                    if(ret < 0) {
                        perror("send error");
                        Close();
                        exit(-1);
                    }
                } 
                else {   
                    int ret = SendBroadcastMessage(sockfd);
                    if(ret < 0) {
                        perror("error");
                        Close();
                        exit(-1);
                    }
                }
            }
        }
        Close();
    }
 
private:
    int SendBroadcastMessage(int clientfd) {
        char recv_buf[BUF_SIZE];
        char send_buf[BUF_SIZE];
        Msg msg;
        bzero(recv_buf, BUF_SIZE);
        cout << "message from client(clientID = " << clientfd << ")" << endl;
        int len = recv(clientfd, recv_buf, BUF_SIZE, 0);
        memset(&msg, 0, sizeof(msg));
        memcpy(&msg, recv_buf, sizeof(msg));
        msg.fromID = clientfd;
        if(len == 0) {
            close(clientfd);
            clients_list.remove(clientfd);
            cout << "ClientID = " << clientfd << " closed. Now there are " << clients_list.size() << " client" << endl;
        } else {
            if(clients_list.size() == 1) { 
                memcpy(&msg.content, CAUTION, sizeof(msg.content));
                bzero(send_buf, BUF_SIZE);
                memcpy(send_buf, &msg, sizeof(msg));
                send(clientfd, send_buf, sizeof(send_buf), 0);
                return len;
            }
            char format_message[BUF_SIZE];
            sprintf(format_message, SERVER_MESSAGE, clientfd, msg.content);
            memcpy(msg.content, format_message, BUF_SIZE);
            for(auto it = clients_list.begin(); it != clients_list.end(); ++it) {
                if(*it != clientfd){
                    bzero(send_buf, BUF_SIZE);
                    memcpy(send_buf, &msg, sizeof(msg));
                    if(send(*it, send_buf, sizeof(send_buf), 0) < 0) return -1;
                }
            }
        }
        return len;
    }

    struct sockaddr_in serverAddr;
    int listener;
    int epfd;
    list<int> clients_list;
};

#endif
