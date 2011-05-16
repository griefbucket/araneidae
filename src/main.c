#include "tasks.h"

#include <stdlib.h>
#include <stdio.h>

typedef struct {
	int count;
} FuncArgs;

void func(Task *t) {
	FuncArgs *fa = (FuncArgs*)t->data;

	fprintf(stdout, "%d\n", fa->count);

	if (fa->count-- > 0) {
		task_requeue(t);
	}
}

int main(int argc, char *argv[]) {
	TaskQueue *tq = taskqueue_alloc();

	FuncArgs *fa = malloc(sizeof(FuncArgs));
	fa->count = 5;

	Task *t = task_alloc(&func, fa);
	taskqueue_enqueue(tq, t);

	taskqueue_run(tq);

	return 0;
}
