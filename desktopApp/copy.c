char *crypt_data(const char *string_a, const char *string_b) {
    
    char *string_all = malloc(9690);
    char save_string_all[86][40];
    char test[9690] = "";
    char save[2] = "";
    char buffer_save_string[40]; 
    int cout_lines_a = 0;
    strcpy(string_all, "");
    for (int x = 0; x != strlen(string_a); x++) {
        FILE *crypt_file = fopen("files/crypt/user_info_data", "r");
        snprintf(save, 2, "%c", string_a[x]);
        for (int y = 0; y != 86; y++) {
            if (!strcmp(password_gen_a[y], save) != 0) {
                while (fgets(buffer_save_string, sizeof(buffer_save_string), crypt_file) != NULL) {
                    if (cout_lines_a == y) {
                        strcat(string_all, buffer_save_string);
                        strcpy(buffer_save_string, "");
                        cout_lines_a = 0;
                        fclose(crypt_file);
                        break;
                    }
                    cout_lines_a++;
                }
                break;
            }
        }
    }
    g_print("%s\n", string_all);
    
    strcat(string_all, string_b);
    strcat(string_all, "\n");

    return (char *)string_all;
}