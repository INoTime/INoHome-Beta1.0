static void show_password_login() {
    if (show_password_login_cout) {
        gtk_entry_set_visibility(GTK_ENTRY(login_password_entry), FALSE);
        gtk_button_set_label(GTK_BUTTON(login_show_password_bt), bad_face_passwd);
        show_password_login_cout = 0;
    }else {
        gtk_entry_set_visibility(GTK_ENTRY(login_password_entry), TRUE);
        gtk_button_set_label(GTK_BUTTON(login_show_password_bt), smile_face_passwd);
        show_password_login_cout = 1;
    }
}

static void get_acess_main_system() {
    // need to unlock program
    // get data from user_info_file
    int pwd_cout_line = 0;
    const gchar *get_login_password_entry = gtk_entry_get_text(GTK_ENTRY(login_password_entry));

    if (!strcmp(get_login_password_entry, "") != 0) {
        select_language_get_acess_main_system(4, login_error_label, NULL);
    }else {
        FILE *user_info_file_o = fopen(user_info_file, "r");
        while (fgets(pwd_aa[pwd_cout_line], sizeof(pwd_aa[pwd_cout_line]), user_info_file_o) != NULL) {
            strcpy(pwd_a[pwd_cout_line], decrypt_data(pwd_aa[pwd_cout_line], crypt_user_info_file));
            pwd_cout_line++;
        }
        fclose(user_info_file_o);

        char pwd_entry[pwd_data];
        // convert entred password from const gchar to char
        sprintf(pwd_entry, "%s", get_login_password_entry);
        if (!strcmp(pwd_entry, pwd_a[1]) != 0) {
            gtk_widget_destroy(get_acess_window);
            loged_in = 1;
            // connect automatically to server if it is active
            if (!strcmp(server_data[2], "auto_connect_on") != 0) {
                connecting_to_server();
                main_connection_handler();
                // fallback to go to main screen user must connect by himself to server
            }else {
                main_screen();
            }
        }else {
            select_language_get_acess_main_system(5, login_error_label, NULL);
        }
    }
}

// if return pressed get acess to main system
gboolean key_pressed_login_window(GtkWidget *widget, GdkEventKey *event, gpointer data) {
    if (!strcmp("Return", gdk_keyval_name(event->keyval))) {
        get_acess_main_system();
        return TRUE;
    }
    return FALSE;
}

static void get_acess() {
    const gchar *login_user_image_a = "login_user_image", *login_password_entry_a = "login_password_entry", *login_show_password_bt_a = "login_show_password_bt", *login_get_acess_bt_a = "login_get_acess_bt";

    get_acess_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(get_acess_window), 450, 300);
    gtk_window_set_position(GTK_WINDOW(get_acess_window), GTK_WIN_POS_CENTER);
    gtk_window_set_title(GTK_WINDOW(get_acess_window), "INoHome get Acess");
    gtk_window_set_resizable(GTK_WINDOW(get_acess_window), FALSE);
    gtk_widget_set_name(get_acess_window, my_window_css);
    gtk_window_set_icon_from_file(GTK_WINDOW(get_acess_window), MAIN_IMAGE_NAME, NULL);
    g_signal_connect(wdP->window, "destroy", G_CALLBACK(system_end_program), NULL);
    gtk_container_set_border_width(GTK_CONTAINER(get_acess_window), 50);
    gtk_widget_add_events(get_acess_window, GDK_KEY_PRESS_MASK);
    g_signal_connect(GTK_WIDGET(get_acess_window), "key_press_event", G_CALLBACK(key_pressed_login_window), NULL);


    get_acess_grid = gtk_grid_new(); 
    gtk_container_add(GTK_CONTAINER(get_acess_window), get_acess_grid);
    gtk_grid_set_row_spacing(GTK_GRID(get_acess_grid), 0);

    login_user_image = gtk_image_new_from_file("images/inoinvestigationLogin.png");
    gtk_grid_attach(GTK_GRID(get_acess_grid), login_user_image, 1, 1, 1, 1);
    gtk_widget_set_name(login_user_image, login_user_image_a);

    // login label
    wdP->label = gtk_label_new("");
    gtk_grid_attach(GTK_GRID(get_acess_grid), wdP->label, 1, 2, 1, 1);
    select_language_get_acess_main_system(1, wdP->label, NULL);

    // password label
    wdP->label = gtk_label_new("");
    gtk_grid_attach(GTK_GRID(get_acess_grid), wdP->label, 0, 3, 1, 1);
    select_language_get_acess_main_system(6, wdP->label, NULL);
    login_password_entry = gtk_entry_new();
    gtk_entry_set_max_length(GTK_ENTRY(login_password_entry), 25);
    gtk_entry_set_visibility(GTK_ENTRY(login_password_entry), FALSE);
    gtk_grid_attach(GTK_GRID(get_acess_grid), login_password_entry, 1, 3, 1, 1);
    select_language_get_acess_main_system(2, login_password_entry, NULL);  
    gtk_widget_set_name(login_password_entry, login_password_entry_a);
    login_show_password_bt = gtk_button_new_with_label(bad_face_passwd);
    g_signal_connect(login_show_password_bt, "clicked", G_CALLBACK(show_password_login), NULL);
    gtk_grid_attach(GTK_GRID(get_acess_grid), login_show_password_bt, 2, 3, 1, 1);
    gtk_widget_set_name(login_show_password_bt, login_show_password_bt_a);

    // login button
    wdP->button = gtk_button_new_with_label("");
    g_signal_connect(wdP->button, "clicked", G_CALLBACK(get_acess_main_system), NULL);
    gtk_grid_attach(GTK_GRID(get_acess_grid), wdP->button, 1, 4, 1, 1);
    select_language_get_acess_main_system(3, NULL, wdP->button);
    gtk_widget_set_name(wdP->button, login_get_acess_bt_a);

    login_error_label = gtk_label_new("");
    gtk_grid_attach(GTK_GRID(get_acess_grid), login_error_label, 1, 5, 1, 1);

    gtk_widget_show_all(get_acess_window);
}