#ifndef _DICTIONARY_H_
#define _DICTIONARY_H_

typedef struct{
    char** keys;
    void** datas;
    size_t len;
} dictionary;

dictionary* dic_create();
void dic_append(dictionary* dic, char* key, void* data);
void dic_update(dictionary* dic, char* key, void* new);
void* dic_get_data(dictionary* dic, char* key);
void dic_destroy(dictionary* dic);

#endif
