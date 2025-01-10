//==============================================================================
//
// Title:
// Purpose:
// Author:
// Created on:
// Copyright:
//
//==============================================================================

//==============================================================================
// Include files
#include "sq_queue.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//==============================================================================
// Constants

//==============================================================================
// Types

//==============================================================================
// Static global variables

//==============================================================================
// Global variables


//==============================================================================
// Static functions

//==============================================================================
// Global functions

/// HIFN  What does your function do?
/// HIPAR x/What inputs does your function expect?
/// HIRET What does your function return?
//int Define_Your_Functions_Here (int x)
//{
//	return x;
//}

// 队列初始化
int queue_init(SqQueue_T *sq_queue_pt)
{
	sq_queue_pt->base = (QElemType *)malloc(MAX_Q_SIZE * sizeof(QElemType));
	if (NULL == sq_queue_pt->base)
		exit(OVERFLOW);
	memset(sq_queue_pt->base, 0, MAX_Q_SIZE * sizeof(QElemType));
	sq_queue_pt->front = 0;
	sq_queue_pt->rear = 0;
	return OK;
}

// 队列销毁
int queue_destory(SqQueue_T *sq_queue_pt)
{
	if (NULL != sq_queue_pt->base)
		free(sq_queue_pt->base);
	sq_queue_pt->front = 0;
	sq_queue_pt->rear = 0;
	return OK;
}

// 求队列长度
int queue_length(SqQueue_T *sq_queue_pt)
{
	return  (sq_queue_pt->rear - sq_queue_pt->front + MAX_Q_SIZE) % MAX_Q_SIZE;
}

// 入队
int queue_push(SqQueue_T *sq_queue_pt, QElemType elem)
{
	// 判断是否队满(循环队列)，若队列为满，则报错
	if ((sq_queue_pt->rear + 1) % MAX_Q_SIZE == sq_queue_pt->front)
		return ERROR;
	sq_queue_pt->base[sq_queue_pt->rear] = elem;
	sq_queue_pt->rear = (sq_queue_pt->rear + 1) % MAX_Q_SIZE;
	return OK;
}

// 出队
int queue_pop(SqQueue_T *sq_queue_pt, QElemType *elem)
{
	// 判断是否对空，若队列为空，则报错
	if (sq_queue_pt->front == sq_queue_pt->rear)
		return ERROR;
	*elem = sq_queue_pt->base[sq_queue_pt->front];
	sq_queue_pt->front = (sq_queue_pt->front + 1) % MAX_Q_SIZE;
	return OK;
}

// 取队头元素
QElemType * queue_head_elem_get(SqQueue_T *sq_queue_pt)
{
	//若队列为空，则返回空指针NULL
	QElemType *p_elem;
	if (sq_queue_pt->front == sq_queue_pt->rear)
		p_elem = NULL;
	else
		p_elem = &sq_queue_pt->base[sq_queue_pt->front];
	return p_elem;
}

// 判断队列是否为空
int  queue_empty(SqQueue_T *sq_queue_pt)
{
	// 若队列为空，则返回值为非0值
	return !((sq_queue_pt->rear - sq_queue_pt->front + MAX_Q_SIZE) % MAX_Q_SIZE);
}