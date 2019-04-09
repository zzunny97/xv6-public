#include "types.h"
#include "stat.h"
#include "user.h"
void *
thread(void *arg)
{
  printf(1, "before thread_exit\n");
	thread_exit((void *)0x87654321);
  printf(1, "after thread_exit\n");
}

int
main(int argc, char **argv)
{
	void *stack;
	void *retval;
	int tid;

	printf(1, "TEST: ");

	stack = malloc(4096);
	
	tid = thread_create(thread, (void *)0x12345678, stack);
  printf(1, "before if\n");
	if(tid == -1) {
		printf(1, "1\n");
    printf(1, "WRONG\n");
		exit();
	}
  printf(1, "before thread_join\n");
	if(thread_join(tid, &retval) == -1) {
    printf(1, "2\n");
		printf(1, "WRONG\n");
		exit();
	}

	if(retval != (void *)0x87654321) {
    printf(1, "3\n");
		printf(1, "WRONG\n");
		exit();
	}

	free(stack);

	printf(1, "OK\n");

	exit();
}

