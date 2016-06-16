#ifndef INPUTDIALOG_H
#define INPUTDIALOG_H


/*****************************************************************/

#include <QDialog>

class QLineEdit;
//class QString;

/*****************************************************************/


class InputDialog
    :public QDialog
{
    Q_OBJECT

public:

    InputDialog( QWidget * _parent = 0 );
    ~InputDialog();

private:

    QLineEdit * m_pNameEdit;
    QLineEdit * m_pNumberEdit;

public:

    QString getName() const;
    QString getNumber() const;


protected slots:

    void sentData();

signals:

    void sent( QString const &, QString const & );

};


/*****************************************************************/

#endif // INPUTDIALOG_H
