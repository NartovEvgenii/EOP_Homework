#include <EOP/homework/mapper/EOP_Homework_mapper.h>
#include <EOP/homework/service/EOP_Homework_service.h>

static bool EOP_Homework_is_post(struct mg_str method) {
    return strncmp("POST", method.buf, strlen("POST")) == 0;
}

static bool EOP_Homework_is_get(struct mg_str method) {
    return strncmp("GET", method.buf, strlen("GET")) == 0;
}

static bool EOP_Homework_is_put(struct mg_str method) {
    return strncmp("PUT", method.buf, strlen("PUT")) == 0;
}

static bool EOP_Homework_is_delete(struct mg_str method) {
    return strncmp("DELETE", method.buf, strlen("DELETE")) == 0;
}

static void EOP_Homework_error_replay(struct mg_connection *pConnection) {
    mg_http_reply(pConnection, 400, "", "Error");
}

static void EOP_Homework_success_200_replay(struct mg_connection *pConnection) {
    mg_http_reply(pConnection, 200, "", "Success");
}

static void EOP_Homework_success_201_replay(struct mg_connection *pConnection) {
    mg_http_reply(pConnection, 201, "", "Success");
}

static void EOP_Homework_handle_get_health(struct mg_connection *pConnection, struct mg_http_message *pMessage) {
    mg_http_reply(pConnection, 200, "Content-Type: application/json\r\n", "OK");
}

static void EOP_Homework_handle_get_all(struct mg_connection *pConnection, struct mg_http_message *pMessage) {
    char *response = EOP_Homework_Service_get_homework_list();
    if (response != NULL) {
        mg_http_reply(pConnection, 200, "Content-Type: application/json\r\n", response);
    } else {
        EOP_Homework_error_replay(pConnection);
    }
}

static void EOP_Homework_handle_get_all_filter(struct mg_connection *pConnection, struct mg_http_message *pMessage) {
    char *response = EOP_Homework_Service_get_homework_list_filter(EOP_Homework_Mapper_to_homework_filter_request(pMessage->body));
    if (response != NULL) {
        mg_http_reply(pConnection, 200, "Content-Type: application/json\r\n", response);
    } else {
        EOP_Homework_error_replay(pConnection);
    }
}

static void EOP_Homework_handle_get_by_id(struct mg_connection *pConnection, struct mg_http_message *pMessage) {
    char *response = EOP_Homework_Service_get_homework_by_id(EOP_Homework_Mapper_to_homework_id(pMessage->body));
    if (response != NULL) {
        mg_http_reply(pConnection, 200, "Content-Type: application/json\r\n", response);
    } else {
        EOP_Homework_error_replay(pConnection);
    }
}

static void EOP_Homework_handle_create_one(struct mg_connection *pConnection, struct mg_http_message *pMessage) {
    char *response = EOP_Homework_Service_save_homework(EOP_Homework_Mapper_to_homework_request(pMessage->body));
    if (response != NULL) {
        mg_http_reply(pConnection, 200, "Content-Type: application/json\r\n", response);
    } else {
        EOP_Homework_error_replay(pConnection);
    }
}

static void EOP_Homework_handle_update_homework(struct mg_connection *pConnection, struct mg_http_message *pMessage) {
    char *response = EOP_Homework_Service_update_homework(EOP_Homework_Mapper_to_homework_update_request(pMessage->body));
    if (response != NULL) {
        mg_http_reply(pConnection, 200, "Content-Type: application/json\r\n", response);
    } else {
        EOP_Homework_error_replay(pConnection);
    }
}

static void EOP_Homework_handle_delete_homework(struct mg_connection *pConnection, struct mg_http_message *pMessage) {
    if (EOP_Homework_Service_delete_homework(EOP_Homework_Mapper_to_homework_id(pMessage->body)) ==
        0) {
        EOP_Homework_success_200_replay(pConnection);
    } else {
        EOP_Homework_error_replay(pConnection);
    }
}

static void EOP_Homework_handle_get_all_type_answer_data(struct mg_connection *pConnection, struct mg_http_message *pMessage) {
    char *response = EOP_Homework_Service_get_type_answer_data_list();
    if (response != NULL) {
        mg_http_reply(pConnection, 200, "Content-Type: application/json\r\n", response);
    } else {
        EOP_Homework_error_replay(pConnection);
    }
}

static void EOP_Homework_handle_homework(struct mg_connection *pConnection, struct mg_http_message *pMessage) {
    // GET health
    if (mg_match(pMessage->uri, mg_str("/api/homework/health"), NULL) && EOP_Homework_is_get(pMessage->method)) {
        EOP_Homework_handle_get_health(pConnection, pMessage);
        return;
    }
    // GET get all
    if (mg_match(pMessage->uri, mg_str("/api/homework/all"), NULL) && EOP_Homework_is_get(pMessage->method)) {
        EOP_Homework_handle_get_all(pConnection, pMessage);
        return;
    }
    // GET get all by filter
    if (mg_match(pMessage->uri, mg_str("/api/homework/filter"), NULL) && EOP_Homework_is_get(pMessage->method)) {
        EOP_Homework_handle_get_all_filter(pConnection, pMessage);
        return;
    }
    // GET by id
    if (mg_match(pMessage->uri, mg_str("/api/homework/id"), NULL) && EOP_Homework_is_get(pMessage->method)) {
        EOP_Homework_handle_get_by_id(pConnection, pMessage);
        return;
    }
    // POST create homework
    if (mg_match(pMessage->uri, mg_str("/api/homework/one"), NULL) && EOP_Homework_is_post(pMessage->method)) {
        EOP_Homework_handle_create_one(pConnection, pMessage);
        return;
    }
    // PUT update homework
    if (mg_match(pMessage->uri, mg_str("/api/homework/update"), NULL) && EOP_Homework_is_put(pMessage->method)) {
        EOP_Homework_handle_update_homework(pConnection, pMessage);
        return;
    }
    // DELETE homework by id
    if (mg_match(pMessage->uri, mg_str("/api/homework/delete"), NULL) && EOP_Homework_is_delete(pMessage->method)) {
        EOP_Homework_handle_delete_homework(pConnection, pMessage);
        return;
    }
    // GET get all typeAnswerData
    if (mg_match(pMessage->uri, mg_str("/api/homework/typeAnswerData/all"), NULL) && EOP_Homework_is_get(pMessage->method)) {
        EOP_Homework_handle_get_all_type_answer_data(pConnection, pMessage);
        return;
    }
}

void EOP_Homework_Controller_api_match(struct mg_connection *pConnection, struct mg_http_message *pMessage) {
    if (mg_match(pMessage->uri, mg_str("/api/homework#"), NULL)) {
        EOP_Homework_handle_homework(pConnection, pMessage);
    } else {
        struct mg_http_serve_opts opts = {.root_dir = "."};     // For all other URLs,
        mg_http_serve_dir(pConnection, pMessage, &opts);    // Serve static files
    }
}
