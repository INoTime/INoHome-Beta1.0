// set theme automatically to window just call this function and set the window name
static void set_theme(GtkWidget *window) {
    gtk_widget_set_name(window, my_window_css);
    cssProvider = gtk_css_provider_new();
    gtk_css_provider_load_from_path(cssProvider, light_theme_style, NULL);
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(cssProvider), GTK_STYLE_PROVIDER_PRIORITY_USER);
    my_style();
}

static void go_next_without_connection() {
    gtk_widget_destroy(connecting_to_server_window);
    main_screen();
}

static void connecting_to_server() {
    connecting_to_server_window_check = 1;
    connecting_to_server_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(connecting_to_server_window), "INoInvestigation Garage");
    gtk_window_set_default_size(GTK_WINDOW(connecting_to_server_window), 400, 200);
    gtk_container_set_border_width(GTK_CONTAINER(connecting_to_server_window), 10);
    gtk_window_set_position(GTK_WINDOW(connecting_to_server_window), GTK_WIN_POS_CENTER);
    gtk_window_set_icon_from_file(GTK_WINDOW(connecting_to_server_window), MAIN_IMAGE_NAME, NULL);
    gtk_window_set_decorated(GTK_WINDOW(connecting_to_server_window), FALSE);
    gtk_widget_set_name(connecting_to_server_window, my_window_css);    

    connecting_to_server_grid = gtk_grid_new(); 
    gtk_container_add(GTK_CONTAINER(connecting_to_server_window), connecting_to_server_grid);
    gtk_grid_set_row_spacing(GTK_GRID(connecting_to_server_grid), 0);

    // connecting to server label
    wdP->label = gtk_label_new("");
    gtk_grid_attach(GTK_GRID(connecting_to_server_grid), wdP->label, 0, 1, 1, 1);
    select_language_connecting_to_server(1, wdP->label, NULL);

    connecting_to_server_progress_bar = gtk_progress_bar_new();
    gtk_grid_attach(GTK_GRID(connecting_to_server_grid), connecting_to_server_progress_bar, 0, 2, 1, 1);

    // go next without connection button 
    wdP->button = gtk_button_new_with_label("");
    g_signal_connect(wdP->button, "clicked", G_CALLBACK(go_next_without_connection), NULL);
    gtk_grid_attach(GTK_GRID(connecting_to_server_grid), wdP->button, 0, 3, 1, 1);
    select_language_connecting_to_server(2, NULL, wdP->button);

    connecting_to_server_error = gtk_label_new("");
    gtk_grid_attach(GTK_GRID(connecting_to_server_grid), connecting_to_server_error, 0, 4, 1, 1);

    wdP->button = gtk_button_new_with_label("");
    g_signal_connect(wdP->button, "clicked", G_CALLBACK(system_end_program), NULL);
    gtk_grid_attach(GTK_GRID(connecting_to_server_grid), wdP->button, 1, 5, 1, 1);
    select_language_connecting_to_server(3, NULL, wdP->button);

    gtk_widget_show_all(connecting_to_server_window);
}

// if F1 key was pressed
gboolean key_pressed_main_screen(GtkWidget *widget, GdkEventKey *event, gpointer data) {
    if (!strcmp("F1", gdk_keyval_name(event->keyval))) {
        main_connection_main_screen_handler();
        return TRUE;
    }
    return FALSE;
}
static void load_garages() {
    // garages
        for (int x = 1; x != cout_all_garages+1; x++) {
            image_offline[x] = gtk_image_new_from_file("images/inoinvestigationLogin.png");
            garage_name_ip_label[x-1] = gtk_label_new(all_garages[x-1]);
            theme_box_image_offline[x-1] = gtk_event_box_new();
            gtk_container_add(GTK_CONTAINER(theme_box_image_offline[x-1]), image_offline[x]);
            g_signal_connect(G_OBJECT(theme_box_image_offline[x-1]), "button_press_event", G_CALLBACK(get_garage_settings), NULL);
            
            if (cout_all_garages_out == my_garages_line) {
                cout_all_garages_out = 0;
                gtk_grid_attach(GTK_GRID(grid), garage_name_ip_label[x-1], 1, x+1, 1, 1);
                gtk_grid_attach(GTK_GRID(grid), theme_box_image_offline[x-1], 1, x+2, 1, 1);
            }else {
                cout_all_garages_out++;
                gtk_grid_attach(GTK_GRID(grid), garage_name_ip_label[x-1], cout_all_garages_out+2, x-cout_all_garages_out+1, 1, 1);
                gtk_grid_attach(GTK_GRID(grid), theme_box_image_offline[x-1], cout_all_garages_out+2, x-cout_all_garages_out+2, 1, 1);
            }        

            buf_check_o_of[x] = 0;   
            select_language_main_window(2, 0, all_garages[x-1], " Offline", garage_name_ip_label[x-1], theme_box_image_offline[x-1]);

            gtk_widget_show_all(wdP->window);
        }
        already_loaded = 1;
}

// main screen (first window)
static void main_screen() {
    if (loged_in) {
        is_on_first_window = 1;
        wdP->window = gtk_application_window_new(programApp);
        gtk_window_set_title(GTK_WINDOW(wdP->window), "INoHome");
        gtk_window_set_default_size(GTK_WINDOW(wdP->window), 800, 400);
        gtk_window_set_position(GTK_WINDOW(wdP->window), GTK_WIN_POS_CENTER);
        gtk_widget_set_name(wdP->window, my_window_css);
        gtk_window_set_icon_from_file(GTK_WINDOW(wdP->window), MAIN_IMAGE_NAME, NULL);
        g_signal_connect(wdP->window, "destroy", G_CALLBACK(system_end_program), NULL);
        gtk_widget_add_events(wdP->window, GDK_KEY_PRESS_MASK);
        gtk_container_set_border_width(GTK_CONTAINER(wdP->window), 10);
        g_signal_connect(GTK_WIDGET(wdP->window), "key_press_event", G_CALLBACK(key_pressed_main_screen), NULL);

        grid = gtk_grid_new(); 
        scrolled_window = gtk_scrolled_window_new(NULL, NULL);
        gtk_container_set_border_width(GTK_CONTAINER(scrolled_window), 10);

        gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
        gtk_container_add(GTK_CONTAINER(wdP->window), scrolled_window);
        gtk_container_add(GTK_CONTAINER(scrolled_window), grid);
        gtk_grid_set_row_spacing(GTK_GRID(grid), 0);

        server_status_label = gtk_label_new("");
        gtk_grid_attach(GTK_GRID(grid), server_status_label, 0, 1, 1, 1);
        if (!ip_add_is_blocked && loged_in) {
            select_language_main_window(1, 1, NULL, NULL, server_status_label, NULL);
        }else {
            select_language_main_window(0, 0, NULL, NULL, server_status_label, NULL);
        }
        
        if (!already_loaded) {
            load_garages();
        }

        main_connection_garage_state_handler();

        gtk_widget_show_all(wdP->window);
    }else {
        get_acess();
    }
    gtk_main();
}

// connect to server button callback
static void connect_to_server() {
    printf("connecting\n");
}

static void dark_theme_activate() {
    style_mode = 1;
    my_style();
    FILE *dark_theme_activate_file_o = fopen(check_my_style_file, "w");
    fputs(crypt_data("dark_theme", "", crypt_check_my_style_file), dark_theme_activate_file_o);
    fclose(dark_theme_activate_file_o);
}

static void light_theme_activate() {
    style_mode = 0;
    my_style();
    FILE *light_theme_activate_file_o = fopen(check_my_style_file, "w");
    fputs(crypt_data("light_theme", "", crypt_check_my_style_file), light_theme_activate_file_o);
    fclose(light_theme_activate_file_o);
}

// get app settings to change something
static void get_app_settings() {
    GtkWidget *app_settings_window, *app_settings_grid, *on_theme_box, *off_theme_box, *dark_theme_image, *light_theme_image;
    app_settings_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(app_settings_window), "INoInvestigation App Settings");
    gtk_window_set_default_size(GTK_WINDOW(app_settings_window), 600, 700);
    gtk_container_set_border_width(GTK_CONTAINER(app_settings_window), 10);
    gtk_window_set_position(GTK_WINDOW(app_settings_window), GTK_WIN_POS_CENTER);
    set_theme(app_settings_window);

    app_settings_grid = gtk_grid_new(); 
    gtk_container_add(GTK_CONTAINER(app_settings_window), app_settings_grid);
    gtk_grid_set_row_spacing(GTK_GRID(app_settings_grid), 0);

    on_theme_box = gtk_event_box_new();
    dark_theme_image = gtk_image_new_from_file("images/window_style/dark_theme_on.png");
    gtk_container_add(GTK_CONTAINER(on_theme_box), dark_theme_image);
    g_signal_connect(G_OBJECT(on_theme_box), "button_press_event", G_CALLBACK(dark_theme_activate), dark_theme_image);
    gtk_grid_attach(GTK_GRID(app_settings_grid), on_theme_box, 1, 1, 1, 1);

    off_theme_box = gtk_event_box_new();
    light_theme_image = gtk_image_new_from_file("images/window_style/dark_theme_off.png");
    gtk_container_add(GTK_CONTAINER(off_theme_box), light_theme_image);
    g_signal_connect(G_OBJECT(off_theme_box), "button_press_event", G_CALLBACK(light_theme_activate), light_theme_image);
    gtk_grid_attach(GTK_GRID(app_settings_grid), off_theme_box, 2, 1, 1, 1);

    gtk_widget_show_all(app_settings_window);
}

static void get_client_settings();

static void change_user_name_check() {
    const gchar *gchar_change_user_name_entry = gtk_entry_get_text(GTK_ENTRY(change_user_name_entry));
    if (!strcmp(gchar_change_user_name_entry, "") != 0) {
        select_language_change_user_name(4, change_user_name_error_label, NULL);
    }else {
        FILE *user_name_file_o = fopen(user_info_file, "w");
        fputs(gchar_change_user_name_entry, user_name_file_o);
        fputs(pwd_a[1], user_name_file_o);
        fclose(user_name_file_o);

        strcpy(pwd_a[0], gchar_change_user_name_entry);

        get_client_settings();
        gtk_widget_destroy(change_user_name_window);
    }
}

// get client settings to change something
static void change_user_name() {
    gtk_widget_destroy(client_settings_window);
    const gchar *change_user_name_entry_a = "change_user_name_entry", *change_user_name_save_bt_a = "change_user_name_save_bt";
    
    change_user_name_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(change_user_name_window), "INoInvestigation Username");
    gtk_window_set_default_size(GTK_WINDOW(change_user_name_window), 200, 100);
    gtk_container_set_border_width(GTK_CONTAINER(change_user_name_window), 10);
    gtk_window_set_position(GTK_WINDOW(change_user_name_window), GTK_WIN_POS_CENTER);
    set_theme(change_user_name_window);

    change_user_name_grid = gtk_grid_new(); 
    gtk_container_add(GTK_CONTAINER(change_user_name_window), change_user_name_grid);
    gtk_grid_set_row_spacing(GTK_GRID(change_user_name_grid), 0);    

    change_user_name_label = gtk_label_new("");
    gtk_grid_attach(GTK_GRID(change_user_name_grid), change_user_name_label, 0, 1, 1, 1);
    select_language_change_user_name(1, change_user_name_label, NULL);

    change_user_name_entry = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(change_user_name_grid), change_user_name_entry, 1, 1, 1, 1);
    gtk_entry_set_max_length(GTK_ENTRY(change_user_name_entry), 31);
    select_language_change_user_name(2, change_user_name_entry, NULL);
    gtk_widget_set_name(change_user_name_entry, change_user_name_entry_a);

    change_user_name_error_label = gtk_label_new("");
    gtk_grid_attach(GTK_GRID(change_user_name_grid), change_user_name_error_label, 0, 2, 1, 1);

    change_user_name_save_bt = gtk_button_new_with_label("");
    g_signal_connect(change_user_name_save_bt, "clicked", G_CALLBACK(change_user_name_check), NULL);
    gtk_grid_attach(GTK_GRID(change_user_name_grid), change_user_name_save_bt, 1, 2, 1, 1);
    select_language_change_user_name(3, NULL, change_user_name_save_bt);
    gtk_widget_set_name(change_user_name_save_bt, change_user_name_save_bt_a);

    gtk_widget_show_all(change_user_name_window);
}

static void change_password_check() {
    const gchar *gchar_change_password_entry = gtk_entry_get_text(GTK_ENTRY(change_password_entry));
    if (!strcmp(gchar_change_password_entry, "") != 0) {
        select_language_change_password(5, change_password_error_label, NULL);
    }else {
        FILE *user_name_file_o = fopen(user_info_file, "w");
        fputs(crypt_data(pwd_a[0], (char *)gchar_change_password_entry, crypt_user_info_file), user_name_file_o);
        fclose(user_name_file_o);

        strcpy(pwd_a[1], gchar_change_password_entry);

        get_client_settings();
        gtk_widget_destroy(change_password_window);
    }
}

static void change_user_password_show_passw() {
    if (change_user_password_show_passw_cout) {
        gtk_entry_set_visibility(GTK_ENTRY(change_password_entry), FALSE);
        gtk_button_set_label(GTK_BUTTON(change_password_show_bt), bad_face_passwd);
        change_user_password_show_passw_cout = 0;
    }else {
        gtk_entry_set_visibility(GTK_ENTRY(change_password_entry), TRUE);
        gtk_button_set_label(GTK_BUTTON(change_password_show_bt), smile_face_passwd);
        change_user_password_show_passw_cout = 1;
    }
}

static void change_user_password() {
    gtk_widget_destroy(client_settings_window);
    const gchar *chahnge_password_entry_a = "chahnge_password_entry", *change_password_show_bt_a = "change_user_password_bt", *change_password_save_bt_a = "change_password_save_bt"; 

    change_password_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(change_password_window), "INoInvestigation Username");
    gtk_window_set_default_size(GTK_WINDOW(change_password_window), 200, 100);
    gtk_container_set_border_width(GTK_CONTAINER(change_password_window), 10);
    gtk_window_set_position(GTK_WINDOW(change_password_window), GTK_WIN_POS_CENTER);
    set_theme(change_password_window);

    change_password_grid = gtk_grid_new(); 
    gtk_container_add(GTK_CONTAINER(change_password_window), change_password_grid);
    gtk_grid_set_row_spacing(GTK_GRID(change_password_grid), 0);  

    change_password_label = gtk_label_new("");
    gtk_grid_attach(GTK_GRID(change_password_grid), change_password_label, 0, 1, 1, 1);
    select_language_change_password(1, change_password_label, NULL);

    change_password_entry = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(change_password_grid), change_password_entry, 1, 1, 1, 1);
    gtk_entry_set_max_length(GTK_ENTRY(change_password_entry), 25);
    gtk_entry_set_visibility(GTK_ENTRY(change_password_entry), FALSE);
    select_language_change_password(2, change_password_entry, NULL);
    gtk_widget_set_name(change_password_entry, chahnge_password_entry_a);

    change_password_show_bt = gtk_button_new_with_label(bad_face_passwd);
    g_signal_connect(change_password_show_bt, "clicked", G_CALLBACK(change_user_password_show_passw), NULL);
    gtk_grid_attach(GTK_GRID(change_password_grid), change_password_show_bt, 2, 1, 1, 1);
    select_language_change_password(3, NULL, change_password_show_bt);
    gtk_widget_set_name(change_password_show_bt, change_password_show_bt_a);

    change_password_error_label = gtk_label_new("");
    gtk_grid_attach(GTK_GRID(change_password_grid), change_password_error_label, 0, 2, 1, 1);

    change_password_save_bt = gtk_button_new_with_label("");
    g_signal_connect(change_password_save_bt, "clicked", G_CALLBACK(change_password_check), NULL);
    gtk_grid_attach(GTK_GRID(change_password_grid), change_password_save_bt, 1, 2, 1, 1);
    select_language_change_password(4, NULL, change_password_save_bt);
    gtk_widget_set_name(change_password_save_bt, change_password_save_bt_a);

    gtk_widget_show_all(change_password_window);
}

static void show_user_password() {
    if (password_show_cout) {
        slect_language_client_settings(9, "******", user_password_label, NULL);
        gtk_button_set_label(GTK_BUTTON(user_password_show_bt), bad_face_passwd);
        password_show_cout = 0;
    }else {
        slect_language_client_settings(9, pwd_a[1], user_password_label, NULL);
        gtk_button_set_label(GTK_BUTTON(user_password_show_bt), smile_face_passwd);
        password_show_cout = 1;
    }
}

char buffer_host[256];
char *ip_add;
struct hostent *host_entry;
int hostname;

static void get_host_ip_add() {
    hostname = gethostname(buffer_host, sizeof(buffer_host));
    host_entry = gethostbyname(buffer_host);
    ip_add = inet_ntoa(*((struct in_addr*) host_entry->h_addr_list[0]));
}

static void get_client_settings() {
    get_host_ip_add();
    const gchar *user_name_change_bt_a = "user_name_change_bt", *user_password_show_bt_a = "user_password_show_bt", *user_password_change_bt_a = "user_password_change_bt";

    client_settings_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(client_settings_window), "INoInvestigation Client Settings");
    gtk_window_set_default_size(GTK_WINDOW(client_settings_window), 450, 220);
    gtk_container_set_border_width(GTK_CONTAINER(client_settings_window), 10);
    gtk_window_set_position(GTK_WINDOW(client_settings_window), GTK_WIN_POS_CENTER);
    set_theme(client_settings_window);

    client_settings_grid = gtk_grid_new(); 
    gtk_container_add(GTK_CONTAINER(client_settings_window), client_settings_grid);
    gtk_grid_set_row_spacing(GTK_GRID(client_settings_grid), 0);

    user_name_label = gtk_label_new("");
    gtk_grid_attach(GTK_GRID(client_settings_grid), user_name_label, 0, 1, 1, 1);
    slect_language_client_settings(1, pwd_a[0], user_name_label, NULL);
    user_name_change_bt = gtk_button_new_with_label("");
    g_signal_connect(user_name_change_bt, "clicked", G_CALLBACK(change_user_name), NULL);
    gtk_grid_attach(GTK_GRID(client_settings_grid), user_name_change_bt, 1, 1, 1, 1);
    slect_language_client_settings(6, NULL, NULL, user_name_change_bt);
    gtk_widget_set_name(user_name_change_bt, user_name_change_bt_a);

    user_password_label = gtk_label_new("");
    gtk_grid_attach(GTK_GRID(client_settings_grid), user_password_label, 0, 2, 1, 1);
    user_password_show_bt = gtk_button_new_with_label(bad_face_passwd);
    g_signal_connect(user_password_show_bt, "clicked", G_CALLBACK(show_user_password), NULL);
    gtk_grid_attach(GTK_GRID(client_settings_grid), user_password_show_bt, 1, 2, 1, 1);
    slect_language_client_settings(2, "******", user_password_label, NULL);
    gtk_widget_set_name(user_password_show_bt, user_password_show_bt_a);
    user_password_change_bt = gtk_button_new_with_label("");
    g_signal_connect(user_password_change_bt, "clicked", G_CALLBACK(change_user_password), NULL);
    gtk_grid_attach(GTK_GRID(client_settings_grid), user_password_change_bt, 1, 3, 1, 1);
    slect_language_client_settings(6, NULL, NULL, user_password_change_bt);
    gtk_widget_set_name(user_password_change_bt, user_password_change_bt_a);

    ip_label = gtk_label_new("");
    gtk_grid_attach(GTK_GRID(client_settings_grid), ip_label, 0, 4, 1, 1);
    slect_language_client_settings(3, ip_add, ip_label, NULL);

    hostanme_label = gtk_label_new("");
    gtk_grid_attach(GTK_GRID(client_settings_grid), hostanme_label, 0, 5, 1, 1);
    slect_language_client_settings(4, buffer_host, hostanme_label, NULL);

    uuid_label = gtk_label_new("");
    gtk_grid_attach(GTK_GRID(client_settings_grid), uuid_label, 0, 6, 1, 1);
    slect_language_client_settings(5, user_uuid, uuid_label, NULL);

    gtk_widget_show_all(client_settings_window);
}
// ------------------------------------------

// get garage settings to add new garages or delted them (to configure)
int check_new_garages() {
    const gchar *gchar_hostname_garage = gtk_entry_get_text(GTK_ENTRY(entry_garage_name));

    if (!strcmp(gchar_hostname_garage, "") != 0) {
        select_language_get_garage_settings(6, error_garage_settings_label, NULL);
        return 0;
    }else {
        // search ip with hostname
        struct addrinfo server_add, *request, *pointer;
        int status_server_add = 0;

        memset(&server_add, 0, sizeof(server_add));
        server_add.ai_family = AF_INET;
        server_add.ai_socktype = SOCK_STREAM;

        if(status_server_add = getaddrinfo(gchar_hostname_garage, NULL, &server_add, &request) != 0) {
            // hostname does not exists
            select_language_change_server_hostname_ip_add(11, error_garage_settings_label, NULL);
            return 0;
        }else {
            for (pointer = request; pointer != NULL; pointer = pointer->ai_next) {
                void *addr;
                char main_server_ip_lookup[INET_ADDRSTRLEN];
                struct sockaddr_in *ipv4 = (struct sockaddr_in *)pointer->ai_addr;
                addr = &(ipv4->sin_addr);
                inet_ntop(pointer->ai_family, addr, main_server_ip_lookup, sizeof(main_server_ip_lookup));
                gtk_entry_set_text(GTK_ENTRY(entry_garage_ip), main_server_ip_lookup);
                select_language_change_server_hostname_ip_add(12, error_garage_settings_label, NULL);
            }
            return 1;
        }
    }
}

// send new garages to server if server ip and hostname exists
static void send_new_garages() {
    gchar_ip_garage = gtk_entry_get_text(GTK_ENTRY(entry_garage_ip));
    gchar_hostname_garage = gtk_entry_get_text(GTK_ENTRY(entry_garage_name));
    if (check_new_garages()) {
        // if garage not exists do it else schow error
        if (!strcmp(gchar_ip_garage, "") != 0 && !strcmp(gchar_hostname_garage, "") != 0) {
            select_language_get_garage_settings(7, error_garage_settings_label, NULL);
        }else {
            // send garage to server
            send_garage_to_server();
        }
    }
}

static void get_garage_settings() {
    garage_settings_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(garage_settings_window), "INoInvestigation Garage Settings");
    gtk_window_set_default_size(GTK_WINDOW(garage_settings_window), 450, 220);
    gtk_container_set_border_width(GTK_CONTAINER(garage_settings_window), 10);
    gtk_window_set_position(GTK_WINDOW(garage_settings_window), GTK_WIN_POS_CENTER);
    set_theme(garage_settings_window);

    garage_settings_grid = gtk_grid_new(); 
    gtk_container_add(GTK_CONTAINER(garage_settings_window), garage_settings_grid);
    gtk_grid_set_row_spacing(GTK_GRID(garage_settings_grid), 0);

    garage_ip_label = gtk_label_new("");
    gtk_grid_attach(GTK_GRID(garage_settings_grid), garage_ip_label, 0, 1, 1, 1);
    select_language_get_garage_settings(2, garage_ip_label, NULL);
    entry_garage_ip = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(garage_settings_grid), entry_garage_ip, 1, 1, 1, 1);
    select_language_get_garage_settings(4, entry_garage_ip, NULL);
    search_ip_with_hostname_bt = gtk_button_new_with_label("");
    g_signal_connect(search_ip_with_hostname_bt, "clicked", G_CALLBACK(check_new_garages), NULL);
    gtk_grid_attach(GTK_GRID(garage_settings_grid), search_ip_with_hostname_bt, 2, 1, 1, 1);
    select_language_get_garage_settings(8, NULL, search_ip_with_hostname_bt);

    garage_name_label = gtk_label_new("");
    gtk_grid_attach(GTK_GRID(garage_settings_grid), garage_name_label, 0, 2, 1, 1);
    select_language_get_garage_settings(1, garage_name_label, NULL);
    entry_garage_name = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(garage_settings_grid), entry_garage_name, 1, 2, 1, 1);
    select_language_get_garage_settings(3, entry_garage_name, NULL);

    garage_settings_save_bt = gtk_button_new_with_label("");
    g_signal_connect(garage_settings_save_bt, "clicked", G_CALLBACK(send_new_garages), NULL);
    gtk_grid_attach(GTK_GRID(garage_settings_grid), garage_settings_save_bt, 1, 3, 1, 1);
    select_language_get_garage_settings(5, NULL, garage_settings_save_bt);

    error_garage_settings_label = gtk_label_new("");
    gtk_grid_attach(GTK_GRID(garage_settings_grid), error_garage_settings_label, 1, 4, 1, 1);

    gtk_widget_show_all(garage_settings_window);
}
// ------------------------------------------

// get server settings to change something
const gchar *gchar_change_ip_add_entry, *gchar_change_hostname_entry;

int check_ip_hostname_change() {
    gtk_label_set_text(GTK_LABEL(change_ip_hostname_error_label), "");
    gchar_change_hostname_entry = gtk_entry_get_text(GTK_ENTRY(change_hostname_entry));
    if (!strcmp(gchar_change_hostname_entry, "") != 0) {
        select_language_change_server_hostname_ip_add(10, change_ip_hostname_error_label, NULL);
    }else {
        struct addrinfo server_add, *request, *pointer;
        int status_server_add = 0;

        memset(&server_add, 0, sizeof(server_add));
        server_add.ai_family = AF_INET;
        server_add.ai_socktype = SOCK_STREAM;

        if(status_server_add = getaddrinfo(gchar_change_hostname_entry, NULL, &server_add, &request) != 0) {
            // hostname does not exists
            select_language_change_server_hostname_ip_add(11, change_ip_hostname_error_label, NULL);
        }else {
            for (pointer = request; pointer != NULL; pointer = pointer->ai_next) {
                void *addr;
                char main_server_ip_lookup[INET_ADDRSTRLEN];
                struct sockaddr_in *ipv4 = (struct sockaddr_in *)pointer->ai_addr;
                addr = &(ipv4->sin_addr);
                inet_ntop(pointer->ai_family, addr, main_server_ip_lookup, sizeof(main_server_ip_lookup));
                gtk_entry_set_text(GTK_ENTRY(change_ip_add_entry), main_server_ip_lookup);
                select_language_change_server_hostname_ip_add(12, change_ip_hostname_error_label, NULL);
            }
        }
    }
}

static void get_server_settings();

static void save_ip_hostname_change() {
    gchar_change_ip_add_entry = gtk_entry_get_text(GTK_ENTRY(change_ip_add_entry));
    gchar_change_hostname_entry = gtk_entry_get_text(GTK_ENTRY(change_hostname_entry));

    if (!strcmp(gchar_change_ip_add_entry, "") != 0) {
        select_language_change_server_hostname_ip_add(9, change_ip_hostname_error_label, NULL);
    }else if (!strcmp(gchar_change_hostname_entry, "") != 0) {
        select_language_change_server_hostname_ip_add(10, change_ip_hostname_error_label, NULL);
    }else {
        check_ip_hostname_change();
        FILE *serverIP_add_file_o = fopen(serverIP_add_file, "w");
        fputs(gchar_change_ip_add_entry, serverIP_add_file_o);
        fputs("\n", serverIP_add_file_o);
        fputs(gchar_change_hostname_entry, serverIP_add_file_o);
        fclose(serverIP_add_file_o);
        strcpy(server_data[0], gchar_change_ip_add_entry);
        strcpy(server_data[1], gchar_change_hostname_entry);
        gtk_widget_destroy(change_server_hostname_ip_add_window);
        get_server_settings();
    }
}

static void change_server_hostname_ip_add() {
    gtk_widget_destroy(server_info_window);
    const gchar *change_ip_add_entry_a = "change_ip_add_entry", *change_hostname_entry_a = "change_hostname_entry", *check_ip_hostname_bt_a = "check_ip_hostname_bt", *save_ip_hostname_bt_a = "save_ip_hostname_bt";

    change_server_hostname_ip_add_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(change_server_hostname_ip_add_window), "INoInvestigation Server Settings");
    gtk_window_set_default_size(GTK_WINDOW(change_server_hostname_ip_add_window), 250, 200);
    gtk_container_set_border_width(GTK_CONTAINER(change_server_hostname_ip_add_window), 10);
    gtk_window_set_position(GTK_WINDOW(change_server_hostname_ip_add_window), GTK_WIN_POS_CENTER);
    set_theme(change_server_hostname_ip_add_window);

    change_server_hostname_ip_add_grid = gtk_grid_new(); 
    gtk_container_add(GTK_CONTAINER(change_server_hostname_ip_add_window), change_server_hostname_ip_add_grid);
    gtk_grid_set_row_spacing(GTK_GRID(change_server_hostname_ip_add_grid), 0);

    change_ip_add_label = gtk_label_new("");
    gtk_grid_attach(GTK_GRID(change_server_hostname_ip_add_grid), change_ip_add_label, 0, 1, 1, 1);
    select_language_change_server_hostname_ip_add(1, change_ip_add_label, NULL);
    change_ip_add_entry = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(change_server_hostname_ip_add_grid), change_ip_add_entry, 1, 1, 1, 1);
    select_language_change_server_hostname_ip_add(2, change_ip_add_entry, NULL);
    gtk_widget_set_name(change_ip_add_entry, change_ip_add_entry_a);

    change_hostname_label = gtk_label_new("");
    gtk_grid_attach(GTK_GRID(change_server_hostname_ip_add_grid), change_hostname_label, 0, 2, 1, 1);
    select_language_change_server_hostname_ip_add(3, change_hostname_label, NULL);
    change_hostname_entry = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(change_server_hostname_ip_add_grid), change_hostname_entry, 1, 2, 1, 1);
    select_language_change_server_hostname_ip_add(4, change_hostname_entry, NULL);
    gtk_widget_set_name(change_hostname_entry, change_hostname_entry_a);
    check_ip_hostname_bt = gtk_button_new_with_label("");
    g_signal_connect(check_ip_hostname_bt, "clicked", G_CALLBACK(check_ip_hostname_change), NULL);
    gtk_grid_attach(GTK_GRID(change_server_hostname_ip_add_grid), check_ip_hostname_bt, 2, 2, 1, 1);
    select_language_change_server_hostname_ip_add(5, NULL, check_ip_hostname_bt);
    gtk_widget_set_name(check_ip_hostname_bt, check_ip_hostname_bt_a);

    save_ip_hostname_bt = gtk_button_new_with_label("");
    g_signal_connect(save_ip_hostname_bt, "clicked", G_CALLBACK(save_ip_hostname_change), NULL);
    gtk_grid_attach(GTK_GRID(change_server_hostname_ip_add_grid), save_ip_hostname_bt, 2, 3, 1, 1);
    select_language_change_server_hostname_ip_add(6, NULL, save_ip_hostname_bt);
    gtk_widget_set_name(save_ip_hostname_bt, save_ip_hostname_bt_a);
    
    change_ip_hostname_error_label = gtk_label_new("");
    gtk_grid_attach(GTK_GRID(change_server_hostname_ip_add_grid), change_ip_hostname_error_label, 1, 3, 1, 1);

    gtk_widget_show_all(change_server_hostname_ip_add_window); 
}

static void turn_auto_connect_on_or_off() {
    FILE *server_data_file_o = fopen(serverIP_add_file, "w");
    // check if auto_connect is on or off
    if (!gtk_switch_get_active(GTK_SWITCH(auto_connect_server_switch))) {
        strcpy(server_data[2], "auto_connect_off");
        select_language_server_info(6, auto_connect_server_switch, NULL);
    }else {
        strcpy(server_data[2], "auto_connect_on");
        select_language_server_info(5, auto_connect_server_switch, NULL);
    }
    // write evrything to file
    for (int x = 0; x != 3; x++) {
        fputs(crypt_data(server_data[x], "", crypt_serverIP_add_file), server_data_file_o);
        fputs("\n", server_data_file_o);
    }
    fclose(server_data_file_o);
}

static void get_server_settings() {
    const gchar *server_info_hostname_ip_add_change_bt_a = "server_info_hostname_ip_add_change_bt";

    server_info_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(server_info_window), "INoInvestigation Server Settings");
    gtk_window_set_default_size(GTK_WINDOW(server_info_window), 250, 200);
    gtk_container_set_border_width(GTK_CONTAINER(server_info_window), 10);
    gtk_window_set_position(GTK_WINDOW(server_info_window), GTK_WIN_POS_CENTER);
    set_theme(server_info_window);

    server_info_grid = gtk_grid_new(); 
    gtk_container_add(GTK_CONTAINER(server_info_window), server_info_grid);
    gtk_grid_set_row_spacing(GTK_GRID(server_info_grid), 0);

    server_info_ip_add = gtk_label_new("");
    gtk_grid_attach(GTK_GRID(server_info_grid), server_info_ip_add, 0, 1, 1, 1);
    select_language_server_info(1, server_info_ip_add, NULL);

    server_info_hostname = gtk_label_new("");
    gtk_grid_attach(GTK_GRID(server_info_grid), server_info_hostname, 0, 2, 1, 1);
    select_language_server_info(2, server_info_hostname, NULL);

    server_info_hostname_ip_add_change_bt = gtk_button_new_with_label("");
    g_signal_connect(server_info_hostname_ip_add_change_bt, "clicked", G_CALLBACK(change_server_hostname_ip_add), NULL);
    gtk_grid_attach(GTK_GRID(server_info_grid), server_info_hostname_ip_add_change_bt, 0, 3, 1, 1);
    select_language_server_info(3, NULL, server_info_hostname_ip_add_change_bt);
    gtk_widget_set_name(server_info_hostname_ip_add_change_bt, server_info_hostname_ip_add_change_bt_a);

    auto_connect_server_label = gtk_label_new("");
    gtk_grid_attach(GTK_GRID(server_info_grid), auto_connect_server_label, 1, 4, 1, 1);
    select_language_server_info(4, auto_connect_server_label, NULL);    

    auto_connect_server_switch = gtk_switch_new();
    g_signal_connect(GTK_SWITCH(auto_connect_server_switch), "notify::active", G_CALLBACK(turn_auto_connect_on_or_off), NULL);
    // if auto_connect is on set switch state to true
    if (!strcmp(server_data[2], "auto_connect_on") != 0) {
        gtk_switch_set_active(GTK_SWITCH(auto_connect_server_switch), TRUE);
        select_language_server_info(5, auto_connect_server_switch, NULL);
    }
    gtk_grid_attach(GTK_GRID(server_info_grid), auto_connect_server_switch, 2, 4, 1, 1);

    gtk_widget_show_all(server_info_window);   
}
// ------------------------------------------

// get help
static void get_help() {

}
// ------------------------------------------

// get support 
static void get_support() {

}
// ------------------------------------------