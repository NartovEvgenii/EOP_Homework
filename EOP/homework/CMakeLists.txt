add_library(EOP_Homework
        EOP_Homework.c
        EOP_Homework.h
        controller/EOP_Homework_controller.c
        controller/EOP_Homework_controller.h
        mapper/EOP_Homework_mapper.c
        mapper/EOP_Homework_mapper.h
        db/tables/EOP_Homework_table.c
        db/tables/EOP_Homework_table.h
        db/dao/EOP_Homework_dao.c
        db/dao/EOP_Homework_dao.h
        service/EOP_Homework_service.c
        service/EOP_Homework_service.h
)

target_include_directories(EOP_Homework PUBLIC ${CMAKE_SOURCE_DIR})
