static void help_win_all() {
    const gchar *stsh_exit_bt_a = "stsh_exit_bt"; 
    GtkWidget *stsh_label, *stsh_exit_bt;

    help_win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(help_win), 100, 60);
    gtk_container_set_border_width(GTK_CONTAINER(help_win), 10);
    gtk_window_set_position(GTK_WINDOW(help_win), GTK_WIN_POS_CENTER);
    gtk_window_set_decorated(GTK_WINDOW(help_win), FALSE);
    
    gtk_widget_set_name(help_win, my_window_css);
    cssProvider = gtk_css_provider_new();
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(cssProvider), GTK_STYLE_PROVIDER_PRIORITY_USER);
    my_style();

    grid_help = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(help_win), grid_help);
    
    stsh_exit_bt = gtk_button_new_with_label("");
    g_signal_connect(stsh_exit_bt, "clicked", G_CALLBACK(exit_help), NULL);
    gtk_grid_attach(GTK_GRID(grid_help), stsh_exit_bt, 0, 2, 1, 1);
    gtk_widget_set_name(stsh_exit_bt, stsh_exit_bt_a);

    select_language_help_window(stsh_exit_bt);

    stsh_label = gtk_label_new(help_text);
    gtk_grid_attach(GTK_GRID(grid_help), stsh_label, 0, 1, 1, 1);

    gtk_widget_show_all(help_win);
}