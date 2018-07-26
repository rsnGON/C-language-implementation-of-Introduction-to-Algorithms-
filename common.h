#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>

#define SEQUENCE_SIZE(name)      (sizeof(name) / sizeof(*name))



#define SENTRY_VALUE_MAX(INT) \
({                      \
	int sentry_value;   \
	switch(sizeof(INT)) \
	{                   \
	case 4: sentry_value = 2147483647; break; \
	case 2: sentry_value = 32767; break; \
	default: \
		printf("error value of sentry_value in %s:%d\n", __FILE__, __LINE__); break; \
	}                   \
	sentry_value;       \
})


#define SENTRY_VALUE_MIN(INT) \
({                      \
	int sentry_value;   \
	switch(sizeof(INT)) \
	{                   \
	case 4: sentry_value = -2147483648; break; \
	case 2: sentry_value = -32768; break; \
	default: \
		printf("error value of sentry_value in %s:%d\n", __FILE__, __LINE__); break; \
	}                   \
	sentry_value;       \
})




void print(int *sequence, int length)
{
	int i;
	for (i = 0; i < length; i++)
	{
		printf("%d ", sequence[i]);
	}   
	printf("\n");
}

#endif
