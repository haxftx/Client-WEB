#include "helpers.h"

void print_books(char *str) {
// afiseaza cartile
	JSON_Value *value;
    JSON_Array *list;
	JSON_Object *obj;
    value = json_parse_string(str);
    list = json_value_get_array(value);
	if (!list) {
		printf("Error : Not a list of JSON\n");
		return;
	}
	if (json_array_get_count(list) == 0) {
		printf("Not books in the library\n");
	} else printf("Books in the library\n");
	for (size_t i = 0 ; i < json_array_get_count(list); i++) {
		obj = json_array_get_object(list, i);
		printf("id\t%d\t", (int)json_object_get_number(obj, "id"));
		printf("title\t%s\n", json_object_get_string(obj, "title"));
	}
	json_value_free(value);
}

void print_book(char *str) {
// afiseaza o carte
	JSON_Value *value;
    JSON_Object *obj;
    value = json_parse_string(str);
    obj = json_value_get_object(value);
    printf("title\t%s\n", json_object_get_string(obj, "title"));
	printf("author\t%s\n", json_object_get_string(obj, "author"));
	printf("genre\t%s\n", json_object_get_string(obj, "genre"));
	printf("publisher\t%s\n", json_object_get_string(obj, "publisher"));
	printf("page_count\t%d\n", (int)json_object_get_number(obj, "page_count"));
	json_value_free(value);
}

void print_error(char *str) {
// afiseaza eroare
	JSON_Value *value;
    JSON_Object *obj;
    value = json_parse_string(str);
    obj = json_value_get_object(value);
    printf("Error : %s\n", json_object_get_string(obj, "error"));
	json_value_free(value);
}