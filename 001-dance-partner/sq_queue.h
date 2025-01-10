//==============================================================================
//
// Title:		
// Purpose:		
// Author:
// Created on:
// Copyright:
//
//==============================================================================

#ifndef __SQ_QUEUE_H__
#define __SQ_QUEUE_H__

#ifdef __cplusplus
extern "C" {
#endif

//==============================================================================
// Include files


//==============================================================================
// Constants
#define MAX_Q_SIZE 100 // 队列空间最大长度

#define ERROR -1
#define OK 0
#define OVERFLOW 1
//==============================================================================
// Types
typedef struct
{
	char name[10];
	char sex;
}Person_T;

typedef Person_T QElemType;

typedef struct
{
	QElemType *base;  // 存储空间的基地址
	int front;        // 头指针
	int rear;         // 尾指针
}SqQueue_T;
//==============================================================================
// External variables

//==============================================================================
// Global functions

//int Declare_Your_Functions_Here (int x);
int queue_init(SqQueue_T *sq_queue_pt);
int queue_destory(SqQueue_T *sq_queue_pt);
int queue_length(SqQueue_T *sq_queue_pt);
int queue_push(SqQueue_T *sq_queue_pt, QElemType elem);
int queue_pop(SqQueue_T *sq_queue_pt, QElemType *elem);
QElemType * queue_head_elem_get(SqQueue_T *sq_queue_pt);
int  queue_empty(SqQueue_T *sq_queue_pt);

#ifdef __cplusplus
}
#endif

#endif