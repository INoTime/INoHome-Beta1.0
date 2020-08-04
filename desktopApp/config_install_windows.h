// don't cancle configuration
static void close_cancle_config() {
    gtk_widget_destroy(cancle_config_win);
    absolute_start();
}
// really cancle configuration?
static void cancle_config(GtkWidget *widget, gpointer data) {
    const gchar *yes_bt_a = "yes_bt", *cancel_bt_a = "cancle_bt";
    GtkWidget *grid_cancle_config;
    GtkWidget *yes_bt, *cancel_bt;
    GtkWidget *label_cancle_ok;

    cancle_config_win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(cancle_config_win), "Really cancle?");
    gtk_window_set_default_size(GTK_WINDOW(cancle_config_win), 100, 60);
    gtk_container_set_border_width(GTK_CONTAINER(cancle_config_win), 10);
    gtk_window_set_position(GTK_WINDOW(cancle_config_win), GTK_WIN_POS_CENTER);
    gtk_window_set_resizable(GTK_WINDOW(cancle_config_win), FALSE);
    gtk_window_set_skip_taskbar_hint(GTK_WINDOW(cancle_config_win), TRUE);
    
    gtk_widget_set_name(cancle_config_win, my_window_css);
    cssProvider = gtk_css_provider_new();
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(cssProvider), GTK_STYLE_PROVIDER_PRIORITY_USER);
    my_style();

    grid_cancle_config = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(cancle_config_win), grid_cancle_config);

    label_cancle_ok = gtk_label_new("");
    gtk_grid_attach(GTK_GRID(grid_cancle_config), label_cancle_ok, 0, 1, 1, 1);
    select_language_cancle_config(1, label_cancle_ok, NULL);

    // if user clicked "yes"
    yes_bt = gtk_button_new_with_label("");
    g_signal_connect(yes_bt, "clicked", G_CALLBACK(system_end_program), NULL);
    gtk_grid_attach(GTK_GRID(grid_cancle_config), yes_bt, 0, 2, 1, 1);
    gtk_widget_set_name(yes_bt, yes_bt_a);
    select_language_cancle_config(2, NULL, yes_bt);

    // if user clicked "no"
    cancel_bt = gtk_button_new_with_label("");
    g_signal_connect(cancel_bt, "clicked", G_CALLBACK(close_cancle_config), NULL);
    gtk_grid_attach(GTK_GRID(grid_cancle_config), cancel_bt, 1, 2, 1, 1);
    gtk_widget_set_name(cancel_bt, cancel_bt_a);
    select_language_cancle_config(3, NULL, cancel_bt);

    gtk_widget_show_all(cancle_config_win);
}

static void ready_finish() {
    if (auto_start_program_check) {
        gtk_main_quit();                    // start after config main program
        exit(0);
    }else {
        system_end_program();
    }
}

static void auto_start_program(GtkToggleButton *toggle_button) {
    if (gtk_toggle_button_get_active(toggle_button)) {
        auto_start_program_check = 1;
    }else {
        auto_start_program_check = 0;
    }
}

static void exit_config() {
    // reset window size 
    gtk_window_set_default_size(GTK_WINDOW(wdP->window), 800, 400);
    // don't need to set/activate new garages
    const gchar *exit_config_help_bt_label_a = "exit_config_help_bt_label", *finish_config_a = "finish_config";
    send(sockfd_server, "000", 4, 0);

    if (check_exit_config_server_conn) {
        exit_config_send();
    }
    gtk_widget_destroy(go_next_will_close_conn_window);
    window_number = 8;
    my_style();

    exit_config_help_bt_label = gtk_button_new_with_label("?");
    g_signal_connect(exit_config_help_bt_label, "clicked", G_CALLBACK(help_win_all), NULL);
    gtk_grid_attach(GTK_GRID(grid), exit_config_help_bt_label, 1, 0, 1, 1);
    gtk_widget_set_name(exit_config_help_bt_label, exit_config_help_bt_label_a);
    select_langauge(0, NULL, exit_config_help_bt_label); 

    if (window_number == check_number) {
        destroy_add_garage();
        check_number++;
    }

    exit_config_label = gtk_label_new("");
    gtk_grid_attach(GTK_GRID(grid), exit_config_label, 1, 1, 1, 1);
    select_langauge(1, exit_config_label, NULL);

    start_checkbutton = gtk_check_button_new_with_label("");
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(start_checkbutton), FALSE);
    g_signal_connect(GTK_TOGGLE_BUTTON(start_checkbutton), "toggled", G_CALLBACK(auto_start_program), wdP->window);
    gtk_grid_attach(GTK_GRID(grid), start_checkbutton, 1, 2, 1, 1);
    select_langauge(2, NULL, start_checkbutton);

    finish_config = gtk_button_new_with_label("");
    g_signal_connect(finish_config, "clicked", G_CALLBACK(ready_finish), NULL);
    gtk_grid_attach(GTK_GRID(grid), finish_config, 2, 3, 1, 1);
    gtk_widget_set_name(finish_config, finish_config_a);
    gtk_widget_set_tooltip_text(finish_config, ""); 
    select_langauge(3, NULL, finish_config);

    gtk_widget_show_all(wdP->window);
}

// those are to show the password and change the label
void password_show_one_v_alpha() {
    if (!password_new_setted_show_one) {
        gtk_entry_set_visibility(GTK_ENTRY(entry_password), TRUE);
        gtk_button_set_label(GTK_BUTTON(show_password_a), smile_face_passwd);
        password_new_setted_show_one++;
    }else {
        gtk_entry_set_visibility(GTK_ENTRY(entry_password), FALSE);
        gtk_button_set_label(GTK_BUTTON(show_password_a), bad_face_passwd);
        password_new_setted_show_one--;
    }    
}
void password_show_two_v_alpha() {
    if (!password_new_setted_show_two) {
        gtk_entry_set_visibility(GTK_ENTRY(entry_password_retype), TRUE);
        gtk_button_set_label(GTK_BUTTON(show_password_b), smile_face_passwd);
        password_new_setted_show_two++;
    }else {
        gtk_entry_set_visibility(GTK_ENTRY(entry_password_retype), FALSE);
        gtk_button_set_label(GTK_BUTTON(show_password_b), bad_face_passwd);
        password_new_setted_show_two--;
    }
}
// ---------------------------------------------------

static void load_from_server_garages() {
    all_loaded_garages_server();
    FILE *all_garages_addr_file_o = fopen(ip_addr_file, "r");
    while (fgets(buf_garages_addr, sizeof(buf_garages_addr), all_garages_addr_file_o) != NULL) {
        strcat(all_garages_addr, buf_garages_addr);
        lines_garages_addr++;
    }
    gtk_label_set_text(GTK_LABEL(garages_server_label), all_garages_addr);
}

static void back_add_garage() {
    destroy_add_garage();
    check_number--;
    final_config();
}

static void add_garage() {
    const gchar *add_garage_help_bt_label_a = "add_garage_help_bt_label", *load_from_server_bt_a = "load_from_server_bt", *add_garage_bt_a = "add_garage_bt", *remove_garage_bt_a = "remove_garage_bt", *save_all_new_garages_bt_a = "save_all_new_garages_bt", *add_garage_next_bt_a = "add_garage_next_bt";
    window_number = 7;
    destroy_final_config();
    check_number++;

    add_garage_help_bt_label = gtk_button_new_with_label("?");
    g_signal_connect(add_garage_help_bt_label, "clicked", G_CALLBACK(help_win_all), NULL);
    gtk_grid_attach(GTK_GRID(grid), add_garage_help_bt_label, 1, 0, 1, 1);
    select_langauge(0, NULL, add_garage_help_bt_label); 
    gtk_widget_set_name(add_garage_help_bt_label, add_garage_help_bt_label_a);

    add_garage_label = gtk_label_new("");
    gtk_grid_attach(GTK_GRID(grid), add_garage_label, 2, 1, 1, 1);
    select_langauge(1, add_garage_label, NULL);

    load_from_server_bt = gtk_button_new_with_label("");
    g_signal_connect(load_from_server_bt, "clicked", G_CALLBACK(load_from_server_garages), NULL);
    gtk_grid_attach(GTK_GRID(grid), load_from_server_bt, 2, 2, 1, 1);
    gtk_widget_set_name(load_from_server_bt, load_from_server_bt_a);
    gtk_widget_set_tooltip_text(load_from_server_bt, ""); 
    select_langauge(2, NULL, load_from_server_bt);

    add_garage_bt = gtk_button_new_with_label("");
    g_signal_connect(add_garage_bt, "clicked", G_CALLBACK(add_garage_entry), NULL);
    gtk_grid_attach(GTK_GRID(grid), add_garage_bt, 2, 3, 1, 1);
    gtk_widget_set_name(add_garage_bt, add_garage_bt_a);
    gtk_widget_set_tooltip_text(add_garage_bt, ""); 
    select_langauge(3, NULL, add_garage_bt);

    new_garages_label = gtk_label_new("");
    gtk_grid_attach(GTK_GRID(grid), new_garages_label, 3, 2, 1, 1);

    remove_garage_bt = gtk_button_new_with_label("");
    g_signal_connect(remove_garage_bt, "clicked", G_CALLBACK(remove_garage), NULL);
    gtk_grid_attach(GTK_GRID(grid), remove_garage_bt, 4, 2, 1, 1);
    gtk_widget_set_sensitive(remove_garage_bt, TRUE);
    gtk_widget_set_name(remove_garage_bt, remove_garage_bt_a);
    gtk_widget_set_tooltip_text(remove_garage_bt, ""); 
    select_langauge(4, NULL, remove_garage_bt);

    save_all_new_garages_bt = gtk_button_new_with_label("");
    g_signal_connect(save_all_new_garages_bt, "clicked", G_CALLBACK(send_garge_server_ip), NULL);
    gtk_grid_attach(GTK_GRID(grid), save_all_new_garages_bt, 4, 3, 1, 1);
    gtk_widget_set_sensitive(save_all_new_garages_bt, FALSE);
    gtk_widget_set_name(save_all_new_garages_bt, save_all_new_garages_bt_a);
    gtk_widget_set_tooltip_text(save_all_new_garages_bt, ""); 
    select_langauge(5, NULL, save_all_new_garages_bt);

    add_garage_next_bt = gtk_button_new_with_label("");
    g_signal_connect(add_garage_next_bt, "clicked", G_CALLBACK(go_next_will_close_conn), NULL);
    gtk_grid_attach(GTK_GRID(grid), add_garage_next_bt, 4, 5, 1, 1);
    gtk_widget_set_name(add_garage_next_bt, add_garage_next_bt_a);
    select_langauge(6, NULL, add_garage_next_bt);

    gtk_widget_show_all(wdP->window);
}

static void back_final_config() {
    destroy_final_config();
    check_number--;
    window_theme_color();
}

static void show_user_password_c() {
    if (!password_show_one_setted) {
        strcpy(show_entry_passwd_saved, "");
        select_language_change_sys_info(7);
        strcat(show_entry_passwd_saved, ch_user_password_re_save);
        strcat(show_entry_passwd_saved, decrypt_data(password_a, crypt_user_info_file));
        gtk_label_set_text(GTK_LABEL(user_password_c_label), show_entry_passwd_saved);
        gtk_button_set_label(GTK_BUTTON(show_user_password_c_bt), smile_face_passwd);
        password_show_one_setted++;
    }else {
        strcpy(show_entry_passwd_saved, "");
        select_language_change_sys_info(7);
        strcat(show_entry_passwd_saved, ch_user_password_re_save);
        strcat(show_entry_passwd_saved, "********");
        gtk_label_set_text(GTK_LABEL(user_password_c_label), show_entry_passwd_saved);
        gtk_button_set_label(GTK_BUTTON(show_user_password_c_bt), bad_face_passwd);
        password_show_one_setted--;
    }  
}

// final up the configuration let user check if all cons are right
static void final_config() {
    const gchar *final_config_help_bt_label_a = "final_config_help_bt_label", *change_user_name_bt_a = "change_user_name_bt", *change_password_bt_a = "change_password_bt", *show_user_password_c_bt_a = "show_user_password_c_bt", *final_config_back_bt_a = "final_config_back_bt", *final_config_next_bt_a = "final_config_next_bt";
    window_number = 6;

    if (window_number == check_number) {
        destroy_window_theme_color();
        check_number++;
    }

    final_config_help_bt_label = gtk_button_new_with_label("?");
    g_signal_connect(final_config_help_bt_label, "clicked", G_CALLBACK(help_win_all), NULL);
    gtk_grid_attach(GTK_GRID(grid), final_config_help_bt_label, 0, 0, 1, 1);
    select_langauge(0, NULL, final_config_help_bt_label); 
    gtk_widget_set_name(final_config_help_bt_label, final_config_help_bt_label_a);

    select_language_change_sys_info(1);
    select_language_change_sys_info(2);
    select_language_change_sys_info(4);
    select_language_change_sys_info(3);
    select_language_change_sys_info(5);

    strcpy(name_b, name_b_save);
    strcpy(name_a, "");
    strcpy(password_b, ch_user_password_re_save);
    strcpy(password_a, "");
    strcpy(server_ip_b, server_ip_b_save);
    strcpy(server_name_b, server_name_b_save);
    strcpy(uuid_b, uuid_b_save);

    // load server info
    FILE *server_info = fopen(server_info_file, "r");
    fgets(server_ip_a, sizeof(server_ip_a), server_info);
    fgets(server_name_a, sizeof(server_name_a), server_info);
    fclose(server_info);
    strcat(server_ip_b, decrypt_data(server_ip_a, crypt_serverIP_add_file));
    strcat(server_name_b, decrypt_data(server_name_a, crypt_serverIP_add_file));

    // load user uuid
    FILE *uuid_info = fopen(user_id_file, "r");
    fgets(uuid_a, sizeof(uuid_a), uuid_info);
    fclose(uuid_info);
    strcat(uuid_b, decrypt_data(uuid_a, crypt_user_id_file));

    all_right_final_label = gtk_label_new("");
    gtk_grid_attach(GTK_GRID(grid), all_right_final_label, 1, 0, 1, 1);
    select_langauge(1, all_right_final_label, NULL);

    change_user_name_bt = gtk_button_new_with_label("");
    gtk_widget_set_name(change_user_name_bt, change_user_name_bt_a);
    cahnge_password_bt = gtk_button_new_with_label("");
    gtk_widget_set_name(cahnge_password_bt, change_password_bt_a);

    // load user info
    FILE *user_info = fopen(user_info_file, "r");
    fgets(name_a, sizeof(name_a), user_info);
    fgets(password_a, sizeof(password_a), user_info);
    fclose(user_info);
    strcat(name_b, decrypt_data(name_a, crypt_user_info_file));
    strcat(password_b, decrypt_data(password_a, crypt_user_info_file));

    // set user name label
    user_name_c_label = gtk_label_new(name_b);
    // change change_user_name_bt button label
    g_signal_connect(change_user_name_bt, "clicked", G_CALLBACK(change_user_name_final), NULL);
    select_langauge(5, NULL, change_user_name_bt);
    // copy password 
    select_language_change_sys_info(7);
    strcpy(show_entry_passwd_saved, "");
    strcat(show_entry_passwd_saved, ch_user_password_re_save);
    // set password len to hidden string
    strcat(show_entry_passwd_saved, "********");
    user_password_c_label = gtk_label_new(show_entry_passwd_saved);
    show_user_password_c_bt = gtk_button_new_with_label(bad_face_passwd);
    g_signal_connect(show_user_password_c_bt, "clicked", G_CALLBACK(show_user_password_c), NULL);
    gtk_grid_attach(GTK_GRID(grid), show_user_password_c_bt, 2, 2, 1, 1); 
    gtk_widget_set_name(show_user_password_c_bt, show_user_password_c_bt_a);
    // change change_password_bt button label
    gtk_button_set_label(GTK_BUTTON(cahnge_password_bt), "");
    g_signal_connect(cahnge_password_bt, "clicked", G_CALLBACK(change_password_final), NULL);
    gtk_grid_attach(GTK_GRID(grid), cahnge_password_bt, 3, 2, 1, 1);
    select_langauge(6, NULL, cahnge_password_bt);
    
    gtk_grid_attach(GTK_GRID(grid), user_name_c_label, 1, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), change_user_name_bt, 2, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), user_password_c_label, 1, 2, 1, 1);

    server_name_c_label = gtk_label_new(server_name_b);
    gtk_grid_attach(GTK_GRID(grid), server_name_c_label, 1, 3, 1, 1);

    server_ip_c_label = gtk_label_new(server_ip_b);
    gtk_grid_attach(GTK_GRID(grid), server_ip_c_label, 1, 4, 1, 1);

    user_uuid_c_label = gtk_label_new(uuid_b);
    gtk_grid_attach(GTK_GRID(grid), user_uuid_c_label, 1, 5, 1, 1);    

    final_config_back_bt = gtk_button_new_with_label("");
    g_signal_connect(final_config_back_bt, "clicked", G_CALLBACK(back_final_config), NULL);
    gtk_grid_attach(GTK_GRID(grid), final_config_back_bt, 1, 6, 1, 1);
    gtk_widget_set_name(final_config_back_bt, final_config_back_bt_a);
    select_langauge(7, NULL, final_config_back_bt);

    final_config_next_bt = gtk_button_new_with_label("");
    g_signal_connect(final_config_next_bt, "clicked", G_CALLBACK(add_garage), NULL);
    gtk_grid_attach(GTK_GRID(grid), final_config_next_bt, 2, 6, 1, 1); 
    gtk_widget_set_name(final_config_next_bt, final_config_next_bt_a);
    select_langauge(8, NULL, final_config_next_bt);

    gtk_widget_show_all(wdP->window);
}

// reopen gtk window to check window style
static void reopen_gtk_window();
static void change_theme_on() {
    FILE *change_theme = fopen(check_my_style_f, "w");
    fputs(crypt_data("dark_theme", "", crypt_check_my_style_file), change_theme);
    style_mode = 1;
    fclose(change_theme);
    my_style();
}

static void change_theme_off() {
    FILE *change_theme = fopen(check_my_style_f, "w");
    fputs(crypt_data("dark_theme_off", "", crypt_check_my_style_file), change_theme);
    style_mode = 0;
    fclose(change_theme);
    my_style();
}

// set the window theme color
static void window_theme_color() {
    const gchar *window_theme_color_help_bt_label_a = "window_theme_color_help_bt_label", *theme_color_next_bt_a = "theme_color_next_bt";
    window_number = 5;
    if (window_number == check_number) {
        destroy_connect_server();
        check_number++;
    }

    window_theme_color_help_bt_label = gtk_button_new_with_label("?");
    g_signal_connect(window_theme_color_help_bt_label, "clicked", G_CALLBACK(help_win_all), NULL);
    gtk_grid_attach(GTK_GRID(grid), window_theme_color_help_bt_label, 1, 0, 1, 1);
    select_langauge(0, NULL, window_theme_color_help_bt_label); 
    gtk_widget_set_name(window_theme_color_help_bt_label, window_theme_color_help_bt_label_a);
    
    on_theme_box = gtk_event_box_new();
    dark_theme_on_image = gtk_image_new_from_file("files/images/window_style/dark_theme_on.png");
    gtk_container_add(GTK_CONTAINER(on_theme_box), dark_theme_on_image);
    g_signal_connect(G_OBJECT(on_theme_box), "button_press_event", G_CALLBACK(change_theme_on), dark_theme_on_image);
    gtk_grid_attach(GTK_GRID(grid), on_theme_box, 2, 3, 1, 1); 
    select_langauge(1, NULL, dark_theme_on_image);

    off_theme_box = gtk_event_box_new();
    dark_theme_off_image = gtk_image_new_from_file("files/images/window_style/dark_theme_off.png");
    gtk_container_add(GTK_CONTAINER(off_theme_box), dark_theme_off_image);
    g_signal_connect(G_OBJECT(off_theme_box), "button_press_event", G_CALLBACK(change_theme_off), dark_theme_off_image);
    gtk_grid_attach(GTK_GRID(grid), off_theme_box, 3, 3, 1, 1); 
    select_langauge(2, NULL, dark_theme_off_image);

    theme_color_next_bt = gtk_button_new_with_label("");
    g_signal_connect(theme_color_next_bt, "clicked", G_CALLBACK(check_uuid_is_here), NULL);
    gtk_grid_attach(GTK_GRID(grid), theme_color_next_bt, 4, 4, 1, 1);
    gtk_widget_set_name(theme_color_next_bt, theme_color_next_bt_a);
    select_langauge(3, NULL, theme_color_next_bt);

    gtk_widget_show_all(wdP->window);
}

// restart window for new theme
static void reopen_gtk_window() {
    destroy_window_theme_color();                                                                           // could deleted?
    check_number--;
    window_theme_color();
}

static void search_for_ip_from_name() {
    gtk_label_set_text(GTK_LABEL(server_ip_found_label), "");
    server_name = gtk_entry_get_text(GTK_ENTRY(server_name_entry));
    gtk_label_set_text(GTK_LABEL(error_connect_server), "");
    if (!strcmp(server_name, "") != 0) {
        select_langauge(9, error_connect_server, NULL);
    }else {
        search_ip_with_hostname();
    }
}

// check if evwrything filled then load it into file
static void check_info_add() {
    server_name = gtk_entry_get_text(GTK_ENTRY(server_name_entry));
    ip_add = gtk_entry_get_text(GTK_ENTRY(server_add_entry));

    if (!strcmp(server_name, "") != 0) {
        select_langauge(9, error_connect_server, NULL);
    }else if (!strcmp(ip_add, "") != 0) {
        select_langauge(10, error_connect_server, NULL);
    }else {
        search_for_ip_from_name();
        if (status_ip_hostname_exists) {
            save_info_add(server_name, ip_add);
            gtk_widget_set_sensitive(connect_server_help_bt_label, FALSE);
            gtk_widget_set_sensitive(server_search_hostname_bt, FALSE);
            gtk_widget_set_sensitive(save_info_add_bt, FALSE);
            if (!was_here_main_connection_handler) {
                // open super user acess window
                super_user_acess();
                was_here_main_connection_handler = 1;
            }
            strcpy(entry_server_name_saved, server_name);
            strcpy(entry_server_ip_saved, ip_add);
        }else {
            gtk_entry_set_text(GTK_ENTRY(server_add_entry), exp_ip_add);
        }
    }
}

// connect first time to server 
static void connect_server() {
    const gchar *connect_server_help_bt_label_a = "connect_server_help_bt_label", *connect_server_add_label_a = "connect_server_add_label", *server_add_entry_a = "server_add_entry", *server_name_entry_a = "server_name_entry", *server_search_hostname_bt_a = "server_search_hostname_bt", *save_info_add_bt_a = "save_info_add_bt";
    window_number = 4;
    if (window_number == check_number) {
        destroy_what_to_install();
        check_number++;
    }

    connect_server_help_bt_label = gtk_button_new_with_label("?");
    g_signal_connect(connect_server_help_bt_label, "clicked", G_CALLBACK(help_win_all), NULL);
    gtk_grid_attach(GTK_GRID(grid), connect_server_help_bt_label, 1, 0, 1, 1);
    select_langauge(0, NULL, connect_server_help_bt_label); 
    gtk_widget_set_name(connect_server_help_bt_label, connect_server_help_bt_label_a);

    connect_server_add_label = gtk_label_new("");
    gtk_grid_attach(GTK_GRID(grid), connect_server_add_label, 2, 0, 1, 1);
    select_langauge(1, connect_server_add_label, NULL);

    server_add_label = gtk_label_new("");
    gtk_grid_attach(GTK_GRID(grid), server_add_label, 2, 2, 1, 1);
    select_langauge(2, server_add_label, NULL);
    server_add_entry = gtk_entry_new();
    gtk_entry_set_max_length(GTK_ENTRY(server_add_entry), INET_ADDRSTRLEN);
    gtk_entry_set_text(GTK_ENTRY(server_add_entry), entry_server_ip_saved);
    gtk_grid_attach(GTK_GRID(grid), server_add_entry, 3, 2, 1, 1);
    gtk_widget_set_name(server_add_entry, server_add_entry_a);
    select_langauge(3, server_add_entry, FALSE); 

    server_ip_found_label = gtk_label_new("");
    gtk_grid_attach(GTK_GRID(grid), server_ip_found_label, 4, 2, 1, 1);

    server_name_label = gtk_label_new("");
    gtk_grid_attach(GTK_GRID(grid), server_name_label, 2, 3, 1, 1);
    select_langauge(5, server_name_label, NULL);
    server_name_entry = gtk_entry_new();
    gtk_entry_set_max_length(GTK_ENTRY(server_name_entry), 31);
    gtk_entry_set_text(GTK_ENTRY(server_name_entry), entry_server_name_saved);
    gtk_grid_attach(GTK_GRID(grid), server_name_entry, 3, 3, 1, 1);
    gtk_widget_set_name(server_name_entry, server_name_entry_a);
    gtk_widget_set_tooltip_text(server_name_entry, ""); 
    select_langauge(6, server_name_entry, NULL);
    server_search_hostname_bt = gtk_button_new_with_label("");
    g_signal_connect(server_search_hostname_bt, "clicked", G_CALLBACK(search_for_ip_from_name), NULL);
    gtk_grid_attach(GTK_GRID(grid), server_search_hostname_bt, 4, 3, 1, 1); 
    gtk_widget_set_name(server_search_hostname_bt, server_search_hostname_bt_a);
    select_langauge(7, NULL, server_search_hostname_bt);

    save_info_add_bt = gtk_button_new_with_label("");
    g_signal_connect(save_info_add_bt, "clicked", G_CALLBACK(check_info_add), NULL);
    gtk_grid_attach(GTK_GRID(grid), save_info_add_bt, 5, 5, 1, 1);
    gtk_widget_set_name(save_info_add_bt, save_info_add_bt_a);
    select_langauge(8, NULL, save_info_add_bt);

    error_connect_server = gtk_label_new("");
    gtk_grid_attach(GTK_GRID(grid), error_connect_server, 4, 6, 1, 1);

    gtk_widget_show_all(wdP->window);
}

// is to set an number to check while installing program
static void check_what_to_install_garage_opener(GtkToggleButton *toggle_button) {
    if (gtk_toggle_button_get_active(toggle_button)) {
        install_programs_garage_opener = 1;
    }else {
        install_programs_garage_opener = 0;
    }
}

static void check_and_install() {
    if (install_programs_garage_opener) {
        connect_server();
    }else {
        install_failed_by_check();
    }
}

static void what_to_install() {
    const gchar *help_garage_control_a = "help_garage_control", *garage_control_a = "garage_control", *garage_opener_a = "garage_opener", *program_install_next_a = "program_install_next";
    window_number = 3;
    if (window_number == check_number) {
        destroy_insta_config();
        check_number++;
    }

    //*video_recorder, *door_opener, *alarm_sensor_door, *alarm_sensor_window, *home_server, *home_server_ssh

    help_garage_control = gtk_button_new_with_label("?");
    g_signal_connect(help_garage_control, "clicked", G_CALLBACK(help_win_all), NULL);
    gtk_grid_attach(GTK_GRID(grid), help_garage_control, 0, 0, 1, 1);
    select_langauge(0, NULL, help_garage_control);
    gtk_widget_set_name(help_garage_control, help_garage_control_a);

    garage_control = gtk_label_new("");
    gtk_widget_set_name(garage_control, garage_control_a);
    gtk_grid_attach(GTK_GRID(grid), garage_control, 1, 0, 1, 1);
    select_langauge(1, garage_control, NULL);

    garage_opener = gtk_check_button_new_with_label("");
    gtk_widget_set_name(garage_opener, garage_opener_a);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(garage_opener), TRUE);
    g_signal_connect(GTK_TOGGLE_BUTTON(garage_opener), "toggled", G_CALLBACK(check_what_to_install_garage_opener), wdP->window);
    gtk_grid_attach(GTK_GRID(grid), garage_opener, 3, 2, 1, 1);
    select_langauge(2, NULL, garage_opener);

    program_install_next = gtk_button_new_with_label("");
    gtk_widget_set_name(program_install_next, program_install_next_a);
    g_signal_connect(program_install_next,"clicked", G_CALLBACK(check_and_install), NULL);
    gtk_grid_attach(GTK_GRID(grid), program_install_next, 5, 3, 1, 1);
    select_langauge(3, NULL, program_install_next);


    gtk_widget_show_all(wdP->window);
}

// save all user informations name, password
static void save_info() {
    entry_name_out = gtk_entry_get_text(GTK_ENTRY(name_entry));
    entry_passwd_out = gtk_entry_get_text(GTK_ENTRY(password_entry));
    entry_re_passwd_out = gtk_entry_get_text(GTK_ENTRY(re_password_entry));

    if (!strcmp(entry_name_out, "") != 0) {
        select_langauge(13, error_insta_config_label, NULL);
    }else if (!strcmp(entry_passwd_out, "") != 0) {
        select_langauge(14, error_insta_config_label, NULL);
    }else if (!strcmp(entry_re_passwd_out, "") != 0) {
        select_langauge(15, error_insta_config_label, NULL);
    }else if (strcmp(entry_passwd_out, entry_re_passwd_out) != 0) {
        select_langauge(16, error_insta_config_label, NULL);
    }else {
        save_user_info(entry_name_out, entry_passwd_out);
        strcpy(entry_name_saved, entry_name_out);
        strcpy(entry_passwd_saved, entry_passwd_out);
        what_to_install();
    }
    gtk_widget_show(error_insta_config_label);
}

// go back to start window
static void back_insta_config() {
    destroy_insta_config();
    check_number--;
    start_screen();
}
// those are to show the password and change the label
void password_show_one_v() {
    if (!password_show_one_setted) {
        gtk_entry_set_visibility(GTK_ENTRY(password_entry), TRUE);
        gtk_button_set_label(GTK_BUTTON(password_show_one), smile_face_passwd);
        password_show_one_setted++;
    }else {
        gtk_entry_set_visibility(GTK_ENTRY(password_entry), FALSE);
        gtk_button_set_label(GTK_BUTTON(password_show_one), bad_face_passwd);
        password_show_one_setted--;
    }    
}
void password_show_two_v() {
    if (!password_show_two_setted) {
        gtk_entry_set_visibility(GTK_ENTRY(re_password_entry), TRUE);
        gtk_button_set_label(GTK_BUTTON(password_show_two), smile_face_passwd);
        password_show_two_setted++;
    }else {
        gtk_entry_set_visibility(GTK_ENTRY(re_password_entry), FALSE);
        gtk_button_set_label(GTK_BUTTON(password_show_two), bad_face_passwd);
        password_show_two_setted--;
    }
}
// ---------------------------------------------------

void create_random_password_generator() {
    char password_gen_p[64][2] = {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z",
                                   "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z",
                                   "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" };
    char create_password[26] = "";
    srand(time(0));
    for (int x = 0; x != 25; x++) {
        if (x == 6 || x == 12 || x == 18) {
            strcat(create_password, "-");
        }else {
            int num = rand() % 64;
            // copy strings to string
            strcat(create_password, password_gen_p[rand() % num]);
        }
    }
    gtk_entry_set_text(GTK_ENTRY(password_entry), "");
    gtk_entry_set_text(GTK_ENTRY(re_password_entry), "");
    gtk_entry_set_text(GTK_ENTRY(password_entry), create_password);
    gtk_entry_set_text(GTK_ENTRY(re_password_entry), create_password);
    gtk_widget_set_sensitive(create_random_password, FALSE);
}

// start installation/configuration 
static void insta_config() {
    const gchar *insta_config_help_bt_label_a = "insta_config_help_bt_label", *config_label_a = "config_label", *name_label_a = "name_label", *name_entry_a = "name_entry", *password_label_a = "password_label", *password_entry_a = "password_entry", *password_show_one_a = "password_show_one", *re_password_label_a = "re_password_label", *re_password_entry_a = "re_password_entry", *password_show_two_a = "password_show_two", *go_back_one_bt_a = "go_back_one_bt", *save_info_bt_a = "save_info_bt", *create_random_password_a = "create_random_password"; 
    window_number = 2;
    if (window_number == check_number) {
        destroy_start_screen();
        check_number++;
    }
    
    insta_config_help_bt_label = gtk_button_new_with_label("?");
    g_signal_connect(insta_config_help_bt_label, "clicked", G_CALLBACK(help_win_all), NULL);
    gtk_grid_attach(GTK_GRID(grid), insta_config_help_bt_label, 1, 0, 1, 1);
    select_langauge(0, NULL, insta_config_help_bt_label);    
    gtk_widget_set_name(insta_config_help_bt_label, insta_config_help_bt_label_a);

    config_label = gtk_label_new("");
    select_langauge(1, config_label, NULL);
    gtk_widget_set_name(config_label, config_label_a);
    gtk_grid_attach(GTK_GRID(grid), config_label, 3, 1, 1, 1);

    name_label = gtk_label_new("");
    gtk_widget_set_name(name_label, name_label_a);
    gtk_grid_attach(GTK_GRID(grid), name_label, 3, 2, 1, 1);
    select_langauge(2, name_label, NULL);
    name_entry = gtk_entry_new();
    gtk_widget_set_name(name_entry, name_entry_a);
    gtk_entry_set_max_length(GTK_ENTRY(name_entry), 25);
    gtk_grid_attach(GTK_GRID(grid), name_entry, 4, 2, 1, 1);
    select_langauge(3, name_entry, NULL);

    password_label = gtk_label_new("");
    gtk_widget_set_name(password_label, password_label_a);
    gtk_grid_attach(GTK_GRID(grid), password_label, 3, 3, 1, 1);
    select_langauge(4, password_label, NULL);
    password_entry = gtk_entry_new();
    gtk_widget_set_name(password_entry, password_entry_a);
    gtk_entry_set_max_length(GTK_ENTRY(password_entry), 25);
    gtk_entry_set_visibility(GTK_ENTRY(password_entry), FALSE);
    gtk_grid_attach(GTK_GRID(grid), password_entry, 4, 3, 1, 1);
    select_langauge(5, password_entry, NULL);
    password_show_one = gtk_button_new_with_label(bad_face_passwd);
    gtk_widget_set_name(password_show_one, password_show_one_a);
    g_signal_connect(password_show_one, "clicked", G_CALLBACK(password_show_one_v), NULL);
    gtk_grid_attach(GTK_GRID(grid), password_show_one, 5, 3, 1, 1);
    select_langauge(6, NULL, password_show_one);

    re_password_label = gtk_label_new("");
    gtk_widget_set_name(re_password_label, re_password_label_a);
    gtk_grid_attach(GTK_GRID(grid), re_password_label, 3, 4, 1, 1);
    select_langauge(7, re_password_label, NULL);
    re_password_entry = gtk_entry_new();
    gtk_widget_set_name(re_password_entry, re_password_entry_a);
    gtk_entry_set_max_length(GTK_ENTRY(re_password_entry), 25);
    gtk_entry_set_text(GTK_ENTRY(re_password_entry), entry_passwd_saved);
    gtk_entry_set_visibility(GTK_ENTRY(re_password_entry), FALSE);
    gtk_grid_attach(GTK_GRID(grid), re_password_entry, 4, 4, 1, 1);
    select_langauge(8, re_password_entry, NULL);
    password_show_two = gtk_button_new_with_label(bad_face_passwd);
    gtk_widget_set_name(password_show_two, password_show_two_a);
    g_signal_connect(password_show_two, "clicked", G_CALLBACK(password_show_two_v), NULL);
    gtk_grid_attach(GTK_GRID(grid), password_show_two, 5, 4, 1, 1);
    select_langauge(9, NULL, password_show_two); 

    create_random_password = gtk_button_new_with_label("");
    gtk_widget_set_name(create_random_password, create_random_password_a);
    g_signal_connect(create_random_password, "clicked", G_CALLBACK(create_random_password_generator), NULL);
    gtk_grid_attach(GTK_GRID(grid), create_random_password, 5, 5, 1, 1);
    select_langauge(20, NULL, create_random_password);

    go_back_one_bt = gtk_button_new_with_label("");
    gtk_widget_set_name(go_back_one_bt, go_back_one_bt_a);
    g_signal_connect(go_back_one_bt, "clicked", G_CALLBACK(back_insta_config), NULL);
    gtk_grid_attach(GTK_GRID(grid), go_back_one_bt, 3, 6, 1, 1);
    select_langauge(10, NULL, go_back_one_bt); 

    save_info_bt = gtk_button_new_with_label("");
    gtk_widget_set_name(save_info_bt, save_info_bt_a);
    g_signal_connect(save_info_bt, "clicked", G_CALLBACK(save_info), NULL);
    gtk_grid_attach(GTK_GRID(grid), save_info_bt, 4, 6, 1, 1);
    select_langauge(11, NULL, save_info_bt); 

    error_insta_config_label = gtk_label_new("");
    gtk_grid_attach(GTK_GRID(grid), error_insta_config_label, 4, 7, 1, 1);
    gtk_widget_show_all(wdP->window);
}

// choose language for program and installation
static void german_language() {
    gtk_widget_set_sensitive(german_language_bt, FALSE);
    gtk_widget_set_sensitive(english_language_bt, TRUE);
    gtk_widget_set_name(german_language_bt, "german_language_selected");
    gtk_widget_set_name(english_language_bt, "english_language_deselected");
    user_language = 1;
    select_langauge(1, hello_label, NULL);
    select_langauge(2, NULL, german_language_bt);
    select_langauge(3, NULL, english_language_bt);
    select_langauge(4, NULL, install_bt);
    select_language_change_sys_info(0);
}

static void english_language() {
    gtk_widget_set_sensitive(german_language_bt, TRUE); 
    gtk_widget_set_sensitive(english_language_bt, FALSE);
    gtk_widget_set_name(german_language_bt, "german_language_deselected");
    gtk_widget_set_name(english_language_bt, "english_language_selected");
    user_language = 2;
    select_langauge(1, hello_label, NULL);
    select_langauge(2, NULL, german_language_bt);
    select_langauge(3, NULL, english_language_bt);
    select_langauge(4, NULL, install_bt);
    select_language_change_sys_info(0);
}

// window start screen 
static void start_screen() {
    const gchar *start_screen_help_bt_label_a = "start_screen_help_bt_label", *hello_label_a = "hello_label", *install_bt_a = "install_bt";
    window_number = 1;

    start_screen_help_bt_label = gtk_button_new_with_label("?");
    g_signal_connect(start_screen_help_bt_label, "clicked", G_CALLBACK(help_win_all), NULL);
    gtk_grid_attach(GTK_GRID(grid), start_screen_help_bt_label, 1, 0, 1, 1);
    gtk_widget_set_name(start_screen_help_bt_label, start_screen_help_bt_label_a);    
    select_langauge(0, NULL, start_screen_help_bt_label);

    hello_label = gtk_label_new("");
    gtk_grid_attach(GTK_GRID(grid), hello_label, 4, 2, 1, 1);
    gtk_widget_set_name(hello_label, hello_label_a);

    german_language_bt = gtk_button_new_with_label("");
    g_signal_connect(german_language_bt, "clicked", G_CALLBACK(german_language), NULL);
    gtk_grid_attach(GTK_GRID(grid), german_language_bt, 4, 3, 1, 1);
    gtk_widget_set_name(german_language_bt, "german_language_deselected");
    select_langauge(2, NULL, german_language_bt);

    english_language_bt = gtk_button_new_with_label("");
    g_signal_connect(english_language_bt, "clicked", G_CALLBACK(english_language), NULL);
    gtk_grid_attach(GTK_GRID(grid), english_language_bt, 4, 4, 1, 1);
    gtk_widget_set_name(english_language_bt, "english_language_deselected");
    select_langauge(3, NULL, english_language_bt);

    install_bt = gtk_button_new_with_label("");
    g_signal_connect(install_bt, "clicked", G_CALLBACK(insta_config), NULL);
    gtk_grid_attach(GTK_GRID(grid), install_bt, 4, 5, 1, 1);
    gtk_widget_set_name(install_bt, install_bt_a);
    
    if (user_language == 1) {
        german_language();
    }else if (user_language == 2) {
        english_language();
    }

    gtk_widget_show_all(wdP->window);
    gtk_main();
}
