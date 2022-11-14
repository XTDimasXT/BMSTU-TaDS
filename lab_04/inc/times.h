#ifndef __TIMES_H__
#define __TIMES_H__

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

#include "structs.h"
#include "errors.h"
#include "array.h"
#include "list.h"
#include "read.h"

unsigned long long milliseconds_now(void);
int compare_time(void);

#endif // __TIMES_H__