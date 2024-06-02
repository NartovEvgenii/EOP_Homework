#ifndef EOP_EOP_HOMEWORK_TABLE_H
#define EOP_EOP_HOMEWORK_TABLE_H

#define HOMEWORK "homework"
#define TYPE_ANSWER_DATA "type_answer_data"
#define TYPE_ANSWER_STAT "type_answer_stat"

#ifdef __cplusplus
extern "C" {
#endif

char *EOP_Type_Answer_Data_Table_create = "CREATE TABLE IF NOT EXISTS " TYPE_ANSWER_DATA " (\n"
                                          "    id INTEGER PRIMARY KEY AUTOINCREMENT,\n"
                                          "    type_name TEXT,\n"
                                          "    code_language TEXT\n"
                                          ")";

char *EOP_Type_Answer_Stat_Table_create = "CREATE TABLE IF NOT EXISTS " TYPE_ANSWER_STAT " (\n"
                                          "    id INTEGER PRIMARY KEY AUTOINCREMENT,\n"
                                          "    status_name TEXT\n"
                                          ")";

char *EOP_Homework_Table_create = "CREATE TABLE IF NOT EXISTS " HOMEWORK " (\n"
                                    "    id INTEGER PRIMARY KEY AUTOINCREMENT,\n"
                                    "    task_id INTEGER,\n"
                                    "    student_ext_id TEXT,\n"
                                    "    answer_text TEXT,\n"
                                    "    download_date DATE DEFAULT (datetime('now','localtime')),"
                                    "    last_upd_date DATE DEFAULT (datetime('now','localtime')),"
                                    "    checked_teacher_ext_id TEXT,\n"
                                    "    teacher_description TEXT,\n"
                                    "    result_grade INTEGER,\n"
                                    "    fk_type_answer_stat_id INTEGER,\n"
                                    "    fk_type_answer_data_id INTEGER,\n"
                                    "    FOREIGN KEY (fk_type_answer_data_id)  REFERENCES " TYPE_ANSWER_DATA " (id)"
                                    "    FOREIGN KEY (fk_type_answer_stat_id)  REFERENCES " TYPE_ANSWER_STAT " (id)"
                                    ")";

char *EOP_Type_Answer_Data_Table_init = "INSERT OR IGNORE INTO " TYPE_ANSWER_DATA " (id, type_name, code_language)\n"
                                          " VALUES (1, 'Java 1.8', 'JAVA'),\n"
                                          " (2, 'C++ 11', 'CPP'),\n"
                                          " (3, 'Python 3.12.0', 'PYTHON')\n"
                                          ;

char *EOP_Type_Answer_Stat_Table_init = "INSERT OR IGNORE INTO " TYPE_ANSWER_STAT " (id, status_name)\n"
                                        " VALUES (1, 'Загружено'),\n"
                                        "(2, 'Ожидает проверки'),\n"
                                        "(3, 'Оценено')\n";

#ifdef __cplusplus
}
#endif


#endif //EOP_EOP_HOMEWORK_TABLE_H
