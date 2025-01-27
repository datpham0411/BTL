/*
 * scheduler.h
 *
 *  Created on: Nov 9, 2024
 *      Author: datph
 */

#ifndef INC_SCHEDULER_H_
#define INC_SCHEDULER_H_

#include "stdint.h"
#include "list_tasks.h"
#include "main.h"
#include "stdlib.h"

typedef struct sTasks{
	void (*pTask)(void);
	uint32_t	Delay;
	uint32_t	Period;
	uint32_t	RunMe;
	uint32_t	TaskID;

	struct sTasks* next;
	struct sTasks* prev;
}sTasks;

#define SCH_MAX_TASKS	40

void SCH_Init(void);

void SCH_Add_Task ( void(*pFunction)(), uint32_t DELAY, uint32_t PERIOD);

void SCH_Update(void);

void SCH_Dispatch_Tasks(void);

void SCH_Delete_Task (sTasks* task);

#endif /* INC_SCHEDULER_H_ */
