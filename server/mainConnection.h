int alive_clients_ch = 0, connfd;
int user_not_detected = 0, commands_cout = 0, ip_blocked = 1;
char check_uuid_client[38];

char ipv4[INET_ADDRSTRLEN], ipv4_changed[sizeof(ipv4)+2];
char all_ip_add_rasp_check[9690] = ""; 

void *main_connect() {
     fd_set readfds;
     int sockfd, len = sizeof(my_addr_main_conn), user_client[MAX_CLIENTS], rc_user_main;
     // set all client ports to 0
     for (int x = 0; x != MAX_CLIENTS; x++) user_client[x] = 0;
     // set master socket and set setsockopt to timeout of 2 seconds 
     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     struct timeval timeout;
     timeout.tv_sec = 2;
     timeout.tv_usec = 0;
     setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (const char *)&timeout, sizeof(timeout));
     if (sockfd == -1) errorSock();

     memset(&server_add_main, BUF_a, sizeof(server_add_main));
     server_add_main.sin_family = AF_INET;
     server_add_main.sin_addr.s_addr = htonl(INADDR_ANY);
     server_add_main.sin_port = htons(PORT_user);

     bind(sockfd, (sock_addr *) &server_add_main, sizeof(server_add_main));
     if (listen(sockfd, 5) != 0) errorListen();
     while(1) {
          FD_ZERO(&readfds);
          FD_SET(sockfd, &readfds);

          for(int x = 0; x < MAX_CLIENTS; x++) {
               if (user_client[x] > 0) FD_SET(user_client[x], &readfds);
          }

          #if defined(__linux__) || defined( __apple__)
               rc_user_main = select(sockfd + 1, &readfds, NULL, NULL, NULL);
          #elif _Win32
               rc_user_main = select(0, &readfds, NULL, NULL, NULL);
          #endif
          if (FD_ISSET(sockfd, &readfds)) {
               connfd = accept(sockfd, (sock_addr *)&cli_main_conn, &len);
               char check_command[38] = "", all_ip_add_rasp_check_a[9690] = "", commands_file[100] = "", buf_commands[9690] = "", commands[255][38];
               // get ip addr
               struct sockaddr_in *s = (struct sockaddr_in *)&cli_main_conn;
               inet_ntop(AF_INET, &s->sin_addr, ipv4, sizeof(ipv4));
               // check if ip is blocked if ip is blocked quit program
               strcpy(ipv4_changed, ipv4);
               strcat(ipv4_changed, "\n");
               for (int x = 0; x != lines_blocked_ip_add; x++) {
                    if (!strcmp(ipv4_changed, blocked_ip_add_b[x]) != 0) {
                        ip_is_blocked_futher(ipv4_changed);
                        ip_blocked = 0;
                        break;
                    }
               }
                // ip is not blocked also 1
                if (ip_blocked) {
                    send(connfd, "1111", 5, 0);
                    
                    // get user uuid to check first
                    read(connfd, check_uuid_client, UUID_SIZE);
                    // get users fisrt command to check again 
                    read(connfd, check_command, sizeof(check_command));
                    
                    // write paths file to read user commands
                    strcat(commands_file, PATH_crypt);
                    strcat(commands_file, ipv4);
                    // get commands to unlock user
                    FILE *commands_file_o = fopen(commands_file, "r");
                    while (fgets(buf_commands, sizeof(buf_commands), commands_file_o) != NULL) {
                        strcpy(commands[commands_cout], buf_commands);
                        commands_cout++;
                    }

                    // check if uuid from user is true else break;
                    strcat(check_uuid_client, "\n");
                    for (int x = 0; x != lines_uuid_file; x++) {
                        if(!strcmp(check_uuid_client, all_uuids[x]) != 0) {
                            // check if command 0 is true else break system
                            if (!strcmp(check_command, commands[0]) != 0) {
                                connected_main_server(connfd, check_uuid_client);
                                user_not_detected = 1;
                                break;
                            }else {
                                false_command_or_false_uuid_from_user(ipv4_changed);
                                break;
                            }
                        }
                    }
                    // if user is not detected in system quit the program
                    if (!user_not_detected) {
                        send(connfd, "your not registred ;)", 25, 0);
                    // user is detected
                    }else {
                        alive_clients_ch++;
                        alive_clients(alive_clients_ch);

                        // send garages to server that client is uptodate
                        send(connfd, all_ip_add_rasp, sizeof(all_ip_add_rasp), 0);
                        
                        // get garage data and send them to client
                        // read commands from server
                        int already_tried = 0;
                        char get_command_from_client[120] = "", get_data_from_client[120] = "", get_second_command[120] = "";
                        int exists = 0;
                        void *main_stuff() {
                            // if client is offline break loop                           
                            while (client_is_on) {
                                // reset data to read before read again
                                strcpy(get_command_from_client, "");
                                strcpy(get_data_from_client, "");
                                strcpy(get_second_command, "");
                                
                                already_tried = 1;                                 
                                read(connfd, get_command_from_client, sizeof(get_command_from_client));

                                if (strcmp(get_command_from_client, "") != 0) {   
                                    char test[40] = "", test0[40];
                                    strcpy(test, commands[3]);
                                    strcpy(test0, commands[5]);
                                    test[0] = '\0';
                                    test0[0] = '\0';
                                    if (!strcmp(get_command_from_client, commands[3]) != 0 || !strcmp(get_command_from_client, test) != 0) {
                                        send(connfd, get_command_from_client, sizeof(get_command_from_client), 0);
                                        read(connfd, get_data_from_client, sizeof(get_data_from_client));

                                        for (int x = 0; x != lines_ip_add_rasp_file; x++) {
                                            if (!strcmp(get_data_from_client+37, all_ip_add_rasp_all[x]+37) != 0) {
                                                exists = 1;
                                            }else {
                                                exists = 0;
                                            }
                                        }
                                        // if garage not exists
                                        if (!exists) {
                                            send(connfd, get_data_from_client, sizeof(get_data_from_client), 0);                                      
                                            read(connfd, get_second_command, sizeof(get_second_command));

                                            // check if garage data were successfully transfered if it is true write 'get_datat_from_client' to file 
                                            if ((!strcmp(get_second_command, commands[3]) != 0) && (!strcmp(check_uuid_client, check_uuid_client) != 0) && (strcmp(get_data_from_client, commands[3]) != 0)) {
                                                strcpy(all_ip_add_rasp_all[lines_ip_add_rasp_file], get_data_from_client);
                                                FILE *garage_ip_file_o = fopen(ip_add_rasp_file, "w");
                                                for (int y = 0; y != lines_ip_add_rasp_file+1; y++) {
                                                    fputs(all_ip_add_rasp_all[y], garage_ip_file_o);
                                                }
                                                fclose(garage_ip_file_o);
                                                lines_ip_add_rasp_file++;
                                                created_new_garage_from_client(check_uuid_client, get_data_from_client+37);
                                            }
                                            already_tried = 0;
                                            break;
                                        // if garage already exists
                                        }else {
                                            failed_create_new_garage_from_client(check_uuid_client, get_data_from_client+37);
                                            send(connfd, commands[4], sizeof(commands[4])+1, 0);
                                            read(connfd, get_second_command, sizeof(get_second_command));
                                            already_tried = 0;
                                            break;
                                        }
                                    // command 5 get garage infos to know which garage is online/offline opened/closed 
                                    }else if (!strcmp(get_command_from_client, commands[5]) != 0 || strcmp(get_command_from_client, test0) != 0) {
                                        int end_garage = 1;
                                        char save_garage_o_c[255][2], save_garage_o_f[255][2], save_garage[255][2];
                                        //if ((!strcmp(save_garage[which_garage], garage[which_garage]) != 0 && !strcmp(save_garage_o_c[which_garage], garage_o_c[which_garage]) != 0 && !strcmp(save_garage_o_f[which_garage], garage_o_f[which_garage]) != 0)) {
                                            char check_command[38] = "", check_garage[2] = "", check_garage_o_f[2] = "", check_garage_o_c[2] = "";

                                                // send which garage
                                                send(connfd, garage[which_garage], sizeof(garage[which_garage]), 0);
                                                strcpy(save_garage[which_garage], garage[which_garage]);
                                                // send state garage offline/online
                                                send(connfd, garage_o_f[which_garage], sizeof(garage_o_f[which_garage]), 0);
                                                strcpy(save_garage_o_f[which_garage], garage_o_f[which_garage]);
                                                // send state garage opened/closed
                                                send(connfd, garage_o_c[which_garage], sizeof(garage_o_c[which_garage]), 0);
                                                strcpy(save_garage_o_c[which_garage], garage_o_c[which_garage]);
                                                system("sleep .55");
                                            already_tried = 0;
                                            break;
                                        //}                      
                                    }else {
                                        send(connfd, commands[14], sizeof(commands[14]), 0);
                                        break;
                                    }
                                }else {
                                    break;
                                }
                            }
                        }

                        // check if client is already online
                        void *check_alive_user() {
                            int check_conn = 0;
                            char *buffer_test;
                            int check_tries = 0;
                            do {
                                check_conn = read(connfd, &buffer_test, 1);
                                // also if the connection is maybe broken 
                                if (!check_conn) {
                                    // close connectin after 2 seconds with no react from client
                                    if (check_tries == 2) {
                                        client_is_on = 0;
                                        break;
                                    }else {
                                        system("sleep 1");
                                        check_tries++;
                                    }
                                }else {
                                    // main stuff to check maybe garage state and recive new garages
                                    main_stuff();
                                }   
                                client_is_on = 1;
                            } while (1);
                            disconnected_main_server(connfd, check_uuid_client);
                            alive_clients_ch--;
                            alive_clients(alive_clients_ch);
                        }

                        pthread_t alive_clients_th;
                        // to check how many clients are at the same time online
                        pthread_create(&alive_clients_th, NULL, check_alive_user, NULL);
                        
                        pthread_join(alive_clients_th, NULL);
                  }

                   for (int x = 0; x > MAX_CLIENTS; x++) {
                        if (user_client[x] == 0) {
                            user_client[x] = connfd;
                            break;
                        }
                    }
                }else {
                    send(connfd, "0000", 5, 0);
                    close(connfd);
                }
                system("sleep .25");
          }
     }
}