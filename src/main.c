#include<stdio.h>
#include<stdlib.h>

#define MAX_STRUCTURE_NAME_SIZE 128
#define MAX_FIELD_NAME_SIZE 128

#define OFFSET_OF(struct_name, fld_name) \
	(unsigned int)&(((struct_name *)0)->fld_name)

// address of element of a null structure is equal to its offset

#define FIELD_SIZE(struct_name, fld_name) \
	sizeof(((struct_name *)0)->fld_name)

typedef struct _struct_db_rec_struct struct_db_rec_t;

typedef enum {
	UINT8,
	UINT32,
	INT32,
	CHAR,
	OBJ_PTR,
	FLOAT,
	DOUBLE,
	OBJ_STRUCT
} data_type_t;

typedef struct _field_info_{
	char fname[MAX_FIELD_NAME_SIZE];
	unsigned int size;
	unsigned int offset;
	data_type_t dtype;
	char nested_str_name[MAX_STRUCTURE_NAME_SIZE];
} field_info_t;

struct _struct_db_rec_{
	struct_db_rec_t *next;
	char struct_name[MAX_STRUCTURE_NAME_SIZE]; //key
	unsigned int ds_size;
	unsigned int n_fields;
	field_info_t *field;
};

typedef struct emp_ {
	char emp_name[30];
	unsigned int emp_id;
	unsigned int age;
	struct emp_ *mgr;
	float salary;
} emp_t;

field_info_t fields[20];

void print_size_and_offset(emp_t *emp)
{
	/*fields[0].size = sizeof(emp->emp_name);
	fields[0].offset = 0;
	fields[1].size = sizeof(emp->emp_id);
	fields[1].offset = (unsigned int)((unsigned int)&emp->emp_id - (unsigned int)emp);
	printf("size0: %u\n", fields[0].size);
	printf("addr_t: %u\n", (unsigned int)emp);
	printf("addr1 : %u\n", (unsigned int)&emp->emp_id);
	printf("offset1: %u\n", fields[1].offset);*/

	
	/** My solution to assignment */
	/*printf("Size  : %u\n", (unsigned int)sizeof(emp->emp_name));
	printf("Offset: %u\n", (unsigned int)emp->emp_name - (unsigned int)emp);
	
	printf("Size  : %u\n", (unsigned int)sizeof(emp->emp_id));
	printf("Offset: %u\n", (unsigned int)&emp->emp_id - (unsigned int)emp);
	
	printf("Size  : %u\n", (unsigned int)sizeof(emp->age));
	printf("Offset: %u\n", (unsigned int)&emp->age - (unsigned int)emp);
	
	printf("Size  : %u\n", (unsigned int)sizeof(emp->mgr));
	printf("Offset: %u\n", (unsigned int)&emp->mgr - (unsigned int)emp);
	
	printf("Size  : %u\n", (unsigned int)sizeof(emp->salary));
	printf("Offset: %u\n", (unsigned int)&emp->salary - (unsigned int)emp);
	*/





}

typedef struct _student {
	char stud_name[32];
	int rollno;
	int age;
}student_t;

student_t student_array[20];

int main(void)
{
	printf("Program Start\n");
	emp_t my_emp;
	print_size_and_offset(&my_emp);
	printf("Program Stop\n");
	return 0;
}
