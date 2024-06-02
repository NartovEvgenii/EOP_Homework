#include <stdio.h>
#include <third_party/sqlite3.h>
#include <EOP/homework/EOP_Homework.h>
#include <EOP/homework/mapper/EOP_Homework_mapper.h>

#ifndef EOP_EOP_HOMEWORK_DAO_H
#define EOP_EOP_HOMEWORK_DAO_H


#ifdef __cplusplus
extern "C" {
#endif

EOP_Homework_err_code EOP_Homework_Dao_create();

EOP_Homework_err_code EOP_Homework_Dao_init_data();

char *EOP_Homework_Dao_get_homework_by_id(EOP_Homework_id homework_id);

char *EOP_Homework_Dao_update_homework(EOP_Homework_update_request update_request);

EOP_Homework_err_code EOP_Homework_Dao_delete_homework(EOP_Homework_id homework_id);

char *EOP_Homework_Dao_save_homework(EOP_Homework_request request);

char *EOP_Homework_Dao_get_homework_list();

char *EOP_Homework_Dao_get_homework_list_filter(EOP_Homework_filter_request filter_request);

char *EOP_Homework_Dao_get_type_answer_data_list();

#ifdef __cplusplus
}
#endif


#endif
