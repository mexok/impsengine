#ifndef IALibrary_h
#define IALibrary_h

#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>

/// this macro marks a constructor function
#define IA_CONSTRUCTOR

/// this macro marks a destructor function
#define IA_DESTRUCTOR

#include "IAAssert.h"
#include "IAOperatingSystem.h"

void IALibrary_commenceIfNeeded(void);

#ifdef DEBUG

#define IA_new(size, deinitFunction) IALibrary_new(size, deinitFunction, CLASSNAME)
#define IA_newWithClassName(size, deinitFunction, className) IALibrary_new(size, deinitFunction, className)
#define IA_retain(object) IALibrary_retain(object)
#define IA_autorelease(object) IALibrary_autorelease(object)
#define IA_release(object) IALibrary_release(object)

void * IALibrary_new(size_t size, void (*deinit)(void * object), const char * className);
void IALibrary_retain(void * object);
void IALibrary_autorelease(void * object);
void IALibrary_release(void * object);

#define IA_malloc(size) IALibrary_malloc(size, CLASSNAME)
#define IA_mallocWithClassName(size, className) IALibrary_malloc(size, className)
#define IA_calloc(count, size) IALibrary_calloc(count, size, CLASSNAME)
#define IA_callocWithClassName(count, size, className) IALibrary_calloc(count, size, className)
#define IA_realloc(data, size) IALibrary_realloc(data, size, CLASSNAME)
#define IA_reallocWithClassName(data, size, className) IALibrary_realloc(data, size, className)
#define IA_free(data) IALibrary_free(data, CLASSNAME);
#define IA_freeWithClassName(data, className) IALibrary_free(data, className);

void * IALibrary_malloc(size_t size, const char * className);
void * IALibrary_calloc(size_t count, size_t size, const char * className);
void * IALibrary_realloc(void * data, size_t size, const char * className);
void IALibrary_free(void * data, const char * className);

#else

#define IA_new(size, deinitFunction) IALibrary_new(size, deinitFunction)
#define IA_newWithClassName(size, deinitFunction, className) IALibrary_new(size, deinitFunction)
#define IA_retain(object) IALibrary_retain(object)
#define IA_autorelease(object) IALibrary_autorelease(object)
#define IA_release(object) IALibrary_release(object)

void * IALibrary_new(size_t size, void (*deinit)(void * object));
void IALibrary_retain(void * object);
void IALibrary_autorelease(void * object);
void IALibrary_release(void * object);

#define IA_malloc(size) IALibrary_malloc(size)
#define IA_mallocWithClassName(size, className) IALibrary_malloc(size)
#define IA_calloc(count, size) IALibrary_calloc(count, size)
#define IA_callocWithClassName(count, className) IALibrary_calloc(count, size)
#define IA_realloc(data, size) IALibrary_realloc(data, size)
#define IA_reallocWithClassName(data, size, className) IALibrary_realloc(data, size)
#define IA_free(data) IALibrary_free(data);
#define IA_freeWithClassName(data, className) IALibrary_free(data);

void * IALibrary_malloc(size_t size);
void * IALibrary_calloc(size_t count, size_t size);
void * IALibrary_realloc(void * data, size_t size);
void IALibrary_free(void * data);

#endif

bool IALibrary_isDebugMode(void);

#include "IAAllocationTracking.h"
#include "IANotificationDelegate.h"

void IALibrary_registerOnMemoryWarningNotification(IANotificationDelegate * delegate);
void IALibrary_unregisterOnMemoryWarningNotification(IANotificationDelegate * delegate);

#ifdef DEBUG
#define debugOnly(e) e
#else
#define debugOnly(e)
#endif

#define swap(a, b) \
    do { \
        __typeof__(a) IA_t; \
        __typeof__(IA_t) * IA_a; \
        __typeof__(b) * IA_b; \
        IA_a  = &(a); \
        IA_b  = &(b); \
        IA_t  = *IA_a; \
        *IA_a = *IA_b; \
        *IA_b =  IA_t; \
    } while (0)

#define in ,

#define list(type, ...) type, make, __VA_ARGS__
#define keys(type, ...) type, makeIteratorOverKeys, __VA_ARGS__
#define values(type, ...) type, makeIteratorOverValues, __VA_ARGS__

#define foreach(...) IA_FOREACH(__VA_ARGS__)
#define IA_FOREACH(item, type, makeIteratorMethod, ...) IA_FOREACH2(item, type, makeIteratorMethod, __COUNTER__, __VA_ARGS__)
#define IA_FOREACH2(item, type, makeIteratorMethod, counter, ...) IA_FOREACH3(item, type, makeIteratorMethod, counter, __VA_ARGS__)
#define IA_FOREACH3(item, type, makeIteratorMethod, counter, ...) IA_FOREACH4(item, type, makeIteratorMethod, IA_tempIterator ## counter, __VA_ARGS__)
#define IA_FOREACH4(item, type, makeIteratorMethod, iteratorName, ...) \
    ;type ## Iterator iteratorName; \
    type ## Iterator_ ## makeIteratorMethod(&iteratorName, (__VA_ARGS__)); \
    while((item = type ## Iterator_getNextObject(&iteratorName)) != NULL)

#include "IALogger.h"

#endif

