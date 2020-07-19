// command file
// 0 connect to server to check
// 1 read all garages from server
// 2 all garages false server output
// 3 send all garages to server
// 4 read garage stats
// 5 send garage
// 6 delete garage

// start main connection from thread
#define PORT_server 3111
#define BUF_a 30
#define sock_addr struct sockaddr

#ifdef _WIN32
    #pragma comment(lib, "Ws2_32.lib")
#endif

int sockfd_server, connfd_server;

struct sockaddr_in server_add_server;

static void mainConnectionServer();

static void send_new_garage() {
    char complete_data_to_send[120] = "", buff_commands[120] = "", buf_callback_from_server[120] = "", buf_callback_command_from_server[120] = "";
    
    // send command 3 that server know what have to do
    send(sockfd_server, commands[3], sizeof(commands[3]), 0);
    g_print("%s\n", commands[3]);
    read(sockfd_server, buf_commands, sizeof(buf_commands));
    g_print("%s\n", buf_commands);
    char test[40] = "";
    strcpy(test, commands[3]);
    test[0] = '\0';
    if (!strcmp(commands[3], buf_commands) != 0 || !strcmp(test, buf_commands) != 0) {
        // send complete data to server
        // command 3/4/14 (send new garage to server)
        // command 14 is the fallback command if something not worked
        strcat(complete_data_to_send, user_uuid);
        strcat(complete_data_to_send, ": ");
        strcat(complete_data_to_send, gchar_hostname_garage);
        strcat(complete_data_to_send, " :: ");
        strcat(complete_data_to_send, gchar_ip_garage);
        strcat(complete_data_to_send, "\n");
        send(sockfd_server, complete_data_to_send, sizeof(complete_data_to_send), 0);
        read(sockfd_server, buf_callback_from_server, sizeof(buf_callback_from_server));
        // check if evrything ok then send command 3 to check
        if (!strcmp(complete_data_to_send, buf_callback_from_server) != 0) {
            send(sockfd_server, commands[3], sizeof(commands[3]), 0);
            select_language_get_garage_settings(14, error_garage_settings_label, NULL);
        // ip was there and couldnt create the garage
        }else {
            send(sockfd_server, commands[4], sizeof(commands[4]), 0);
            select_language_get_garage_settings(15, error_garage_settings_label, NULL);
        }
    }else {
        select_language_get_garage_settings(16, error_garage_settings_label, NULL);
    }
    gtk_widget_set_sensitive(garage_settings_save_bt, TRUE);
}

// check if main connection to server is here
static void send_garage_to_server() {
    gtk_widget_set_sensitive(garage_settings_save_bt, FALSE);
    if (connection_server_is_true) {
        // try to send new garage to server
        send_new_garage();
    }else {
        // connecting to server to send new garages
        select_language_get_garage_settings(13, error_garage_settings_label, NULL);             // !!!!!!!!!! work here
        main_connection_handler();
        send_new_garage();
    }
}

int buf_check_o_of[255], buf_check_o_c[255];

// load garage states
static void check_garage_state() {
    // while disconnect button was not clicked    
    while (1) {
        char check_command[38] = "", check_state[2] = "", check_state_o_f[2] = "";
        char check_state_o_c[2] = "";
        // send command to server and read
        send(sockfd_server, commands[5], sizeof(commands[5]), 0);
        char test[40] = "";
        strcpy(test, commands[5]);
        test[0] = '\0';
        if (!strcmp(commands[5], check_command) != 0 || !strcmp(test, check_command) != 0) {
            // read which garage
            read(sockfd_server, check_state, sizeof(check_state));
            // read garage is online/offline
            read(sockfd_server, check_state_o_f, sizeof(check_state_o_f));
            // read garage state is closed/opened
            read(sockfd_server, check_state_o_c, sizeof(check_state_o_c));
                
            // need to know which garage is selected
            int choose_garage = atoi(check_state);

            // set status bar if garage is online/offline
            if (!strcmp(check_state_o_f, "1") != 0) {
                // if garage is online and if garage was not setted online yet
                if (buf_check_o_of[choose_garage] == 0) {
                    buf_check_o_of[choose_garage] = 1;
                    // if garge is online but closed check check if garage is longer online or not if it dont update label
                    select_language_main_window(2, 1, all_garages[choose_garage], " Online", garage_name_ip_label[choose_garage], theme_box_image_offline[choose_garage]);
                }
            }else if (!strcmp(check_state_o_f, "0") != 0) {
                // if garage is offline befor check check if garge is longer offline or not if it dont update label
                if (buf_check_o_of[choose_garage] == 1) {
                    buf_check_o_of[choose_garage] = 0;
                    select_language_main_window(2, 0, all_garages[choose_garage], " Offline", garage_name_ip_label[choose_garage], theme_box_image_offline[choose_garage]);
                }
            }
            int checked_cout_all_garages_out = 2, f = 0;
            for (f = 0; f != 255; f++) {
                if (choose_garage%3 == f) {
                    break;
                }
            }
            // change image so user could easier check if garge is opened or not
            if (!strcmp(check_state_o_c, "1") != 0) {
                if (buf_check_o_c[choose_garage] == 0) {
                    buf_check_o_c[choose_garage] = 1;
                    theme_box_image[choose_garage] = gtk_event_box_new();
                    image[choose_garage] = gtk_image_new_from_file("images/inoinvestigation.jpg");
                    garage_name_ip_label[choose_garage] = gtk_label_new(all_garages[choose_garage]);
                    gtk_container_add(GTK_CONTAINER(theme_box_image[choose_garage]), image[choose_garage]);
                    g_signal_connect(G_OBJECT(theme_box_image[choose_garage]), "button_press_event", G_CALLBACK(get_garage_settings), NULL);
                        
                    if (choose_garage == 0 || choose_garage%3 == f) {
                        gtk_grid_attach(GTK_GRID(grid), theme_box_image[choose_garage], 3, choose_garage+2, 1, 1);
                    }else {
                        gtk_grid_attach(GTK_GRID(grid), theme_box_image[choose_garage], checked_cout_all_garages_out+2, choose_garage-checked_cout_all_garages_out+2, 1, 1);
                    }                        
                    gtk_widget_destroy(theme_box_image_offline[choose_garage]);          
                    gtk_widget_show(image[choose_garage]);    
                    gtk_widget_show(theme_box_image[choose_garage]);
                }
            }else if (!strcmp(check_state_o_c, "0") != 0) {
                if (buf_check_o_c[choose_garage] == 1) {
                    buf_check_o_c[choose_garage] = 0;
                    theme_box_image_offline[choose_garage] = gtk_event_box_new();
                    image_offline[choose_garage] = gtk_image_new_from_file("images/inoinvestigationLogin.png");
                    gtk_container_add(GTK_CONTAINER(theme_box_image_offline[choose_garage]), image_offline[choose_garage]);
                    g_signal_connect(G_OBJECT(theme_box_image_offline[choose_garage]), "button_press_event", G_CALLBACK(get_garage_settings), NULL);
                   
                    if (choose_garage == 0 || choose_garage%3 == f) {
                        gtk_grid_attach(GTK_GRID(grid), theme_box_image_offline[choose_garage], 3, choose_garage+2, 1, 1);
                    }else {
                        gtk_grid_attach(GTK_GRID(grid), theme_box_image_offline[choose_garage], checked_cout_all_garages_out+2, choose_garage-checked_cout_all_garages_out+3, 1, 1);
                    }
                    gtk_widget_destroy(theme_box_image[choose_garage]);    
                    gtk_widget_show(image_offline[choose_garage]);
                    gtk_widget_show(theme_box_image_offline[choose_garage]);
                }
            }        
       }else if (!strcmp(check_command, commands[14]) != 0) {
           g_print("error garage state handler\n");
       }
       system("sleep .55");
    }
    // send that server dont want to recive more garage states
    send(sockfd_server, "0000", 5, 0);
}

// check if server is online
static void check_server_state() {
    int check_conn = 0;
    char *buffer_test;
    int check_tries = 0;
    do {
        check_conn = read(sockfd_server, &buffer_test, 1);
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
    connection_server_is_true = 0;
    select_language_main_window(0, 1, NULL, NULL, server_status_label, NULL);
}

static gboolean rest_progress_bar() {
    return FALSE;
}

static void mainConnectionServer() {
    if (!connection_server_is_true) {
        #ifdef _WIN32
            WORD wsaRequest;
            WSADATA wsaData;
            int iResult;
            wsaRequest = MAKEWORD(2, 2);

            iResult = WSAStartup(wsaRequest, &wsaData);

        #endif
        // get new (for new user) user uuid from server
        sockfd_server = socket(AF_INET, SOCK_STREAM, 0);

        memset(&server_add_server, BUF_a, sizeof(server_add_server));
        server_add_server.sin_family = AF_INET;
        server_add_server.sin_addr.s_addr = inet_addr(server_data[0]);
        server_add_server.sin_port = htons(PORT_server);
        // progress bar
        gdouble fraction = 0.0;
        if (!loged_in) {
            gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(connecting_to_server_progress_bar), fraction);
            //g_timeout_add(500, rest_progress_bar, GTK_PROGRESS_BAR(connecting_to_server_progress_bar));
        }

        while (connfd_server = connect(sockfd_server, (sock_addr * ) &server_add_server, sizeof(server_add_server)) != 0) system("sleep .25");
        // check if ip is blocked on server
        read(sockfd_server, buffer_blocked_ip, sizeof(buffer_blocked_ip));
        if (!loged_in) {
            fraction += 0.25;
            gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(connecting_to_server_progress_bar), fraction);
        }
        // ip is not blocked
        if (!strcmp(buffer_blocked_ip, "1111") != 0) {
            // send user uuid 
            send(sockfd_server, user_uuid, sizeof(user_uuid), 0);

            // send first command to check on server
            send(sockfd_server, commands[0], sizeof(commands[0]), 0);                                    // command 0
            if (!loged_in) {
                fraction += 0.25;
                gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(connecting_to_server_progress_bar), fraction);
            }

            // read all garage ips to be uptodate and resend to check
            read(sockfd_server, buffer_all_garage_ips, sizeof(buffer_all_garage_ips));
            // save all new garages to file
            FILE *set_all_garages_o = fopen(ip_addr_garage_file, "w");
            fputs(buffer_all_garage_ips, set_all_garages_o);
            fclose(set_all_garages_o);
            // read again all garages for main window 
            if (already_loaded) {
                for (int x = 0; x != cout_all_garages; x++) {
                    gtk_widget_destroy(garage_name_ip_label[x]);
                    gtk_widget_destroy(theme_box_image_offline[x]);
                }
            }
            // write all garage ips and hostnames to file
            read_all_garage_ips();

            if (!loged_in) {
                fraction += 0.25;
                gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(connecting_to_server_progress_bar), fraction);
            }
            

            if (!loged_in) {
                fraction += 0.25;
                gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(connecting_to_server_progress_bar), fraction);
            }
             
            connection_server_is_true = 1;
            ip_add_is_blocked = 0;
            main_connection_server_state_handler();
        // ip is blocked on server
        }else {
            // if it is the connecting to server window
            if (connecting_to_server_window_check) {
                select_language_connecting_to_server(4, connecting_to_server_error, NULL);
            }
            ip_add_is_blocked = 1;
        }
    }else {
        // start main server client program because main connection is true
        select_language_main_window(1, 1, NULL, NULL, server_status_label, NULL);
        // print that client is actually connected to server  
    }
}