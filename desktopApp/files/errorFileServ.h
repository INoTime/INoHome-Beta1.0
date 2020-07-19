/*
#   Made by: INo Time
#   by questions write an email to: ino@inotime.de
#
#       started: 26.08.2019
#       finished: 26.08.2019
#
#   This is the errorFile header to write into log if something went wrong 
#   like error to create a new socket or bind to a client and listen and 
#   accept the client.
#
#
#   This is only for the server!!
*/

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