#include <EOP/homework/db/dao/EOP_Homework_dao.h>
#include <EOP/homework/db/tables/EOP_Homework.h>

static bool EOP_Homework_is_ok(int rc) {
    return rc == SQLITE_OK;
}


EOP_Homework_err_code EOP_Homework_create_homework_tb(sqlite3 *db, char **err_msg) {
    return sqlite3_exec(db, EOP_Homework_Table_create, 0, 0, err_msg);
}

EOP_Homework_err_code EOP_Homework_create_type_answer_data_tb(sqlite3 *db, char **err_msg) {
    return sqlite3_exec(db, EOP_Type_Answer_Data_Table_create, 0, 0, err_msg);
}

EOP_Homework_err_code EOP_Homework_create_type_answer_stat_tb(sqlite3 *db, char **err_msg) {
    return sqlite3_exec(db, EOP_Type_Answer_Stat_Table_create, 0, 0, err_msg);
}

EOP_Homework_err_code EOP_Homework_init_type_answer_data(sqlite3 *db, char **err_msg) {
    return sqlite3_exec(db, EOP_Type_Answer_Data_Table_init, 0, 0, err_msg);
}

EOP_Homework_err_code EOP_Homework_init_type_answer_stat(sqlite3 *db, char **err_msg) {
    return sqlite3_exec(db, EOP_Type_Answer_Stat_Table_init, 0, 0, err_msg);
}

EOP_Homework_err_code EOP_Homework_Dao_create() {
    sqlite3 *db;
    char *err_msg = 0;
    int rc = sqlite3_open("homework.db", &db);
    if (!EOP_Homework_is_ok(rc)) {
        sqlite3_close(db);
        return 1;
    }
    rc = EOP_Homework_create_type_answer_data_tb(db, &err_msg);
    if (!EOP_Homework_is_ok(rc)) {
        printf("SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        return 1;
    }
    rc = EOP_Homework_create_type_answer_stat_tb(db, &err_msg);
    if (!EOP_Homework_is_ok(rc)) {
        printf("SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        return 1;
    }
    rc = EOP_Homework_create_homework_tb(db, &err_msg);
    if (!EOP_Homework_is_ok(rc)) {
        printf("SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        return 1;
    }
    sqlite3_close(db);
    return 0;
}

EOP_Homework_err_code EOP_Homework_Dao_init_data() {
    sqlite3 *db;
    char *err_msg = 0;
    int rc = sqlite3_open("homework.db", &db);
    if (!EOP_Homework_is_ok(rc)) {
        sqlite3_close(db);
        return 1;
    }
    rc = EOP_Homework_init_type_answer_data(db, &err_msg);
    if (!EOP_Homework_is_ok(rc)) {
        printf("SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        return 1;
    }
    rc = EOP_Homework_init_type_answer_stat(db, &err_msg);
    if (!EOP_Homework_is_ok(rc)) {
        printf("SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        return 1;
    }
    sqlite3_close(db);
    return 0;
}

static int EOP_Homework_check_error(int rc, sqlite3 *db) {
    if (rc != SQLITE_DONE) {
        printf("SQL error");
        sqlite3_free(0);
        sqlite3_close(db);
        return 1;
    }
    return 0;
}

static EOP_Homework EOP_Homework_Mapper_to_homework(sqlite3_stmt *stmt) {
    EOP_Homework homework;
    homework.id = sqlite3_column_int(stmt, 0);
    homework.task_id = sqlite3_column_int(stmt, 1);
    homework.student_ext_id = (const char *)sqlite3_column_text(stmt, 2);
    homework.answer_text = (const char *)sqlite3_column_text(stmt, 3);
    homework.download_date = (const char *)sqlite3_column_text(stmt, 4);
    homework.last_upd_date = (const char *)sqlite3_column_text(stmt, 5);
    homework.checked_teacher_ext_id = (const char *)sqlite3_column_text(stmt, 6);
    homework.teacher_description = (const char *)sqlite3_column_text(stmt, 7);
    homework.result_grade = sqlite3_column_int(stmt, 8);
    return homework;
}

static EOP_Type_answer_data EOP_Homework_Mapper_to_type_answer_data(sqlite3_stmt *stmt) {
    EOP_Type_answer_data type_answer_data;
    type_answer_data.id = sqlite3_column_int(stmt, 9);
    type_answer_data.type_name = (const char *)sqlite3_column_text(stmt, 10);
    type_answer_data.code_language = (const char *)sqlite3_column_text(stmt, 11);
    return type_answer_data;
}

static EOP_Type_answer_stat EOP_Homework_Mapper_to_type_answer_stat(sqlite3_stmt *stmt) {
    EOP_Type_answer_stat type_answer_stat;
    type_answer_stat.id = sqlite3_column_int(stmt, 12);
    type_answer_stat.status_name = (const char *)sqlite3_column_text(stmt, 13);
    return type_answer_stat;
}

static EOP_Homework EOP_Homework_Mapper_to_homework_full(sqlite3_stmt *stmt) {
    EOP_Homework homework = EOP_Homework_Mapper_to_homework(stmt);
    homework.type_answer_data = EOP_Homework_Mapper_to_type_answer_data(stmt);
    homework.type_answer_stat = EOP_Homework_Mapper_to_type_answer_stat(stmt);
    return homework;
}

char *EOP_Homework_Dao_get_homework_by_id(EOP_Homework_id homework_id) {
    sqlite3 *db;
    int rc = sqlite3_open("homework.db", &db);
    if (!EOP_Homework_is_ok(rc)) {
        sqlite3_close(db);
        return NULL;
    }

    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(db,
                       "SELECT h.id, h.task_id, h.student_ext_id, h.answer_text, h.download_date, "
                               "h.last_upd_date, h.checked_teacher_ext_id, h.teacher_description, h.result_grade,"
                               " td.id, td.type_name, td.code_language, sd.id, sd.status_name \n"
                            "FROM homework h\n"
                            "LEFT JOIN  type_answer_data td on h.fk_type_answer_data_id = td.id \n"
                            "LEFT JOIN  type_answer_stat sd on h.fk_type_answer_stat_id = sd.id \n"
                            "WHERE h.id = ?1",
                       -1, &stmt, 0);
    sqlite3_bind_int(stmt, 1, (int)homework_id);

    rc = sqlite3_step(stmt);
    char *response = malloc(sizeof(char) * 10000);
    while (rc == SQLITE_ROW) {
        EOP_Homework homework = EOP_Homework_Mapper_to_homework_full(stmt);
        strcat(response, EOP_Homework_Mapper_to_json_full(homework));
        rc = sqlite3_step(stmt);
    }
    sqlite3_finalize(stmt);
    if (EOP_Homework_check_error(rc, db) == 1) return NULL;
    sqlite3_close(db);
    return response;
}

char *EOP_Homework_Dao_save_homework(EOP_Homework_request request) {
    sqlite3 *db;
    int rc = sqlite3_open("homework.db", &db);
    if (!EOP_Homework_is_ok(rc)) {
        sqlite3_close(db);
        return NULL;
    }

    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(db,
                       "INSERT INTO homework (task_id, student_ext_id, answer_text, fk_type_answer_data_id, fk_type_answer_stat_id) "
                       "VALUES (?, ?, ?, ?, 1)",
                       -1, &stmt, 0);
    sqlite3_bind_int(stmt, 1, request.task_id);
    sqlite3_bind_text(stmt, 2, request.student_ext_id, -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, request.answer_text, -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 4, request.type_answer_data_id);

    rc = sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    sqlite3_int64 homework_id = sqlite3_last_insert_rowid(db);
    if (EOP_Homework_check_error(rc, db) == 1) return NULL;
    sqlite3_close(db);
    return EOP_Homework_Dao_get_homework_by_id(homework_id);
}

char *EOP_Homework_Dao_update_homework(EOP_Homework_update_request update_request) {
    sqlite3 *db;
    int rc = sqlite3_open("homework.db", &db);
    if (!EOP_Homework_is_ok(rc)) {
        sqlite3_close(db);
        return NULL;
    }

    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(db,
                       "UPDATE homework SET checked_teacher_ext_id = ?, teacher_description = ?, "
                       "result_grade = ?, fk_type_answer_stat_id = ? WHERE id = ?",
                       -1, &stmt, 0);
    sqlite3_bind_text(stmt, 1, update_request.checked_teacher_ext_id, -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, update_request.teacher_description, -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 3, update_request.result_grade);
    sqlite3_bind_int(stmt, 4, (int)update_request.stat_id);
    sqlite3_bind_int(stmt, 5, update_request.id);

    rc = sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    if (EOP_Homework_check_error(rc, db) == 1) return NULL;
    sqlite3_close(db);
    return EOP_Homework_Dao_get_homework_by_id(update_request.id);
}

EOP_Homework_err_code EOP_Homework_Dao_delete_homework(EOP_Homework_id homework_id) {
    sqlite3 *db;
    int rc = sqlite3_open("homework.db", &db);
    if (!EOP_Homework_is_ok(rc)) {
        sqlite3_close(db);
        return 1;
    }

    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(db,
                       "DELETE FROM homework WHERE id = ?",
                       -1, &stmt, 0);
    sqlite3_bind_int(stmt, 1, homework_id);

    rc = sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    if (EOP_Homework_check_error(rc, db) == 1) return 1;
    sqlite3_close(db);
    return 0;
}

char *EOP_Homework_Dao_get_homework_list() {
    sqlite3 *db;
    int rc = sqlite3_open("homework.db", &db);
    if (!EOP_Homework_is_ok(rc)) {
        sqlite3_close(db);
        return NULL;
    }
    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(db, "SELECT id, task_id, student_ext_id, answer_text, download_date, "
                           "last_upd_date, checked_teacher_ext_id, teacher_description, result_grade\n"
                           "FROM homework",
                       -1, &stmt, 0);

    rc = sqlite3_step(stmt);
    char *response = malloc(sizeof(char) * 10000);
    strcat(response, "[\n");
    while (rc == SQLITE_ROW) {
        EOP_Homework homework = EOP_Homework_Mapper_to_homework(stmt);
        strcat(response, EOP_Homework_Mapper_to_json(homework));
        rc = sqlite3_step(stmt);
        if (rc == SQLITE_ROW) {
            strcat(response, ",\n");
        }
    }
    strcat(response, "\n]");
    sqlite3_finalize(stmt);
    if (EOP_Homework_check_error(rc, db) == 1) return "";
    sqlite3_close(db);
    return response;
}

char *EOP_Homework_Dao_get_homework_list_filter(EOP_Homework_filter_request filter_request) {
    sqlite3 *db;
    int rc = sqlite3_open("homework.db", &db);
    if (!EOP_Homework_is_ok(rc)) {
        sqlite3_close(db);
        return NULL;
    }
    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(db, "SELECT h.id, h.task_id, h.student_ext_id, h.answer_text, h.download_date, "
                           "h.last_upd_date, h.checked_teacher_ext_id, h.teacher_description, h.result_grade,"
                           " td.id, td.type_name, td.code_language, sd.id, sd.status_name \n"
                           "FROM homework h\n"
                           "LEFT JOIN  type_answer_data td on h.fk_type_answer_data_id = td.id \n"
                           "LEFT JOIN  type_answer_stat sd on h.fk_type_answer_stat_id = sd.id \n"
                           "WHERE (?1 = -1 OR ?1 = h.task_id)\n"
                           "  AND (?2 IS NULL OR ?2 = h.student_ext_id)\n"
                           "  AND (?3 IS NULL OR ?3 = h.checked_teacher_ext_id)\n",
                       -1, &stmt, 0);
    sqlite3_bind_int(stmt, 1, filter_request.task_id);
    sqlite3_bind_text(stmt, 2, filter_request.student_ext_id, -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, filter_request.checked_teacher_ext_id, -1, SQLITE_TRANSIENT);

    rc = sqlite3_step(stmt);
    char *response = malloc(sizeof(char) * 10000);
    strcat(response, "[\n");
    while (rc == SQLITE_ROW) {
        EOP_Homework homework = EOP_Homework_Mapper_to_homework_full(stmt);
        strcat(response, EOP_Homework_Mapper_to_json_full(homework));
        rc = sqlite3_step(stmt);
        if (rc == SQLITE_ROW) {
            strcat(response, ",\n");
        }
    }
    strcat(response, "\n]");
    sqlite3_finalize(stmt);
    if (EOP_Homework_check_error(rc, db) == 1) return "";
    sqlite3_close(db);
    return response;
}

char *EOP_Homework_Dao_get_type_answer_data_list() {
    sqlite3 *db;
    int rc = sqlite3_open("homework.db", &db);
    if (!EOP_Homework_is_ok(rc)) {
        sqlite3_close(db);
        return NULL;
    }
    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(db, "SELECT id, type_name, code_language\n"
                           "FROM type_answer_data",
                       -1, &stmt, 0);

    rc = sqlite3_step(stmt);
    char *response = malloc(sizeof(char) * 10000);
    strcat(response, "[\n");
    while (rc == SQLITE_ROW) {
        EOP_Type_answer_data typeAnswerData;
        typeAnswerData.id = sqlite3_column_int(stmt, 0);
        typeAnswerData.type_name = (const char *)sqlite3_column_text(stmt, 1);
        typeAnswerData.code_language = (const char *)sqlite3_column_text(stmt, 2);
        strcat(response, EOP_Type_answer_data_to_json(typeAnswerData));
        rc = sqlite3_step(stmt);
        if (rc == SQLITE_ROW) {
            strcat(response, ",\n");
        }
    }
    strcat(response, "\n]");
    sqlite3_finalize(stmt);
    if (EOP_Homework_check_error(rc, db) == 1) return "";
    sqlite3_close(db);
    return response;
}