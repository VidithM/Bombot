#pragma once

#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>

int server_socket;
char recv_buf[32];

void start_server(int port){
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    bind(server_socket, (struct sockaddr*) &server_addr, sizeof(server_addr));
}

void connect_client(){
    listen(server_socket, 1);
    int client_socket;
    client_socket = accept(server_socket, NULL, NULL);
}

void next_word(){
    recv(client_socket, recv_buf, sizeof(recv_buf), 0);
}