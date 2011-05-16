#ifndef GUARD_TASK_H
#define GUARD_TASK_H

#include <glib.h>

typedef struct {
	void(*func)(void*);
	void *data;
} Task;

Task *task_alloc(void(*)(void*), void*);
void task_free(Task*);

typedef struct {
	GQueue *queue;
} TaskQueue;

TaskQueue *taskqueue_alloc();
void taskqueue_free(TaskQueue*);

void taskqueue_enqueue(TaskQueue*, Task*);
void taskqueue_run(TaskQueue*);

#endif
