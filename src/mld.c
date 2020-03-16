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

    printf("Struct name: %-14s, Size: %u, No of fields: %u\n",
           struct_rec->struct_name, struct_rec->ds_size,
           struct_rec->n_fields);

    field_info_t *curr_field = NULL;

    for(int i=0; i<struct_rec->n_fields; i++){
        curr_field = &struct_rec->fields[i];
        printf("Field name: %-15s, Size: %u, Offset: %u, Type: %s, \
               Nested str name: %s\n",
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
    for(int i=0; curr_rec!=NULL; i++, curr_rec=curr_rec->next){
        printf("\n\nStruct #%d (%p)\n", i, curr_rec);
        print_struct_rec(curr_rec);
    }
    printf("\n");
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


//function must return pointer to the structure record corresponding to the
//structure name passed as 2nd arg
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


void
print_obj_rec(obj_db_rec_t *obj_rec, int i){
    printf("Enter print_obj_rec\n");

    if(obj_rec==NULL) return;

    printf("%-3d ptr = %-10p, next = %-10p, units = %-4d, struct_name = %-10s, "
           "is_root = %s\n",
         i, obj_rec->ptr, obj_rec->next, obj_rec->units,
         obj_rec->struct_rec->struct_name, obj_rec->is_root ? "TRUE " : "FALSE");
}

void
print_obj_db(obj_db_t *obj_db){
    printf("Enter print_obj_db\n");

	if(obj_db==NULL) return;//maybe add some error msg

    obj_db_rec_t *curr_rec = obj_db->head;

    if(curr_rec==NULL){
            printf("curr_rec is null\n");
    }

    printf("Num of Obj Records: %u\n", obj_db->count);
    for(int i=0; curr_rec!=NULL; i++, curr_rec=curr_rec->next){
        printf("\n\nObject #%d (%p)\n", i, curr_rec);
        print_obj_rec(curr_rec, i);
    }
    printf("\n");
}



static obj_db_rec_t*
obj_db_look_up(obj_db_t *obj_db, void *ptr)
{
    printf("Enter obj_db_look_up\n");
    //check if list empty
    //iterate through list and compare rec key ptr against ptr
    //compare ptrs normally
    obj_db_rec_t *head = obj_db->head;
    if(head==NULL){
        printf("head==NULL\n");
        return NULL;
    }

    printf("here...\n");
    #if 0
        if(head->ptr == ptr){
            printf("return head;\n");
            //return head;
        }

    }
    #endif // 0for(; head; head->next){

    printf("head==NULL(2)\n");
    return NULL;
}

static void
add_obj_to_obj_db(obj_db_t *obj_db,
                  void* ptr,
                  int units,
                  struct_db_rec_t *struct_rec,
                  mld_boolean_t is_root)
{
    printf("Enter add_obj_to_obj_db\n");
    //from course: don't add same object twice
    obj_db_rec_t *obj_rec = obj_db_look_up(obj_db, ptr);
    if (obj_rec==NULL) printf("obj_rec is NULL\n");
    assert(!obj_rec);

    //allocate memory for a new obj record
    //fill the new record with function arguments
    //then like with struct, add record to linked list

    obj_rec = calloc(1, sizeof(obj_db_rec_t));

    obj_rec->next=NULL;
    obj_rec->ptr=ptr;
    obj_rec->struct_rec=struct_rec;
    obj_rec->units=units;
    obj_rec->is_visited = MLD_FALSE;
    obj_rec->is_root = is_root;

    obj_db_rec_t *head = obj_db->head;

    if(head==NULL){
        obj_rec->next=NULL;
        obj_db->head=obj_rec;
        obj_db->count++;
        return;
    }
    obj_rec->next=head;
    obj_db->head=obj_rec;
    obj_db->count++;
}

void *
xcalloc(obj_db_t *obj_db, char *struct_name, int units){
    //create obj using calloc
    //whatever it creates, add to obj db
    //insert new obj to obj db (add_obj_to_obj_db(pointer to obj db,
    //pointer to obj, units, pointer to struct rec)
    printf("Enter xcalloc\n");

    struct_db_rec_t *struct_rec = struct_db_look_up(obj_db->struct_db,
                                                    struct_name);
    assert(struct_rec);

    void *ptr = calloc(units, struct_rec->ds_size);

    add_obj_to_obj_db(obj_db, ptr, units, struct_rec, MLD_FALSE);

    return ptr;
}





static void print_obj_rec_data(obj_db_rec_t *obj_rec)
{
    printf("Ender print_obj_rec_data\n");

    //print object records data
    //objects of various types, therefore multiple print options...

    int n_fields = obj_rec->struct_rec->n_fields;
    int db_rec_size = obj_rec->struct_rec->ds_size;

    int units = obj_rec->units;
    int obj_index = 0, field_index = 0;

    field_info_t *curr_field = NULL;

    //iterate through objects
    for(obj_index = 0; obj_index < units; obj_index++)
    {
        //conversion to byte for pointer arithmetic
        //jump to next object record (same xcalloc) by adding db record size to offset
        //in simple terms - iterate through units
        char *curr_obj_ptr = (char *)(obj_rec->ptr) + (obj_index * db_rec_size);

        for(field_index = 0; field_index < n_fields; field_index++)
        {
            //iterate through db record fields
            curr_field = &obj_rec->struct_rec->fields[field_index];

            //printf struct name, obj index, field name, field data
            //TODO fix this massive bug
            switch(curr_field->dtype){
            case UINT8:
            case INT32:
            case UINT32:
                printf("%s[%u]->%s = %u\n", obj_rec->struct_rec->struct_name,
                       obj_index, curr_field->fname,
                       *(int*)(curr_obj_ptr + curr_field->offset));
                break;
            case CHAR:
                printf("%s[%u]->%s = %s\n", obj_rec->struct_rec->struct_name,
                       obj_index, curr_field->fname,
                       (char*)(curr_obj_ptr + curr_field->offset));
                break;
            case FLOAT:
            case DOUBLE:
                printf("%s[%u]->%s = %f\n", obj_rec->struct_rec->struct_name,
                       obj_index, curr_field->fname,
                       *(double*)(curr_obj_ptr + curr_field->offset));
                break;
            case OBJ_PTR:
                printf("%s[%u]->%s = %u\n", obj_rec->struct_rec->struct_name,
                       obj_index, curr_field->fname,
                       (void*)*(int*)(curr_obj_ptr + curr_field->offset));
                break;
            case OBJ_STRUCT:
                //TODO implement
                break;
            default:
                printf("ERROR: Unsupported data type.\n");
                break;
            }
        }
    }
}

void
print_obj_data(obj_db_t *obj_db){

    obj_db_rec_t *head = obj_db->head;

    for(; head; head = head->next){
            print_obj_rec_data(head);
    }
}






