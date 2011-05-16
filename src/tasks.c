#include "tasks.h"

#include <stdlib.h>

Task *task_alloc(void(*func)(Task*), void *data) {
	Task *t = malloc(sizeof(Task));
	t->tq = NULL;
	t->refcount = 0;

	t->func = func;
	t->data = data;
	return t;
}

void task_free(Task *t) {
	free(t->data);
	free(t);
}

void task_requeue(Task *t) {
	if (!t->tq) return;

	taskqueue_enqueue(t->tq, t);
}

void task_ref(Task *t) {
	t->refcount++;
}

void task_unref(Task *t) {
	if (0 >= --t->refcount) {
		task_free(t);
	}
}

TaskQueue *taskqueue_alloc() {
	TaskQueue *tq = malloc(sizeof(TaskQueue));
	tq->queue = g_queue_new();
	g_queue_init(tq->queue);
	return tq;
}

void taskqueue_free(TaskQueue *tq) {
	g_queue_free(tq->queue);
	free(tq);
}

void taskqueue_enqueue(TaskQueue *tq, Task *t) {
	t->tq = tq;
	task_ref(t);

	g_queue_push_tail(tq->queue, t);
}

void taskqueue_run(TaskQueue *tq) {
	while (!g_queue_is_empty(tq->queue)) {
		Task *t = g_queue_pop_head(tq->queue);
		t->func(t);

		task_unref(t);
	}
}
