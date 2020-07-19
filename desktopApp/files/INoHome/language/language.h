static void select_language_get_acess_main_system(int choose, GtkWidget *label, GtkWidget *button) {
    switch (chosen_language) {
        // german
        case 1:
            switch(choose) {
                case 1: gtk_label_set_text(GTK_LABEL(label), "\nLogin\n"); break;
                case 2: gtk_widget_set_tooltip_text(label, "Bitte geben Sie hier ihr Passwort ein!"); break;
                case 3: gtk_button_set_label(GTK_BUTTON(button), "Zugriff"); break;
                case 4: gtk_label_set_text(GTK_LABEL(label), "Bitte geben Sie ihr Passwort ein!"); break;
                case 5: gtk_label_set_text(GTK_LABEL(label), "Passwort ist falsch!"); break;
                case 6: gtk_label_set_text(GTK_LABEL(label), "Passwort:\t"); break;
            }
        break;

        // englisch
        case 2:
            switch (choose) {
                case 1: gtk_label_set_text(GTK_LABEL(label), "\nLogin\n"); break;
                case 2: gtk_widget_set_tooltip_text(label, "Please enter here your password!"); break;
                case 3: gtk_button_set_label(GTK_BUTTON(button), "Get acess"); break;
                case 4: gtk_label_set_text(GTK_LABEL(label), "Please enter password!"); break;
                case 5: gtk_label_set_text(GTK_LABEL(label), "Password is incorrect!"); break;
                case 6: gtk_label_set_text(GTK_LABEL(label), "Password:\t"); break;
            }
        break;
    }
}

static void select_language_main_window(int choose, int connected_to_server, char *garage_ip_add_hostname, char *garage_status, GtkWidget *label, GtkWidget *button) {
    char for_one[200] = "", for_two[300] = "";
    switch (chosen_language) {
        // german
        case 1:
            switch(choose) {
                case 0: gtk_label_set_text(GTK_LABEL(label), "\U0001f534 Getrennt"); break;
                case 1: gtk_label_set_text(GTK_LABEL(label), "\U0001f7e2 Verbunden"); break;
                case 2: if (connected_to_server == 1) {
                            // connected
                            strcpy(for_one, "\n\U0001f7e2");
                        }else if (connected_to_server == 0){
                            // Disconnected
                            strcpy(for_one, "\n\U0001f534");
                        }else {
                            strcpy(for_one, "");
                        }
                        strcpy(for_one, garage_status);
                        strcat(for_one, "\n");
                        strcat(for_one, garage_ip_add_hostname);
                        gtk_label_set_text(GTK_LABEL(label), for_one); 
                        strcpy(for_two, "Um Garage zu bearbeiten, bitte klicken:\n");
                        strcat(for_two, for_one);
                        for_two[strlen(for_two)-1] = '\0';
                        gtk_widget_set_tooltip_text(button, for_two); break;
            }
        break;

        // englisch
        case 2:
            switch (choose) {
                case 0: gtk_label_set_text(GTK_LABEL(label), "\U0001f534 Disconnected"); break;
                case 1: gtk_label_set_text(GTK_LABEL(label), "\U0001f7e2 Connected"); break;
                case 2: if (connected_to_server == 1) {
                            // connected
                            strcpy(for_one, "\n\U0001f7e2");
                        }else if (connected_to_server == 0){
                            // Disconnected
                            strcpy(for_one, "\n\U0001f534");
                        }else {
                            strcpy(for_one, "");
                        }
                        strcat(for_one, garage_status);
                        strcat(for_one, "\n");
                        strcat(for_one, garage_ip_add_hostname);
                        gtk_label_set_text(GTK_LABEL(label), for_one); 
                        strcpy(for_two, "To change garage, click here:\n");
                        strcat(for_two, for_one);
                        for_two[strlen(for_two)-1] = '\0';
                        gtk_widget_set_tooltip_text(button, for_two); break;
            }
        break;
    }
}


static void select_language_connecting_to_server(int choose, GtkWidget *label, GtkWidget *button) {
    char for_one[250] = "";
    switch (chosen_language) {
        // german
        case 1:
            switch(choose) {
                case 1: strcat(for_one, "\nAuto-Connecting zum Server...\nStellen Sie sicher dass Ihg Server online ist:\n\nServer IP: ");
                        strcat(for_one, server_data[1]);
                        strcat(for_one, "Hostname: ");
                        strcat(for_one, server_data[0]);
                        gtk_label_set_text(GTK_LABEL(label), for_one); break;
                case 2: gtk_button_set_label(GTK_BUTTON(button), "Ohne Server verbindung weiter"); 
                        gtk_widget_set_tooltip_text(button, "Das ist nicht Ihr Server?\nSie können diesen in den server Einstellungen ändern!\nIst Ihre IP-Adresse gesperrt?\nEntsperren auf dem Server!"); break;
                case 3: gtk_button_set_label(GTK_BUTTON(button), "Beenden"); 
                        gtk_widget_set_tooltip_text(button, "Programm beenden"); break;
                case 4: gtk_label_set_text(GTK_LABEL(label), "\nIhre IP-Adresse ist blockiert...\nEndblockieren auf dem Server!"); break;
            }
        break;

        // englisch
        case 2:
            switch (choose) {
                case 1: strcat(for_one, "\nAuto-connecting to server...\nMake sure server is online:\n\nServer IP: ");
                        strcat(for_one, server_data[0]);
                        strcat(for_one, "Hostname: ");
                        strcat(for_one, server_data[1]);
                        gtk_label_set_text(GTK_LABEL(label), for_one); break;
                case 2: gtk_button_set_label(GTK_BUTTON(button), "Go next without server connection"); 
                        gtk_widget_set_tooltip_text(button, "This is not your server?\nYou can change it in server settings!\nIs your IP-adress blocked?\nEndblock on server!"); break;
                case 3: gtk_button_set_label(GTK_BUTTON(button), "Quit"); 
                        gtk_widget_set_tooltip_text(button, "Quit program"); break;
                case 4: gtk_label_set_text(GTK_LABEL(label), "\nYour IP-adress is blocked...\nEndblock on server!"); break;
            }
        break;
    }
}

static void slect_language_client_settings(int choose, char *username_or_hostname_or_ip, GtkWidget *label, GtkWidget *button) {
    char for_one[100] = "";
    switch (chosen_language) {
        case 1:
            switch(choose) {
                case 1: strcat(for_one, "User Name: ");
                        strcat(for_one, username_or_hostname_or_ip);
                        gtk_label_set_text(GTK_LABEL(label), for_one); break;
                case 2: strcat(for_one, "User Passwort: ");
                        strcat(for_one, username_or_hostname_or_ip);
                        gtk_label_set_text(GTK_LABEL(label), for_one); break;        
                case 3: strcat(for_one, "IP-Adresse: ");
                        strcat(for_one, username_or_hostname_or_ip);
                        gtk_label_set_text(GTK_LABEL(label), for_one); break; 
                case 4: strcat(for_one, "Hostname: ");
                        strcat(for_one, username_or_hostname_or_ip);
                        gtk_label_set_text(GTK_LABEL(label), for_one); break; 
                case 5: strcat(for_one, "UUID: ");
                        strcat(for_one, username_or_hostname_or_ip);
                        gtk_label_set_text(GTK_LABEL(label), for_one); break; 
                case 6: gtk_button_set_label(GTK_BUTTON(button), "Ändern"); break;

                case 9: strcat(for_one, "User Passwort: ");
                        strcat(for_one, username_or_hostname_or_ip);
                        gtk_label_set_text(GTK_LABEL(label), for_one); break;
            }
        break;

        case 2:
            switch (choose) {
                case 1: strcat(for_one, "Username: ");
                        strcat(for_one, username_or_hostname_or_ip);
                        gtk_label_set_text(GTK_LABEL(label), for_one); break;
                case 2: strcat(for_one, "User password: ");
                        strcat(for_one, username_or_hostname_or_ip);
                        gtk_label_set_text(GTK_LABEL(label), for_one); break;
                case 3: strcat(for_one, "IP-adress: ");
                        strcat(for_one, username_or_hostname_or_ip);
                        gtk_label_set_text(GTK_LABEL(label), for_one); break; 
                case 4: strcat(for_one, "Hostname: ");
                        strcat(for_one, username_or_hostname_or_ip);
                        gtk_label_set_text(GTK_LABEL(label), for_one); break; 
                case 5: strcat(for_one, "UUID: ");
                        strcat(for_one, username_or_hostname_or_ip);
                        gtk_label_set_text(GTK_LABEL(label), for_one); break; 
                case 6: gtk_button_set_label(GTK_BUTTON(button), "Change"); break;

                case 9: strcat(for_one, "User password: ");
                        strcat(for_one, username_or_hostname_or_ip);
                        gtk_label_set_text(GTK_LABEL(label), for_one); break;
            }
        break;
    }
}



static void select_language_about(int choose, GtkWidget *about_dialog) {
    switch (chosen_language) {
        // german
        case 1:
            switch (choose) {
                case 1: gtk_about_dialog_set_program_name(GTK_ABOUT_DIALOG(about_dialog), "Über INoInvestigation Garage"); break;
            }
        break;

        // englisch
        case 2:
            switch (choose) {
                case 1: gtk_about_dialog_set_program_name(GTK_ABOUT_DIALOG(about_dialog), "About INoInvestigation Garage"); break;
            }
        break;
    }
}

static void select_language_change_user_name(int choose, GtkWidget *label, GtkWidget *button) {
    switch (chosen_language) {
        // german
        case 1:
            switch (choose) {
                case 1: gtk_label_set_text(GTK_LABEL(label), "User Name:"); break;
                case 2: gtk_widget_set_tooltip_text(label, "Hier können Sie Ihren Benutzernamen ändern"); break;
                case 3: gtk_button_set_label(GTK_BUTTON(button), "Sichern"); break;
                case 4: gtk_label_set_text(GTK_LABEL(label), "Bitte geben Sie einen User Namen ein!"); break;
            }
        break;

        // englisch
        case 2:
            switch (choose) {
                case 1: gtk_label_set_text(GTK_LABEL(label), "Username:"); break;
                case 2: gtk_widget_set_tooltip_text(label, "Here you can change your username"); break;
                case 3: gtk_button_set_label(GTK_BUTTON(button), "Save"); break;
                case 4: gtk_label_set_text(GTK_LABEL(label), "Please insert an username!"); break;
            }
        break;
    }
}

static void select_language_change_password(int choose, GtkWidget *label, GtkWidget *button) {
    switch (chosen_language) {
        // german
        case 1:
            switch (choose) {
                case 1: gtk_label_set_text(GTK_LABEL(label), "Passwort:"); break;
                case 2: gtk_widget_set_tooltip_text(label, "Hier können Sie Ihre Passwort ändern"); break;
                case 3: gtk_widget_set_tooltip_text(button, "Passwort anzeigen"); break;
                case 4: gtk_button_set_label(GTK_BUTTON(button), "Sichern"); break;
                case 5: gtk_label_set_text(GTK_LABEL(label), "Bitte geben Sie ein Passwort ein!"); break;
            }
        break;

        // englisch
        case 2:
            switch (choose) {
                case 1: gtk_label_set_text(GTK_LABEL(label), "Password:"); break;
                case 2: gtk_widget_set_tooltip_text(label, "Here you can change your password"); break;
                case 3: gtk_widget_set_tooltip_text(button, "Show password"); break;
                case 4: gtk_button_set_label(GTK_BUTTON(button), "Save"); break;
                case 5: gtk_label_set_text(GTK_LABEL(label), "Please insert a password!"); break;
            }
        break;
    }
}

static void select_language_server_info(int choose, GtkWidget *label, GtkWidget *button) {
    char for_one[100] = "";
    switch (chosen_language) {
        // german
        case 1:
            switch (choose) {
                case 1: strcat(for_one, "IP-Adresse: ");
                        strcat(for_one, server_data[0]); 
                        gtk_label_set_text(GTK_LABEL(label), for_one); break;
                case 2: strcat(for_one, "Hostname: ");
                        strcat(for_one, server_data[1]); 
                        gtk_label_set_text(GTK_LABEL(label), for_one); break;
                case 3: gtk_button_set_label(GTK_BUTTON(button), "Server ändern"); break;
                case 4: gtk_label_set_text(GTK_LABEL(label), "Beim Starten automatisch mit Server verbinden"); break;
                case 5: gtk_widget_set_tooltip_text(label, "Aktiviert"); break;
                case 6: gtk_widget_set_tooltip_text(label, "Deaktiviert"); break;
            }
        break;

        // englisch
        case 2:
            switch (choose) {
                case 1: strcat(for_one, "IP-adress: ");
                        strcat(for_one, server_data[0]); 
                        gtk_label_set_text(GTK_LABEL(label), for_one); break;
                case 2: strcat(for_one, "Hostname: ");
                        strcat(for_one, server_data[1]); 
                        gtk_label_set_text(GTK_LABEL(label), for_one); break;
                case 3: gtk_button_set_label(GTK_BUTTON(button), "Change server"); break;
                case 4: gtk_label_set_text(GTK_LABEL(label), "At start connect automatically to server"); break;
                case 5: gtk_widget_set_tooltip_text(label, "Activated"); break;
                case 6: gtk_widget_set_tooltip_text(label, "Deactivated"); break;
            }
        break;
    }
}

static void select_language_get_garage_settings(int choose, GtkWidget *label, GtkWidget*button) {
    switch (chosen_language) {
        // german
        case 1:
            switch (choose) {
                case 1: gtk_label_set_text(GTK_LABEL(label), "Garagen Hostname:"); break;
                case 2: gtk_label_set_text(GTK_LABEL(label), "Garagen IP-Adresse:"); break;
                case 3: gtk_widget_set_tooltip_text(label, "Garagen Hostname eingeben"); break;
                case 4: gtk_widget_set_tooltip_text(label, "Garagen IP-Adresse eingeben"); break;
                case 5: gtk_button_set_label(GTK_BUTTON(button), "Sichern"); 
                        gtk_widget_set_tooltip_text(button, "Garagen Hostname und IP-Adresse zum Server senden"); break;
                case 6: gtk_label_set_text(GTK_LABEL(label), "Bitte Garagen Hostname eingeben!"); break;
                case 7: gtk_label_set_text(GTK_LABEL(label), "Bitte Garagen IP-Adresse eingeben!"); break;
                case 8: gtk_button_set_label(GTK_BUTTON(button), "IP-Adresse Suchen"); break;

                case 11: gtk_label_set_text(GTK_LABEL(label), "Hostname existiert nicht!"); break;
                case 12: gtk_label_set_text(GTK_LABEL(label), "IP-Adresse gefunden!"); break;
                case 13: gtk_label_set_text(GTK_LABEL(label), "Verbinde mit Server..."); break;
                case 14: gtk_label_set_text(GTK_LABEL(label), "Garage wurde erstellt!"); break;
                case 15: gtk_label_set_text(GTK_LABEL(label), "Garage existiert bereits!"); break;
                case 16: gtk_label_set_text(GTK_LABEL(label), "Ein Fehler ist aufgetreten.\nBitte erneut Versuchen!"); break;
            }
        break;

        // englisch
        case 2:
            switch (choose) {
                case 1: gtk_label_set_text(GTK_LABEL(label), "Garage hostname:"); break;
                case 2: gtk_label_set_text(GTK_LABEL(label), "Garage IP-adress:"); break;
                case 3: gtk_widget_set_tooltip_text(label, "Entry garage hostname"); break;
                case 4: gtk_widget_set_tooltip_text(label, "Entry garagen IP-adress"); break;
                case 5: gtk_button_set_label(GTK_BUTTON(button), "Save");
                        gtk_widget_set_tooltip_text(button, "Send garagen hostname and IP-adress to server"); break;
                case 6: gtk_label_set_text(GTK_LABEL(label), "Please insert garage hostname!"); break;
                case 7: gtk_label_set_text(GTK_LABEL(label), "Please insert garage IP-adress!"); break;
                case 8: gtk_button_set_label(GTK_BUTTON(button), "Search IP-adress"); break;

                case 11: gtk_label_set_text(GTK_LABEL(label), "Hostname does not exists!"); break;
                case 12: gtk_label_set_text(GTK_LABEL(label), "Found IP-adress!"); break;
                case 13: gtk_label_set_text(GTK_LABEL(label), "Connecting with server..."); break;
                case 14: gtk_label_set_text(GTK_LABEL(label), "Garage created!"); break;
                case 15: gtk_label_set_text(GTK_LABEL(label), "Garage exists!"); break;
                case 16: gtk_label_set_text(GTK_LABEL(label), "Error corrupted.\nPlease try again!"); break;
            }
        break;
    }
}

static void select_language_change_server_hostname_ip_add(int choose, GtkWidget *label, GtkWidget *button) {
    switch (chosen_language) {
        // german
        case 1:
            switch (choose) {
                case 1: gtk_label_set_text(GTK_LABEL(label), "Server IP-Adresse:"); break;
                case 2: gtk_widget_set_tooltip_text(label, "Bitte geben Sie eine Server IP-Adresse ein"); break;
                case 3: gtk_label_set_text(GTK_LABEL(label), "Server Hostname:"); break;
                case 4: gtk_widget_set_tooltip_text(label, "Bitte geben Sie einen Server Hostname ein"); break;
                case 5: gtk_button_set_label(GTK_BUTTON(button), "IP-Suchen");
                        gtk_widget_set_tooltip_text(button, "Suchen Sie mit dem Hostname die IP-Adresse"); break;
                case 6: gtk_button_set_label(GTK_BUTTON(button), "Sichern"); break;

                case 9: gtk_label_set_text(GTK_LABEL(label), "IP-Adresse eingeben!"); break;
                case 10: gtk_label_set_text(GTK_LABEL(label), "Hostname eingeben!"); break;
                case 11: gtk_label_set_text(GTK_LABEL(label), "Hostname existiert nicht!"); break;
                case 12: gtk_label_set_text(GTK_LABEL(label), "IP-Adresse gefunden!"); break;
            }
        break;

        // englisch
        case 2:
            switch (choose) {
                case 1: gtk_label_set_text(GTK_LABEL(label), "Server IP-adress:"); break;
                case 2: gtk_widget_set_tooltip_text(label, "Please enter server IP-adress"); break;
                case 3: gtk_label_set_text(GTK_LABEL(label), "Server hostname:"); break;
                case 4: gtk_widget_set_tooltip_text(label, "Please enter server hostname"); break;
                case 5: gtk_button_set_label(GTK_BUTTON(button), "Search-IP");
                        gtk_widget_set_tooltip_text(button, "Search with hostname IP-adress"); break;
                case 6: gtk_button_set_label(GTK_BUTTON(button), "Save"); break;

                case 9: gtk_label_set_text(GTK_LABEL(label), "Enter IP-adresse!"); break;
                case 10: gtk_label_set_text(GTK_LABEL(label), "Enter hostname!"); break;
                case 11: gtk_label_set_text(GTK_LABEL(label), "Hostname does not exists!"); break;
                case 12: gtk_label_set_text(GTK_LABEL(label), "IP-adress found!"); break;
            }
        break;
    }
}