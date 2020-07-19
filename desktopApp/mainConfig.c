// ############################################################################
// ########################## INo Investigation Time ##########################
// ############################### mainConfig.c ###############################
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
#include <sys/stat.h>
#include <sys/types.h>

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


#include "files/errorFileServ.h"

typedef struct {
    GtkWidget *window;
    guint p_id_start;
    guint p_id_main_conn;
    guint p_id_main_conn_o_f;
    guint p_id_time;
}WorkerData;

typedef struct {
    int user_id_saved;
}user_id;

// style theme files 
#define check_my_style_f "files/tmp/check_my_style"
#define dark_theme_style "files/style/dark_theme_style.css"
#define not_dark_theme_style "files/style/not_dark_theme_style.css"
#define user_info_file "files/tmp/user_info"
#define server_info_file "files/tmp/serverIP_add"
#define user_id_file "files/tmp/user_id"
#define MAIN_IMAGE_NAME "inoinvestigation.jpg"
// crypt files
#define crypt_user_info_file "files/crypt/user_info_data"
#define crypt_check_my_style_file "files/crypt/check_my_style_data"
#define crypt_commands_file "files/crypt/commands_data"
#define crypt_ip_addr_garage_file "files/crypt/ip_addr_garage_data"
#define crypt_serverIP_add_file "files/crypt/serverIP_add_data"
#define crypt_user_id_file "files/crypt/user_id_data"

#define ipv4_len 16
#define exp_ip_add "127.0.0.1"

GtkWidget *grid;
GtkWidget *german_language_bt, *english_language_bt;
GtkWidget *super_user_access_window, *entry_super_user_name, *entry_super_user_password, *bt_show_passwd_super_user, *check_box_save_super_user_data, *super_user_save_bt, *error_user_save_label;
GtkWidget *hello_label, *install_bt, *start_screen_help_bt_label;
GtkWidget *help_garage_control, *garage_control, *garage_opener, *program_install_next;
GtkWidget *config_label, *name_label, *name_entry, *password_label, *password_entry, *re_password_label, *re_password_entry, *go_back_one_bt, *save_info_bt, *error_insta_config_label;
GtkWidget *server_search_hostname_bt, *connect_server_add_label, *server_name_label, *server_name_entry, *server_add_label, *server_add_entry, *save_info_add_bt, *error_connect_server, *change_user_name_bt, *cahnge_password_bt, *server_ip_found_label;
GtkWidget *password_show_one, *password_show_two, *dont_create_acc, *create_random_password;
GtkWidget *all_right_final_label, *user_name_c_label, *user_password_c_label, *server_name_c_label, *server_ip_c_label, *user_uuid_c_label, *final_config_back_bt, *final_config_next_bt;
GtkWidget *loading_label_server, *label_dn, *dark_theme_on_image, *dark_theme_off_image, *off_theme_box, *on_theme_box, *theme_color_next_bt;
GtkWidget *add_garage_label, *add_garage_bt, *add_garage_next_bt, *new_garages_label, *save_all_new_garages_bt, *remove_garage_bt;
GtkWidget *remove_garage_window, *remove_garage_name_entry, *remove_garage_name_retry_label;
GtkWidget *ip_garage_found,*entry_name_garage, *entry_ip_garage, *check_garage_info_label, *load_from_server_bt;
GtkWidget *go_next_will_close_conn_window;
GtkWidget *exit_config_label, *start_checkbutton;
GtkWidget *sorry_name_ip_garage_is_given_window, *sorry_name_ip_garage_is_given_label, *sorry_name_ip_garage_is_given_ok_bt;
GtkWidget *cancle_config_win, *change_user_name_window, *change_password_window, *finish_config, *create_acc_yet_a_window, *entry_name, *entry_password, *entry_password_retype, *error_create_acc_yet_a_label, *show_password_a, *show_password_b, *show_user_password_c_bt;
GtkWidget *check_uuid_client_window, *check_uuid_client_grid, *check_label;
GtkWidget *ip_name_garage_window, *go_next_will_close_conn_label, *yes_exit_bt, *cancle_exit_bt;
GtkWidget *help_win, *grid_help;
GtkWidget *insta_config_help_bt_label, *connect_server_help_bt_label, *window_theme_color_help_bt_label, *final_config_help_bt_label, *add_garage_help_bt_label, *exit_config_help_bt_label;  
GtkWidget *ok_bt, *install_failed_by_check_label;
GtkWidget *entry_password_final, *entry_password_final_ch, *false_password_label, *show_pass_a_final_bt, *show_pass_b_final_bt;
GtkWidget *all_loaded_garages_server_window, *garages_server_label;
GtkWidget *install_failed_by_check_window;
const gchar *my_window_css = "my_window";
GdkScreen *my_screen;
GtkCssProvider *cssProvider;
GdkDisplay *display;
GError *error = 0;
WorkerData *wdP;
user_id u_id;

// window starts by 1; user_language = 1 = german, 2 = english; 1 = dark mode; 0 = normal mode; 
int window_number = 1, user_language = 2, check_if_ip_is_blocked = 0, acc_created = 0, check_number = 2, style_mode = 0, auto_start_program_check = 0, would_cancle = 0, was_here_main_connection_handler = 0, password_show_one_setted = 0, password_show_two_setted = 0, lines_garages_addr = 0, check_number_all = 1, check_exit_config_server_conn = 1, status_ip_hostname_exists = 0, password_new_setted_show_one = 0, password_new_setted_show_two = 0, super_user_auto = 0, was_here_super_user = 0, check_again_super_user = 3, install_programs_garage_opener = 1, was_here_super_user_only_started = 0, hostname_or_ip_not_exists = 0;
char bad_face_passwd[3] = ":(", smile_face_passwd[3] = ":)"; 
const gchar *entry_name_out, *entry_passwd_out, *entry_re_passwd_out, *server_name, *ip_add;
const gchar *gchar_user_name_re, *gchar_password_re, *gchar_password_re_ch;
const gchar *gchar_super_user_name, *gchar_super_user_password;
const gchar *entry_name_new, *entry_password_new, *entry_password_retype_new;
const gchar *gchar_name_garage, *gchar_ip_garage, *gchar_remove_garage_name;
// all infos from user
char name_a[9060] = "", name_b[9060] = "", password_a[9060] = "", password_b[9060] = "", server_name_a[9060] = "", server_name_b[9060] = "", server_ip_a[9060] = "", server_ip_b[9060] = "", uuid_a[9060] = "", uuid_b[9060] = "";
char ch_user_name_re[40], ch_user_password_re[40];
char entry_name_saved[sizeof(entry_name_out)], entry_passwd_saved[sizeof(entry_passwd_out)] = "";
char get_server_ip_add_auto[ipv4_len], get_server_name_auto[31], main_server_ip_lookup[ipv4_len];
char entry_server_ip_saved[ipv4_len] = exp_ip_add, entry_server_name_saved[31] = "localhost";
char set_name_b_again[40], set_password_b_again[40];
char name_garage[31] = "", ip_garage[ipv4_len] = "";
char name_ip_garage[9048] = "", save_name_ip_garage[9048], check_ip_name_garage[9048] = "", save_again_passwd[40] = "", show_entry_passwd_saved[40] = "", first_save_again_passwd[40] = "";;
char super_user_name_password[60] = "", check_super_user_acess[4] = "", check_super_user_acess_auto[4] = "", check_super_user_acess_two[4] = "";
char rest_tries_super_user[60] = "", rest_tries_counter[2] = "";
char super_user_name_password_saved[60];
char save_name_ip_garage_a[255][160], save_name_garage_a[255][160], save_ip_garage_a[255][160];
char buf_garages_addr[4080], all_garages_addr[40], all_garages_for_label[4100] = "Server Garagen:\n";
char *help_text = "";
char name_ip_garage_is_given[100];
char name_b_save[sizeof(name_b)], password_b_save[sizeof(password_b)], server_name_b_save[sizeof(server_name_b)], server_ip_b_save[sizeof(server_ip_b)], uuid_b_save[sizeof(uuid_b)], ch_user_name_re_save[sizeof(ch_user_name_re)], ch_user_password_re_save[sizeof(ch_user_password_re)];
char ip_is_blocked_label[100];

char password_gen_a[89][2] = {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z",
                               "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z",
                               "0", "1", "2", "3", "4", "5", "6", "7", "8", "9",
                               "!", "#", "$", "%", "&", "(", ")", "*", "+", ",", ":", "<", "=", ">", "?", "@", "[", "]", "{", "}", "|", "~", " ", ";", ".", "_", "-"};

static void absolute_start();
static void start_screen();
static void insta_config();
static void connect_server();
static void window_theme_color();
static void check_user_id_server();
static void final_config();
static void change_password_final();
static void change_user_name_final();
static void add_garage();
static void remove_garage();
static void exit_config();
static void go_next_will_close_conn();
static void super_user_acess();
void main_connection_handler();
void super_user_acess_two();
static void add_garage_entry();
static void check_uuid_is_here();
static void create_acc_yet_a();
static void install_failed_by_check();
static void super_user_access_start();
static void all_loaded_garages_server();
void start_crypt_second_handler();
char *crypt_data(const char *string_a, const char *string_b, char *file_location);
char *decrypt_data(const char *string_a, char *file_location);

// help to start thread from config.h file
static void start_main_connection_handler() {
    main_connection_handler();
}

// if user end the configuration manually
void system_end_program() {
    gtk_main_quit();
    exit(0);
}

// theme style for window
void my_style() {
    if (style_mode == 1) {
        gtk_css_provider_load_from_file(cssProvider, g_file_new_for_path(dark_theme_style), &error);
    }else {
        gtk_css_provider_load_from_file(cssProvider, g_file_new_for_path(not_dark_theme_style), &error);
    }
}

#include "language/language_select.h"

// main config file which connects to server
#include "config.h"
// thread functions 
#include "crypt.h"
#include "threads_main_config.h"
#include "destroy_windows.h"
#include "help_window.h"
#include "super_user_acess.h"
#include "config_install_windows.h"
#include "extra_windows.h"
#include "create_file.h"

// this is the absolute start to configure window
static void absolute_start() {
    // create dir's
    create();
    // create crypt files
    crypt_handler();
    
    wdP = g_malloc(sizeof *wdP);

    cssProvider = gtk_css_provider_new();
    gtk_css_provider_load_from_path(cssProvider, not_dark_theme_style, NULL);
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(cssProvider), GTK_STYLE_PROVIDER_PRIORITY_USER);

    // settings for start_screen (in main window)
    wdP->window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(wdP->window), "INoTime Garage Configuration");
    gtk_window_set_default_size(GTK_WINDOW(wdP->window), 800, 400);
    gtk_container_set_border_width(GTK_CONTAINER(wdP->window), 10);
    gtk_window_set_position(GTK_WINDOW(wdP->window), GTK_WIN_POS_CENTER);
    g_signal_connect(wdP->window, "destroy", G_CALLBACK(cancle_config), NULL);
    gtk_window_set_resizable(GTK_WINDOW(wdP->window), FALSE);
    gtk_widget_set_name(wdP->window, my_window_css);
    gtk_window_set_icon_from_file(GTK_WINDOW(wdP->window), MAIN_IMAGE_NAME, NULL);

    // grid for the main window 
    grid = gtk_grid_new(); 
    gtk_container_add(GTK_CONTAINER(wdP->window), grid);
    gtk_grid_set_row_spacing(GTK_GRID(grid), 0);

    // check which window would be reopened. First start "start_screen" would be opened
    switch(window_number) {
        case 1: start_screen(); break;
        case 2: insta_config(); break;
        case 3: what_to_install(); break;
        case 4: connect_server(); break;
        case 5: window_theme_color(); break;
        case 6: final_config(); break;
        case 7: add_garage(); break;
        case 8: exit_config(); break;
    }
} 

int main(int argc, char *argv[]) {
    // open programm app
    GtkApplication *programApp;
    int statusApp;
    programApp = gtk_application_new("org.gtk.inoinvestigationSystemConfig", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(programApp, "activate", G_CALLBACK(absolute_start), NULL);
    
    statusApp = g_application_run(G_APPLICATION(programApp), argc, argv);
    g_object_unref(programApp);
    // ----------------------------------------------

    return statusApp;
}