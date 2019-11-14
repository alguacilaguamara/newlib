#include <wait.h>

pid_t wait(int *status)
{
	return waitpid((pid_t)-1, status, 0);
}
