#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <pthread.h>
#include <uuid/uuid.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

#include "fail.log.h"
#include "terminal/display.h"

#define sock_addr struct sockaddr
#define sock_addr_user struct sockaddr
#define sock_addr_new_user struct sockaddr
#define sock_addr_new_garage struct sockaddr
#define sock_addr_garage struct sockaddr
#define PORT_user 3111
#define PORT_new_user 8185
#define PORT_new_garage 8080 
#define PORT_garage 8081
#define BUF_a 64
#define BUF_msg 64
#define garage_log "tmp/garage_OC.log"
#define all_users_file "tmp/all_users"
#define MAX_CLIENTS 3
#define UUID_SIZE 38
#define uuid_file "tmp/uuid_only"
#define ip_add_rasp_file "tmp/ip_add_rasp"
#define server_super_user "tmp/user_server"
#define blocked_ip_add "tmp/blocked_ip_add"
#define PATH_crypt_len 40
#define PATH_crypt "tmp/users_crypt/"
#define PATH_crypt_garage "tmp/garage_crypt/"

struct sockaddr_in server_add_main, cli_main_conn, my_addr_main_conn;
struct sockaddr_in server_add_new_user, cli_new_user, my_addr_new_user;
struct sockaddr_in server_add_main_new_garage, cli_new_garage;
struct sockaddr_in server_add_garage, cli_garage, my_addr_garage;


char ip_addr_client[INET_ADDRSTRLEN];
char user_uuid_a[UUID_SIZE], *only_user_uuid;
char buf_uuid_file[9690], buf_ip_addr_rasp_file[9690];
char a_garage_save[80];
char super_user_name_password_a[60] = "", super_user_name_password_b[60] = "";
char blocked_ip_add_a[INET_ADDRSTRLEN];
char ip_addr_client_b[INET_ADDRSTRLEN+2];
char uuid_command_b[UUID_SIZE*100];
char garage[255][2], garage_o_f[255][2], garage_o_c[255][2];

int which_garage = 0;

int user_is_blocked_or_not = 0;
int lines_uuid_file = 0, lines_ip_add_rasp_file = 0, lines_blocked_ip_add = 0;
int sockfd_new_user, connfd_new_user, len_new_user = sizeof(my_addr_new_user), y_check_main_s_new_user = 1, user_client_new_user[MAX_CLIENTS], rc_user_main_new_user;
int check_conn_tries = 3, check_super_user_access_twice = 0, check_new_garage_is_not_blocked = 0;
int client_is_on = 1;

// all user uuid with a max of users: 255
char all_uuids[255][38];
// all ip adtresses from rasp max of rasp's: 255
char all_ip_add_rasp[9690], test[sizeof(all_ip_add_rasp)], all_ip_add_rasp_all[255][80];
// all blocked ip addresses with a max of blocked users: 255
char blocked_ip_add_b[255][INET_ADDRSTRLEN];

char password_gen_final[UUID_SIZE*100];
#include "password_generator.h"

static void start_program();

char *current_time() {
     time_t rawtime;
     struct tm *timeinfo;
     time(&rawtime);
     timeinfo = localtime(&rawtime);
     char *time = asctime(timeinfo);
     return time;
}

// create new user on server
#include "create_new_user.h"
#include "mainConnection.h"
#include "connection_garage.h"

static void start_program() {
     // reset evrything if program need restart
     for (int x = 0; x != lines_uuid_file; x++) strcpy(all_uuids[x], "");
     for (int x = 0; x != lines_blocked_ip_add; x++) strcpy(blocked_ip_add_b[x], "");
     lines_uuid_file = 0;
     lines_ip_add_rasp_file = 0;
     lines_blocked_ip_add = 0;

     // open file with all uuids and read thme to an 2D array
     FILE *uuid_file_o = fopen(uuid_file, "r+");
     while (fgets(buf_uuid_file, sizeof(buf_uuid_file), uuid_file_o) != NULL) {
          strcpy(all_uuids[lines_uuid_file], buf_uuid_file);    
          lines_uuid_file++;   
     }  
     fclose(uuid_file_o);
     start_program_print_users(lines_uuid_file);
     // -------------------------------------

     // open file with all ip adresses and read them to an 2D array garages
     FILE *ip_add_all_garages_o = fopen(ip_add_rasp_file, "r+");
     while (fgets(a_garage_save, sizeof(a_garage_save), ip_add_all_garages_o) != NULL) {
          strcat(all_ip_add_rasp, a_garage_save);
          strcpy(all_ip_add_rasp_all[lines_ip_add_rasp_file], a_garage_save);
          lines_ip_add_rasp_file++;
     }
     fclose(ip_add_all_garages_o);
     start_program_print_ip_add_rasp(lines_ip_add_rasp_file);
     // -------------------------------------

     // get super user name and super user password from file
     FILE *super_user_file_o = fopen(server_super_user, "r+");
     while (fgets(super_user_name_password_a, sizeof(super_user_name_password_a), super_user_file_o) != NULL) {
          strcat(super_user_name_password_b, super_user_name_password_a);
     }
     // -------------------------------------

     // list all blocked ip addresses
     FILE *blocked_ip_add_file_o = fopen(blocked_ip_add, "r+");
     while (fgets(blocked_ip_add_a, sizeof(blocked_ip_add_a), blocked_ip_add_file_o) != NULL) {
          strcat(blocked_ip_add_b[lines_blocked_ip_add], blocked_ip_add_a);
          lines_blocked_ip_add++;
     }
     start_program_print_blocked_users(lines_blocked_ip_add);
     // -------------------------------------
} 

int main() {
     start_program();
     pthread_t main_connect_th, new_user_th, garage_conn_th;

     pthread_create(&main_connect_th, NULL, main_connect, NULL);
     pthread_create(&new_user_th, NULL, new_user, NULL);
     pthread_create(&garage_conn_th, NULL, garage_conn, NULL);

     pthread_join(main_connect_th, NULL);
     pthread_join(new_user_th, NULL);
     pthread_join(garage_conn_th, NULL);

     return 0;
}
