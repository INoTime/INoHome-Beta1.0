// change user name if something is wrong
GtkWidget *entry_user_name_final;
static void save_ch_user_name() {
    FILE *ch_user_name = fopen(user_info_file, "w");
    gchar_user_name_re = gtk_entry_get_text(GTK_ENTRY(entry_user_name_final));
    fputs(crypt_data(gchar_user_name_re, "", crypt_user_info_file), ch_user_name);
    fputs("\n", ch_user_name);
    fputs(password_a, ch_user_name);
    fclose(ch_user_name);
    select_language_change_sys_info(1);
    strcpy(name_b, name_b_save);
    strcat(name_b, gchar_user_name_re);
    gtk_label_set_text(GTK_LABEL(user_name_c_label), name_b);

    gtk_widget_destroy(change_user_name_window);
    destroy_final_config();
    final_config();
}
static void change_user_name_final() {
    const gchar *entry_user_name_final_a = "entry_user_name_final", *save_changes_user_name_f_a = "save_changes_user_name_f";
    GtkWidget *grid_change_user_name;
    GtkWidget *save_changes_user_name_f, *user_label;

    change_user_name_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(change_user_name_window), "Change user name");
    gtk_window_set_default_size(GTK_WINDOW(change_user_name_window), 100, 60);
    gtk_container_set_border_width(GTK_CONTAINER(change_user_name_window), 10);
    gtk_window_set_position(GTK_WINDOW(change_user_name_window), GTK_WIN_POS_CENTER);
    gtk_window_set_resizable(GTK_WINDOW(change_user_name_window), FALSE);
    
    gtk_widget_set_name(change_user_name_window, my_window_css);
    cssProvider = gtk_css_provider_new();
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(cssProvider), GTK_STYLE_PROVIDER_PRIORITY_USER);
    my_style();

    grid_change_user_name = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(change_user_name_window), grid_change_user_name);

    user_label = gtk_label_new("");
    gtk_grid_attach(GTK_GRID(grid_change_user_name), user_label, 1, 1, 1, 1);
    select_language_change_user_name_final(1, user_label, NULL);
    entry_user_name_final = gtk_entry_new();
    gtk_entry_set_max_length(GTK_ENTRY(entry_user_name_final), 25);
    gtk_entry_set_text(GTK_ENTRY(entry_user_name_final), decrypt_data(name_a, crypt_user_info_file));
    gtk_grid_attach(GTK_GRID(grid_change_user_name), entry_user_name_final, 2, 1, 1, 1);
    gtk_widget_set_name(entry_user_name_final, entry_user_name_final_a);
    
    save_changes_user_name_f = gtk_button_new_with_label("");
    g_signal_connect(save_changes_user_name_f, "clicked", G_CALLBACK(save_ch_user_name), NULL);
    gtk_grid_attach(GTK_GRID(grid_change_user_name), save_changes_user_name_f, 1, 2, 1, 1);
    gtk_widget_set_name(save_changes_user_name_f, save_changes_user_name_f_a);
    select_language_change_user_name_final(2, NULL, save_changes_user_name_f);

    gtk_widget_show_all(change_user_name_window);
}
// ---------------------------------------------------------------------------------------------

// those are to show the password and change the label

    // change password if something is wrong
void show_pass_a_final() {
    if (!password_show_one_setted) {
        gtk_entry_set_visibility(GTK_ENTRY(entry_password_final), TRUE);
        gtk_button_set_label(GTK_BUTTON(show_pass_a_final_bt), smile_face_passwd);
        password_show_one_setted++;
    }else {
        gtk_entry_set_visibility(GTK_ENTRY(entry_password_final), FALSE);
        gtk_button_set_label(GTK_BUTTON(show_pass_a_final_bt), bad_face_passwd);
        password_show_one_setted--;
    }    
}
void show_pass_b_final() {
    if (!password_show_two_setted) {
        gtk_entry_set_visibility(GTK_ENTRY(entry_password_final_ch), TRUE);
        gtk_button_set_label(GTK_BUTTON(show_pass_b_final_bt), smile_face_passwd);
        password_show_two_setted++;
    }else {
        gtk_entry_set_visibility(GTK_ENTRY(entry_password_final_ch), FALSE);
        gtk_button_set_label(GTK_BUTTON(show_pass_b_final_bt), bad_face_passwd);
        password_show_two_setted--;
    }
}
    // ---------------------------------------------------------------------------------------------
static void save_ch_password() {
    gchar_password_re = gtk_entry_get_text(GTK_ENTRY(entry_password_final));
    gchar_password_re_ch = gtk_entry_get_text(GTK_ENTRY(entry_password_final_ch));

    if (!strcmp(gchar_password_re, "") != 0) {
        select_language_change_password_final(4, false_password_label, NULL);
    }else if (!strcmp(gchar_password_re_ch, "") != 0) {
        select_language_change_password_final(5, false_password_label, NULL);
    }else if (!strcmp(gchar_password_re, gchar_password_re_ch) != 0) {
        FILE *ch_password = fopen(user_info_file, "w");
        fputs(name_a, ch_password);
        fputs(crypt_data(gchar_password_re, "", crypt_user_info_file), ch_password);
        fclose(ch_password);
        select_language_change_sys_info(1);
        select_language_change_sys_info(2);
        strcat(password_b, ch_user_password_re_save);
        strcpy(name_b, name_b_save);
        strcat(name_b, name_a);
        
        gtk_widget_destroy(change_password_window);
        destroy_final_config();
        final_config();  
    }else {
        select_language_change_password_final(6, false_password_label, NULL);
    }
}
static void change_password_final() {
    const gchar *entry_password_final_a = "entry_password_final", *show_pass_a_final_bt_a = "show_pass_a_final_bt", *entry_password_final_ch_a = "re_entry_password_final_ch", *show_pass_b_final_bt_a = "show_pass_b_final_bt", *save_changes_password_f_a = "save_changes_password_f"; 
    GtkWidget *grid_change_password;
    GtkWidget *save_changes_password_f, *entry_pass_label, *re_entry_pass_label;

    change_password_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(change_password_window), "Change user name");
    gtk_window_set_default_size(GTK_WINDOW(change_password_window), 100, 60);
    gtk_container_set_border_width(GTK_CONTAINER(change_password_window), 10);
    gtk_window_set_position(GTK_WINDOW(change_password_window), GTK_WIN_POS_CENTER);
    gtk_window_set_resizable(GTK_WINDOW(change_password_window), FALSE);
    
    gtk_widget_set_name(change_password_window, my_window_css);
    cssProvider = gtk_css_provider_new();
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(cssProvider), GTK_STYLE_PROVIDER_PRIORITY_USER);
    my_style();                                                                                         

    grid_change_password = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(change_password_window), grid_change_password);

    entry_pass_label = gtk_label_new("");
    gtk_grid_attach(GTK_GRID(grid_change_password), entry_pass_label, 1, 1, 1, 1);
    select_language_change_password_final(1, entry_pass_label, NULL);
    entry_password_final = gtk_entry_new();
    gtk_entry_set_max_length(GTK_ENTRY(entry_password_final), 25);
    gtk_entry_set_visibility(GTK_ENTRY(entry_password_final), FALSE);
    gtk_grid_attach(GTK_GRID(grid_change_password), entry_password_final, 2, 1, 1, 1);
    gtk_widget_set_name(entry_password_final, entry_password_final_a);
    show_pass_a_final_bt = gtk_button_new_with_label(bad_face_passwd);
    g_signal_connect(show_pass_a_final_bt, "clicked", G_CALLBACK(show_pass_a_final), NULL);
    gtk_grid_attach(GTK_GRID(grid_change_password), show_pass_a_final_bt, 3, 1, 1, 1);
    gtk_widget_set_name(show_pass_a_final_bt, show_pass_a_final_bt_a);

    re_entry_pass_label = gtk_label_new("");
    gtk_grid_attach(GTK_GRID(grid_change_password), re_entry_pass_label, 1, 2, 1, 1);
    select_language_change_password_final(2, re_entry_pass_label, NULL);
    entry_password_final_ch = gtk_entry_new();
    gtk_entry_set_max_length(GTK_ENTRY(entry_password_final_ch), 25);
    gtk_entry_set_visibility(GTK_ENTRY(entry_password_final_ch), FALSE);
    gtk_grid_attach(GTK_GRID(grid_change_password), entry_password_final_ch, 2, 2, 1, 1);
    gtk_widget_set_name(entry_password_final_ch, entry_password_final_ch_a);
    show_pass_b_final_bt = gtk_button_new_with_label(bad_face_passwd);
    g_signal_connect(show_pass_b_final_bt, "clicked", G_CALLBACK(show_pass_b_final), NULL);
    gtk_grid_attach(GTK_GRID(grid_change_password), show_pass_b_final_bt, 3, 2, 1, 1);
    gtk_widget_set_name(show_pass_b_final_bt, show_pass_b_final_bt_a);

    save_changes_password_f = gtk_button_new_with_label("");
    g_signal_connect(save_changes_password_f, "clicked", G_CALLBACK(save_ch_password), NULL);
    gtk_grid_attach(GTK_GRID(grid_change_password), save_changes_password_f, 1, 3, 1, 1);
    gtk_widget_set_name(save_changes_password_f, save_changes_password_f_a);
    select_language_change_password_final(3, NULL, save_changes_password_f);

    false_password_label = gtk_label_new("");
    gtk_grid_attach(GTK_GRID(grid_change_password), false_password_label, 1, 4, 1, 1);

    gtk_widget_show_all(change_password_window);
}
// ---------------------------------------------------------------------------------------------

static void cancle_go_next_to_final() {
    gtk_widget_destroy(go_next_will_close_conn_window);
}

static void go_next_will_close_conn() {
    const gchar *yes_exit_bt_a = "yes_exit_bt", *cancel_exit_bt_a = "cancel_exit_bt"; 
    GtkWidget *go_next_will_close_conn_grid;

    go_next_will_close_conn_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(go_next_will_close_conn_window), "Go next?");
    gtk_window_set_default_size(GTK_WINDOW(go_next_will_close_conn_window), 100, 60);
    gtk_container_set_border_width(GTK_CONTAINER(go_next_will_close_conn_window), 10);
    gtk_window_set_position(GTK_WINDOW(go_next_will_close_conn_window), GTK_WIN_POS_CENTER);
    gtk_window_set_resizable(GTK_WINDOW(go_next_will_close_conn_window), FALSE);
    
    gtk_widget_set_name(go_next_will_close_conn_window, my_window_css);
    cssProvider = gtk_css_provider_new();
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(cssProvider), GTK_STYLE_PROVIDER_PRIORITY_USER);
    my_style();                                                                                         

    go_next_will_close_conn_grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(go_next_will_close_conn_window), go_next_will_close_conn_grid);

    go_next_will_close_conn_label = gtk_label_new("");
    gtk_grid_attach(GTK_GRID(go_next_will_close_conn_grid), go_next_will_close_conn_label, 1, 0, 1, 1);
    select_language_go_next_will_close_conn(1, go_next_will_close_conn_label, NULL);

    yes_exit_bt = gtk_button_new_with_label("");
    g_signal_connect(yes_exit_bt, "clicked", G_CALLBACK(exit_config), NULL);
    gtk_grid_attach(GTK_GRID(go_next_will_close_conn_grid), yes_exit_bt, 1, 1, 1, 1);
    gtk_widget_set_name(yes_exit_bt, yes_exit_bt_a);
    select_language_go_next_will_close_conn(2, NULL, yes_exit_bt);

    cancle_exit_bt = gtk_button_new_with_label("");
    g_signal_connect(cancle_exit_bt, "clicked", G_CALLBACK(cancle_go_next_to_final), NULL);
    gtk_grid_attach(GTK_GRID(go_next_will_close_conn_grid), cancle_exit_bt, 2, 1, 1, 1);
    gtk_widget_set_name(cancle_exit_bt, cancel_exit_bt_a);
    select_language_go_next_will_close_conn(3, NULL, cancle_exit_bt);

    gtk_widget_show_all(go_next_will_close_conn_window);
}

static void remove_garage() {
    const gchar *remove_garage_name_entry_a = "remove_garage_name_entry", *remove_garage_accept_bt_a = "remove_garage_accept_bt"; 
    GtkWidget *remove_garage_grid, *remove_garage_name_label, *remove_garage_accept_bt;

    remove_garage_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(remove_garage_window), "Sorry...");
    gtk_window_set_default_size(GTK_WINDOW(remove_garage_window), 100, 60);
    gtk_container_set_border_width(GTK_CONTAINER(remove_garage_window), 10);
    gtk_window_set_position(GTK_WINDOW(remove_garage_window), GTK_WIN_POS_CENTER);
    gtk_window_set_resizable(GTK_WINDOW(remove_garage_window), FALSE);

    gtk_widget_set_name(remove_garage_window, my_window_css);
    cssProvider = gtk_css_provider_new();
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(cssProvider), GTK_STYLE_PROVIDER_PRIORITY_USER);
    my_style();   

    remove_garage_grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(remove_garage_window), remove_garage_grid); 

    remove_garage_name_label = gtk_label_new("");
    gtk_grid_attach(GTK_GRID(remove_garage_grid), remove_garage_name_label, 1, 0, 1, 1);
    select_language_remove_garage(1, remove_garage_name_label, FALSE);
    remove_garage_name_entry = gtk_entry_new();
    gtk_entry_set_max_length(GTK_ENTRY(remove_garage_name_entry), 31);
    gtk_grid_attach(GTK_GRID(remove_garage_grid), remove_garage_name_entry, 2, 0, 1, 1);
    gtk_widget_set_name(remove_garage_name_entry, remove_garage_name_entry_a);

    remove_garage_name_retry_label = gtk_label_new("");
    gtk_grid_attach(GTK_GRID(remove_garage_grid), remove_garage_name_retry_label, 1, 1, 1, 1);

    remove_garage_accept_bt = gtk_button_new_with_label("");
    g_signal_connect(remove_garage_accept_bt, "clicked", G_CALLBACK(remove_garage_choose), NULL);
    gtk_grid_attach(GTK_GRID(remove_garage_grid), remove_garage_accept_bt, 1, 2, 1, 1);
    gtk_widget_set_name(remove_garage_accept_bt, remove_garage_accept_bt_a);
    select_language_remove_garage(2, NULL, remove_garage_accept_bt);

    gtk_widget_show_all(remove_garage_window);
}

// close sorry_name_ip_garage_is_given_window
static void close_sorry_name_ip_garage_is_given_window() {
    gtk_widget_destroy(sorry_name_ip_garage_is_given_window);
}

// if name_ip_garage typed in twice show this window
static void sorry_name_ip_garage_is_given() {
    const gchar *sorry_name_ip_garage_is_given_ok_bt_a = "sorry_name_ip_garage_is_given_ok_bt";
    GtkWidget *sorry_name_ip_garage_is_given_grid;

    sorry_name_ip_garage_is_given_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(sorry_name_ip_garage_is_given_window), "Sorry...");
    gtk_window_set_default_size(GTK_WINDOW(sorry_name_ip_garage_is_given_window), 100, 60);
    gtk_container_set_border_width(GTK_CONTAINER(sorry_name_ip_garage_is_given_window), 10);
    gtk_window_set_position(GTK_WINDOW(sorry_name_ip_garage_is_given_window), GTK_WIN_POS_CENTER);
    gtk_window_set_resizable(GTK_WINDOW(sorry_name_ip_garage_is_given_window), FALSE);

    gtk_widget_set_name(sorry_name_ip_garage_is_given_window, my_window_css);
    cssProvider = gtk_css_provider_new();
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(cssProvider), GTK_STYLE_PROVIDER_PRIORITY_USER);
    my_style();   

    sorry_name_ip_garage_is_given_grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(sorry_name_ip_garage_is_given_window), sorry_name_ip_garage_is_given_grid); 

    sorry_name_ip_garage_is_given_label = gtk_label_new("");
    gtk_grid_attach(GTK_GRID(sorry_name_ip_garage_is_given_grid), sorry_name_ip_garage_is_given_label, 1, 1, 1, 1);

    sorry_name_ip_garage_is_given_ok_bt = gtk_button_new_with_label("Ok");
    g_signal_connect(sorry_name_ip_garage_is_given_ok_bt, "clicked", G_CALLBACK(close_sorry_name_ip_garage_is_given_window), sorry_name_ip_garage_is_given_ok_bt);
    gtk_grid_attach(GTK_GRID(sorry_name_ip_garage_is_given_grid), sorry_name_ip_garage_is_given_ok_bt, 1, 2, 1, 1);
    gtk_widget_set_name(sorry_name_ip_garage_is_given_ok_bt, sorry_name_ip_garage_is_given_ok_bt_a);
    select_language_sorry_name_ip_garage_is_given(1, NULL, sorry_name_ip_garage_is_given_ok_bt, NULL);

    gtk_widget_show_all(sorry_name_ip_garage_is_given_window);
}

static void search_for_ip_garage_a() {
    gchar_name_garage = gtk_entry_get_text(GTK_ENTRY(entry_name_garage));
    search_ip_garages();
}

static void add_garage_offline() {
    gchar_name_garage = gtk_entry_get_text(GTK_ENTRY(entry_name_garage));
    gchar_ip_garage = gtk_entry_get_text(GTK_ENTRY(entry_ip_garage));

    search_ip_garages();
    if (hostname_or_ip_not_exists) {
        if (!strcmp(gchar_name_garage, "") != 0) {
            select_language_add_garage_entry(5, check_garage_info_label, NULL);
        }else if (!strcmp(gchar_ip_garage, "") != 0) {
            select_language_add_garage_entry(6, check_garage_info_label, NULL);
        }else {  
            char save_for_one_name_ip_garage[160];   
            strcpy(save_for_one_name_ip_garage, ""); 
            strcat(save_for_one_name_ip_garage, "Name: ");
            strcat(save_for_one_name_ip_garage, gchar_name_garage);
            strcat(save_for_one_name_ip_garage, "\nIP: ");
            strcat(save_for_one_name_ip_garage, gchar_ip_garage);
            strcat(save_for_one_name_ip_garage, "\n\n");
            // check if name_ip_garage is typed in twice or more if yes block it and give output with an extra_window
            for (int x = 0; x != 255; x++) {
                if (!strcmp(save_name_ip_garage_a[x], save_for_one_name_ip_garage) != 0) {
                    sorry_name_ip_garage_is_given();
                    // set label for window
                    select_language_sorry_name_ip_garage_is_given(2, sorry_name_ip_garage_is_given_label, FALSE, save_for_one_name_ip_garage);
                    break;
                }else {
                    // save name_ip_garage in free space
                    if (!strcmp(save_name_ip_garage_a[x], "") != 0) {
                        strcat(save_name_ip_garage_a[x], save_for_one_name_ip_garage);
                        strcat(name_ip_garage, save_for_one_name_ip_garage);

                        strcat(save_name_garage_a[x], gchar_name_garage);
                        strcat(save_ip_garage_a[x], gchar_ip_garage);

                        strcat(save_name_ip_garage, gchar_name_garage);
                        strcat(save_name_ip_garage, " :: ");
                        strcat(save_name_ip_garage, gchar_ip_garage);
                        strcat(save_name_ip_garage, "\n");

                        gtk_label_set_text(GTK_LABEL(new_garages_label), name_ip_garage);
                        gtk_widget_set_sensitive(save_all_new_garages_bt, TRUE);
                        break;
                    }
                }
            }
            check_exit_config_server_conn = 0;
            gtk_widget_destroy(ip_name_garage_window);
        }
    }
}

static void add_garage_entry() {
    const gchar *entry_ip_garage_a = "entry_ip_garage_add_garage", *entry_name_garage_a = "entry_name_garage_add_garage", *search_for_ip_bt_a = "search_for_ip_bt_add_garage", *save_new_garage_bt_a = "save_new_garage_bt_add_garage";
    GtkWidget *ip_name_garage_grid, *name_garage_label, *ip_garage_label, *save_new_garage_bt, *search_for_ip_bt;
    ip_name_garage_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(ip_name_garage_window), "Change user name");
    gtk_window_set_default_size(GTK_WINDOW(ip_name_garage_window), 100, 60);
    gtk_container_set_border_width(GTK_CONTAINER(ip_name_garage_window), 10);
    gtk_window_set_position(GTK_WINDOW(ip_name_garage_window), GTK_WIN_POS_CENTER);
    gtk_window_set_resizable(GTK_WINDOW(ip_name_garage_window), FALSE);
    
    gtk_widget_set_name(ip_name_garage_window, my_window_css);
    cssProvider = gtk_css_provider_new();
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(cssProvider), GTK_STYLE_PROVIDER_PRIORITY_USER);
    my_style();                                                                                         

    ip_name_garage_grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(ip_name_garage_window), ip_name_garage_grid);

    ip_garage_label = gtk_label_new("");
    gtk_grid_attach(GTK_GRID(ip_name_garage_grid), ip_garage_label, 1, 1, 1, 1);
    select_language_add_garage_entry(1, ip_garage_label, NULL);
    entry_ip_garage = gtk_entry_new();
    gtk_entry_set_max_length(GTK_ENTRY(entry_ip_garage), INET_ADDRSTRLEN);
    gtk_grid_attach(GTK_GRID(ip_name_garage_grid), entry_ip_garage, 2, 1, 1, 1);
    gtk_widget_set_name(entry_ip_garage, entry_ip_garage_a);
    ip_garage_found = gtk_label_new("");
    gtk_grid_attach(GTK_GRID(ip_name_garage_grid), ip_garage_found, 3, 1, 1, 1);

    name_garage_label = gtk_label_new("");
    gtk_grid_attach(GTK_GRID(ip_name_garage_grid), name_garage_label, 1, 2, 1, 1);
    select_language_add_garage_entry(2, name_garage_label, NULL);
    entry_name_garage = gtk_entry_new();
    gtk_entry_set_max_length(GTK_ENTRY(entry_name_garage), 31);
    gtk_grid_attach(GTK_GRID(ip_name_garage_grid), entry_name_garage, 2, 2, 1, 1);
    gtk_widget_set_name(entry_name_garage, entry_name_garage_a);
    search_for_ip_bt = gtk_button_new_with_label("");
    g_signal_connect(search_for_ip_bt, "clicked", G_CALLBACK(search_for_ip_garage_a), NULL);
    gtk_grid_attach(GTK_GRID(ip_name_garage_grid), search_for_ip_bt, 3, 2, 1, 1);
    gtk_widget_set_name(search_for_ip_bt, search_for_ip_bt_a);
    select_language_add_garage_entry(3, NULL, search_for_ip_bt);

    save_new_garage_bt = gtk_button_new_with_label("");
    g_signal_connect(save_new_garage_bt, "clicked", G_CALLBACK(add_garage_offline), NULL);
    gtk_grid_attach(GTK_GRID(ip_name_garage_grid), save_new_garage_bt, 1, 3, 1, 1);
    gtk_widget_set_name(save_new_garage_bt, save_new_garage_bt_a);
    select_language_add_garage_entry(4, NULL, save_new_garage_bt);

    check_garage_info_label = gtk_label_new("");
    gtk_grid_attach(GTK_GRID(ip_name_garage_grid), check_garage_info_label, 1, 4, 1, 1);
    
    gtk_widget_show_all(ip_name_garage_window);
}

static void check_user_id_server() {
    // here must come the commands to control if uuid is saved and true
    int count_time = 0;
    for (;;) {
        system("sleep .5");
        count_time++;
        if (u_id.user_id_saved) {
            break;
        }else if (count_time >= 20) {
            select_language_check_uuid_is_here(2, check_label);
        }
    }
}

static void check_uuid_is_here() {
    gtk_widget_set_sensitive(dark_theme_on_image, FALSE);
    gtk_widget_set_sensitive(on_theme_box, FALSE);
    gtk_widget_set_sensitive(dark_theme_off_image, FALSE);
    gtk_widget_set_sensitive(off_theme_box, FALSE);
    gtk_widget_set_sensitive(theme_color_next_bt, FALSE);
    gtk_widget_set_sensitive(window_theme_color_help_bt_label, FALSE);

    check_uuid_client_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(check_uuid_client_window), 100, 60);
    gtk_container_set_border_width(GTK_CONTAINER(check_uuid_client_window), 10);
    gtk_window_set_position(GTK_WINDOW(check_uuid_client_window), GTK_WIN_POS_CENTER);
    gtk_window_set_decorated(GTK_WINDOW(check_uuid_client_window), FALSE);
    
    gtk_widget_set_name(check_uuid_client_window, my_window_css);
    cssProvider = gtk_css_provider_new();
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(cssProvider), GTK_STYLE_PROVIDER_PRIORITY_USER);
    my_style();

    check_uuid_client_grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(check_uuid_client_window), check_uuid_client_grid);

    check_label = gtk_label_new("");
    gtk_grid_attach(GTK_GRID(check_uuid_client_grid), check_label, 1, 0, 1, 1);
    select_language_check_uuid_is_here(1, check_label);

    gtk_widget_show_all(check_uuid_client_window);
    get_user_id_end();
}


static void install_failed_by_check_exit() {
    gtk_widget_destroy(install_failed_by_check_window);
}

static void install_failed_by_check() {
    const gchar *ok_bt_a = "ok_bt_install_failed";
    GtkWidget *install_failed_by_check_grid;

    install_failed_by_check_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(install_failed_by_check_window), "Fail");
    gtk_window_set_default_size(GTK_WINDOW(install_failed_by_check_window), 100, 60);
    gtk_container_set_border_width(GTK_CONTAINER(install_failed_by_check_window), 10);
    gtk_window_set_position(GTK_WINDOW(install_failed_by_check_window), GTK_WIN_POS_CENTER);
    gtk_window_set_resizable(GTK_WINDOW(install_failed_by_check_window), FALSE);
    
    gtk_widget_set_name(install_failed_by_check_window, my_window_css);
    cssProvider = gtk_css_provider_new();
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(cssProvider), GTK_STYLE_PROVIDER_PRIORITY_USER);
    my_style();                                                                                         

    install_failed_by_check_grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(install_failed_by_check_window), install_failed_by_check_grid);

    install_failed_by_check_label = gtk_label_new("");
    gtk_grid_attach(GTK_GRID(install_failed_by_check_grid), install_failed_by_check_label, 1, 0, 1, 1);
    select_language_install_failed_by_check(1, install_failed_by_check_label, FALSE);

    ok_bt = gtk_button_new_with_label("");
    g_signal_connect(ok_bt, "clicked", G_CALLBACK(install_failed_by_check_exit), NULL);
    gtk_grid_attach(GTK_GRID(install_failed_by_check_grid), ok_bt, 1, 1, 1, 1);
    gtk_widget_set_name(ok_bt, ok_bt_a);
    select_language_install_failed_by_check(2, ok_bt, FALSE);

    gtk_widget_show_all(install_failed_by_check_window);
}

static void all_loaded_garages_server() {
    GtkWidget *grid_all_loaded_gareges_server, *scrolled_window;

    all_loaded_garages_server_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(all_loaded_garages_server_window), "All garages");
    gtk_window_set_default_size(GTK_WINDOW(all_loaded_garages_server_window), 450, 600);
    gtk_container_set_border_width(GTK_CONTAINER(all_loaded_garages_server_window), 10);
    gtk_window_set_position(GTK_WINDOW(all_loaded_garages_server_window), GTK_WIN_POS_CENTER);
    gtk_window_set_resizable(GTK_WINDOW(all_loaded_garages_server_window), FALSE);

    gtk_widget_set_name(all_loaded_garages_server_window, my_window_css);
    cssProvider = gtk_css_provider_new();
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(cssProvider), GTK_STYLE_PROVIDER_PRIORITY_USER);
    my_style();  

    garages_server_label = gtk_label_new("");

    scrolled_window = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);

    gtk_container_add(GTK_CONTAINER(scrolled_window), garages_server_label);
    gtk_container_add(GTK_CONTAINER(all_loaded_garages_server_window), scrolled_window);

    gtk_widget_show_all(all_loaded_garages_server_window);

}