#ifndef IAHashMap_h
#define IAHashMap_h

#include "IAString.h"


typedef struct IAHashMapList IAHashMapList;

struct IAHashMapList{
    void * object;
    IAHashMapList * next;
    char key[];
};

typedef struct{
    //@extend
    IAObject base;
    //@get
    size_t size;
    IAHashMapList ** list;
} IAHashMap;


#define IA_KEY_SIZE_FOR_OBJECT (sizeof(void *) * 2 + 1)

void IAHashMap_getKeyForObject(const void * object, char keyOut[IA_KEY_SIZE_FOR_OBJECT]);

void IAHashMap_init(IAHashMap *, size_t estimatedNumberOfElements);
void IAHashMap_initWithFixedSize(IAHashMap *, size_t fixedSize);

void IAHashMap_add(IAHashMap *, const char * key, void * object);

bool IAHashMap_containsKey(const IAHashMap *, const char * key);
bool IAHashMap_containsKeyWithKeySize(const IAHashMap *, size_t keySize, const char key[keySize]);
void * IAHashMap_get(const IAHashMap *, const char * key);
void * IAHashMap_getWithKeySize(const IAHashMap *, size_t keySize, const char key[keySize]);

void * IAHashMap_remove(IAHashMap *, const char *  key);

void IAHashMap_clear(IAHashMap *);

void IAHashMap_changeSize(IAHashMap *, size_t estimatedNumberOfElements);
void IAHashMap_changeSizeWithFixedSize(IAHashMap *, size_t fixedSize);

void IAHashMap_callFunctionOnAllObjects(const IAHashMap *, void(*function)(void * object));

void IAHashMap_deinit(IAHashMap *);

#include "IAHashMapIterator.h"
#include "IAHashMap+Generated.h"

#endif


