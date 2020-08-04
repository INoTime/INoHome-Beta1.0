#define PORT_server 8185
#define BUF_a 30
#define sock_addr struct sockaddr
#define user_info_file_a "files/tmp/user_info"
#define all_useres_file "files/tmp/user_id"
#define server_file "files/tmp/serverIP_add"
#define ip_addr_file "files/tmp/ip_addr_garage"
#define uuid_command_file "files/tmp/commands"

#ifdef _WIN32
    #pragma comment(lib, "Ws2_32.lib")
#endif

int sockfd_server, connfd_server, sockfd_new_garage, connfd_new_garage, super_user_auto_yes = 0;
char get_uuid[38], check_uuid_a[4];
char check_name_garage[31], check_ip_garage[ipv4_len], check_status_garage[4];
char all_garage_ip_addr[9690];
char uuid_command[38*100], check_uuid_command[5];

struct sockaddr_in server_add_server;

// save infos like server name and server ip add to file 
void save_info_add(const char *server_name, const char *ip_add) {
    FILE *server_info = fopen(server_file, "w");
    fputs(crypt_data(ip_add, server_name, crypt_serverIP_add_file), server_info);
    fclose(server_info);
}

// save infos like user name and password also login data to file
void save_user_info(const char *name, const char *password) {
    FILE *user_info = fopen(user_info_file_a, "w");  
    fputs(crypt_data(name, password, crypt_user_info_file), user_info);
    fclose(user_info);
}

void remove_garage_choose() {
    gchar_remove_garage_name = gtk_entry_get_text(GTK_ENTRY(remove_garage_name_entry));

    if (!strcmp(gchar_remove_garage_name, "") != 0) {
        select_language_remove_garage(3, remove_garage_name_retry_label, FALSE);
    }else {
        for (int x = 0; x != 255; x++) {
            // convert data to another data types for strchr
            const char *con_save_name_ip_garage_a = save_name_ip_garage_a[x];
            char ch_remove_garage_name[31];
            sprintf(ch_remove_garage_name, "%8s", gchar_remove_garage_name);
            const char *con_remove_garage_name = ch_remove_garage_name;
            const char con_final_remove_garage_name = *con_remove_garage_name;
            // check where does it found
            if (strchr(con_save_name_ip_garage_a, con_final_remove_garage_name)) {
                // reset everything
                strcpy(save_name_ip_garage_a[x], "");
                strcpy(name_ip_garage, "");

                // set everything to the front of the 2D char
                for (int y = 0; y != 255; y++) {
                    if (!strcmp(save_name_ip_garage_a[y], "") != 0) {
                        strcpy(save_name_ip_garage_a[y], save_name_ip_garage_a[y+1]);
                        strcpy(save_name_ip_garage_a[y+1], "");
                        break;
                    } 
                }

                // write everything to normal output
                for (int y = 0; y != 255; y++) {
                    if (!strcmp(save_name_ip_garage_a[y], "") != 0) {
                        break;
                    }else {
                        strcat(name_ip_garage, save_name_ip_garage_a[y]);
                    }
                }

                // reset with new informations new_garages_label
                gtk_label_set_text(GTK_LABEL(new_garages_label), "");
                gtk_label_set_text(GTK_LABEL(new_garages_label), name_ip_garage);
                
                // reset the send to server variable "save_name_ip_garage"
                strcpy(save_name_ip_garage, "");
                for (int y = 0; y != 255; y++) {
                    if (!strcmp(save_name_ip_garage_a[y], "") != 0) {
                        break;
                    }else {
                        strcat(save_name_ip_garage, save_name_garage_a[y]);
                        strcat(save_name_ip_garage, " :: ");
                        strcat(save_name_ip_garage, save_ip_garage_a[y]);
                        strcat(save_name_ip_garage, "\n");
                    }
                }
                gtk_widget_destroy(remove_garage_window);
                break;
            }
        }
    }
}

void get_all_garges();

// send garages to server 
void end_super_user_access() {
    char uuid_user_and_name_ip_from_garage[9048];
    strcpy(uuid_user_and_name_ip_from_garage, get_uuid);
    strcat(uuid_user_and_name_ip_from_garage, ": ");
    strcat(uuid_user_and_name_ip_from_garage, save_name_ip_garage);
    send(sockfd_server, uuid_user_and_name_ip_from_garage, sizeof(uuid_user_and_name_ip_from_garage), 0);
    read(sockfd_server, check_ip_name_garage, sizeof(check_ip_name_garage));
    if (!strcmp(uuid_user_and_name_ip_from_garage, check_ip_name_garage) != 0) {
        send(sockfd_server, "110", 4, 0);
        // get all garages again 
        get_all_garges();
        gtk_widget_destroy(super_user_access_window);
        // destroy the buffer of the add garage show
        strcpy(name_ip_garage, "");
        strcpy(save_name_ip_garage, "");
        gtk_label_set_text(GTK_LABEL(new_garages_label), "");
        /*#if __APPLE__
            system("osascript -e 'display notification \"Garage ips were send!\" with title \"Garage ip!\" sound name \"Hello\"'");
        #elif __linux__
            system("notify-send 'Garage ip!' 'Garage ips were send!' --icon=dialog-information");
        #endif*/
    }else {
        select_language_super_user_acess(15, check_garage_info_label, NULL);
        send(sockfd_server, "101", 4, 0);
    }
    check_exit_config_server_conn = 0;
}

// sent to server request auto
void super_user_auto_check() {
    send(sockfd_server, super_user_name_password_saved, sizeof(super_user_name_password_saved), 0);
    read(sockfd_server, check_super_user_acess_two, sizeof(check_super_user_acess_two));
    if (!strcmp(check_super_user_acess_two, "011") != 0) {
        end_super_user_access();
        super_user_auto_yes = 1;
    }else {
        select_language_super_user_acess(14, check_garage_info_label, NULL);
    }
}

void get_all_garges() {
    // read all garage ip's from server and write them to file
    read(sockfd_server, all_garage_ip_addr, sizeof(all_garage_ip_addr));
    send(sockfd_server, all_garage_ip_addr, sizeof(all_garage_ip_addr), 0);
    char check_all_garages_ip_addr[4], buf_all_garage_ip_addr[100] = "";
    read(sockfd_server, check_all_garages_ip_addr, sizeof(check_all_garages_ip_addr));
    if (!strcmp(check_all_garages_ip_addr, "111") != 0) {
        FILE *ip_addr_file_o = fopen(ip_addr_file, "w");
        fputs(all_garage_ip_addr, ip_addr_file_o);
        fclose(ip_addr_file_o);
    } 
}

// get all data from server and check them again by reciving
void logged_in_to_server() {
    // get uuid from server and paste it into class
    read(sockfd_server, get_uuid, sizeof(get_uuid));
    // resend uuid to server to check if evrything gone right
    send(sockfd_server, get_uuid, sizeof(get_uuid), 0);
    // check answer from server if everything gone right
    read(sockfd_server, check_uuid_a, sizeof(check_uuid_a));
    if (!strcmp(check_uuid_a, "011") != 0) {
        // write new uuid to file 
        FILE *all_users = fopen(all_useres_file, "w");
        fputs(crypt_data(get_uuid, "", crypt_user_id_file), all_users);
        fclose(all_users);
        u_id.user_id_saved = 1;
    }

    // get all garages from server
    get_all_garges();
    // get all commands from server for client in main application
    read(sockfd_server, uuid_command, sizeof(uuid_command));
    send(sockfd_server, uuid_command, sizeof(uuid_command), 0);
    read(sockfd_server, check_uuid_command, sizeof(check_uuid_command));
    if (!strcmp(check_uuid_command, "1110") != 0) {
        FILE *uuid_command_file_o = fopen(uuid_command_file, "w");
        fputs(uuid_command, uuid_command_file_o);                                                       // !!!!!!!!!!! need to be crypted!!!!
        fclose(uuid_command_file_o);
    }
}

void check_if_user_blocked() {
    char blocked_or_not[5];
    read(sockfd_server, blocked_or_not, sizeof(blocked_or_not));
    if (!strcmp(blocked_or_not, "1111") != 0) {
        check_if_ip_is_blocked = 0;
    }else if (!strcmp(blocked_or_not, "0000") != 0) {
        check_if_ip_is_blocked = 1;
        gtk_widget_set_sensitive(save_info_add_bt, FALSE);
        char system_is_shutting_down_ip_blocked[110];
        select_language_super_user_acess(13, NULL, NULL);
        for (int x = 10; x != 0; x--) {
            sprintf(system_is_shutting_down_ip_blocked, "%s%d.", ip_is_blocked_label, x);
            gtk_label_set_text(GTK_LABEL(error_user_save_label), system_is_shutting_down_ip_blocked);
            system("sleep 1");
        }
        system_end_program();
    }
}

// send to server request
void super_user_acess_server() {
    if (!check_if_ip_is_blocked) {
        // if super_user_auto is not true also 0 try this to get super user data
        strcpy(super_user_name_password, "");
        strcat(super_user_name_password, gchar_super_user_name);
        strcat(super_user_name_password, "\n");
        strcat(super_user_name_password, gchar_super_user_password);
        strcat(super_user_name_password, "\n");
        // if super user auto is activated it will not ask again for super user access
        if (super_user_auto) {
            strcpy(super_user_name_password_saved, super_user_name_password);
        }

        send(sockfd_server, super_user_name_password, sizeof(super_user_name_password), 0);
        read(sockfd_server, check_super_user_acess, sizeof(check_super_user_acess));
        if (!strcmp(check_super_user_acess, "011") != 0) {
            check_again_super_user = 3;
            if (!was_here_super_user) {
                gtk_widget_set_sensitive(super_user_save_bt, TRUE);
                gtk_widget_destroy(super_user_access_window);
                window_theme_color();
                was_here_super_user = 1;
                // start rest of connection client -><- server 
                logged_in_to_server();
            }else {
                end_super_user_access();
            }
        }else {
            check_again_super_user--;
            if (check_again_super_user <= 3) {
                gtk_label_set_text(GTK_LABEL(error_user_save_label), "");
                strcpy(rest_tries_super_user, "");
                select_language_super_user_acess(10, NULL, NULL);
                sprintf(rest_tries_counter, "%d", check_again_super_user);
                strcat(rest_tries_super_user, rest_tries_counter);
                if (check_again_super_user == 1) {
                    select_language_super_user_acess(11, NULL, NULL);
                }else {
                    select_language_super_user_acess(12, NULL, NULL);
                }
                gtk_label_set_text(GTK_LABEL(error_user_save_label), rest_tries_super_user);
                if (check_again_super_user < 1) {
                    gtk_widget_set_sensitive(super_user_save_bt, FALSE);
                    select_language_super_user_acess(9, error_user_save_label, NULL);
                }else {
                    gtk_widget_set_sensitive(super_user_save_bt, TRUE);
                }
            }
            was_here_super_user_only_started = 1;    
        }
    }
}

// get super user acess to connect to server
void get_super_user_acess() {
    gtk_widget_set_sensitive(super_user_save_bt, FALSE);
    gchar_super_user_name = gtk_entry_get_text(GTK_ENTRY(entry_super_user_name));
    gchar_super_user_password = gtk_entry_get_text(GTK_ENTRY(entry_super_user_password));

    if (!strcmp(gchar_super_user_name, "") != 0) {
        select_language_super_user_acess(7, error_user_save_label, NULL);
        gtk_widget_set_sensitive(super_user_save_bt, TRUE);
    }else if (!strcmp(gchar_super_user_password, "") != 0) {
        select_language_super_user_acess(8, error_user_save_label, NULL);
        gtk_widget_set_sensitive(super_user_save_bt, TRUE);
    }else {
        if (was_here_super_user_only_started || was_here_super_user) {
            // if main connection is true and password or username was false to retry 
            super_user_acess_server();
        }else if ((!was_here_super_user && check_again_super_user < 4) || !was_here_super_user_only_started) {
            // start main connection by first try
            start_main_connection_handler();
        }
    }
}

// to search from hostname for ip
void search_ip_garages() {
    struct addrinfo server_add, *request, *pointer;
    int status_server_add = 0;

    memset(&server_add, 0, sizeof(server_add));
    server_add.ai_family = AF_INET;
    server_add.ai_socktype = SOCK_STREAM;

    gtk_label_set_text(GTK_LABEL(check_garage_info_label), "");

    if(status_server_add = getaddrinfo(gchar_name_garage, NULL, &server_add, &request) != 0) {
        select_language_add_garage_entry(8, check_garage_info_label, NULL);
        hostname_or_ip_not_exists = 0;
    }else {
        for (pointer = request; pointer != NULL; pointer = pointer->ai_next) {
            void *addr;
            struct sockaddr_in *ipv4 = (struct sockaddr_in *)pointer->ai_addr;
            addr = &(ipv4->sin_addr);
            inet_ntop(pointer->ai_family, addr, main_server_ip_lookup, sizeof(main_server_ip_lookup));
            strcpy(entry_server_ip_saved, main_server_ip_lookup);
            gtk_entry_set_text(GTK_ENTRY(entry_ip_garage), main_server_ip_lookup);
            select_language_add_garage_entry(7, ip_garage_found, NULL);
            hostname_or_ip_not_exists = 1;
        }
    }
}

void search_ip() {
    struct addrinfo server_add, *request, *pointer;
    int status_server_add = 0;

    memset(&server_add, 0, sizeof(server_add));
    server_add.ai_family = AF_INET;
    server_add.ai_socktype = SOCK_STREAM;

    if(status_server_add = getaddrinfo(server_name, NULL, &server_add, &request) != 0) {
        select_langauge(11, server_ip_found_label, NULL);
    }else {
        for (pointer = request; pointer != NULL; pointer = pointer->ai_next) {
            void *addr;
            struct sockaddr_in *ipv4 = (struct sockaddr_in *)pointer->ai_addr;
            addr = &(ipv4->sin_addr);
            inet_ntop(pointer->ai_family, addr, main_server_ip_lookup, sizeof(main_server_ip_lookup));
            status_ip_hostname_exists = 1;
            strcpy(entry_server_ip_saved, main_server_ip_lookup);
            gtk_entry_set_text(GTK_ENTRY(server_add_entry), main_server_ip_lookup);
            select_langauge(4, server_ip_found_label, NULL);
        }
    }
}
// ----------------------------------------------------------------------------------------------------------------------------------

// main configuration to get uuid (to be registred on server)
void main_configuration() {
    if (!was_here_super_user || !was_here_super_user_only_started) {
        #ifdef _WIN32
            WORD wsaRequest;
            WSADATA wsaData;
            int iResult;
            wsaRequest = MAKEWORD(2, 2);

            iResult = WSAStartup(wsaRequest, &wsaData);
            if (iResult != 0) {
                printf("WSAStartup started! %d\n", iResult);
            }
        #endif
        // get new (for new user) user uuid from server
        sockfd_server = socket(AF_INET, SOCK_STREAM, 0);
        if (sockfd_server == -1) errorSock();

        memset(&server_add_server, BUF_a, sizeof(server_add_server));
        server_add_server.sin_family = AF_INET;
        server_add_server.sin_addr.s_addr = inet_addr(ip_add);
        server_add_server.sin_port = htons(PORT_server);

        while (connfd_server = connect(sockfd_server, (sock_addr * ) &server_add_server, sizeof(server_add_server)) != 0);
        check_if_user_blocked();
    }
}

void send_garge_server_ip() {
    gtk_widget_set_sensitive(save_all_new_garages_bt, FALSE);
    check_if_user_blocked();
    // to send what server must do next close connection or be still alive to create new garages with super user rights
    send(sockfd_server, "111", 4, 0);
    if (super_user_auto) {
        // if super user acess is on        
        super_user_auto_check();
    }else {
        // if super user acess is off
        super_user_acess();
    }
}

// exit configuration connection 
void exit_config_send() {
    send(sockfd_server, "000", 4, 0);
    close(sockfd_server);
#ifdef _WIN32
    WSACleanup();
#endif
}
