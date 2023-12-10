/*
 * pagedir.h
 *
 * Chahak Goyal, Spring 2021
 */
#ifndef __PAGEDIR_H
#define __PAGEDIR_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../libcs50/file.h"
#include "index.h"
#include "../libcs50/webpage.h"

bool pagedir_init(const char* pageDirectory);
void pagedir_save(const webpage_t* page, const char* pageDirectory, const int docID);
bool pagedir_validate(const char* pageDirectory);
webpage_t* pagedir_load(const char* pageDirectory, const int docId);
void pagedir_write(index_t* index, FILE* fp);
void pagedir_delete(index_t* index);


#endif //__PAGEDIR_H
