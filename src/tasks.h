#ifndef GUARD_TASK_H
#define GUARD_TASK_H

#include <glib.h>

typedef struct {
	GQueue *queue;
} TaskQueue;

typedef struct TAG_Task{
	TaskQueue *tq;
	int refcount;

	void(*func)(struct TAG_Task*);
	void *data;
} Task;

Task *task_alloc(void(*)(Task*), void*);
void task_free(Task*);
void task_requeue(Task*);

void task_ref(Task*);
void task_unref(Task*);

TaskQueue *taskqueue_alloc();
void taskqueue_free(TaskQueue*);

void taskqueue_enqueue(TaskQueue*, Task*);
void taskqueue_run(TaskQueue*);

#endif
