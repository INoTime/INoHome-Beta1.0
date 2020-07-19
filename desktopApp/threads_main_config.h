// create crypt data 
static gboolean crypt_handler_finish_conn(gpointer data) {
    WorkerData *wd = data;
    if (wd == NULL) {
        g_source_remove(wd->p_id_main_conn);
        g_free(wd);
    }
    return FALSE;
}

static gpointer crypt_handler_conn(gpointer data) {
    random_password_generator();
    WorkerData *wd = data;
    g_usleep(50000);
    g_idle_add(crypt_handler_finish_conn, wd);
    return NULL;
}

void crypt_handler() {
    WorkerData *wd;
    GThread *crypt_han;
    wd = g_malloc(sizeof(*wd));
    crypt_han = g_thread_new("crypt_handler_conn", crypt_handler_conn, wd);
    g_thread_unref(crypt_han);
}
// ------------------------------------------------------------------------

// main connection to server to get uuid
static gboolean worker_finish_main_conn(gpointer data) {
    super_user_acess_server();
    WorkerData *wd = data;
    if (wd == NULL) {
        g_source_remove(wd->p_id_main_conn);
        g_free(wd);
    }
    return FALSE;
}

static gpointer worker_main_conn(gpointer data) {
    main_configuration();
    WorkerData *wd = data;
    g_usleep(50000);
    g_idle_add(worker_finish_main_conn, wd);
    return NULL;
}

void main_connection_handler() {
    WorkerData *wd;
    GThread *main_conn;
    wd = g_malloc(sizeof(*wd));
    main_conn = g_thread_new("worker_main_conn", worker_main_conn, wd);
    g_thread_unref(main_conn);
}
// ------------------------------------------------------------------------

// wait until user got uuid (user id)
static gboolean worker_finish_user_id_end(gpointer data) {
    gtk_widget_destroy(check_uuid_client_window);
    final_config();
    WorkerData *wd = data;
    if (wd == NULL) {
        g_source_remove(wd->p_id_main_conn);
        g_free(wd);
    }
    return FALSE;
}

static gpointer worker_get_user_id_end(gpointer data) {
    check_user_id_server();
    WorkerData *wd = data;
    g_usleep(50000);
    g_idle_add(worker_finish_user_id_end, wd);
    return NULL;
}

void get_user_id_end() {
    WorkerData *wd;
    GThread *main_conn;
    wd = g_malloc(sizeof(*wd));
    main_conn = g_thread_new("worker_main_conn_user_id_end", worker_get_user_id_end, wd);
    g_thread_unref(main_conn);
}
// ------------------------------------------------------------------------

// send new garage to server
static gboolean worker_finish_send_garage_server(gpointer data) {
    WorkerData *wd = data;
    if (wd == NULL) {
        g_source_remove(wd->p_id_main_conn);
        g_free(wd);
    }
    return FALSE;
}

static gpointer worker_send_garage_server(gpointer data) {
    send_garge_server_ip();
    WorkerData *wd = data;
    g_usleep(50000);
    g_idle_add(worker_finish_send_garage_server, wd);
    return NULL;
}

void send_garage_server() {
    WorkerData *wd;
    GThread *main_conn;
    wd = g_malloc(sizeof(*wd));
    main_conn = g_thread_new("worker_send_garage_server", worker_send_garage_server, wd);
    g_thread_unref(main_conn);
}
// ------------------------------------------------------------------------

// search for server with hostname
static gboolean worker_finish_search_ip_with_hostname(gpointer data) {
    WorkerData *wd = data;
    if (wd == NULL) {
        g_source_remove(wd->p_id_main_conn);
        g_free(wd);
    }
    return FALSE;
}

static gpointer worker_search_ip_with_hostname(gpointer data) {
    search_ip();
    WorkerData *wd = data;
    g_usleep(50000);
    g_idle_add(worker_finish_search_ip_with_hostname, wd);
    return NULL;
}

void search_ip_with_hostname() {
    WorkerData *wd;
    GThread *main_conn;
    wd = g_malloc(sizeof(*wd));
    main_conn = g_thread_new("worker_search_ip_with_hostname", worker_search_ip_with_hostname, wd);
    g_thread_unref(main_conn);
}
// ------------------------------------------------------------------------

// get super user acess in installtion
static gboolean worker_finish_get_acess_thread(gpointer data) {
    WorkerData *wd = data;
    if (wd == NULL) {
        g_source_remove(wd->p_id_main_conn);
        g_free(wd);
    }
    return FALSE;
}

static gpointer worker_get_acess_thread(gpointer data) {
    get_super_user_acess();
    WorkerData *wd = data;
    g_usleep(50000);
    g_idle_add(worker_finish_get_acess_thread, wd);
    return NULL;
}

void get_acess_thread() {
    WorkerData *wd;
    GThread *main_conn;
    wd = g_malloc(sizeof(*wd));
    main_conn = g_thread_new("worker_get_acess_thread", worker_get_acess_thread, wd);
    g_thread_unref(main_conn);
}
// ------------------------------------------------------------------------