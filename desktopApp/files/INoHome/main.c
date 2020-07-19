// ############################################################################
// ########################## INo Investigation Time ##########################
// ############################### main.c ###############################
// ############################################################################

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <gtk/gtk.h>
#include <pthread.h>

#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>

#ifdef _WIN32
    #include <winsock2.h> 
    #include <windows.h>
    #include <ws2tcpip.h>
#endif

#ifdef __unix__
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <netdb.h>
    #include <arpa/inet.h>
#endif

#define MAIN_IMAGE_NAME "images/inoinvestigation.jpg"
#define dark_theme_style "style/dark_theme.css"
#define light_theme_style "style/light_theme.css"

// crypt files
#define crypt_user_info_file "crypt/user_info_data"
#define crypt_check_my_style_file "crypt/check_my_style_data"
#define crypt_commands_file "crypt/commands_data"
#define crypt_ip_addr_garage_file "crypt/ip_addr_garage_data"
#define crypt_serverIP_add_file "crypt/serverIP_add_data"
#define crypt_user_id_file "crypt/user_id_data"

#define check_my_style_file "tmp/check_my_style"
#define commands_file "tmp/commands"
#define ip_addr_garage_file "tmp/ip_addr_garage"
#define serverIP_add_file "tmp/serverIP_add"
#define user_id_file "tmp/user_id"
#define user_info_file "tmp/user_info" 
#define menubar_en "language/menubar_en.ui"
#define menubar_de "language/menubar_de.ui"
#define pwd_data 25

#define smile_face_passwd ":)"
#define bad_face_passwd ":("

typedef struct {
    GtkWidget *window;
    GtkWidget *label;
    GtkWidget *button;
    guint p_id_start;
    guint p_id_main_conn;
    guint p_id_main_conn_o_f;
    guint p_id_time;
}WorkerData;

GtkWidget *grid;
GtkWidget *get_acess_window, *get_acess_grid;
GtkWidget *login_user_image, *login_password_entry, *login_show_password_bt, *login_error_label; 

GtkWidget *server_status_label;
GtkWidget *connecting_to_server_window, *connecting_to_server_grid, *connecting_to_server_error, *connecting_to_server_progress_bar;
GtkWidget *client_settings_window, *client_settings_grid, *user_name_label, *user_password_label, *user_password_show_bt, *user_password_change_bt, *ip_label, *hostanme_label, *uuid_label, *user_name_change_bt;
GtkWidget *change_user_name_window, *change_user_name_grid, *change_user_name_label, *change_user_name_error_label, *change_user_name_entry, *change_user_name_save_bt;
GtkWidget *change_password_window, *change_password_grid, *change_password_label, *change_password_error_label, *change_password_entry, *change_password_show_bt, *change_password_save_bt;
GtkWidget *server_info_window, *server_info_grid, *server_info_ip_add, *server_info_hostname, *server_info_hostname_ip_add_change_bt, *auto_connect_server_label, *auto_connect_server_switch;
GtkWidget *garage_settings_window, *garage_settings_grid, *garage_name_label, *garage_ip_label, *entry_garage_name, *entry_garage_ip, *search_ip_with_hostname_bt, *garage_settings_save_bt, *error_garage_settings_label;
GtkWidget *change_server_hostname_ip_add_window, *change_server_hostname_ip_add_grid, *change_ip_add_label, *change_ip_add_entry, *change_hostname_label, *change_hostname_entry, *check_ip_hostname_bt, *save_ip_hostname_bt, *change_ip_hostname_error_label;
GtkWidget *scrolled_window, *image[255], *theme_box_image[255], *garage_name_ip_label[255], *image_offline[255], *theme_box_image_offline[255], *theme_box_image_offline[255];
GtkApplication *programApp;
const gchar *my_window_css = "my_window";
GdkScreen *my_screen;
GtkCssProvider *cssProvider;
GdkDisplay *display;
GError *error = 0;
WorkerData *wdP;

char commands[255][39] = { 0 }, all_garages_buffer[9064] = "", server_data_a[3][9690] = { 0 }, server_data[3][40] = { 0 }, user_uuid_a[9690] = "", user_uuid[38] = "";
char my_style_final_a[9060] = "", my_style_final[20] = "";
char buf_commands[9690] = "";
char pwd_aa[2][9690] = { 0 }, pwd_a[2][pwd_data] = { 0 };
char all_garages[255][90] = { 0 };
char buffer_blocked_ip[5] = "", buffer_all_garage_ips[9690] = "", buffer_check_garages[38] = "";

int style_mode = 0, window_number = 0, chosen_language = 2, cout_commands = 0, cout_all_garages = 0, show_password_login_cout = 0, loged_in = 0, password_show_cout = 0, change_user_password_show_passw_cout = 0;
int ip_add_is_blocked = 1, connecting_to_server_window_check = 0, connection_server_is_true = 0, is_on_first_window = 0;;
// need my_garages_line so that user could change cound of lines on start screen
int my_garages_line = 2, cout_all_garages_out = 2, disconnected_from_server_bt = 1;
int already_loaded = 0;
const gchar *gchar_ip_garage, *gchar_hostname_garage;

// if user end the app manually
void system_end_program() {
    gtk_main_quit();
    exit(0);
}

// theme style for window
void my_style() {
    if (style_mode == 1) {
        gtk_css_provider_load_from_file(cssProvider, g_file_new_for_path(dark_theme_style), &error);
    }else {
        gtk_css_provider_load_from_file(cssProvider, g_file_new_for_path(light_theme_style), &error);
    }
}

static void main_connection_handler();
static void main_screen();
static void load_garages();
static void connecting_to_server();
void main_connection_new_garage_handler();
void main_connection_garage_settings_handler();
void main_connection_send_garage_handler();
static gboolean progress_bar_fill(gpointer data);
static void check_server_state();
static void get_garage_settings();
void main_connection_server_state_handler();
char *crypt_data(char *string_a, char *string_b, char *file_location);
char *decrypt_data(char *string_a, char *file_location);
void read_all_garage_ips();

#include "language/language.h"

#include "mainConnection.h"
#include "threads.h"

#include "destroy_window.h"
#include "login_window.h"
#include "my_window.h"
#include "menu_bar_settings.h"
#include "crypt.h"

// this is the absolute start to configure window
static void absolute_start() {
    wdP = g_malloc(sizeof *wdP);

    cssProvider = gtk_css_provider_new();
    gtk_css_provider_load_from_path(cssProvider, light_theme_style, NULL);
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(cssProvider), GTK_STYLE_PROVIDER_PRIORITY_USER);

    // settings for start_screen (in main window)
    wdP->window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(wdP->window), 800, 400);
    gtk_window_set_position(GTK_WINDOW(wdP->window), GTK_WIN_POS_CENTER);

    // must changed if new window exists                                                                                    !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    gtk_window_set_resizable(GTK_WINDOW(wdP->window), FALSE);
    gtk_widget_set_name(wdP->window, my_window_css);

    start_program_get_infos();

    // check which window would be reopened
    switch(window_number) {
        case 0: main_screen(); break;
    }
} 

int main(int argc, char *argv[]) {
    // open programm app
    int statusApp;

    programApp = gtk_application_new("org.gtk.inoinvestigationSystem", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(programApp, "activate", G_CALLBACK(absolute_start), NULL);
    g_signal_connect(programApp, "startup", G_CALLBACK(menu_bar), NULL);

    statusApp = g_application_run(G_APPLICATION(programApp), argc, argv);
    g_object_unref(programApp);
    // ----------------------------------------------

    return statusApp;
}