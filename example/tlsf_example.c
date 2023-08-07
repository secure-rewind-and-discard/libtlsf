 /**
 * @file tlsf_example.c
 * @author Merve Gulmez
 * @brief tlsf example test code 
 * @version 0.1
 * @date 2023-05-17
 * 
 * @copyright © Ericsson AB 2022-2023
 * 
 * SPDX-License-Identifier: BSD 3-Clause
 */
#define _GNU_SOURCE
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/mman.h>
#include <setjmp.h>
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <signal.h>
#include <string.h>



int main()
{
    void *ptr; 

    ptr = malloc(5); 

    free(ptr);
}

