/*
 * $Header$
 */
#ifndef __COMMON_H__
#define __COMMON_H__

#include <QObject>
#include <QDebug>
#include <QString>
#include <QApplication>
#include <QIODevice>


#define DBG qDebug() <<  __FILE__ << __LINE__ <<__FUNCTION__ <<":"


int testFor (char *data, int data_len, char *buffer, int buffer_len);

#endif // __COMMON_H__
