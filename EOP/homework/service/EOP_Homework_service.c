#include <EOP/homework/db/dao/EOP_Homework_dao.h>
#include <EOP/homework/service/EOP_Homework_service.h>

static int EOP_Homework_validate_homework_id(EOP_Homework_id homework_id) {
    if (homework_id < 1) {
        printf("incorrect task_id");
        return 1;
    }
    return 0;
}

static int EOP_Homework_validate_task_id(EOP_Homework_task_id task_id) {
    if (task_id < 1) {
        printf("incorrect task_id");
        return 1;
    }
    return 0;
}

static int EOP_Homework_validate_student_ext_id(EOP_Homework_student_ext_id student_ext_id) {
    if (strlen(student_ext_id) < 1) {
        printf("incorrect student_ext_id");
        return 1;
    }
    return 0;
}

static int EOP_Homework_validate_answer_text(EOP_Homework_answer_text answer_text) {
    if (strlen(answer_text) < 1) {
        printf("incorrect answer_text");
        return 1;
    }
    return 0;
}

static int EOP_Homework_validate_type_answer_data_id(EOP_Type_answer_data_id type_answer_data_id) {
    if (type_answer_data_id < 1) {
        printf("incorrect type_answer_data_id");
        return 1;
    }
    return 0;
}

static int EOP_Homework_validate_answer_stat_id(EOP_Type_answer_stat_id answer_stat_id) {
    if (answer_stat_id < 1) {
        printf("incorrect answer_stat_id");
        return 1;
    }
    return 0;
}

static int EOP_Homework_validate_result_grade(EOP_Homework_result_grade result_grade) {
    if (result_grade < 1 || result_grade > 100) {
        printf("incorrect result_grade");
        return 1;
    }
    return 0;
}

static int EOP_Homework_validate_homework(EOP_Homework_request request) {
    if (EOP_Homework_validate_task_id(request.task_id) == 1) return 1;
    if (EOP_Homework_validate_student_ext_id(request.student_ext_id) == 1) return 1;
    if (EOP_Homework_validate_answer_text(request.answer_text) == 1) return 1;
    if (EOP_Homework_validate_type_answer_data_id(request.type_answer_data_id) == 1) return 1;
    return 0;
}

static int EOP_Homework_validate_update_homework(EOP_Homework_update_request update_request) {
    if (EOP_Homework_validate_homework_id(update_request.id) == 1) return 1;
    if (EOP_Homework_validate_answer_stat_id(update_request.stat_id) == 1) return 1;
    if (EOP_Homework_validate_result_grade(update_request.result_grade) == 1) return 1;
    return 0;
}

char *EOP_Homework_Service_save_homework(EOP_Homework_request request) {
    if (EOP_Homework_validate_homework(request) == 1) return NULL;
    char * result = EOP_Homework_Dao_save_homework(request);
    printf("homework saved\n");
    return result;
}

char *EOP_Homework_Service_get_homework_list() {
    printf("Getting homework list\n");
    return EOP_Homework_Dao_get_homework_list();
}

char *EOP_Homework_Service_get_homework_list_filter(EOP_Homework_filter_request filter_request) {
    printf("Getting homework list filter\n");
    return EOP_Homework_Dao_get_homework_list_filter(filter_request);
}

char *EOP_Homework_Service_get_homework_by_id(EOP_Homework_id homework_id) {
    if (EOP_Homework_validate_homework_id(homework_id) == 1) return NULL;
    printf("Getting homework\n");
    return EOP_Homework_Dao_get_homework_by_id(homework_id);
}

char *EOP_Homework_Service_update_homework(EOP_Homework_update_request update_request) {
    if (EOP_Homework_validate_update_homework(update_request) == 1) return NULL;
    char * result = EOP_Homework_Dao_update_homework(update_request);
    printf("homework updated\n");
    return result;
}

EOP_Homework_err_code EOP_Homework_Service_delete_homework(EOP_Homework_id homework_id) {
    if (EOP_Homework_validate_homework_id(homework_id) == 1) return 1;
    printf("homework deleted\n");
    return EOP_Homework_Dao_delete_homework(homework_id);
}

char *EOP_Homework_Service_get_type_answer_data_list() {
    printf("Getting type_answer_data list\n");
    return EOP_Homework_Dao_get_type_answer_data_list();
}
