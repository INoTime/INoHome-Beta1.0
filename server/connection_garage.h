// 0 verify garage
// 1 garage door is closed
// 2 garage door is opened
// 3 garage is turning offline

int connfd_garage, alive_garages = 0;
void *check_alive_garages() {
    int check_conn = 0;
    char *buffer_test;
    int check_tries = 0;
    do {
        check_conn = read(connfd_garage, &buffer_test, 1);
        // also if the connection is maybe broken 
        if (!check_conn) {
            // close connectin after 2 seconds with no react from client
            if (check_tries == 2) {
                break;
            }else {
                system("sleep 1");
                check_tries++;
            }
        }else {
            system("sleep .25");
        }   
    } while (1);
    alive_garages--;
}

void *garage_conn() {
    fd_set readfds_garage;
    int sockfd_garage, len_garage = sizeof(my_addr_garage), y_check_garage = 1, garage_cout[MAX_CLIENTS], rc_garage;
    // set all client ports to 0
    for (int x = 0; x != MAX_CLIENTS; x++) garage_cout[x] = 0;
    // set master socket and set setsockopt to open fast new connections 
    sockfd_garage = socket(AF_INET, SOCK_STREAM, 0);
    setsockopt(sockfd_garage, SOL_SOCKET, SO_REUSEADDR, &y_check_garage, sizeof(y_check_garage));
    if (sockfd_garage == -1) errorSock();

    memset(&server_add_garage, BUF_a, sizeof(server_add_garage));
    server_add_garage.sin_family = AF_INET;
    server_add_garage.sin_addr.s_addr = htonl(INADDR_ANY);
    server_add_garage.sin_port = htons(PORT_garage);

    bind(sockfd_garage, (sock_addr_garage *) &server_add_garage, sizeof(server_add_garage));
    if (listen(sockfd_garage, 5) != 0) errorListen();
    while(1) {
        FD_ZERO(&readfds_garage);
        FD_SET(sockfd_garage, &readfds_garage);

        for(int x = 0; x < MAX_CLIENTS; x++) {
            if (garage_cout[x] > 0) FD_SET(garage_cout[x], &readfds_garage);
        }

        #if defined(__linux__) || defined( __apple__)
            rc_garage = select(sockfd_garage + 1, &readfds_garage, NULL, NULL, NULL);
        #elif _Win32
            rc_garage = select(0, &readfds_garage, NULL, NULL, NULL);
        #endif
        if (FD_ISSET(sockfd_garage, &readfds_garage)) {
            connfd_garage = accept(sockfd_garage, (sock_addr_garage *)&cli_garage, &len_garage);
            alive_garages++;
            printf("Alive garages: %d\n", alive_garages);
                
            char verifying_garage[40], ipv4_garage[INET_ADDRSTRLEN], ipv4_garage_changed[INET_ADDRSTRLEN+2], garage_crypt_file[INET_ADDRSTRLEN+25], buf_garage_crypt[40], garage_crypt_all[255][40];
            char check_garage_command[40], end_garage_conn[40];
            int lines_garage_crypt = 0;

            struct sockaddr_in *s = (struct sockaddr_in *)&cli_garage;
            inet_ntop(AF_INET, &s->sin_addr, ipv4_garage, sizeof(ipv4_garage));
            
            printf("a\n");
            /*pthread_t alive_garages_th;
            pthread_create(&alive_garages_th, NULL, check_alive_garages, NULL);
            pthread_join(alive_garages_th, NULL);
*/
            // choose file to read crypt to get states if garage is opened or closed
            strcpy(garage_crypt_file, PATH_crypt_garage);
            strcat(garage_crypt_file, ipv4_garage);

            FILE *garage_crypt_file_o = fopen(garage_crypt_file, "r+");
            while (fgets(buf_garage_crypt, sizeof(buf_garage_crypt), garage_crypt_file_o) != NULL) {
                strcpy(garage_crypt_all[lines_garage_crypt], buf_garage_crypt);
                lines_garage_crypt++;
            }
            read(connfd_garage, verifying_garage, sizeof(verifying_garage));
            send(connfd_garage, verifying_garage, sizeof(verifying_garage), 0);
            strcat(verifying_garage, "\n");
            if (!strcmp(verifying_garage, garage_crypt_all[0]) != 0) {
                // set garage status to online in main connection
                while (1) {
                    int x = 0;
                    for (x = 0; x != lines_ip_add_rasp_file; x++) {
                        if (strstr(all_ip_add_rasp_all[x], ipv4_garage) && client_is_on) {
                            which_garage = x;
                            strcpy(garage_o_f[x], "1");
                            char a[4];
                            sprintf(a, "%d", x);
                            strcpy(garage[x], a);
                            break;
                        }
                    }                   
                
                    read(connfd_garage, check_garage_command, sizeof(check_garage_command));
                    if (!strcmp(garage_crypt_all[1], check_garage_command) != 0) {
                        // garage is closed
                        printf("garage is closed\n");
                        strcpy(garage_o_c[x], "0");
                    }else if (!strcmp(garage_crypt_all[2], check_garage_command) != 0) {
                        // garage is opened
                        printf("garage is opened\n");
                        strcpy(garage_o_c[x], "1");
                    }

                    read(connfd_garage, end_garage_conn, sizeof(end_garage_conn));
                    if (!strcmp(garage_crypt_all[3], end_garage_conn) != 0) {
                        break;
                    }
                    system("sleep .15");
                }
            }
            
            
            for (int x = 0; x > MAX_CLIENTS; x++) {
                if (garage_cout[x] == 0) {
                    garage_cout[x] = connfd_garage;
                    break;
                }
            }
            close(connfd_garage);
        }
    }
}