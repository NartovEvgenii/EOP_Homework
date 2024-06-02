#ifndef EOP_HOMEWORK_EOP_HOMEWORK_H
#define EOP_HOMEWORK_EOP_HOMEWORK_H


#ifdef __cplusplus
extern "C" {
#endif

#include <time.h>
#include <stdbool.h>
#include <third_party/mongoose.h>
#include <third_party/sqlite3.h>

typedef short EOP_Homework_err_code;

typedef long EOP_Homework_id;
typedef int EOP_Homework_task_id;
typedef const char *EOP_Homework_student_ext_id;
typedef const char *EOP_Homework_answer_text;
typedef const char *EOP_Homework_checked_teacher_ext_id;
typedef const char *EOP_Homework_checked_teacher_description;
typedef int EOP_Homework_result_grade;
typedef const char *EOP_Homework_download_date;
typedef const char *EOP_Homework_last_upd_date;

typedef long EOP_Type_answer_data_id;
typedef const char *EOP_Type_answer_data_type_name;
typedef const char *EOP_Type_answer_data_code_language;

typedef long EOP_Type_answer_stat_id;
typedef const char *EOP_Type_answer_stat_status_name;

typedef struct {
    EOP_Type_answer_data_id id;
    EOP_Type_answer_data_type_name type_name;
    EOP_Type_answer_data_code_language code_language;
} EOP_Type_answer_data;

typedef struct {
    EOP_Type_answer_stat_id id;
    EOP_Type_answer_stat_status_name status_name;
} EOP_Type_answer_stat;

typedef struct {
    EOP_Homework_id id;
    EOP_Homework_task_id task_id;
    EOP_Homework_student_ext_id student_ext_id;
    EOP_Homework_answer_text answer_text;
    EOP_Homework_download_date download_date;
    EOP_Homework_last_upd_date last_upd_date;
    EOP_Homework_checked_teacher_ext_id checked_teacher_ext_id;
    EOP_Homework_checked_teacher_description teacher_description;
    EOP_Homework_result_grade result_grade;
    EOP_Type_answer_data type_answer_data;
    EOP_Type_answer_stat type_answer_stat;
} EOP_Homework;

typedef struct {
    EOP_Homework_task_id task_id;
    EOP_Homework_student_ext_id student_ext_id;
    EOP_Homework_answer_text answer_text;
    EOP_Type_answer_data_id type_answer_data_id;
} EOP_Homework_request;

typedef struct {
    EOP_Homework_id id;
    EOP_Homework_checked_teacher_ext_id checked_teacher_ext_id;
    EOP_Homework_checked_teacher_description teacher_description;
    EOP_Homework_result_grade result_grade;
    EOP_Type_answer_stat_id stat_id;
} EOP_Homework_update_request;

typedef struct {
    EOP_Homework_task_id task_id;
    EOP_Homework_student_ext_id student_ext_id;
    EOP_Homework_checked_teacher_ext_id checked_teacher_ext_id;
} EOP_Homework_filter_request;

void EOP_Homework_api_matcher(struct mg_connection *pConnection, struct mg_http_message *pMessage);

EOP_Homework_err_code EOP_Homework_create_homework_db();

EOP_Homework_err_code EOP_Homework_init_homework_db();

#ifdef __cplusplus
}
#endif

#endif