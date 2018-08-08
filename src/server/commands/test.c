#include <string.h>

char		*hello_test_callback(void *arg)
{
	(void)arg;
	return (strdup("test success!"));
}
