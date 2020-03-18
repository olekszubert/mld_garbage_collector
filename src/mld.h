#ifndef __MLD__
#define __MLD__

#include<assert.h>

#define MAX_STRUCTURE_NAME_SIZE 128
#define MAX_FIELD_NAME_SIZE 128

// address of element of a null structure is equal to its offset
#define OFFSET_OF(struct_name, fld_name) \
	(unsigned long)&(((struct_name *)0)->fld_name)

#define FIELD_SIZE(struct_name, fld_name) \
	sizeof(((struct_name *)0)->fld_name)

typedef enum {
	UINT8,
	UINT32,
	INT32,
	CHAR,
	FLOAT,
	DOUBLE,
    OBJ_PTR,
	OBJ_STRUCT
} data_type_t;

typedef enum{
    MLD_FALSE,
    MLD_TRUE
} mld_boolean_t;

//Structure to store info of one field of a C struct
typedef struct {
	char fname[MAX_FIELD_NAME_SIZE];
	unsigned int size;
	unsigned int offset;
	data_type_t dtype;
	char nested_str_name[MAX_STRUCTURE_NAME_SIZE];//for dtype=OBJ_PTR or OBJ_STRUCT
} field_info_t;

/*Structure definitions*/
//Structure to store info of on C struct with n fields
typedef struct _struct_db_rec{
	struct _struct_db_rec *next;	//pointer to next struct - linked list
	char struct_name[MAX_STRUCTURE_NAME_SIZE]; //key
	unsigned int ds_size;	//size of struct
	unsigned int n_fields;	//n of fields in struct
	field_info_t *fields;	//pointer to array of fields
}struct_db_rec_t;

//Head of linked list representing the struct db
typedef struct _struct_db{
	struct_db_rec_t *head;
	unsigned int count;
} struct_db_t;

/*Object definitions*/
typedef struct _obj_db_rec{
    struct _obj_db_rec *next;
    void *ptr; //key
    unsigned int units; //num of units of obj that has been malloced (for continuous mem alloc)
    struct_db_rec_t *struct_rec; //pointer to struct rec that object is init'd based on
    mld_boolean_t is_visited; /*Used for Graph traversal*/
    mld_boolean_t is_root;    /*Is this object is Root object*/
}obj_db_rec_t;

typedef struct {
    struct_db_t *struct_db; //model after struct db
    obj_db_rec_t *head;
    unsigned int count;
} obj_db_t;


//Structure Registration helping APIs
//# operator converts anything after it into a string
#define FIELD_INFO(struct_name, fld_name, dtype, nested_struct_name)	\
	{#fld_name, dtype, FIELD_SIZE(struct_name, fld_name), 		\
	OFFSET_OF(struct_name, fld_name), #nested_struct_name}


//pointer to database, name of structure, pointer to array that stores fields info
//create new struct db record
//find size of structure db rec and n_fields
//link with fields array
//add struct db rec to struct db
#define REG_STRUCT(struct_db, st_name, fields_arr)				\
	do{									\
		struct_db_rec_t *rec = calloc(1, sizeof(struct_db_rec_t)); 	\
		strncpy(rec->struct_name, #st_name, MAX_STRUCTURE_NAME_SIZE);	\
		rec->ds_size = sizeof(st_name);					\
		rec->n_fields = sizeof(fields_arr)/sizeof(field_info_t);	\
		rec->fields = fields_arr;					\
		if(add_struct_to_struct_db(struct_db, rec)){			\
			assert(0);						\
		}								\
	}while(0);


//Printing functions
void print_struct_rec(struct_db_rec_t *struct_rec);
void print_struct_db(struct_db_t *struct_db);
void print_obj_rec(obj_db_rec_t *obj_rec, int i);
void print_obj_db(obj_db_t *obj_db);
void print_obj_data(obj_db_t *obj_db);

//---
int add_struct_to_struct_db(struct_db_t *struct_db,
                            struct_db_rec_t *struct_rec);

// emp_t *emp = xcalloc(object_db, "emp_t", 1);
//allocate 'units' of units of memory for object of type "stuct_name"
//create the obj record for new allocated object and add the obj record to db
//link the object record with struc record for struct "struct_name"
//return pointer to the allocated object
//allocate memory and create internal data structure in MLD lib so
//MLD can keep track of allocated objects
void* xcalloc(obj_db_t *obj_db, char *struct_name, int units);
void xfree(obj_db_t *obj_db, void *ptr);





/* MLD */









#endif /* __MLD__ */

