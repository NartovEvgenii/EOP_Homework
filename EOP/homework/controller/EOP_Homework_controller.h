#ifndef EOP_EOP_HOMEWORK_CONTROLLER_H
#define EOP_EOP_HOMEWORK_CONTROLLER_H

#include <third_party/mongoose.h>

#ifdef __cplusplus
extern "C" {
#endif

void EOP_Homework_Controller_api_match(struct mg_connection *pConnection, struct mg_http_message *pMessage);

#ifdef __cplusplus
}
#endif

#endif //EOP_EOP_HOMEWORK_CONTROLLER_H
