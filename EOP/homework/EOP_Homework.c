#include <EOP/homework/EOP_Homework.h>
#include <EOP/homework/db/dao/EOP_Homework_dao.h>
#include <EOP/homework/controller/EOP_Homework_controller.h>

void EOP_Homework_api_matcher(struct mg_connection *pConnection, struct mg_http_message *pMessage) {
    EOP_Homework_Controller_api_match(pConnection, pMessage);
}

EOP_Homework_err_code EOP_Homework_create_homework_db() {
    return EOP_Homework_Dao_create();
}

EOP_Homework_err_code EOP_Homework_init_homework_db() {
    return EOP_Homework_Dao_init_data();
}