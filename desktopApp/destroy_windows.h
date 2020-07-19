static void exit_help() {
    gtk_widget_destroy(help_win);
}

static void destroy_start_screen() {
    gtk_widget_destroy(hello_label);
    gtk_widget_destroy(german_language_bt);
    gtk_widget_destroy(english_language_bt);
    gtk_widget_destroy(install_bt);
    gtk_widget_destroy(start_screen_help_bt_label);
}

static void destroy_insta_config() {
    gtk_widget_destroy(config_label);
    gtk_widget_destroy(name_label);
    gtk_widget_destroy(name_entry);
    gtk_widget_destroy(password_label);
    gtk_widget_destroy(password_entry);
    gtk_widget_destroy(password_show_one);
    gtk_widget_destroy(re_password_label);
    gtk_widget_destroy(re_password_entry);
    gtk_widget_destroy(password_show_two);
    gtk_widget_destroy(go_back_one_bt);
    gtk_widget_destroy(save_info_bt);
    gtk_widget_destroy(error_insta_config_label);
    gtk_widget_destroy(insta_config_help_bt_label);
    gtk_widget_destroy(create_random_password);
}

static void destroy_what_to_install() {
    gtk_widget_destroy(help_garage_control);
    gtk_widget_destroy(garage_control);
    gtk_widget_destroy(garage_opener);
    gtk_widget_destroy(program_install_next);
}

static void destroy_connect_server() {
    gtk_widget_destroy(connect_server_help_bt_label);
    gtk_widget_destroy(connect_server_add_label);
    gtk_widget_destroy(server_name_label);
    gtk_widget_destroy(server_name_entry);
    gtk_widget_destroy(server_add_label);
    gtk_widget_destroy(server_add_entry);
    gtk_widget_destroy(server_search_hostname_bt);
    gtk_widget_destroy(save_info_add_bt);
    gtk_widget_destroy(error_connect_server);
    gtk_widget_destroy(server_ip_found_label);
}

static void destroy_window_theme_color() {
    gtk_widget_destroy(dark_theme_on_image);
    gtk_widget_destroy(on_theme_box);
    gtk_widget_destroy(dark_theme_off_image);
    gtk_widget_destroy(off_theme_box);
    gtk_widget_destroy(theme_color_next_bt);
    gtk_widget_destroy(window_theme_color_help_bt_label);
}

static void destroy_final_config() {
    gtk_widget_destroy(final_config_help_bt_label);
    gtk_widget_destroy(all_right_final_label);
    gtk_widget_destroy(change_user_name_bt);
    gtk_widget_destroy(user_name_c_label);
    gtk_widget_destroy(user_password_c_label);
    gtk_widget_destroy(cahnge_password_bt);
    gtk_widget_destroy(server_name_c_label);
    gtk_widget_destroy(server_ip_c_label);
    gtk_widget_destroy(user_uuid_c_label);
    gtk_widget_destroy(final_config_back_bt);
    gtk_widget_destroy(final_config_next_bt);
    if (!acc_created) {
        gtk_widget_destroy(show_user_password_c_bt);
    }
}

static void destroy_add_garage() {
    gtk_widget_destroy(add_garage_label);
    gtk_widget_destroy(add_garage_bt);
    gtk_widget_destroy(load_from_server_bt);
    gtk_widget_destroy(new_garages_label);
    gtk_widget_destroy(add_garage_next_bt);
    gtk_widget_destroy(save_all_new_garages_bt);
    gtk_widget_destroy(add_garage_help_bt_label);
    gtk_widget_destroy(remove_garage_bt);
}