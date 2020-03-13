#include "mld.h"
#include <memory.h>
#include <stdlib.h>
#include <stdio.h>

//Application Structures

typedef struct emp_ {
	char emp_name[30];
	unsigned int emp_id;
	unsigned int age;
	struct emp_ *mgr;
	float salary;
} emp_t;

typedef struct student_ {
	char stud_name[32];
	unsigned int rollno;
	unsigned int age;
	float aggregate;
	struct student_ *best_colleage;
} student_t;

int
main(int argc, char **argv){
	printf("Main\n");

	//Init a new structure database
	struct_db_t *struct_db = calloc(1, sizeof(struct_db_t));
	if(struct_db==NULL){
        printf("struct_db calloc failed");
        return 0;
	}

	//Create structure record for structure emp_t
	static field_info_t emp_fields[] = {
		FIELD_INFO(emp_t, emp_name, CHAR, 0),
		FIELD_INFO(emp_t, emp_id, UINT32, 0),
		FIELD_INFO(emp_t, age, UINT32, 0),
		FIELD_INFO(emp_t, mgr, OBJ_PTR, emp_t),
		FIELD_INFO(emp_t, salary, FLOAT, 0)
	};
	REG_STRUCT(struct_db, emp_t, emp_fields);

	static field_info_t stud_fields[] = {
		FIELD_INFO(student_t, stud_name, CHAR, 0),
		FIELD_INFO(student_t, rollno, UINT32, 0),
		FIELD_INFO(student_t, age, UINT32, 0),
		FIELD_INFO(student_t, aggregate, FLOAT, 0),
		FIELD_INFO(student_t, best_colleage, OBJ_PTR, student_t)
	};
	REG_STRUCT(struct_db, student_t, stud_fields);

	print_struct_db(struct_db);





    //init a new obj db
    obj_db_t *obj_db = calloc(1, sizeof(obj_db_t));
	if(obj_db==NULL){
        printf("obj_db calloc failed");
        return 0;
	}
    //associate obj_db with one struct_db
    obj_db->struct_db = struct_db;

    //create some sample objs, equivalent to standard
    student_t *john = xcalloc(obj_db, "student_t", 1);
    john->age=25;
    john->aggregate=33.5;
    john->best_colleage=NULL;
    john->rollno=254;
    strncpy(john->stud_name, "John Williams", strlen("John Williams"));

    student_t *bob = xcalloc(obj_db, "student_t", 1);
    bob->age=24;
    bob->aggregate=35.5;
    bob->best_colleage=NULL;
    bob->rollno=253;
    strncpy(bob->stud_name, "Bob Willis", strlen("Bob Willis"));

    emp_t *rick = xcalloc(obj_db, "emp_t", 2);

    print_obj_db(obj_db);

    print_obj_data(obj_db);

	return 0;
}
