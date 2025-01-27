/*
 * scheduler.c
 *
 *  Created on: Nov 9, 2024
 *      Author: datph
 */
#include "scheduler.h"

sTasks* head = NULL;
sTasks* tail = NULL;

void SCH_Init(void){
    head = NULL;
    tail = NULL;
}

void SCH_Add_Task (void (*pFunction)(), uint32_t DELAY, uint32_t PERIOD) {
	sTasks* newTask = (sTasks*)malloc(sizeof(sTasks));
	    if (newTask) {
	        newTask->pTask = pFunction;
	        newTask->Delay = DELAY;
	        newTask->Period = PERIOD;
	        newTask->RunMe = 0;
	        newTask->next = NULL;
	        newTask->prev = tail;

	        if (tail) {
	            tail->next = newTask;
	        }
	        else {
	            head = newTask;
	        }
	        tail = newTask;
	    }
}

void SCH_Update(void) {
	sTasks* current = head;
	    while (current) {
	        if (current->Delay > 0) {
	            current->Delay--;
	        } else {
	            current->Delay = current->Period;
	            current->RunMe++;
	        }
	        current = current->next;
	    }
}

void SCH_Dispatch_Tasks(void) {
	sTasks* current = head;
	    while (current) {
	        if (current->RunMe > 0) {
	            current->RunMe--;
	            (*current->pTask)();

	            if (current->Period == 0) {
	                sTasks* toDelete = current;
	                current = current->next;
	                SCH_Delete_Task(toDelete);
	            }
	            else {
	                current = current->next;
	            }
	        }
	        else {
	            current = current->next;
	        }
	    }
}

void SCH_Delete_Task (sTasks* task) {
	if (!task) return;

	    if (task->prev) {
	        task->prev->next = task->next;
	    }
	    else {
	        head = task->next;
	    }

	    if (task->next) {
	        task->next->prev = task->prev;
	    }
	    else {
	        tail = task->prev;
	    }

	    free(task);
}
