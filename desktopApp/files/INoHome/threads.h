// main connection to server to check evrything
static gboolean worker_finish_main_conn(gpointer data) {
    if (loged_in && !is_on_first_window) {
        gtk_widget_destroy(connecting_to_server_window);
        main_screen();
    }else if (loged_in && is_on_first_window) {
        select_language_main_window(1, 1, NULL, NULL, server_status_label, NULL);
    }
    WorkerData *wd = data;
    if (wd == NULL) {
        g_source_remove(wd->p_id_main_conn);
        g_free(wd);
    }
    return FALSE;
}

static gpointer worker_main_conn(gpointer data) {
    mainConnectionServer();
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

// main connection start main screen
static gboolean main_connection_main_screen_conn_finish(gpointer data) {
    select_language_main_window(1, 0, NULL, NULL, server_status_label, NULL);
    WorkerData *wd = data;
    if (wd == NULL) {
        g_source_remove(wd->p_id_main_conn);
        g_free(wd);
    }
    return FALSE;
}

static gpointer main_connection_main_screen_conn(gpointer data) {
    mainConnectionServer();
    WorkerData *wd = data;
    g_usleep(50000);
    g_idle_add(main_connection_main_screen_conn_finish, wd);
    return NULL;
}

void main_connection_main_screen_handler() {
    WorkerData *wd;
    GThread *main_conn;
    wd = g_malloc(sizeof(*wd));
    main_conn = g_thread_new("main_connection_main_screen_conn", main_connection_main_screen_conn, wd);
    g_thread_unref(main_conn);
}
// ------------------------------------------------------------------------

// main connection send new garage to server
static gboolean main_connection_send_garage_handler_conn_finish(gpointer data) {
    send_garage_to_server();
    WorkerData *wd = data;
    if (wd == NULL) {
        g_source_remove(wd->p_id_main_conn);
        g_free(wd);
    }
    return FALSE;
}

static gpointer main_connection_send_garage_handler_conn(gpointer data) {
    for (;;) {
        if (loged_in && connection_server_is_true) break;
    }
    WorkerData *wd = data;
    g_usleep(50000);
    g_idle_add(main_connection_send_garage_handler_conn_finish, wd);
    return NULL;
}

void main_connection_send_garage_handler() {
    WorkerData *wd;
    GThread *main_conn;
    wd = g_malloc(sizeof(*wd));
    main_conn = g_thread_new("main_connection_send_garage_handler_conn", main_connection_send_garage_handler_conn, wd);
    g_thread_unref(main_conn);
}
// ------------------------------------------------------------------------#


// main connection check garage state
static gboolean main_connection_garage_state_handler_conn_finish(gpointer data) {
    WorkerData *wd = data;
    if (wd == NULL) {
        g_source_remove(wd->p_id_main_conn);
        g_free(wd);
    }
    return FALSE;
}

static gpointer main_connection_garage_state_handler_conn(gpointer data) {
    check_garage_state();
    WorkerData *wd = data;
    g_usleep(50000);
    g_idle_add(main_connection_garage_state_handler_conn_finish, wd);
    return NULL;
}

void main_connection_garage_state_handler() {
    WorkerData *wd;
    GThread *main_conn;
    wd = g_malloc(sizeof(*wd));
    main_conn = g_thread_new("main_connection_garage_state_handler_conn", main_connection_garage_state_handler_conn, wd);
    g_thread_unref(main_conn);
}
// ------------------------------------------------------------------------

// main connection check server state
static gboolean main_connection_server_state_handler_conn_finish(gpointer data) {
    WorkerData *wd = data;
    if (wd == NULL) {
        g_source_remove(wd->p_id_main_conn);
        g_free(wd);
    }
    return FALSE;
}

static gpointer main_connection_server_state_handler_conn(gpointer data) {
    check_server_state();
    WorkerData *wd = data;
    g_usleep(50000);
    g_idle_add(main_connection_server_state_handler_conn_finish, wd);
    return NULL;
}

void main_connection_server_state_handler() {
    WorkerData *wd;
    GThread *main_conn;
    wd = g_malloc(sizeof(*wd));
    main_conn = g_thread_new("main_connection_server_state_handler_conn", main_connection_server_state_handler_conn, wd);
    g_thread_unref(main_conn);
}
// ------------------------------------------------------------------------