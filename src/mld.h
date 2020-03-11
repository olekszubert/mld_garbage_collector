#ifndef __MLD__
#include<assert.h>

#define MAX_STRUCTURE_NAME_SIZE 128
#define MAX_FIELD_NAME_SIZE 128

#define OFFSET_OF(struct_name, fld_name) \
	(unsigned long)&(((struct_name *)0)->fld_name)

// address of element of a null structure is equal to its offset

#define FIELD_SIZE(struct_name, fld_name) \
	sizeof(((struct_name *)0)->fld_name)

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

//Structure to store info of one field of a C struct
typedef struct {
	char fname[MAX_FIELD_NAME_SIZE];
	unsigned int size;
	unsigned int offset;
	data_type_t dtype;
	char nested_str_name[MAX_STRUCTURE_NAME_SIZE];//for dtype=OBJ_PTR or OBJ_STRUCT
} field_info_t;

typedef struct _struct_db_rec struct_db_rec_t;

//Structure to store info of on C struct with n fields
struct _struct_db_rec{
	struct_db_rec_t *next;	//pointer to next struct - linked list
	char struct_name[MAX_STRUCTURE_NAME_SIZE]; //key
	unsigned int ds_size;	//size of struct
	unsigned int n_fields;	//n of fields in struct
	field_info_t *field;	//pointer to array of fields
};

//Head of linked list representing the struct db
typedef struct _struct_db{
	struct_db_rec_t *head;
	unsigned int count;
} struct_db_t;


//Printing functions
void
print_struct_rec (struct_db_rec_t *struct_rec);

void
print_struct_db(struct_db_t *struct_db);

//Func to add struct rec to a struct db
int
add_struct_to_struct_db(struct_db_t *struct_db, struct_db_rec_t *struct_rec);


//Structure Registration helping APIs

#define FIELD_INFO(struct_name, fld_name, dtype, nested_struct_name)	\
	{#fld_name, dtype, FIELD_SIZE(struct_name, fld_name), 		\
	OFFSET_OF(struct_name, fld_name), #nested_struct_name}

//# operator converts anything after it into a string

#define REG_STRUCT(struct_db, st_name, fields_arr)				\
	do{									\
		struct_db_rec_t *rec = calloc(1, sizeof(struct_db_rec_t)); 	\
		strncpy(rec->struct_name, #st_name, MAX_STRUCTURE_NAME_SIZE);	\
		rec->ds_size = sizeof(st_name);					\
		rec->n_fields = sizeof(fields_arr)/sizeof(field_info_t);	\
		rec->field = fields_arr;					\
		if(add_struct_to_struct_db(struct_db, rec)){			\
			assert(0);						\
		}								\
	}while(0);

//pointer to database, name of structure, pointer to array that stores fields info
//create new struct db record 
//find size of structure db rec and n_fields
//link with fields array
//add struct db rec to struct db

#endif /* __MLD__ */









