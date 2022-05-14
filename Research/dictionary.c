#include <stdlib.h>
#include "dictionary.h"
#include <string.h>

dictionary* dic_create(){
    dictionary* dic = malloc(sizeof(dictionary));
    dic->keys = NULL;
    dic->datas = NULL;
    dic->len = 0;
    return dic;
}

void dic_append(dictionary* dic, char* key, void* data){
    dic->keys = realloc(dic->keys,sizeof(long)*(dic->len+1));
    dic->keys[dic->len] = key;
    dic->datas = realloc(dic->datas,sizeof(long)*(dic->len+1));
    dic->datas[dic->len] = data;
    dic->len += 1;
}

void dic_update(dictionary* dic, char* key,void* new){
    size_t i = 0;
       while(i < dic->len && strcmp(dic->keys[i],key))
           ++i;
    free(dic->datas[i]);
    dic->datas[i] = new;
}

void* dic_get_data(dictionary* dic, char* key){
    size_t i = 0;
    while(i < dic->len && strcmp(dic->keys[i],key))
        ++i;
    if(i == dic->len)
        return NULL;
    return dic->datas[i];
}

void dic_destroy(dictionary* dic){
    for(size_t i=0; i<dic->len; ++i){
        free(dic->keys[i]);
        free(dic->datas[i]);
    }
    free(dic->keys);
    free(dic->datas);
    free(dic);
}
