#include "tasks.h"

#include <stdlib.h>
#include <stdio.h>

typedef struct {
	TaskQueue *tq;
	int count;
} FuncArgs;

void func(void *d) {
	FuncArgs *fa = (FuncArgs*)d;

	if (fa->count > 0) {
		FuncArgs *fa2 = malloc(sizeof(FuncArgs));
		fa2->tq = fa->tq;
		fa2->count = fa->count - 1;

		Task *t = task_alloc(&func, fa2);
		taskqueue_enqueue(fa->tq, t);
	}

	fprintf(stdout, "%d\n", fa->count);
}

int main(int argc, char *argv[]) {
	TaskQueue *tq = taskqueue_alloc();

	FuncArgs *fa = malloc(sizeof(FuncArgs));
	fa->tq = tq;
	fa->count = 5;

	Task *t = task_alloc(&func, fa);
	taskqueue_enqueue(tq, t);

	taskqueue_run(tq);

	return 0;
}
