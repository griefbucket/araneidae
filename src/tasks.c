#include "tasks.h"

#include <stdlib.h>

Task *task_alloc(void(*func)(void*), void *data) {
	Task *t = malloc(sizeof(Task));
	t->func = func;
	t->data = data;
	return t;
}

void task_free(Task *t) {
	free(t->data);
	free(t);
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
	g_queue_push_tail(tq->queue, t);
}

void taskqueue_run(TaskQueue *tq) {
	while (!g_queue_is_empty(tq->queue)) {
		Task *t = g_queue_pop_head(tq->queue);
		t->func(t->data);
		task_free(t);
	}
}
