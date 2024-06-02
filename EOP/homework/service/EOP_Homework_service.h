#include <stdio.h>
#include <EOP/homework/EOP_Homework.h>

#ifndef EOP_EOP_HOMEWORK_SERVICE_H
#define EOP_EOP_HOMEWORK_SERVICE_H

#ifdef __cplusplus
extern "C" {
#endif

char *EOP_Homework_Service_save_homework(EOP_Homework_request request);

char *EOP_Homework_Service_update_homework(EOP_Homework_update_request update_request);

EOP_Homework_err_code EOP_Homework_Service_delete_homework(EOP_Homework_id homework_id);

char *EOP_Homework_Service_get_homework_list();

char *EOP_Homework_Service_get_homework_list_filter(EOP_Homework_filter_request filter_request);

char *EOP_Homework_Service_get_homework_by_id(EOP_Homework_id homework_id);

char *EOP_Homework_Service_get_type_answer_data_list();

#ifdef __cplusplus
}
#endif

#endif //EOP_EOP_HOMEWORK_SERVICE_H
