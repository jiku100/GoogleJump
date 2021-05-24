#ifndef MYTYPE_H_
#define MYTYPE_H_

typedef int boolean;

typedef enum {
	FALSE = 0,
	TRUE  = 1
} truth_t;

typedef enum {
	ERROR	= 0,
	SUCCESS	= 1
} error_t;


typedef enum{
	FAIL  = 0,
	CLEAR = 1
} state_t;

#endif