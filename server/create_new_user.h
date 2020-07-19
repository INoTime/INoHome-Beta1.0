// +++++++++++++++++++++++++++++++++++++++ //
// +++++++++++ create_new_user.h +++++++++ //
// ++++ to create new user on server +++++ //
// +++++++++++++++ program +++++++++++++++ //
// +++++++++++++++++++++++++++++++++++++++ //

void *generate_with_ip_add_crypt_file() {
     // get ip adress from connected client
     struct sockaddr_in *s = (struct sockaddr_in *)&cli_new_user;
     inet_ntop(AF_INET, &s->sin_addr, ip_addr_client, sizeof(ip_addr_client));

     char ip_add_file_with_path[PATH_crypt_len+INET_ADDRSTRLEN], uuid_command_a[UUID_SIZE];
     strcpy(uuid_command_b,"");
     strcpy(ip_add_file_with_path, PATH_crypt);
     strcat(ip_add_file_with_path, ip_addr_client);

     // get passwords/commands (cout)
     random_password_generator(15);
     // write to user file
     FILE *uuid_command_file = fopen(ip_add_file_with_path, "w");
     fputs(password_gen_final, uuid_command_file);
     fclose(uuid_command_file); 
}

int check_blocked_users() {
     // get ip adress from connected client
     struct sockaddr_in *s = (struct sockaddr_in *)&cli_new_user;
     inet_ntop(AF_INET, &s->sin_addr, ip_addr_client, sizeof(ip_addr_client));
     // check if ip adress is blocked
     strcpy(ip_addr_client_b, ip_addr_client);
     strcat(ip_addr_client_b, "\n");
     for (int x = 0; x != lines_blocked_ip_add; x++) {
          if (!strcmp(ip_addr_client_b, blocked_ip_add_b[x]) != 0) {
               ip_is_blocked(ip_addr_client, current_time());
               user_is_blocked_or_not = 1;
               send(connfd_new_user, "0000", 5, 0);
               break;
          }
     }
     if (!user_is_blocked_or_not) {
          send(connfd_new_user, "1111", 5, 0);
          return 1;
     }
}

// block client if client typed in 3 times false password
void block_client_ip_add() {
     char *ip_addr_to_block;
     strcpy(ip_addr_to_block, ip_addr_client);
     FILE *block_new_client_ip_add = fopen(blocked_ip_add, "a");
     strcat(ip_addr_to_block, "\n");
     fputs(ip_addr_to_block, block_new_client_ip_add);
     fclose(block_new_client_ip_add);
}

// check for new_user if user is super user
int check_if_super_user_new_user() {
     char buf_ch_super_user[60] = "";
     check_super_user_access_twice = 0;
     read(connfd_new_user, buf_ch_super_user, sizeof(buf_ch_super_user));
     if (check_conn_tries > 0) {
          check_conn_tries--;
          if (!strcmp(super_user_name_password_b, buf_ch_super_user) != 0) {
               send(connfd_new_user, "011", 4, 0);
               check_conn_tries = 3;
               check_super_user_access_twice = 1;
               return 1;    
          }else {
               ssize_t check_conn;
               char *buffer_test;
               check_conn = recv(connfd_new_user, buffer_test, 10, 66);
               if (check_conn != 0) {
                    struct sockaddr_in *s = (struct sockaddr_in *)&cli_new_user;
                    inet_ntop(AF_INET, &s->sin_addr, ip_addr_client, sizeof(ip_addr_client));
                    false_password_from_ip(ip_addr_client, current_time());
                    send(connfd_new_user, "000", 4, 0);
                    false_password_from_ip_create_user(ip_addr_client, current_time());
                    check_if_super_user_new_user();
               }else {
                    check_conn_tries = 3;
                    struct sockaddr_in *s = (struct sockaddr_in *)&cli_new_user;
                    inet_ntop(AF_INET, &s->sin_addr, ip_addr_client, sizeof(ip_addr_client));
                    new_user_print(6, ip_addr_client, NULL);
               }
          }
     }else {
          // block user
          struct sockaddr_in *s = (struct sockaddr_in *)&cli_new_user;
          inet_ntop(AF_INET, &s->sin_addr, ip_addr_client, sizeof(ip_addr_client));
          ip_is_blocked(ip_addr_client, current_time());
          
          block_client_ip_add();
          // user is blocked
          save_in_fail_log(1, 3);

          // restart program 
          start_program();
     }
}

void check_again_if_super_user_new_user_garage();

void send_all_garage_ips() {
     send(connfd_new_user, all_ip_add_rasp, sizeof(all_ip_add_rasp), 0);
     char all_garage_ips_check[9690];
     read(connfd_new_user, all_garage_ips_check, sizeof(all_garage_ips_check));
     if (!strcmp(all_ip_add_rasp, all_garage_ips_check) != 0) {
          send(connfd_new_user, "111", 4, 0);
     }
}

// save garages to file 
void save_garage_fun(char *user_uuid) {
     // get new garages from user
     char check_message_new_garage_and_uuid[9048], new_garage_buf_ip_name_check[4] = "", again_or_not[4];       
     read(connfd_new_user, check_message_new_garage_and_uuid, sizeof(check_message_new_garage_and_uuid));
     send(connfd_new_user, check_message_new_garage_and_uuid, sizeof(check_message_new_garage_and_uuid), 0);
     read(connfd_new_user, new_garage_buf_ip_name_check, sizeof(new_garage_buf_ip_name_check));
     if (!strcmp(new_garage_buf_ip_name_check, "110") != 0) {
          new_garage(check_message_new_garage_and_uuid);
          FILE *add_new_garages_file_o = fopen(ip_add_rasp_file, "a");
          fputs(check_message_new_garage_and_uuid, add_new_garages_file_o);
          fclose(add_new_garages_file_o);
     }
     strcat(all_ip_add_rasp, check_message_new_garage_and_uuid);
     // send again all garages
     send_all_garage_ips();
     new_user_print(4, NULL, user_uuid);
     check_new_garage_is_not_blocked = 1;
     // check if user want to send more new garages
     check_again_if_super_user_new_user_garage();
}

void check_again_if_super_user_new_user_garage(char *user_uuid) {
     if (check_new_garage_is_not_blocked) {
          check_blocked_users();
     }
     char check_need_add_garage[4];
     read(connfd_new_user, check_need_add_garage, sizeof(check_need_add_garage));
     if (!strcmp(check_need_add_garage, "111") != 0) {
          // create new garages need here super user access
          check_if_super_user_new_user();
          if (check_super_user_access_twice) {
               save_garage_fun(user_uuid);
          }
     }
}

// create new uuid for new user (threading)
void *create_uuid() {
     uuid_t user_uuid;
     uuid_generate_time_safe(user_uuid);
     uuid_unparse_lower(user_uuid, user_uuid_a);
}

// create new user on server 
void *new_user() {
     fd_set readfds_new_user;

     sockfd_new_user = socket(AF_INET, SOCK_STREAM, 0);
     if (sockfd_new_user == -1) errorSock();
     memset(&server_add_new_user, BUF_a, sizeof(server_add_new_user));
     server_add_new_user.sin_family = AF_INET;
     server_add_new_user.sin_addr.s_addr = htonl(INADDR_ANY);
     server_add_new_user.sin_port = htons(PORT_new_user);
    
     bind(sockfd_new_user, (sock_addr_new_user *) &server_add_new_user, sizeof(server_add_new_user));
     if (listen(sockfd_new_user, 5) != 0) errorListen();
     while(1) {
          FD_ZERO(&readfds_new_user);
          FD_SET(sockfd_new_user, &readfds_new_user);

          for(int x = 0; x < MAX_CLIENTS; x++) {
               if (user_client_new_user[x] > 0) FD_SET(user_client_new_user[x], &readfds_new_user);
          }

          #if defined(__linux__) || defined( __apple__)
               rc_user_main_new_user = select(sockfd_new_user + 1, &readfds_new_user, NULL, NULL, NULL);
          #elif _Win32
               rc_user_main_new_user = select(0, &readfds_new_user, NULL, NULL, NULL);
          #endif

          if (FD_ISSET(sockfd_new_user, &readfds_new_user)) {
               char check_uuid_client_new_user[38];
               connfd_new_user = accept(sockfd_new_user, (sock_addr *)&cli_new_user, &len_new_user);     

               if (check_blocked_users()) {
                    if (!user_is_blocked_or_not) {
                         if (check_if_super_user_new_user()) {
                              // thread for uuid and command uuid's
                              pthread_t create_uuid_th, create_uuid_command_th;
                              pthread_create(&create_uuid_th, NULL, create_uuid, NULL);
                              pthread_create(&create_uuid_command_th, NULL, generate_with_ip_add_crypt_file, NULL);
                              pthread_join(create_uuid_th, NULL);
                              pthread_join(create_uuid_command_th, NULL);

                              // get ip address from server
                              new_user_print(1, ip_addr_client, user_uuid_a);     
                              // send user id to user (client)
                              send(connfd_new_user, user_uuid_a, sizeof(user_uuid_a), 0);
                              char check_new_user_uuid[UUID_SIZE], user_uuid_b[UUID_SIZE];
                              read(connfd_new_user, check_new_user_uuid, sizeof(check_new_user_uuid));
                              if (!strcmp(user_uuid_a, check_new_user_uuid) != 0) {
                                   send(connfd_new_user, "011", 4, 0);
                                   new_user_print(2, ip_addr_client, check_new_user_uuid);
                                   full_new_user_print(user_uuid_a, ip_addr_client, connfd_new_user, current_time());
                                   strcpy(user_uuid_b, user_uuid_a);
                                   // write user uuid and user ip into file "all_users"
                                   FILE *uuid_only_set = fopen(uuid_file, "a");
                                   strcat(user_uuid_b, "\n");
                                   fputs(user_uuid_b, uuid_only_set);
                                   fclose(uuid_only_set);

                                   strcat(user_uuid_a, "\t:: ");
                                   strcat(user_uuid_a, ip_addr_client);
                                   strcat(user_uuid_a, " ::\t");
                                   strcat(user_uuid_a, current_time());
                                   FILE *all_users = fopen(all_users_file, "a");
                                   fputs(user_uuid_a, all_users);
                                   fclose(all_users);

                                   // send all registred garages to user
                                   char lines_ip_addr_rasp[255];
                                   sprintf(lines_ip_addr_rasp, "%d", lines_ip_add_rasp_file);
                    
                                   send_all_garage_ips();
                                   new_user_print(4, ip_addr_client, check_new_user_uuid);
                         
                                   // send user commands command data to client
                                   send(connfd_new_user, password_gen_final, sizeof(password_gen_final), 0);
                                   char password_gen_final_check[sizeof(password_gen_final)];
                                   read(connfd_new_user, password_gen_final_check, sizeof(password_gen_final_check));

                                   if (!strcmp(password_gen_final, password_gen_final_check) != 0) {
                                        send(connfd_new_user, "1110", 5, 0);
                                        new_user_print(5, NULL, check_new_user_uuid);
                                        // new garages 
                                        if (check_blocked_users()) {
                                             check_again_if_super_user_new_user_garage(check_new_user_uuid);
                                        }
                                   }
                              }else {
                                   // non or false user uuid got back
                                   save_in_fail_log(1, 1);
                              }
                         }else {
                              // connection brok or super user name or/and password was incoreect
                              save_in_fail_log(1, 2);
                         }
                    }
               }
          }
          close(connfd_new_user);

          for (int x = 0; x > MAX_CLIENTS; x++) {
               if (user_client_new_user[x] == 0) {
                    user_client_new_user[x] = connfd_new_user;
                    break;
               }
          }
          system("sleep .25");
     }
}