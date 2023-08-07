/**
 * @file libtlsf_init.c
 * @author Merve Gulmez 
 * @brief Library version of TLSF
 * @version 0.1
 * @date 2022-02-07
 * 
 * @copyright © Ericsson AB 2022-2023
 * 
 * SPDX-License-Identifier: BSD 3-Clause
 */

#include "tlsf.h"
#include <sys/syscall.h>
#include <sys/mman.h>
#include <pthread.h> 
#include <stdlib.h>
#include <string.h>
#include <stdint.h> 

#define APP_DEFAULT_HEAP_SIZE               0x500000000
#define TLSF_MAX_POOL_SIZE                  0x100000000

pthread_mutex_t application_mutex = PTHREAD_MUTEX_INITIALIZER;

tlsf_t tlsf;

/*Multithreaded application support*/
#ifdef TLSF_MULTITHREAD
#define TLSF_MUTEX_LOCK(...)  pthread_mutex_lock(&application_mutex);
#define TLSF_MUTEX_UNLOCK(...)  pthread_mutex_unlock(&application_mutex);
#else
#define TLSF_MUTEX_LOCK(...)     
#define TLSF_MUTEX_UNLOCK(...)   
#endif


/* it will run before the main() function*/
__attribute__((constructor))
void libtlsf_init()
{
    uintptr_t  app_heap_size; 
    uintptr_t  app_heap_address; 

    char *pTmp;

    pTmp = getenv( "APP_HEAP_SIZE");

    if(pTmp != NULL){
        app_heap_size = atoi(pTmp); 
    }else{
        app_heap_size = APP_DEFAULT_HEAP_SIZE; 
    }


    app_heap_address = (uintptr_t)mmap(NULL, APP_DEFAULT_HEAP_SIZE,
                            PROT_READ | PROT_WRITE,
                            MAP_PRIVATE |
                            MAP_ANONYMOUS,
                            -1,
                            0);
    
    if(app_heap_size <= TLSF_MAX_POOL_SIZE){
        tlsf = tlsf_create_with_pool((void *)app_heap_address, app_heap_size);
    }else{
        tlsf = tlsf_create_with_pool((void *)app_heap_address, TLSF_MAX_POOL_SIZE);
        app_heap_size = app_heap_size - TLSF_MAX_POOL_SIZE;
        app_heap_address =  app_heap_address + TLSF_MAX_POOL_SIZE;
        while (app_heap_size  > TLSF_MAX_POOL_SIZE)
        {
            tlsf_add_pool(tlsf, (void *)app_heap_address, TLSF_MAX_POOL_SIZE);
            app_heap_size = app_heap_size - TLSF_MAX_POOL_SIZE;
            app_heap_address = app_heap_address + TLSF_MAX_POOL_SIZE;
        } 
        tlsf_add_pool(tlsf, (void *)app_heap_address, app_heap_size);
    }
}

__attribute__((destructor))
int application_end()
{
    tlsf_destroy(tlsf);
}


/* That's avoiding to calloc directly call libcmalloc*/
void *__malloc(size_t size);
void *__malloc(size_t size)
{
    void *ptr;
    ptr = malloc(size);
    return ptr;
}


void *malloc(size_t size);
void *malloc(size_t size)
{
    void *ptr;
    TLSF_MUTEX_LOCK();
    ptr = tlsf_malloc(tlsf, size);
    TLSF_MUTEX_UNLOCK();
    return ptr;
}

char *strdup (const char *s);
char *strdup (const char *s)
{
    size_t len = strlen (s) + 1;
    void *new = malloc (len);
    if (new == NULL)
        return NULL;
    return (char *) memcpy (new, s, len);
}


void *realloc(void *ptr, size_t size);
void *realloc(void *ptr, size_t size)
{
    TLSF_MUTEX_LOCK();
    ptr = tlsf_realloc(tlsf, ptr, size);
    TLSF_MUTEX_UNLOCK();
    return ptr;
}

void *calloc(size_t nelem, size_t elsize);
void *calloc (size_t nelem, size_t elsize)
{
    register void *ptr;  
    if (nelem == 0 || elsize == 0)
        nelem = elsize = 1;
    
    ptr = __malloc (nelem * elsize); 
    if (ptr) bzero (ptr, nelem * elsize);
    
    return ptr;
}



void free(void *ptr);
void free(void *ptr)
{
    TLSF_MUTEX_LOCK();
    tlsf_free(tlsf, ptr);
    TLSF_MUTEX_UNLOCK();
}


int posix_memalign(void **memptr, size_t alignment, size_t size)
{
    void *ptr; 
    TLSF_MUTEX_LOCK();
    ptr = tlsf_memalign(tlsf, alignment, size); 
    TLSF_MUTEX_UNLOCK();
    *memptr = ptr; 
    return 0; //tlsf_memalign doesn't have any zero code
}
