#ifndef ALARM_H
#define ALARM_H


/******************************************************************/


#include <QWidget>
#include <QSettings>


/*-----------------------------------------*/


class QDateTimeEdit;
class QLineEdit;


/*-----------------------------------------*/


class Alarm : public QWidget
{
    Q_OBJECT

public:
    Alarm( QWidget *parent = 0 );
    ~Alarm();


    /*-----------------------------------------*/

private:

    QDateTimeEdit* m_dateEdit;  //переменная хранит указатель на класс установки времени и даты
    QLineEdit*     m_lineEdit;  //переменная хранит указатель на класс, представляющий собой строку для ввода текста
    QTimer*        m_timer;     //переменная хранит указатель на класс таймера

    QString        m_alarmText; //переменная хранит строку текста уведомления будильника
    QString        m_ringTime;  //переменная хранит строку со временем срабатывания будильника, для сохранения настроек в регистр

    QSettings      m_settings;  //переменная хранит класс позволяющий сохранить данные сеанса, для дальнейшего восстановления

    /*-----------------------------------------*/

private:

    const QString TEXT_ALARM_KEY_SETTINGS = "/Settings/Text for alarm";   //строка, которая хранит путь в регистре,
                                                                            //куда будут сохранены настройки сеанса(текст будильника)
    const QString RING_TIME_KEY_SETTINGS = "/Settings/Ring Time";         //строка, которая хранит путь в регистре,
                                                                            //куда будут сохранены настройки сеанса(время срабатывания будильника)

public slots:

    void ring();        //слот вызывающийся при срабатывании будильника
    void startAlarm();  //запуск будильника


    /*-----------------------------------------*/

};


/******************************************************************/


#endif // ALARM_H
