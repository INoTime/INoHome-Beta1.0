#include <stdio.h>
#include <string.h>
#include <time.h>
// pi header
#include <wiringPi.h>
// socket header's
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
// GPIO 27 but wiringPi 0
#define button_5 2

// server connection
#define PORT 8081
#define BUF 64
#define serverIpV4 "192.168.178.58"
#define sock_add struct sockaddr

int sockfd, connfd;
void connect_server() {
    struct sockaddr_in server_add, cli;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    memset(&server_add, BUF, sizeof(server_add));

    server_add.sin_family = AF_INET;
    server_add.sin_addr.s_addr = inet_addr(serverIpV4);
    server_add.sin_port = htons(PORT);

    while (connfd = connect(sockfd, (sock_add *) &server_add, sizeof(server_add)) != 0);
    printf("[\033[32mCONNECTED\033[0m\033[0m via. \033[31mipV4\033[0m on port: %d] to server\n", PORT);
}

int conn_send() {
    char check_crypt_verify[40] = "11", check_a_crypt[40] = "";
    send(sockfd, check_crypt_verify, sizeof(check_crypt_verify), 0);
    read(sockfd, check_a_crypt, sizeof(check_a_crypt));
    printf("%s, %s\n", check_crypt_verify, check_a_crypt);
    if (!strcmp(check_crypt_verify, check_a_crypt) != 0) {
        while (1) {
            int check_pressed = 1;
            char buff[2];
            // wiring pi setup
            if (wiringPiSetup() == -1) return 1;

            pinMode(button_5, INPUT);
            pullUpDnControl(button_5, PUD_UP);
    
            if (digitalRead(button_5) == 1) {
                printf("[\033[31mGarage\033[0m] opened\n");
                send(sockfd, "13\n", 4, 0);
            }else {
                printf("[\033[32mGarage\033[0m] closed\n");
                send(sockfd, "12\n", 4, 0);
            }

            send(sockfd, "15\n", 4, 0);
            system("sleep .5");
        }
    }
    send(sockfd, "14\n", 4, 0);
}

int main() {
    connect_server();
    conn_send();

    return 0;
}