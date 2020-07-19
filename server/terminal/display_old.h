#define buf_ag 20
#define buf_all 4096
#define strlen_buf_a 60
#define strlen_buf_b 20

struct display_settings {
     char      ip_add_user[buf_ag];
     char      option[2];

     struct display_new_garage {
          char      name_garage[buf_ag];
          char      ip_garage[buf_ag];
     }new_garage;    
};

void *display_evrything() {
     
          char printf_ip_garage[buf_all] = "<\033[32mOK\033[0m> garage ip: ", printf_option[buf_all] = "option: ", printf_name_garage[buf_all] = "", printf_name_ex[buf_all] = "", printf_ip_ex[buf_all] = "", printf_error[buf_all] = "<\033[31m!!\033[0m> error by switch\n";
          struct display_settings open;
     
          // print status and garage ip
          strcat(printf_ip_garage, open.new_garage.ip_garage);
          printf("%s\n", printf_ip_garage);

          // print only status from garages
          strcat(printf_option, open.option);
          printf("%s\n", printf_option);

          // print new garage name by creating and ip addres
          strcat(printf_name_garage, "<\033[32mCREATED\033[0m> garage name: ");
          strcat(printf_name_garage, open.new_garage.name_garage);
          strcat(printf_name_garage, " ip address: ");
          strcat(printf_name_garage, open.new_garage.ip_garage);
          printf("%s\n", printf_name_garage);

          // if garage name exists by creating
          strcat(printf_name_ex, "<\033[31m!!\033[0m> garage name exists: ");
          strcat(printf_name_ex, open.new_garage.name_garage);
          printf("%s\n", printf_name_ex);

          // if garage ip adress exists by creating
          strcat(printf_ip_ex, "<\033[31m!!\033[0m> garage ip exists: ");
          strcat(printf_ip_ex, open.new_garage.ip_garage);
          printf("%s\n", printf_ip_ex);    
     
} 


/*void display_start(int x) { 
     if (x == 1) {
          //strcat (printf_ip_garage, printf_option);

          //printf("%s\n", open.option);
          //fflush(stdout);
          //system("sleep 1");


          //printf("\033[?25"); 
     }
}*/