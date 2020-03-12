#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "mld.h"


char *DATA_TYPE[] = {"UINT8", "UINT32", "INT32",
                     "CHAR", "OBJ_PTR", "VOID_PTR", "FLOAT",
                     "DOUBLE", "OBJ_STRUCT"};

//dump info of one struct rec
void
print_struct_rec(struct_db_rec_t *struct_rec)
{
    printf("Enter print_struct_rec\n");
    //check if struct_rec valid
    //iterate record elements
    //iterate field elements
    if(struct_rec==NULL) return;

    printf("Struct name: %-14s, Size: %u, No of fields: %u\n", struct_rec->struct_name, struct_rec->ds_size, struct_rec->n_fields);

    field_info_t *curr_field = NULL;

    for(int i=0; i<struct_rec->n_fields; i++){
        curr_field = &struct_rec->fields[i];
        printf("Field name: %-15s, Size: %u, Offset: %u, Type: %s, Nested str name: %s\n",
               curr_field->fname, curr_field->size, curr_field->offset,
               DATA_TYPE[curr_field->dtype], curr_field->nested_str_name);
    }
}

//dump info of struct db
void
print_struct_db(struct_db_t *struct_db)
{
    printf("Enter print_struct_db\n");

	if(struct_db==NULL) return;

    struct_db_rec_t *curr_rec = struct_db->head;

    if(curr_rec==NULL){
            printf("curr_rec is null\n");
    }

    printf("Num of Struct Records: %u\n", struct_db->count);
    //for(int i=0; curr_rec!=NULL; i++, curr_rec=curr_rec->next){
    //    print_struct_rec(curr_rec);
        int i=0;
        while(curr_rec){
        printf("\n\nstructure No : %d (%p)\n", i++, curr_rec);
        print_struct_rec(curr_rec);
        curr_rec = curr_rec->next;
        }

}

//add struct to struct db
int //return -1 on fail, 0 otherwise
add_struct_to_struct_db(struct_db_t *struct_db, struct_db_rec_t *struct_rec)
{
    printf("Enter add_struct_to_struct_db\n");
    if(!struct_db || !struct_rec){
        printf("add_struct_to_struct_db invalid args\n");
    }
    //struct_db->head and head
    //head points to where struct_db->head did, but it dies with the function
    struct_db_rec_t *head = struct_db->head;

    if(head==NULL){
        struct_db->head = struct_rec;
        struct_rec->next = NULL;
        struct_db->count++;
        return 0;
    }
    //insert it as "first" element
    struct_rec->next = head;
    struct_db->head = struct_rec;
    struct_db->count++;
    return 0;
}


//function must return pointer to the structure record corresponding to the structure name passed as 2nd arg
//if record not found, return NULL

static struct_db_rec_t*
struct_db_look_up(struct_db_t *struct_db, char *struct_name)
{
    //check if linked list empty
    //iterate through list and compare keys against 2nd arg
    struct_db_rec_t *head = struct_db->head;
    if(head==NULL){
        return NULL;
    }

    for(; head; head=head->next){
        if(strncmp(head->struct_name, struct_name, MAX_STRUCTURE_NAME_SIZE)==0)
            return head;
    }
    return NULL;
}







