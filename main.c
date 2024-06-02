#include <third_party/mongoose.h>
#include <third_party/sqlite3.h>
#include <EOP/homework/EOP_Homework.h>

static bool EOP_Homework_is_ok(int rc) {
    return rc == SQLITE_OK;
}

static EOP_Homework_err_code create_db() {
    return EOP_Homework_create_homework_db();
}

static EOP_Homework_err_code init_db() {
    return EOP_Homework_init_homework_db();
}

static void fn(struct mg_connection *c, int ev, void *ev_data) {
    if (ev == MG_EV_HTTP_MSG) {  // New HTTP request received
        struct mg_http_message *hm = (struct mg_http_message *) ev_data;// Parsed HTTP request
        EOP_Homework_api_matcher(c, hm);
    }
}

int main(void) {
    create_db();
    init_db();
    struct mg_mgr mgr;  // Mongoose event manager. Holds all connections
    mg_mgr_init(&mgr);
    mg_http_listen(&mgr, "http://localhost:8083", fn, NULL);  // Setup listener

    for (;;) {
        mg_mgr_poll(&mgr, 1000);  // Infinite event loop
    }
}
