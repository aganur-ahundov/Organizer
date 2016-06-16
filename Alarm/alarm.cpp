#include <QtWidgets>
#include "alarm.h"
#include <cassert>

/*-----------------------------------------------*/


Alarm::Alarm( QWidget *parent )
    : QWidget( parent ),
      m_dateEdit( new QDateTimeEdit( QDateTime::currentDateTime() ) ),
      m_settings("Home", "Alarm")
{

    m_timer = new QTimer();

/*-------------------------------------------------------------------*/

    m_lineEdit = new QLineEdit( "Введите текст для будильника" );

/*-------------------------------------------------------------------*/


    QPushButton * pOkButton = new QPushButton( "Установить" );
    connect( pOkButton, SIGNAL( clicked( bool )), SLOT( startAlarm()) );


/*-------------------------------------------------------------------*/

    QVBoxLayout * pVLayout = new QVBoxLayout();

    pVLayout->addWidget( m_dateEdit );
    pVLayout->addWidget( m_lineEdit );
    pVLayout->addWidget( pOkButton );

    pVLayout->setMargin( 70 );
    setLayout( pVLayout );

    /*-------------------------------------------------------------------*/

    connect(m_timer, SIGNAL(timeout()), SLOT(ring()));


    /*-------------------------------------------------------------------*/

    QString time = m_settings.value(RING_TIME_KEY_SETTINGS, "\0").toString();

    if( time != 0)
    {
        int day = 0,
                month = 0,
                hour = 0,
                min = 0,
                sec = 0;

        sscanf( const_cast<char*>(time.toStdString().c_str())
                , "%d.%d %d.%d.%d", &day, &month, &hour, &min, &sec );

        m_dateEdit->setDateTime(QDateTime( QDate(QDate::currentDate().year(), month, day)
                                           , QTime(hour, min, sec)));

        if(QTime::currentTime().secsTo(m_dateEdit->time()) > 0)
{
        m_alarmText = m_settings.value( TEXT_ALARM_KEY_SETTINGS, "\0").toString();
        assert(!m_alarmText.isEmpty());

        m_settings.remove(TEXT_ALARM_KEY_SETTINGS);
        m_settings.remove(RING_TIME_KEY_SETTINGS);

        startAlarm();
 }
    }
}


/*-----------------------------------------------*/


Alarm::~Alarm()
{
    if(m_timer->isActive())
    {
        m_settings.setValue(RING_TIME_KEY_SETTINGS, m_ringTime);
        m_settings.setValue(TEXT_ALARM_KEY_SETTINGS, m_alarmText);
    }

    delete m_timer;
    delete m_lineEdit;
    delete m_dateEdit;
}


/*-----------------------------------------------*/


void Alarm::startAlarm()
{
    m_alarmText = m_lineEdit->text();
    m_lineEdit->clear();

    m_ringTime = m_dateEdit->dateTime().toString("dd.MM hh.mm.ss");

                      //Дни умножаем на часы в сутках(24), на минут в часу(60), на секунд в минуте(60) и переводим в милисекунды(1000)
    double nTime = ( ( (  QDate::currentDate().daysTo( m_dateEdit->date() ) ) * 24 * 60 * 60 * 1000 )
                    + (  QTime::currentTime().msecsTo( m_dateEdit->time() ) ) )
                    ;//считаем сколько дней + времени (в миллисекундах) до заданого будильником времени

    if( nTime < 0 )
        QMessageBox::information(
                    0,
                    "Не корректное время",
                    "Установленно не корректное время",
                    "Oк"
                    );
    else if( m_alarmText.isEmpty() )
        QMessageBox::information(
                    0,
                    "Не корректное уведомление",
                    "Поле с уведомлением - пустое",
                    "Oк"
                    );
    else
    {


        m_timer->start(nTime);

        int min = nTime / (60 * 1000) ;

        QMessageBox::information(
                    0,
                    "Будильник установлен",
                    "Будильник сработает через " +
                    QString::number( static_cast< int >( min )) +
                    " минут ",
                    "Oк"
                    );

    }

}


void Alarm::ring()
{
    m_timer->stop();

    QMessageBox::information(
                0,
                "Оповещение",
                m_alarmText,
                "Ок"
                );
}

/*-----------------------------------------------*/
