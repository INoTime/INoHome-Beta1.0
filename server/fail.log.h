// this is the automation of the fail log if an fail currupted it will show an fail number
// you can read all fail numbers in fail.log.txt

#define fail_log_all "tmp/fail.log"
#define fail_loag_create_user 1

// fail.log create user fail
#define main_fail_log_create_user "fail.log create user fail number: " 

static void save_in_fail_log(int which_fail_log, int fail_log_number) {
    FILE *main_fail_log_create_user_file = fopen(fail_log_all, "ab");
    char main_fail_log_create_user_all[40], all[4];
    switch (which_fail_log) {
        case 1:
            strcat(main_fail_log_create_user_all, main_fail_log_create_user);
            sprintf(all, "%d", fail_log_number);
            strcat(main_fail_log_create_user_all, all);
            perror(main_fail_log_create_user_all);
            fputs(main_fail_log_create_user_all, main_fail_log_create_user_file);
            fclose(main_fail_log_create_user_file);
        break;

        default:
        break;
    }
}

#define false_pass_file "tmp/false_password.log"

static void false_password_from_ip_create_user(char *ip_addr, char *time) {
    char false_password_a[30] = "fail.log false password from: ", false_password_all_a[200];
    FILE *false_password_from_ip_create_user_file = fopen(false_pass_file, "ab");
    strcat(false_password_all_a, false_password_a);
    strcat(false_password_all_a, ip_addr);
    strcat(false_password_all_a, " at: ");
    strcat(false_password_all_a, time);
    fputs(false_password_all_a, false_password_from_ip_create_user_file);
    fclose(false_password_from_ip_create_user_file);
}

#include <time.h>

#define logErrorFile "tmp/log_err_file_Serv.log"

/* get local time */
char *time_now() {
    time_t rawtime;
    struct tm *timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    char *timeinfo_r = asctime(timeinfo);
    return timeinfo_r;
}

/* get error log file for socket error (in error log file("log_err_file_Serv.log"))*/
int errorSock() {
    FILE *log_err_file = fopen(logErrorFile, "ab");
    char _sockGetAll[64] = "\nopening socket failed:\n\tat: ", *get_time_toFile = time_now();
    strcat(_sockGetAll, get_time_toFile);
    char *_socketRe = _sockGetAll;
    fputs(_socketRe, log_err_file);
    fclose(log_err_file);
    return 0;
}

/* get error log file for error binding (in error log file("log_err_file_Serv.log"))*/
int errorBind() {
    FILE *log_err_file = fopen(logErrorFile, "ab");
    char _sockGetAll[64] = "\nbindig failed:\n\tat: ", *get_time_toFile = time_now();
    strcat(_sockGetAll, get_time_toFile);
    char *_socketRe = _sockGetAll;
    fputs(_socketRe, log_err_file);
    fclose(log_err_file);
    return 0;
}

/* get error log file for listening error (in error log file("log_err_file_Serv.log"))*/
int errorListen() {
    FILE *log_err_file = fopen(logErrorFile, "ab");
    char _sockGetAll[64] = "\nlistening failed:\n\tat: ", *get_time_toFile = time_now();
    strcat(_sockGetAll, get_time_toFile);
    char *_socketRe = _sockGetAll;
    fputs(_socketRe, log_err_file);
    fclose(log_err_file);
    return 0;
}

/* get error log file for accept client error (in error log file("log_err_file_Serv.log"))*/
int errorAccept() {
    FILE *log_err_file = fopen(logErrorFile, "ab");
    char _sockGetAll[64] = "\naccepting client failed:\n\tat: ", *get_time_toFile = time_now();
    strcat(_sockGetAll, get_time_toFile);
    char *_socketRe = _sockGetAll;
    fputs(_socketRe, log_err_file);
    fclose(log_err_file);
    return 0;    
}