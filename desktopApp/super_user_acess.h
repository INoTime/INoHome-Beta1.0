// super user access
static void checked_auto_super_user_acess() {
    if (!super_user_auto) {
        super_user_auto = 1;
    }else {
        super_user_auto = 0;
    }
}

static void show_passwd_super_user() {
    if (!password_show_one_setted) {
        gtk_button_set_label(GTK_BUTTON(bt_show_passwd_super_user), smile_face_passwd);
        gtk_entry_set_visibility(GTK_ENTRY(entry_super_user_password), TRUE);
        password_show_one_setted++;
    }else {
        gtk_button_set_label(GTK_BUTTON(bt_show_passwd_super_user), bad_face_passwd);
        gtk_entry_set_visibility(GTK_ENTRY(entry_super_user_password), FALSE);
        password_show_one_setted--;
    }    
}

static void super_user_acess() {
    GtkWidget *super_user_access_grid, *super_user_access_help_bt, *label_super_user_name, *label_super_user_password;
    const gchar *super_user_access_help_bt_a = "super_user_access_help_bt", *entry_super_user_name_a = "entry_super_user_name", *entry_super_user_password_a = "entry_super_user_password", *bt_show_passwd_super_user_a = "bt_show_passwd_super_user", *super_user_save_bt_a = "super_user_save_bt";
    window_number = 101;
    
    super_user_access_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(super_user_access_window), 120, 100);
    gtk_container_set_border_width(GTK_CONTAINER(super_user_access_window), 10);
    gtk_window_set_position(GTK_WINDOW(super_user_access_window), GTK_WIN_POS_CENTER);
    gtk_window_set_decorated(GTK_WINDOW(super_user_access_window), FALSE);
    
    gtk_widget_set_name(super_user_access_window, my_window_css);
    cssProvider = gtk_css_provider_new();
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(cssProvider), GTK_STYLE_PROVIDER_PRIORITY_USER);
    my_style();

    super_user_access_grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(super_user_access_window), super_user_access_grid);

    super_user_access_help_bt = gtk_button_new_with_label("?");
    g_signal_connect(super_user_access_help_bt, "clicked", G_CALLBACK(help_win_all), NULL);
    gtk_grid_attach(GTK_GRID(super_user_access_grid), super_user_access_help_bt, 0, 1, 1, 1);
    select_language_super_user_acess(0, NULL, super_user_access_help_bt);
    gtk_widget_set_name(super_user_access_help_bt, super_user_access_help_bt_a);

    label_super_user_name = gtk_label_new("Super username:");
    gtk_grid_attach(GTK_GRID(super_user_access_grid), label_super_user_name, 1, 1, 1, 1);
    select_language_super_user_acess(1, label_super_user_name, NULL);
    entry_super_user_name = gtk_entry_new();
    gtk_entry_set_max_length(GTK_ENTRY(entry_super_user_name), 25);
    gtk_grid_attach(GTK_GRID(super_user_access_grid), entry_super_user_name, 2, 1, 1, 1);
    gtk_widget_set_name(entry_super_user_name, entry_super_user_name_a);
    select_language_super_user_acess(2, entry_super_user_name, NULL);

    label_super_user_password = gtk_label_new("Password:");
    gtk_grid_attach(GTK_GRID(super_user_access_grid), label_super_user_password, 1, 2, 1, 1);
    select_language_super_user_acess(3, label_super_user_password, NULL);
    entry_super_user_password = gtk_entry_new();
    gtk_entry_set_max_length(GTK_ENTRY(entry_super_user_password), 25);
    gtk_entry_set_visibility(GTK_ENTRY(entry_super_user_password), FALSE);
    gtk_grid_attach(GTK_GRID(super_user_access_grid), entry_super_user_password, 2, 2, 1, 1);
    gtk_widget_set_name(entry_super_user_password, entry_super_user_password_a);
    select_language_super_user_acess(4, entry_super_user_password, NULL);
    bt_show_passwd_super_user = gtk_button_new_with_label(bad_face_passwd);
    g_signal_connect(bt_show_passwd_super_user, "clicked", G_CALLBACK(show_passwd_super_user), NULL);
    gtk_grid_attach(GTK_GRID(super_user_access_grid), bt_show_passwd_super_user, 3, 2, 1, 1);
    gtk_widget_set_name(bt_show_passwd_super_user, bt_show_passwd_super_user_a);

    if (!was_here_super_user) {
        check_box_save_super_user_data = gtk_check_button_new_with_label("");
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(check_box_save_super_user_data), FALSE);
        g_signal_connect(GTK_TOGGLE_BUTTON(check_box_save_super_user_data), "toggled", G_CALLBACK(checked_auto_super_user_acess), super_user_access_window);
        gtk_grid_attach(GTK_GRID(super_user_access_grid), check_box_save_super_user_data, 1, 3, 1, 1); 
        select_language_super_user_acess(5, NULL, check_box_save_super_user_data);
    }

    super_user_save_bt = gtk_button_new_with_label("");
    // start thread to check if entrys are ok to start main_connection_handler and check if super user is right
    g_signal_connect(super_user_save_bt, "clicked", G_CALLBACK(get_super_user_acess), NULL);
    gtk_grid_attach(GTK_GRID(super_user_access_grid), super_user_save_bt, 2, 4, 1, 1);
    gtk_widget_set_name(super_user_save_bt, super_user_save_bt_a);
    select_language_super_user_acess(6, NULL, super_user_save_bt);

    error_user_save_label = gtk_label_new("");
    gtk_grid_attach(GTK_GRID(super_user_access_grid), error_user_save_label, 1, 4, 1, 1);

    gtk_widget_show_all(super_user_access_window);
}
// ---------------------------------------------------------------------------------------------