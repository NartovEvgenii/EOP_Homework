#include <EOP/homework/mapper/EOP_Homework_mapper.h>

static int EOP_Homework_get_homework_id(struct mg_str json) {
    return mg_json_get_long(json, "$.id", -1);
}

static int EOP_Homework_get_task_id(struct mg_str json) {
    return mg_json_get_long(json, "$.task_id", -1);
}

static int EOP_Homework_get_type_answer_data_id(struct mg_str json) {
    return mg_json_get_long(json, "$.type_answer_data_id", -1);
}

static char *EOP_Homework_get_student_ext_id(struct mg_str json) {
    return mg_json_get_str(json, "$.student_ext_id");
}
static char *EOP_Homework_get_answer_text(struct mg_str json) {
    return mg_json_get_str(json, "$.answer_text");
}

static char *EOP_Homework_get_checked_teacher_ext_id(struct mg_str json) {
    return mg_json_get_str(json, "$.checked_teacher_ext_id");
}

static char *EOP_Homework_get_teacher_description(struct mg_str json) {
    return mg_json_get_str(json, "$.teacher_description");
}

static int EOP_Homework_get_result_grade(struct mg_str json) {
    return mg_json_get_long(json, "$.result_grade", -1);
}

static int EOP_Homework_get_stat_id(struct mg_str json) {
    return mg_json_get_long(json, "$.stat_id", -1);
}

EOP_Homework_id EOP_Homework_Mapper_to_homework_id(struct mg_str json) {
    return EOP_Homework_get_homework_id(json);
}

EOP_Homework_request EOP_Homework_Mapper_to_homework_request(struct mg_str json) {
    EOP_Homework_request request;
    request.task_id = EOP_Homework_get_task_id(json);
    request.student_ext_id = EOP_Homework_get_student_ext_id(json);
    request.answer_text = EOP_Homework_get_answer_text(json);
    request.type_answer_data_id = EOP_Homework_get_type_answer_data_id(json);
    return request;
}

EOP_Homework_update_request EOP_Homework_Mapper_to_homework_update_request(struct mg_str json){
    EOP_Homework_update_request update_request;
    update_request.id = EOP_Homework_get_homework_id(json);
    update_request.checked_teacher_ext_id = EOP_Homework_get_checked_teacher_ext_id(json);
    update_request.teacher_description = EOP_Homework_get_teacher_description(json);
    update_request.result_grade = EOP_Homework_get_result_grade(json);
    update_request.stat_id = EOP_Homework_get_stat_id(json);
    return update_request;
}

EOP_Homework_filter_request EOP_Homework_Mapper_to_homework_filter_request(struct mg_str json) {
    EOP_Homework_filter_request filter_request;
    filter_request.task_id = EOP_Homework_get_task_id(json);
    filter_request.student_ext_id = EOP_Homework_get_student_ext_id(json);
    filter_request.checked_teacher_ext_id = EOP_Homework_get_checked_teacher_ext_id(json);
    return filter_request;
}


char *EOP_Type_answer_data_to_json(EOP_Type_answer_data type_answer_data) {
    char buf[600];
    snprintf(buf, 600,
             "    {\n"
             "        \"id\": %ld,\n"
             "        \"type_name\": %s, \n"
             "        \"code_language\": %s\n"
             "    }",
             type_answer_data.id,
             type_answer_data.type_name,
             type_answer_data.code_language
    );
    char *json_string = malloc(strlen(buf) + 1);
    strcpy(json_string, buf);
    return json_string;
}

char *EOP_Type_answer_stat_to_json(EOP_Type_answer_stat type_answer_stat) {
    char buf[600];
    snprintf(buf, 600,
             "    {\n"
             "        \"id\": %ld,\n"
             "        \"status_name\": %s\n"
             "    }",
             type_answer_stat.id,
             type_answer_stat.status_name
    );
    char *json_string = malloc(strlen(buf) + 1);
    strcpy(json_string, buf);
    return json_string;
}

char *EOP_Homework_Mapper_to_json_full(EOP_Homework homework) {
    char buf[1000];
    snprintf(buf, 1000,
             "    {\n"
             "        \"id\": %ld,\n"
             "        \"task_id\": %d,\n"
             "        \"student_ext_id\": %s, \n"
             "        \"answer_text\": %s,\n"
             "        \"download_date\": %s,\n"
             "        \"last_upd_date\": \"%s,\n"
             "        \"checked_teacher_ext_id\": \"%s,\n"
             "        \"teacher_description\": \"%s,\n"
             "        \"result_grade\": \"%d,\n"
             "        \"type_answer_data\": \"%s,\n"
             "        \"type_answer_stat\": \"%s\n"
             "    }",
             homework.id,
             homework.task_id,
             homework.student_ext_id,
             homework.answer_text,
             homework.download_date,
             homework.last_upd_date,
             homework.checked_teacher_ext_id,
             homework.teacher_description,
             homework.result_grade,
             EOP_Type_answer_data_to_json(homework.type_answer_data),
             EOP_Type_answer_stat_to_json(homework.type_answer_stat)
    );
    char *json_string = malloc(strlen(buf) + 1);
    strcpy(json_string, buf);
    return json_string;
}

char *EOP_Homework_Mapper_to_json(EOP_Homework homework) {
    char buf[1000];
    snprintf(buf, 1000,
             "    {\n"
             "        \"id\": %ld,\n"
             "        \"task_id\": %d,\n"
             "        \"student_ext_id\": %s, \n"
             "        \"answer_text\": %s,\n"
             "        \"download_date\": %s,\n"
             "        \"last_upd_date\": \"%s,\n"
             "        \"checked_teacher_ext_id\": \"%s,\n"
             "        \"teacher_description\": \"%s,\n"
             "        \"result_grade\": \"%d\n"
             "    }",
             homework.id,
             homework.task_id,
             homework.student_ext_id,
             homework.answer_text,
             homework.download_date,
             homework.last_upd_date,
             homework.checked_teacher_ext_id,
             homework.teacher_description,
             homework.result_grade
    );
    char *json_string = malloc(strlen(buf) + 1);
    strcpy(json_string, buf);
    return json_string;
}