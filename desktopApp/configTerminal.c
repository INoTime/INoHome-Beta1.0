#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <pthread.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

#include "../errorFileServ.h"

#define PORT_server 8185
#define BUF_a 30
#define sock_addr struct sockaddr
#define all_useres_file "../tmp/user_id"

int sockfd_server, connfd_server;
char get_uuid[38], check_uuid_a[4];

typedef struct {
    char server_ip_add[INET_ADDRSTRLEN];
} all_main_settings;

all_main_settings all_mains;

struct sockaddr_in server_add_server;

void configuration() {
    // get server ip address
    //fscanf(stdin, "%s", (char *)&all_mains.server_ip_add);
    //printf("%s\n", all_mains.server_ip_add);
    // get new (for new user) user uuid from server
    sockfd_server = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd_server == -1) errorSock();

    memset(&server_add_server, BUF_a, sizeof(server_add_server));
    server_add_server.sin_family = AF_INET;
    server_add_server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_add_server.sin_port = htons(PORT_server);

    while (connfd_server = connect(sockfd_server, (sock_addr * ) &server_add_server, sizeof(server_add_server)) != 0);
    printf("<\033[0;32mCONNECTED\033[0m> server: %s\n", all_mains.server_ip_add);
    
    // get uuid from server and paste it into klass
    read(sockfd_server, get_uuid, sizeof(get_uuid));

    // resend uuid to server to check if evrything gone right
    send(sockfd_server, get_uuid, sizeof(get_uuid), 0);

    // check answer from server if evrything gone right
    read(sockfd_server, check_uuid_a, sizeof(check_uuid_a));
    if (!strcmp(check_uuid_a, "011") != 0) {
        printf("<\033[0;32mUUID\033[0m> Your uuid: %s\n", get_uuid);
        // write new uuid to file 
        FILE *all_users = fopen(all_useres_file, "w");
        fputs(get_uuid, all_users);
        fclose(all_users);
    }else {
        printf("<\033[0;31mFAILED\033[0m> restart configuration!\n");
    }
    close(sockfd_server);
    
}