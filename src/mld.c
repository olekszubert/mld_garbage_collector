#include<stdio.h>
#include<stdlib.h>
#include "mld.h"

#if 0
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
#endif

//dump info of one struct rec
void
print_struct_rec(struct_db_rec_t *struct_rec)
{
	

}

//dump info of struct db
void
print_struct_db(struct_db_t *struct_db)
{
	if(struct_db!=NULL){
		struct_db_rec_t *curr_rec = struct_db->head;
		//printf("%u", curr_rec->ds_size);
		/*printf("%s,\t%u,\t%u,\t%s,\t%u,\t%u,\t<data_type>,\t%s", curr_rec->struct_name, curr_rec->ds_size, 
				curr_rec->n_fields, curr_rec->field->fname, curr_rec->field->size, 
			       curr_rec->field->offset, curr_rec->field->nested_str_name);	
		*/
	}
}

//add struct to struct db
int //return -1 on fail, 0 otherwise
add_struct_to_struct_db(struct_db_t *struct_db, struct_db_rec_t *struct_rec)
{
	if(struct_db!=NULL){
		if(struct_db->head==NULL){
			struct_db->head=struct_rec;
		}
		else
		{
			struct_db_rec_t *curr_rec = 	
		}
	
	}
	else{
		return -1;
	}
	return 0;
}


//function must return pointer to the structure record corresponding to the structure name passed as 2nd arg
//if record not found, return NULL

struct_db_rec_t*
struct_db_look_up(struct_db_t *struct_db, char *struct_name)
{
	

	return 0;
}







