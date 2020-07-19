char password_gen_final[34] = "";
char create_crypt_data_file[6][20] = {"user_info_data", "serverIP_add_data", "check_my_style_data", "commands_data", "ip_addr_garage_data", "user_id_data"}; 
char intern_crypt[90][5] = {"cC[;", "l$|;", "#7);", "Ako;", "%G!;", "jbX;", "xRs;", "CX~;", "[6z;", "[T1;", "{VM;", "<pr;", ",[@;", "l9S;", "(P?;", "SiI;", "YF[;", "*7Q;",
                            "yk6;", "YT8;", "sO$;", "oD];", "F5:;", "%)X;", "yYV;", "6Z3;", "Xrb;", "Qbs;", "Qz+;", "pG:;", ">iC;", "2wo;", "f1C;", "@?l;", "~5s;", "UE*;",
                            "q{b;", "8]S;", "JKB;", "uZq;", "h~y;", "@jU;", "Wo5;", "?hW;", "SVu;", "!ii;", "V(T;", "f N;", "hIH;", "?2 ;", "hsO;", "G1g;", "Jqv;", "XY+;",
                            "mjG;", ">:~;", "O?%;", "aM$;", "}c3;", "D[y;", ",b ;", "AH0;", "G)A;", "k>?;", "{cQ;", "+I,;", ")=!;", "fF6;", "AC8;", "}52;", "!Rm;", "sAT;",
                            "C7+;", "2A8;", "cwu;", "SX2;", "F=b;", "YKG;", "%!8;", "Pp>;", "0IH;", "$j8;", "&L?;", "iWr;", "*YN;", "U0T;", "5OI;", "&@e;", "f%d;"};

// create random strings for cryptation data
static void random_password_generator() {
    char crypt_path[40], password_gen_final_o[89][40];
    for (int a = 0; a != 6; a++) {
        strcpy(crypt_path, "files/crypt/");
        strcat(crypt_path, create_crypt_data_file[a]);
        FILE *my_crypt_o = fopen(crypt_path, "w");
        // create random number
        srand(time(0)+a);
        for (int y = 0; y != 90; y++) {
            for (int x = 0; x < 3; x++) {
                int num = rand() % 88;
                strcat(password_gen_final, password_gen_a[num]); 
            }
            strcat(password_gen_final, ";\n");
            strcpy(password_gen_final_o[y], password_gen_final);
            strcpy(password_gen_final, "");
        }
        for (int x = 0; x != 90; x++) {
            fputs(password_gen_final_o[x], my_crypt_o);
            strcpy(password_gen_final_o[x], "");
        }
        fclose(my_crypt_o);
    }
}

// create with file and intern crypt crypt for file
char *crypt_data(const char *string_a, const char *string_b, char *file_location) {
    char buffer_save_string[89] = "", save_string[89][6] = { 0 }, get_one[2] = "", *string_all = malloc(9690), *string_all_save = malloc(9690), string_save_a[4], *string_all_b = malloc(9690), *string_all_b_save = malloc(9690), string_save_b[4];
    int cout_lines_crypt_file = 0;

    // get crypt from file
    FILE *crypt_file_o = fopen(file_location, "r+");
    while (fgets(buffer_save_string, sizeof(buffer_save_string), crypt_file_o) != NULL) {
        strcpy(save_string[cout_lines_crypt_file], buffer_save_string);
        cout_lines_crypt_file++;
    }
    fclose(crypt_file_o);
    // ------------------------------------------------------------------------

    // string_a crypt
    if (!strcmp(string_a, "") == 0) {
        // intern crypt string_a
        strcpy(string_all, "");
        for (int x = 0; x != strlen(string_a); x++) {
            snprintf(get_one, 2, "%c", string_a[x]);
            for (int y = 0; y != 89; y++) {
                if (!strcmp(password_gen_a[y], get_one) != 0) {
                    for (int a = 0; a != 4; a++) {
                        snprintf(string_save_a, 4, "%c", intern_crypt[y][a]);
                        strcat(string_all, string_save_a);
                    }
                    break;
                }
            }
        }

        // out crypt string_a
        strcpy(string_all_save, "");
        for (int x = 0; x != strlen(string_all); x++) {
            snprintf(get_one, 2, "%c", string_all[x]);
            for (int y = 0; y != 89; y++) {
                if (!strcmp(password_gen_a[y], get_one) != 0) {
                    for (int a = 0; a != 4; a++) {
                        snprintf(string_save_a, 4, "%c", save_string[y][a]);
                        strcat(string_all_save, string_save_a);
                    }
                    break;
                }
            }
        }
    }
    // ------------------------------------------------------------------------

    // string_b crypt 
    if (!strcmp(string_b, "") == 0) {
        // intern crypt string_b
        strcpy(string_all_b, "");
        for (int x = 0; x != strlen(string_b); x++) {
            snprintf(get_one, 2, "%c", string_b[x]);
            for (int y = 0; y != 89; y++) {
                if (!strcmp(password_gen_a[y], get_one) != 0) {
                    for (int a = 0; a != 4; a++) {
                        snprintf(string_save_b, 4, "%c", intern_crypt[y][a]);
                        strcat(string_all_b, string_save_b);
                    }
                    break;
                }
            }   
        }

        // out crypt string_b
        strcpy(string_all_b_save, "");
        for (int x = 0; x != strlen(string_all_b); x++) {
            snprintf(get_one, 2, "%c", string_all_b[x]);
            for (int y = 0; y != 89; y++) {
                if (!strcmp(password_gen_a[y], get_one) != 0) {
                    for (int a = 0; a != 4; a++) {
                        snprintf(string_save_b, 4, "%c", save_string[y][a]);
                        strcat(string_all_b_save, string_save_b);
                    }
                    break;
                }
            }
        }
        // save string to file
        strcat(string_all_save, "\n");
        strcat(string_all_save, string_all_b_save);
    }
    // ------------------------------------------------------------------------

    return (char *)string_all_save;
}

// decrypt data 
char *decrypt_data(const char *string_a, char *file_location) {
    char buffer_save_string[89] = "", save_string[89][6], buffer_crypted_a[4][2] = { 0 }, buffer_intern_crypt_a[4][4], save_buffer[6] = "", save[9690] = ""; 
    char buffer_save_string_s[89] = "", buffer_crypted_a_s[4][2] = { 0 }, buffer_intern_crypt_a_s[4][4], save_buffer_s[6] = "", save_s[9690] = "";
    int cout_lines_crypt_file = 0;
    // ------------------------------------------------------------------------
    
        
    // get crypt from file
    FILE *crypt_file_o = fopen(file_location, "r");
    while (fgets(buffer_save_string, sizeof(buffer_save_string), crypt_file_o) != NULL) {
        strcpy(save_string[cout_lines_crypt_file], buffer_save_string);
        save_string[cout_lines_crypt_file][strlen(save_string[cout_lines_crypt_file])-1] = '\0';
        cout_lines_crypt_file++;
    }
    fclose(crypt_file_o);
    // ------------------------------------------------------------------------
    
    // out decyption
    for (int c = 0; c != strlen(string_a); c++) {
        for (int a = 0; a != 4; a++) {
            strcpy(buffer_crypted_a[a], "");
            snprintf(buffer_crypted_a[a], 2, "%c", string_a[c+a]);
        }
        for (int a = 0; a != 89; a++) {
            for (int b = 0; b != 4; b++) {
                strcpy(buffer_intern_crypt_a[b], "");
                snprintf(buffer_intern_crypt_a[b], 4, "%c", save_string[a][b]);
            }
            if (((!strcmp(buffer_crypted_a[0], buffer_intern_crypt_a[0])) && (!strcmp(buffer_crypted_a[1], buffer_intern_crypt_a[1])) && (!strcmp(buffer_crypted_a[2], buffer_intern_crypt_a[2])) && (!strcmp(buffer_crypted_a[3], buffer_intern_crypt_a[3]))) != 0) {
                strcpy(save_buffer, "");
                for (int x = 0; x != 4; x++) {
                    strcat(save_buffer, buffer_crypted_a[x]);
                }
                for (int y = 0; y != 89; y++) {
                    if (!strcmp(save_buffer, save_string[y]) != 0) {
                        strcat(save, password_gen_a[y]);
                        break;
                    }
                }
            }
        }
    }   

    // intern decryption
    for (int c = 0; c != strlen(save); c++) {
        for (int a = 0; a != 4; a++) {
            strcpy(buffer_crypted_a_s[a], "");
            snprintf(buffer_crypted_a_s[a], 2, "%c", save[c+a]);
        }
        for (int a = 0; a != 89; a++) {
            for (int b = 0; b != 4; b++) {
                strcpy(buffer_intern_crypt_a_s[b], "");
                snprintf(buffer_intern_crypt_a_s[b], 4, "%c", intern_crypt[a][b]);
            }
            if (((!strcmp(buffer_crypted_a_s[0], buffer_intern_crypt_a_s[0])) && (!strcmp(buffer_crypted_a_s[1], buffer_intern_crypt_a_s[1])) && (!strcmp(buffer_crypted_a_s[2], buffer_intern_crypt_a_s[2])) && (!strcmp(buffer_crypted_a_s[3], buffer_intern_crypt_a_s[3]))) != 0) {
                strcpy(save_buffer_s, "");
                for (int x = 0; x != 4; x++) {
                    strcat(save_buffer_s, buffer_crypted_a_s[x]);
                }
                for (int y = 0; y != 89; y++) {
                    if (!strcmp(save_buffer_s, intern_crypt[y]) != 0) {
                        strcat(save_s, password_gen_a[y]);
                        break;
                    }
                }
            }
        }
    }

    // returning string back to callback
    char *cp = save_s;
    return cp;
}