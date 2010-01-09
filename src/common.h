/*
 * $Header$
 */
#ifndef __COMMON_H__
#define __COMMON_H__

//#define kstNEW_DELETE 

#include <QObject>
#include <QDebug>
#include <QString>
#include <QApplication>
#include <QIODevice>

#define DBG qDebug() <<  __FILE__ << __LINE__ <<__FUNCTION__ <<":"

int                 testFor (char *data,
			     int data_len, char *buffer, int buffer_len);
void                kst_mem_cpy (char *src,
				 char *dst,
				 quint64 src_size, quint64 dst_size);
void                kst_mem_cpy2 (char *src, char *dst, quint64 size);

#ifdef kstNEW_DELETE
void               *operator  new[] (size_t size);
void               *operator  new (size_t size);
void operator       delete[] (void *ptr);
void operator       delete[] (void *ptr, size_t);
void operator       delete (void *ptr);
void operator       delete (void *ptr, size_t);
#endif

#endif // __COMMON_H
