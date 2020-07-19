int select_langauge(int script, GtkWidget *label, GtkWidget *button) {
    #define need_help_german "Wenn Sie Hilfe benötigen, klicken Sie hier"
    #define need_help_english "If you need help, click here"
    switch (user_language) {
        case 1:
            switch (window_number) {    
                // start_screen
                case 1:
                    switch (script) {
                        case 0: gtk_widget_set_tooltip_text(button, need_help_german); break;
                        case 1: gtk_label_set_text(GTK_LABEL(label), "Hallo bei INoTime Garage!\nUm die Installation zu starten bitte auf: 'Installieren =>'\nklicken :)\n"); break;
                        case 2: gtk_button_set_label(GTK_BUTTON(button), "Deutsch"); break;
                        case 3: gtk_button_set_label(GTK_BUTTON(button), "Englisch"); break;
                        case 4: gtk_button_set_label(GTK_BUTTON(button), "Installieren =>"); break;
                    }
                break;
                // insta_config
                case 2:
                    switch (script) {
                        case 0: gtk_widget_set_tooltip_text(button, need_help_german); break;
                        case 1: gtk_label_set_text(GTK_LABEL(label), "Bitte geben Sie Ihren Namen und ein Passwort ein\n(und Passwort erneut eingeben)!"); break;
                        case 2: gtk_label_set_text(GTK_LABEL(label), "Name:"); break;
                        case 3: gtk_widget_set_tooltip_text(label, "Bitte geben Sie Ihren Namen ein");  break;
                        case 4: gtk_label_set_text(GTK_LABEL(label), "Passwort:"); break;
                        case 5: gtk_widget_set_tooltip_text(label, "Bitte geben Sie ein Passwort ein"); break;
                        case 6: gtk_widget_set_tooltip_text(button, "Zeige Passwort"); break;
                        case 7: gtk_label_set_text(GTK_LABEL(label), "Passwort erneut eingeben:"); break;
                        case 8: gtk_widget_set_tooltip_text(label, "Bitte geben Sie Ihr Passwort erneut ein"); break;
                        case 9: gtk_widget_set_tooltip_text(button, "Zeige Passwort"); break;
                        case 10: gtk_button_set_label(GTK_BUTTON(button), "<= Zurück"); break;
                        case 11: gtk_button_set_label(GTK_BUTTON(button), "Weiter =>"); break;
                        
                        case 13: gtk_label_set_text(GTK_LABEL(label), "Name muss eingegeben werden!"); break;
                        case 14: gtk_label_set_text(GTK_LABEL(label), "Passwort muss eingegeben werden!"); break;
                        case 15: gtk_label_set_text(GTK_LABEL(label), "Passwort muss erneut eingegeben werden!"); break;
                        case 16: gtk_label_set_text(GTK_LABEL(label), "Passwörter stimmen nicht überein!"); break;
                    
                        case 20: gtk_button_set_label(GTK_BUTTON(button), "Auto-Passwort"); 
                                 gtk_widget_set_tooltip_text(button, "Hier können Sie ein Passworrt automatisch generieren lassen."); break;
                    }
                break;
                // what_to_install
                case 3:
                    switch (script) {
                        case 0: gtk_widget_set_tooltip_text(button, need_help_german); break;
                        case 1: gtk_label_set_text(GTK_LABEL(label), "Hier können Sie aussuchen welche Programme\ninstalliert werden sollen.\n"); break;
                        case 2: gtk_button_set_label(GTK_BUTTON(button), "Installation von Garagen öffner und Garagenkontrolle."); break;
                        case 3: gtk_button_set_label(GTK_BUTTON(button), "Weiter =>"); break;
                    }
                break;
                // connect_server
                case 4:
                    switch (script) {
                        case 0: gtk_widget_set_tooltip_text(button, need_help_german); break;
                        case 1: gtk_label_set_text(GTK_LABEL(label), "Bitte geben Sie auf dieser Seite\nIhre Server Informationen an."); break;
                        case 2: gtk_label_set_text(GTK_LABEL(label), "Server IP:"); break;
                        case 3: gtk_widget_set_tooltip_text(label, "Bitte geben Sie Ihre Server IP-Adresse ein"); break;
                        case 4: gtk_label_set_text(GTK_LABEL(label), "IP-Adresse gefunden!"); break;
                        case 5: gtk_label_set_text(GTK_LABEL(label), "Server Name:"); break;
                        case 6: gtk_widget_set_tooltip_text(label, "Bitte geben Sie Ihren Server Hostname ein"); break; 
                        case 7: gtk_button_set_label(GTK_BUTTON(button), "Nach IP suchen");
                                gtk_widget_set_tooltip_text(button, "Wenn Sie die Server IP-Adresse nicht wissen können Sie\nauch mit dem Hostname suchen."); break; 
                        case 8: gtk_button_set_label(GTK_BUTTON(button), "Weiter =>"); break;
                        case 9: gtk_label_set_text(GTK_LABEL(label), "Server Hostname muss eingegeben werden!"); break;
                        case 10: gtk_label_set_text(GTK_LABEL(label), "Server IP muss eingegeben werden!"); break;
                        case 11: gtk_label_set_text(GTK_LABEL(label), "Hostname existiert nicht!"); break;
                    }
                break;
                // window_theme_color
                case 5:
                    switch (script) {
                        case 0: gtk_widget_set_tooltip_text(button, need_help_german); break;
                        case 1: gtk_widget_set_tooltip_text(button, "Dark-Theme"); break;
                        case 2: gtk_widget_set_tooltip_text(button, "Light-Theme"); break;
                        case 3: gtk_button_set_label(GTK_BUTTON(button), "Weiter =>"); break;
                    }
                break;
                // final_config
                case 6:
                    switch (script) {
                        case 0: gtk_widget_set_tooltip_text(button, need_help_german); break;
                        case 1: gtk_label_set_text(GTK_LABEL(label), "Sind alle Konfigurationen richtig?"); break;
                        case 2: gtk_label_set_text(GTK_LABEL(label), "Sie haben keinen Account erstellt.\nErstellen Sie jetzt einen Account."); break;
                        case 3: gtk_button_set_label(GTK_BUTTON(button), "Account erstellen"); break;
                        case 4: gtk_button_set_label(GTK_BUTTON(button), "Account erstellen"); break;
                        case 5: gtk_button_set_label(GTK_BUTTON(button), "Ändern"); break;
                        case 6: gtk_button_set_label(GTK_BUTTON(button), "Ändern"); break;
                        case 7: gtk_button_set_label(GTK_BUTTON(button), "<= Zurück"); break;
                        case 8: gtk_button_set_label(GTK_BUTTON(button), "Weiter =>"); break;
                    }
                break;
                // add_garage
                case 7:
                    switch (script) {
                        case 0: gtk_widget_set_tooltip_text(button, need_help_german); break;
                        case 1: gtk_label_set_text(GTK_LABEL(label), "Hier können Sie Garagen hinzufügen\n"); break;
                        case 2: gtk_button_set_label(GTK_BUTTON(button), "Garagen laden");
                                gtk_widget_set_tooltip_text(button, "Lade alle Gargen Info's"); break;
                        case 3: gtk_button_set_label(GTK_BUTTON(button), "Hinzufügen einzelner Garagen");
                                gtk_widget_set_tooltip_text(button, "Fügen Sie Garagen hinzu (vielleicht zwei oder mehr) und sende diese zum Server"); break;
                        case 4: gtk_button_set_label(GTK_BUTTON(button), "Garagen löschen");
                                gtk_widget_set_tooltip_text(button, "Garagen von der Liste löschen"); break;
                        case 5: gtk_button_set_label(GTK_BUTTON(button), "Senden");
                                gtk_widget_set_tooltip_text(button, "Sende alle Garagen zum Server"); break;
                        case 6: gtk_button_set_label(GTK_BUTTON(button), "Weiter =>"); break; 
                    }
                break;
                // exit_config
                case 8: 
                    switch (script) {
                        case 0: gtk_widget_set_tooltip_text(button, need_help_german); break;
                        case 1: gtk_label_set_text(GTK_LABEL(label), "Vielen Dank, für die Installation von INoTime Garage Software.\nFalls Sie in den nächsten Schritte Probleme haben sollten,\nkontaktiern Sie mich bitte:\nino@inotime.com\n\nHaben Sie einen schönen Tag."); break;
                        case 2: gtk_button_set_label(GTK_BUTTON(button), "Programm starten"); break;
                        case 3: gtk_button_set_label(GTK_BUTTON(button), "Beenden"); 
                                gtk_widget_set_tooltip_text(button, "Installation wird beendet"); break;
                    }
                break;
            }
        break;
        case 2:
            switch (window_number) {
                // start_screen
                case 1:
                    switch (script) {
                        case 0: gtk_widget_set_tooltip_text(button, need_help_english); break;
                        case 1: gtk_label_set_text(GTK_LABEL(label), "Hello to INoTime Garage!\nTo install click on the bottom the button: 'Install =>' :)\n"); break;
                        case 2: gtk_button_set_label(GTK_BUTTON(button), "German"); break;
                        case 3: gtk_button_set_label(GTK_BUTTON(button), "English"); break;
                        case 4: gtk_button_set_label(GTK_BUTTON(button), "Install =>"); break;
                    }
                break;
                // insta_config
                case 2:
                    switch (script) {
                        case 0: gtk_widget_set_tooltip_text(button, need_help_english); break;
                        case 1: gtk_label_set_text(GTK_LABEL(label), "Please enter here your name\nand a password (and retipe the password)!"); break;
                        case 2: gtk_label_set_text(GTK_LABEL(label), "Name:"); break;
                        case 3: gtk_widget_set_tooltip_text(label, "Please enter your name");  break;
                        case 4: gtk_label_set_text(GTK_LABEL(label), "Password:"); break;
                        case 5: gtk_widget_set_tooltip_text(label, "Please enter a password"); break;
                        case 6: gtk_widget_set_tooltip_text(button, "Show password"); break;
                        case 7: gtk_label_set_text(GTK_LABEL(label), "Retype Password:"); break;
                        case 8: gtk_widget_set_tooltip_text(label, "Please retype your password"); break;
                        case 9: gtk_widget_set_tooltip_text(button, "Show password"); break;
                        case 10: gtk_button_set_label(GTK_BUTTON(button), "<= Back"); break;
                        case 11: gtk_button_set_label(GTK_BUTTON(button), "Next =>"); break;
                        case 12: gtk_button_set_label(GTK_BUTTON(button), "Next without account =>"); 
                                 gtk_widget_set_tooltip_text(button, "Go next wihout accound.\nNot recommendet"); break;
                        case 13: gtk_label_set_text(GTK_LABEL(label), "Name must filled!"); break;
                        case 14: gtk_label_set_text(GTK_LABEL(label), "Password entry must filled!"); break;
                        case 15: gtk_label_set_text(GTK_LABEL(label), "Re-password must filles!"); break;
                        case 16: gtk_label_set_text(GTK_LABEL(label), "Password is not the same!"); break;

                        case 20: gtk_button_set_label(GTK_BUTTON(button), "Auto-Password"); 
                                 gtk_widget_set_tooltip_text(button, "Here you could generate an auto password."); break;
                    }
                break;
                // what_to_install
                case 3:
                    switch (script) {
                        case 0: gtk_widget_set_tooltip_text(button, need_help_english); break;
                        case 1: gtk_label_set_text(GTK_LABEL(label), "Here you can choose programs to install.\n"); break;
                        case 2: gtk_button_set_label(GTK_BUTTON(button), "Install garage opener and garage check."); break;
                        case 3: gtk_button_set_label(GTK_BUTTON(button), "Next =>"); break;
                    }
                break;
                // connect_server
                case 4:
                    switch (script) {
                        case 0: gtk_widget_set_tooltip_text(button, need_help_english); break;
                        case 1: gtk_label_set_text(GTK_LABEL(label), "Please enter on this side\nthe informations from your server!"); break;
                        case 2: gtk_label_set_text(GTK_LABEL(label), "Server IP:"); break;
                        case 3: gtk_widget_set_tooltip_text(label, "Please enter server ip"); break;
                        case 4: gtk_label_set_text(GTK_LABEL(label), "IP found!"); break;
                        case 5: gtk_label_set_text(GTK_LABEL(label), "Server name:"); break;
                        case 6: gtk_widget_set_tooltip_text(label, "Please enter server hostname"); break; 
                        case 7: gtk_button_set_label(GTK_BUTTON(button), "Search for ip");
                                gtk_widget_set_tooltip_text(button, "If you don't know your server ip you are able to search with the hostname"); break; 
                        case 8: gtk_button_set_label(GTK_BUTTON(button), "Next =>"); break;
                        case 9: gtk_label_set_text(GTK_LABEL(label), "Hostname must entred!"); break;
                        case 10: gtk_label_set_text(GTK_LABEL(label), "Server ip must entred!"); break;
                        case 11: gtk_label_set_text(GTK_LABEL(label), "Hostname does not exists!"); break;
                    }
                break;
                // window_theme_color
                case 5:
                    switch (script) {
                        case 0: gtk_widget_set_tooltip_text(button, need_help_english); break;
                        case 1: gtk_widget_set_tooltip_text(button, "Dark-theme"); break;
                        case 2: gtk_widget_set_tooltip_text(button, "Light-theme"); break;
                        case 3: gtk_button_set_label(GTK_BUTTON(button), "Next =>"); break;
                    }
                break;
                // final_config
                case 6:
                    switch (script) {
                        case 0: gtk_widget_set_tooltip_text(button, need_help_english); break;
                        case 1: gtk_label_set_text(GTK_LABEL(label), "Are all configurations right?"); break;
                        case 2: gtk_label_set_text(GTK_LABEL(label), "You don't have created an account.\nCreate accound yet."); break;
                        case 3: gtk_button_set_label(GTK_BUTTON(button), "Create account"); break;
                        case 4: gtk_button_set_label(GTK_BUTTON(button), "Create account"); break;
                        case 5: gtk_button_set_label(GTK_BUTTON(button), "Change"); break;
                        case 6: gtk_button_set_label(GTK_BUTTON(button), "Change"); break;
                        case 7: gtk_button_set_label(GTK_BUTTON(button), "<= Back"); break;
                        case 8: gtk_button_set_label(GTK_BUTTON(button), "Next =>"); break;
                    }
                break;
                // add_garage
                case 7:
                    switch (script) {
                        case 0: gtk_widget_set_tooltip_text(button, need_help_english); break;
                        case 1: gtk_label_set_text(GTK_LABEL(label), "Here you can add new garages\n"); break;
                        case 2: gtk_button_set_label(GTK_BUTTON(button), "Load garages");
                                gtk_widget_set_tooltip_text(button, "Load all garage infos from server"); break;
                        case 3: gtk_button_set_label(GTK_BUTTON(button), "Add garage seperatly");
                                gtk_widget_set_tooltip_text(button, "Enter firstly garage infos (maybe two or more) and send them to server"); break;
                        case 4: gtk_button_set_label(GTK_BUTTON(button), "Remove garage");
                                gtk_widget_set_tooltip_text(button, "Remove garges from list to send"); break;
                        case 5: gtk_button_set_label(GTK_BUTTON(button), "Send");
                                gtk_widget_set_tooltip_text(button, "Send all new garages to server"); break;
                        case 6: gtk_button_set_label(GTK_BUTTON(button), "Next =>"); break; 
                    }
                break;
                // exit_config
                case 8: 
                    switch (script) {
                        case 0: gtk_widget_set_tooltip_text(button, need_help_english); break;
                        case 1: gtk_label_set_text(GTK_LABEL(label), "Thank you for the installation of INoTime Garage Software.\nIf you have problems in few steps please contact me.\nino@inotime.com\n\nHave a nice day."); break;
                        case 2: gtk_button_set_label(GTK_BUTTON(button), "Start program"); break;
                        case 3: gtk_button_set_label(GTK_BUTTON(button), "Finish"); 
                                gtk_widget_set_tooltip_text(button, "Installation will be quitted"); break;
                    }
                break;
        }
    }
}

void select_language_help_window(GtkWidget *button) {
    switch (user_language) {
        case 1:
            gtk_button_set_label(GTK_BUTTON(button), "Zurück zur Konfiguration");
            switch(window_number) {
                case 1: help_text = "Hier können Sie die Installation starten\nund Ihre Sprache wählen.\nDannach müssen Sie nurnoch auf\n\"Installieren =>\" klicken\n"; break;
                case 2: help_text = "Hier müssen Sie Ihren Namen eintragen\nund ein Password wählen,\nwelches Sie dann bestätigen müssen.\nNach der Installation müssen Sie die Daten\neingeben um sich einzuloggen.\nOder Sie müssen keinen Account anlegen\n(nicht wünschenswert).\nKlicken Sie dazu auf \"Weiter ohne account\"\n"; break;
                case 3: help_text = "Hier müssen Sie Programme aussuchen,\ndie Sie installieren möchten.\n"; break;
                case 4: help_text = "Hier müssen Sie die Server IP-Adresse\noder/und den Hostnamen vom Server.\nWenn Sie den Hostnamen eingeben,\nkann nach der IP-Adresse gesucht werden.\n\nStellen Sie sicher, dass der Server online ist.\n"; break;
                case 5: help_text = "Hier können Sie ein Theme auswählen.\nSie können dieses später in den\nEinstellungen wieder ändern.\n"; break;
                case 6: help_text = "Überprüfen Sie ob alle Eingaben korrekt\nsind. Falls nicht können Sie den\nBenutzernamen sowie das Passwort ändern.\nDie UUID ist eine automatisch generierte\nID für Ihren Computer.\n"; break;
                case 7: help_text = "Hier können Sie Garagen konfigurieren\n(max. Garagen 255). Geben Sie dazu die Ip-Adresse\nund den Hostnamen der Garage ein.\n"; break;
                case 8: help_text = "Wenn Sie einen Haaken in die Box setzen,\nwird nach der Installation,\ndas Programm automatisch gestartet.\n"; break;
                case 101: help_text = "Dieses Fenster ist zur Eingabe von super user Daten\n(Server super user Passwort)\nWenn sie einen Haaken in die Box setzen,\nwerden die super user Daten während\nder Installation gespeichert.\n Sie werden dann nicht noch einmal dazu\naufgefordert, diese erneut einzugeben.\n"; break;
            }
        break;

        case 2:
        gtk_button_set_label(GTK_BUTTON(button), "Back to Config");
            switch(window_number) {
                case 1: help_text = "Here you can start the installation.\nAnd choose your language.\nThen you only have to click \"Install =>\"\n"; break;
                case 2: help_text = "Here you must enter your name, an\npassword and retype your password\nThis would be later important after\ninstallation to log in!\n\nOtherwise you don't must create an\naccount. Click then \"Next without\naccount\"\n"; break;
                case 3: help_text = "Hery you have to choose programs\nwhich to install.\n"; break;
                case 4: help_text = "Here you must enter the server IP\naddress or the hostname from server.\nIf you enter the hostname to\nsearch for ip.\n\nMake sure your server is online!\n"; break;
                case 5: help_text = "Here you can choose a color theme\nYou could change it later in Settings\nagain!\n"; break;
                case 6: help_text = "Check if all entries are correct.\nIf not you can change user name or/and\npassword.\nUUID is the auto generated\nID from your PC\n"; break;
                case 7: help_text = "Here you can configuarte garages\n(max. garages 255). Enter IP and a garage\n name.\n"; break;
                case 8: help_text = "If you check the box program will\nstart auto.\n"; break;
                case 101: help_text = "This window is to enter super user\ndata (server super user password).\nIf you check the checkbox while the\ninstalltion won't ask\nyou again for super user data!\n"; break;
            }
        break;
    }
}

void select_language_cancle_config(int choose, GtkWidget *label, GtkWidget *button) {
    switch (user_language) {
        case 1:
            switch (choose) {
                case 1: gtk_label_set_text(GTK_LABEL(label), "Möchten Sie wirklich\ndie Konfiguration abbrechen?"); break;
                case 2: gtk_button_set_label(GTK_BUTTON(button), "Ja"); break;
                case 3: gtk_button_set_label(GTK_BUTTON(button), "Abbrechen"); break;
            }
        break;
    
        case 2:
            switch (choose) {
                case 1: gtk_label_set_text(GTK_LABEL(label), "Would you really \ncancle the configuration?"); break;
                case 2: gtk_button_set_label(GTK_BUTTON(button), "Yes"); break;
                case 3: gtk_button_set_label(GTK_BUTTON(button), "Cancle"); break;
            }
        break;
    }
}

void select_language_super_user_acess(int choose, GtkWidget *label, GtkWidget *button) {
    switch (user_language) {
        case 1:
            switch (choose) {
                case 0: gtk_widget_set_tooltip_text(button, need_help_german); break;
                case 1: gtk_label_set_text(GTK_LABEL(label), "Super Username:"); break;
                case 2: gtk_widget_set_tooltip_text(label, "Eingabe super Username"); break;
                case 3: gtk_label_set_text(GTK_LABEL(label), "Passwort:"); break; 
                case 4: gtk_widget_set_tooltip_text(label, "Eingabe super user Passwort"); break;
                case 5: gtk_button_set_label(GTK_BUTTON(button), "Super User Daten Sichern (nur für Installation)");
                        gtk_widget_set_tooltip_text(button, "Super User Login Daten werden für die Installation gespeichert\nandernfalls werden Sie noch einmal zur Eingabe der Daten aufgefordert."); break;
                case 6: gtk_button_set_label(GTK_BUTTON(button), "Zugriff"); break;
                case 7: gtk_label_set_text(GTK_LABEL(label), "Bitte geben Sie den Super Usernamen ein!"); break;
                case 8: gtk_label_set_text(GTK_LABEL(label), "Bitte geben Sie das Super User Passwort ein!"); break;
                case 9: gtk_label_set_text(GTK_LABEL(label), "Zugriff verweigert!\nSie wurden blockiert! Endblockieren auf dem Server!"); break;
                case 10: strcat(rest_tries_super_user, "Verbindung Fehlgeschlagen...\nSie haben noch: "); break;
                case 11: strcat(rest_tries_super_user, " Versuch"); break;
                case 12: strcat(rest_tries_super_user, " Versuche"); break;
                case 13: strcat(ip_is_blocked_label, "Sorry Ihre IP istblockiert...\nKontaktieren Sie Ihren Admin!\nProgramm wird beendet in: "); break;
                case 14: gtk_label_set_text(GTK_LABEL(label), "Error beim erneuten Verbinden mit super user Rechten..!\nRestart installation!"); break;
                case 15: gtk_label_set_text(GTK_LABEL(label), "Fehler erneut versuchen!"); break;
            }
        break;
    
        case 2:
            switch (choose) {
                case 0: gtk_widget_set_tooltip_text(button, need_help_english); break;
                case 1: gtk_label_set_text(GTK_LABEL(label), "Super username:"); break;
                case 2: gtk_widget_set_tooltip_text(label, "Enter super username"); break;
                case 3: gtk_label_set_text(GTK_LABEL(label), "Password:"); break; 
                case 4: gtk_widget_set_tooltip_text(label, "Enter super user password"); break;
                case 5: gtk_button_set_label(GTK_BUTTON(button), "Save super user data (only for installation)");
                        gtk_widget_set_tooltip_text(button, "Super user login data would be saved during the installation\nelse you maybe retype it during the installation."); break;
                case 6: gtk_button_set_label(GTK_BUTTON(button), "Get Acess"); break;
                case 7: gtk_label_set_text(GTK_LABEL(label), "Please enter super user name!"); break;
                case 8: gtk_label_set_text(GTK_LABEL(label), "Please enter super user password!"); break;
                case 9: gtk_label_set_text(GTK_LABEL(label), "Access denided!\nYou are blocked! Endblock on server!"); break;
                case 10: strcat(rest_tries_super_user, "Connection Failed...\nYou have only: "); break;
                case 11: strcat(rest_tries_super_user, " try"); break;
                case 12: strcat(rest_tries_super_user, " tries"); break;
                case 13: strcat(ip_is_blocked_label, "Sorry your ip is blocked...\nContact your admin!\nProgram is shutting down in: "); break;
                case 14: gtk_label_set_text(GTK_LABEL(label), "Error by connecting again with super user rights..!\nRestart installation!"); break;
                case 15: gtk_label_set_text(GTK_LABEL(label), "Fail try again!"); break;
            }
        break;
    }
}

void select_language_install_failed_by_check(int choose, GtkWidget *label, GtkWidget *button) {
    switch (user_language) {
        case 1:
            switch (choose) {
                case 1: gtk_label_set_text(GTK_LABEL(label), "Sie haben nichts angeklickt..!\n"); break;
                case 2: gtk_button_set_label(GTK_BUTTON(button), "Ok"); break;
            }
        break;
    
        case 2:
            switch (choose) {
                case 1: gtk_label_set_text(GTK_LABEL(label), "You don't have clicked anything..!\n"); break;
                case 2: gtk_button_set_label(GTK_BUTTON(button), "Ok"); break;
            }
        break;
    }
}

void select_language_check_uuid_is_here(int choose, GtkWidget *label) {
    switch (user_language) {
        case 1:
            switch (choose) {
                case 1: gtk_label_set_text(GTK_LABEL(label), "Programm prüft die Eingaben und die Verbindung..."); break;
                case 2: gtk_label_set_text(GTK_LABEL(label), "Stellen Sie sicher, dass Ihr serveronline ist.\nKann keine Verbindung zu Server aufbauen um System\nEinstellungen zu laden!"); break;            
            }
        break;
    
        case 2:
            switch (choose) {
                case 1: gtk_label_set_text(GTK_LABEL(label), "Program is checking entrys and connections..."); break;
                case 2:  gtk_label_set_text(GTK_LABEL(label), "Make sure that your server is online.\nCan not connect and get system settings!"); break;
            }
        break;
    }
}

void select_language_create_acc_yet(int choose, GtkWidget *label, GtkWidget *button) {
    switch (user_language) {
        case 1:
            switch (choose) {
                case 1: gtk_label_set_text(GTK_LABEL(label), "Name:"); break;
                case 2: gtk_label_set_text(GTK_LABEL(label), "Passwort:"); break;
                case 3: gtk_label_set_text(GTK_LABEL(label), "Re-Passwort:"); break;
                case 4: gtk_button_set_label(GTK_BUTTON(button), "Sichern"); break;
                case 5: gtk_label_set_text(GTK_LABEL(label), "Bitte Namen eingeben!"); break;
                case 6: gtk_label_set_text(GTK_LABEL(label), "Bitte Passwort eingeben!"); break;
                case 7: gtk_label_set_text(GTK_LABEL(label), "Bitte Passwort erneut eingeben!"); break;
                case 8: gtk_label_set_text(GTK_LABEL(label), "Passwörter stimmen nicht überein!"); break; 
            }
        break;
    
        case 2:
            switch (choose) {
                case 1: gtk_label_set_text(GTK_LABEL(label), "Name:"); break;
                case 2: gtk_label_set_text(GTK_LABEL(label), "Password:"); break;
                case 3: gtk_label_set_text(GTK_LABEL(label), "Re-Password:"); break;
                case 4: gtk_button_set_label(GTK_BUTTON(button), "Save"); break;
                case 5: gtk_label_set_text(GTK_LABEL(label), "Please enter a name!"); break;
                case 6: gtk_label_set_text(GTK_LABEL(label), "Please enter a password!"); break;
                case 7: gtk_label_set_text(GTK_LABEL(label), "Please retype your password!"); break;
                case 8: gtk_label_set_text(GTK_LABEL(label), "Password's are not the same!"); break; 
            }
        break;
    }
}

void select_language_add_garage_entry(int choose, GtkWidget *label, GtkWidget *button) {
    #define ip_found_german "IP gefunden!"
    #define ip_found_english "IP found!"
    #define ip_not_found_german "Hostname existiert leider nicht!"
    #define ip_not_found_english "Hostname does not exists!"
    switch (user_language) {
        case 1:
            switch (choose) {
                case 1: gtk_label_set_text(GTK_LABEL(label), "Garagen IP:"); break;
                case 2: gtk_label_set_text(GTK_LABEL(label), "Garagen Name:"); break;
                case 3: gtk_button_set_label(GTK_BUTTON(button), "Suchen nach IP"); break;
                case 4: gtk_button_set_label(GTK_BUTTON(button), "Sichern"); break;
                case 5: gtk_label_set_text(GTK_LABEL(label), "Bitte geben Sie den Namen ein!"); break;
                case 6: gtk_label_set_text(GTK_LABEL(label), "Bitte geben Sie die IP-Adresse ein!"); break;
                case 7: gtk_label_set_text(GTK_LABEL(ip_garage_found), ip_found_german); break;
                case 8: gtk_label_set_text(GTK_LABEL(label), ip_not_found_german); break;
            }
        break;
    
        case 2:
            switch (choose) {
                case 1: gtk_label_set_text(GTK_LABEL(label), "Garage IP:"); break;
                case 2: gtk_label_set_text(GTK_LABEL(label), "Garage name:"); break;
                case 3: gtk_button_set_label(GTK_BUTTON(button), "Search for IP"); break;
                case 4: gtk_button_set_label(GTK_BUTTON(button), "Save"); break;
                case 5: gtk_label_set_text(GTK_LABEL(label), "Please insert the name!"); break;
                case 6: gtk_label_set_text(GTK_LABEL(label), "Please insert the IP address!"); break;
                case 7: gtk_label_set_text(GTK_LABEL(label), ip_found_english); break;
                case 8: gtk_label_set_text(GTK_LABEL(label), ip_not_found_english); break;
            }
        break;
    } 
}

void select_language_sorry_name_ip_garage_is_given(int choose, GtkWidget *label, GtkWidget *button, char *save_for_one_name_ip_garage) {
    switch (user_language) {
        case 1:
            switch (choose) {
                case 1: gtk_button_set_label(GTK_BUTTON(button), "Ok"); break;
                case 2: strcpy(name_ip_garage_is_given, "Sorry IP-Adresse und Garagen Name sind schon\nvergeben:\n");
                        strcat(name_ip_garage_is_given, save_for_one_name_ip_garage); 
                        gtk_label_set_text(GTK_LABEL(label), name_ip_garage_is_given); break;
            }
        break;
    
        case 2:
            switch (choose) {
                case 1: gtk_button_set_label(GTK_BUTTON(button), "Ok"); break;
                case 2: strcpy(name_ip_garage_is_given, "Sorry ip and garage name were already given:\n");
                        strcat(name_ip_garage_is_given, save_for_one_name_ip_garage); 
                        gtk_label_set_text(GTK_LABEL(label), name_ip_garage_is_given); break;
            }
        break;
    } 
}

void select_language_remove_garage(int choose, GtkWidget *label, GtkWidget *button) {
    switch (user_language) {
        case 1:
            switch (choose) {
                case 1: gtk_label_set_text(GTK_LABEL(label), "Garage Name:"); break;
                case 2: gtk_button_set_label(GTK_BUTTON(button), "Garage löschen"); break;
                case 3: gtk_label_set_text(GTK_LABEL(label), "Bitte geben Sie den Garagen Hostname ein"); break;
            }
        break;
    
        case 2:
            switch (choose) {
                case 1: gtk_label_set_text(GTK_LABEL(label), "Garage name:"); break;
                case 2: gtk_button_set_label(GTK_BUTTON(button), "Remove garage"); break;
                case 3: gtk_label_set_text(GTK_LABEL(label), "Please enter the garage host name"); break;
            }
        break;
    } 
}

void select_language_go_next_will_close_conn(int choose, GtkWidget *label, GtkWidget *button) {
    switch (user_language) {
        case 1:
            switch (choose) {
                case 1: gtk_label_set_text(GTK_LABEL(label), "Wenn Sie auf \"Ja\" klicken\ntrennen Sie die Verbindung\nzum Server.\nSie können nicht zurück gehen!\nWenn Sie auf\"Abbrechen\" klicken, können\nSie noch mehr Garagen hinzufügen."); break;
                case 2: gtk_button_set_label(GTK_BUTTON(button), "Ja"); break;
                case 3: gtk_button_set_label(GTK_BUTTON(button), "Abbrechen"); break;
            }
        break;
    
        case 2:
            switch (choose) {
                case 1: gtk_label_set_text(GTK_LABEL(label), "If you click \"Yes\" you will\nclose connection to server.\nYou can't go back!\nIf you press \"Cancle\" you\ncould add more new garages."); break;
                case 2: gtk_button_set_label(GTK_BUTTON(button), "Yes"); break;
                case 3: gtk_button_set_label(GTK_BUTTON(button), "Cancle"); break;
            }
        break;
    } 
}

void select_language_change_password_final(int choose, GtkWidget *label, GtkWidget *button) {
    switch (user_language) {
        case 1:
            switch (choose) {
                case 1: gtk_label_set_text(GTK_LABEL(label), "Passwort"); break;
                case 2: gtk_label_set_text(GTK_LABEL(label), "Re-Passwort"); break;
                case 3: gtk_button_set_label(GTK_BUTTON(button), "Sichern"); break;
                case 4: gtk_label_set_text(GTK_LABEL(label), "Passwort muss erneut eingegben werden!"); break;
                case 5: gtk_label_set_text(GTK_LABEL(label), "Re-Passwort muss eingegeben werden!"); break;
                case 6: gtk_label_set_text(GTK_LABEL(label), "Passwörter stimmen nicht überein!"); break;
            }
        break;
    
        case 2:
            switch (choose) {
                case 1: gtk_label_set_text(GTK_LABEL(label), "Password"); break;
                case 2: gtk_label_set_text(GTK_LABEL(label), "Re-Password"); break;
                case 3: gtk_button_set_label(GTK_BUTTON(button), "Save"); break;
                case 4: gtk_label_set_text(GTK_LABEL(label), "password must typed in"); break;
                case 5: gtk_label_set_text(GTK_LABEL(label), "re-password must typed in"); break;
                case 6: gtk_label_set_text(GTK_LABEL(label), "password's are not same"); break;
            }
        break;
    } 
}

void select_language_change_user_name_final(int choose, GtkWidget *label, GtkWidget *button) {
    switch (user_language) {
        case 1:
            switch (choose) {
                case 1: gtk_label_set_text(GTK_LABEL(label), "User Name:"); break;
                case 2: gtk_button_set_label(GTK_BUTTON(button), "Sichern"); break;
            }
        break;
    
        case 2:
            switch (choose) {
                case 1: gtk_label_set_text(GTK_LABEL(label), "User name:"); break;
                case 2: gtk_button_set_label(GTK_BUTTON(button), "Save"); break;
            }
        break;
    } 
}

void select_language_change_sys_info(int choose) {
    #define U_NAME_german "Ihr Name: "
    #define U_PASS_german "Ihr Passwort: "
    #define S_NAME_german "Server Name: "
    #define S_IP_german "Server IP Adresse: "
    #define U_UUID_german "Ihre UUID: "
    #define U_NAME_english "Your name: "
    #define U_PASS_english "Your password: "
    #define S_NAME_english "Server name: "
    #define S_IP_english "Server IP adress: "
    #define U_UUID_english "Your UUID: "

    switch (user_language) {
        case 1:
            switch (choose) {
                case 0: strcpy(name_b, U_NAME_german); 
                    strcpy(password_b, U_PASS_german); 
                    strcpy(server_name_b, S_NAME_german);
                    strcpy(server_ip_b, S_IP_german); 
                    strcpy(uuid_b, U_UUID_german); 
                    strcpy(ch_user_name_re, U_NAME_german); 
                    strcpy(ch_user_password_re, U_PASS_german);
                break; 
                case 1: strcpy(name_b_save, U_NAME_german); break;
                case 2: strcpy(password_b_save, U_PASS_german); break;
                case 3: strcpy(server_name_b_save, S_NAME_german); break;
                case 4: strcpy(server_ip_b_save, S_IP_german); break;
                case 5: strcpy(uuid_b_save, U_UUID_german); break;
                case 6: strcpy(ch_user_name_re_save, U_NAME_german); break;
                case 7: strcpy(ch_user_password_re_save, U_PASS_german); break;
            }
        break;

        case 2:
            switch (choose) {
                case 0: strcpy(name_b, U_NAME_english); 
                    strcpy(password_b, U_PASS_english); 
                    strcpy(server_name_b, S_NAME_english);
                    strcpy(server_ip_b, S_IP_english); 
                    strcpy(uuid_b, U_UUID_english); 
                    strcpy(ch_user_name_re, U_NAME_english); 
                    strcpy(ch_user_password_re, U_PASS_english);
                break; 
                case 1: strcpy(name_b_save, U_NAME_english); break;
                case 2: strcpy(password_b_save, U_PASS_english); break;
                case 3: strcpy(server_name_b_save, S_NAME_english); break;
                case 4: strcpy(server_ip_b_save, S_IP_english); break;
                case 5: strcpy(uuid_b_save, U_UUID_english); break;
                case 6: strcpy(ch_user_name_re_save, U_NAME_english); break;
                case 7: strcpy(ch_user_password_re_save, U_PASS_english); break;
            }
        break;
    }
}