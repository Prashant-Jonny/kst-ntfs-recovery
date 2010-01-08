/* 
 * $Header$
 */
#ifndef KNR_DIALOGIMPL_H
#define KNR_DIALOGIMPL_H
//
#include <QDialog>
#include "ui_knr_dialog.h"
//
class DialogImpl : public QDialog, public Ui::Dialog
{
Q_OBJECT
public:
	DialogImpl( QWidget * parent = 0, Qt::WFlags f = 0 );
private slots:
};
#endif




