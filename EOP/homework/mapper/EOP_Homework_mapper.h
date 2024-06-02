#ifndef EOP_EOP_HOMEWORK_MAPPER_H
#define EOP_EOP_HOMEWORK_MAPPER_H

#include <EOP/homework/EOP_Homework.h>
#include <third_party/mongoose.h>
#include <third_party/sqlite3.h>

#ifdef __cplusplus
extern "C" {
#endif

EOP_Homework_id EOP_Homework_Mapper_to_homework_id(struct mg_str json);

EOP_Homework_request EOP_Homework_Mapper_to_homework_request(struct mg_str json);

EOP_Homework_update_request EOP_Homework_Mapper_to_homework_update_request(struct mg_str json);

EOP_Homework_filter_request EOP_Homework_Mapper_to_homework_filter_request(struct mg_str json);

char *EOP_Homework_Mapper_to_json(EOP_Homework homework);

char *EOP_Homework_Mapper_to_json_full(EOP_Homework homework);

char *EOP_Type_answer_data_to_json(EOP_Type_answer_data typeAnswerData);

#ifdef __cplusplus
}
#endif

#endif //EOP_EOP_HOMEWORK_MAPPER_H
