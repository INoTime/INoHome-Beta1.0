// close about dialog
void close_about_callback(GtkDialog *dialog) {
    gtk_widget_destroy(GTK_WIDGET(dialog));
}

// about dialog 
void about_callback() {
    GtkWidget *about_dialog;

    about_dialog = gtk_about_dialog_new();

    GdkPixbuf *main_image = gdk_pixbuf_new_from_file(MAIN_IMAGE_NAME, NULL);
    const gchar *author[] = {"Niklas Lurse", NULL};
    const gchar *documenters[] = {"Niklas Lurse", NULL};

    gtk_about_dialog_set_logo(GTK_ABOUT_DIALOG(about_dialog), main_image);
    gtk_window_set_icon_from_file(GTK_WINDOW(about_dialog), MAIN_IMAGE_NAME, NULL);
    select_language_about(1, about_dialog);
    gtk_about_dialog_set_version(GTK_ABOUT_DIALOG(about_dialog), "0.0.1");
    gtk_about_dialog_set_copyright(GTK_ABOUT_DIALOG(about_dialog), "Copyright \xc2\xa9 2020 Niklas Lurse");
    gtk_about_dialog_set_authors(GTK_ABOUT_DIALOG(about_dialog), author);
    gtk_about_dialog_set_documenters(GTK_ABOUT_DIALOG(about_dialog), documenters);
    gtk_about_dialog_set_translator_credits(GTK_ABOUT_DIALOG(about_dialog), "Niklas Lurse");
    gtk_about_dialog_set_website_label(GTK_ABOUT_DIALOG(about_dialog), "INoInvestigation Website");
    gtk_about_dialog_set_website(GTK_ABOUT_DIALOG(about_dialog), "https://inoinvestigation.com");

    g_signal_connect(GTK_DIALOG(about_dialog), "response", G_CALLBACK(close_about_callback), NULL);

    gtk_widget_show(about_dialog);
}

// the main thing in this file the menu bar
static void menu_bar(GtkApplication *programApp, gpointer user_data) {
    GSimpleAction *conenct_server, *quit_app;
    GSimpleAction *app_settings, *client_settings, *garage_settings, *server_settings;
    GSimpleAction *help, *support, *about;
//    const gchar *connect_server_a = "connect_server", *quit_app_a = "quit_app", *app_settings_a = "app_settings", *client_settings_a = "client_settings", *garage_settings_a = "garage_settings", *server_settings_a = "server_settings", *config_garage_a = "config_garage", *config_server_a = "config_server", *about_a = "about", *help_a = "help";

    GtkBuilder *builder;
    GError *error = NULL;

    // Connect
    conenct_server = g_simple_action_new("connect_server", NULL);
    g_signal_connect(conenct_server, "activate", G_CALLBACK (main_connection_main_screen_handler), programApp);
    g_action_map_add_action(G_ACTION_MAP(programApp), G_ACTION(conenct_server));

    quit_app = g_simple_action_new("quit_app", NULL);
    g_signal_connect(quit_app, "activate", G_CALLBACK(system_end_program), programApp);
    g_action_map_add_action(G_ACTION_MAP(programApp), G_ACTION(quit_app));
    // --------------------------

    // Settings
    app_settings = g_simple_action_new("app_settings", NULL);
    g_signal_connect(app_settings, "activate", G_CALLBACK(get_app_settings), programApp);
    g_action_map_add_action(G_ACTION_MAP(programApp), G_ACTION(app_settings));

    client_settings = g_simple_action_new("client_settings", NULL);
    g_signal_connect(client_settings, "activate", G_CALLBACK(get_client_settings), programApp);
    g_action_map_add_action(G_ACTION_MAP(programApp), G_ACTION(client_settings));

    garage_settings = g_simple_action_new("garage_settings", NULL);
    g_signal_connect(garage_settings, "activate", G_CALLBACK(get_garage_settings), programApp);
    g_action_map_add_action(G_ACTION_MAP(programApp), G_ACTION(garage_settings));

    server_settings = g_simple_action_new("server_settings", NULL);
    g_signal_connect(server_settings, "activate", G_CALLBACK(get_server_settings), programApp);
    g_action_map_add_action(G_ACTION_MAP(programApp), G_ACTION(server_settings));
    // --------------------------

    // Help
    help = g_simple_action_new("help", NULL);
    g_signal_connect(help, "activate", G_CALLBACK(get_help), programApp);
    g_action_map_add_action(G_ACTION_MAP(programApp), G_ACTION(help)); 
    
    support = g_simple_action_new("support", NULL);
    g_signal_connect(support, "activate", G_CALLBACK(get_support), programApp);
    g_action_map_add_action(G_ACTION_MAP(programApp), G_ACTION(support));
    
    about = g_simple_action_new("about", NULL);
    g_signal_connect(about, "activate", G_CALLBACK(about_callback), programApp);
    g_action_map_add_action(G_ACTION_MAP(programApp), G_ACTION(about));
    // --------------------------


    builder = gtk_builder_new();
    // select language for menubar
    if (chosen_language == 1) {
        gtk_builder_add_from_file(builder, menubar_de, &error);
    }else {
        gtk_builder_add_from_file(builder, menubar_en, &error);
    }
    
    GObject *menubar = gtk_builder_get_object (builder, "menubar");
    gtk_application_set_menubar(GTK_APPLICATION(programApp), G_MENU_MODEL(menubar));
}