// ############################################# 
// ### This is the Terminal version to print ### 
// ########### everythin in terminal ###########
// ##### Questions? EMail: ino@inotime.com #####
// ############################################# 


// start program print count user lines
void start_program_print_users(int total_registred_users) {
    printf("Total registred users: %d\n", total_registred_users);
}

// start program print count ip_add_rasp lines
void start_program_print_ip_add_rasp(int total_registred_ip_add_rasp) {
    printf("Total regsitred garages: %d\n", total_registred_ip_add_rasp);
}

// start program print count blocked ip add
void start_program_print_blocked_users(int total_blocked_ip_add) {
    printf("Total blocked users: %d\n\n", total_blocked_ip_add);
}

// show how many clients are online at one time
void alive_clients(int active_clients) {
    printf("Online clients: %d\n", active_clients);
}

// connected to main server (user uuid and number will be printed)
void connected_main_server(int user_number, char *uuid_user) {
    printf("<\033[0;32mCONNECTED\033[0m> user id: %d, uuid: %s", user_number, uuid_user);
} 

// disconnected from main server (user uuid and number will be printed)
void disconnected_main_server(int user_number, char *uuid_user) {
    printf("<\033[0;31mDISCONNECTED\033[0m> from user id: %d, uuid: %s", user_number, uuid_user);
}

// creating new user
void new_user_print(int x, char *ip_addr, char *uuid) {
    switch(x) {
        // print ip address from user
        case 1:
           printf("<\033[0;32mUSER\033[0;m> wants uuid ip: %s\n", ip_addr);
        break;

        // print that user uuid was settet to ip address ...
        case 2:
            printf("<\033[0;32mSETTED\033[0;m> user uuid was setted for: %s\n", ip_addr);
        break;

        // print if a faile corrupted while configuration uuid
        case 3:
            printf("<\033[0;31mFAILED\033[0;m> user uuid failed for: %s\n", ip_addr);
        break;

        case 4:
            printf("<\033[0;32mGARAGE IP\033[0;m> garage ip's were send to user: %s\n", uuid);
        break;

        case 5:
            printf("<\033[0;32mCOMMANDS\033[0;m> were send to user: %s\n", uuid);
        break;

        case 6:
            printf("<\033[0;31mDISCONNECTED\033[0m> ip: %s\n", ip_addr);
        break;
    } 
}

// print the full dialog of the new user
void full_new_user_print(char *user_uuid, char *ip_addr, int user_number, char *time_out) {
    printf("<\033[0;32mCREATED\033[0;m> new uuid: %s, for ip: %s, current user number: %d, at date/time: %s", user_uuid, ip_addr, user_number, time_out);
}

void new_garage(char *user_uuid_and_garage_name_ip) {
    printf("<\033[0;32mSAVED\033[0;m> new garage/s from: %s", user_uuid_and_garage_name_ip);
}

// if client typed in wrong password
void false_password_from_ip(char *false_pwd_from_ip, char *time_out) {
    printf("<\033[0;31mFalse password\033[0m> from ip: %s at: %s", false_pwd_from_ip, time_out);
}

// if client typed 3 times false password user will be blocked
void ip_is_blocked(char *false_pwd_from_ip, char *time_out) {
    printf("<\033[0;31mIP blocked\033[0m> ip: %s at: %s", false_pwd_from_ip, time_out);
}

void ip_is_blocked_futher(char *ip) {
    printf("<\033[0;31mIP is blocked\033[0m> ip: %s", ip);
}

void false_command_or_false_uuid_from_user(char *ip) {
    printf("<\033[0;31mERROR\033[0m> not registred? False command or uuid from user-ip: %s", ip);
}

void created_new_garage_from_client(char *uuid_user, char *hostanem_ip_garage) {
    printf("<\033[0;32mCREATED\033[0;m> new garage from: %s\t%s", uuid_user, hostanem_ip_garage);
}

void failed_create_new_garage_from_client(char *uuid_user, char *hostanem_ip_garage) {
    printf("<\033[0;31mERROR\033[0m> could not create new garage from: %s\t%s", uuid_user, hostanem_ip_garage);
}