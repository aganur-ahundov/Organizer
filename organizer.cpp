#include "organizer.h"

#include "Alarm/alarm.h"
#include "Calendar/calendar.h"
#include "Phonebook/phonebook.h"
#include <QTabWidget>
#include <QIcon>


Organizer::Organizer(QWidget *parent)
    : QWidget( parent )
{

    setFixedSize( 400, 300 );

    m_tab = new QTabWidget( this );
    m_tab->resize( 400, 300 );

    QIcon mainIcon( "../Qt_Organizer/organizer.png" );
    Q_ASSERT( !mainIcon.isNull() );

    window()->setWindowIcon( mainIcon );

    QIcon calendarIcon( "../Qt_Organizer/calendar.png" );
    QIcon alarmIcon( "../Qt_Organizer/clock.png" );
    QIcon noteIcon( "../Qt_Organizer/pencil.png" );

    Q_ASSERT( !calendarIcon.isNull() );
    Q_ASSERT( !alarmIcon.isNull() );
    Q_ASSERT( !noteIcon.isNull() );

    m_calendar = new Calendar( m_tab );
    m_alarm = new Alarm( m_tab );
    m_phonebook = new Phonebook( m_tab );

    m_tab->addTab( m_calendar, calendarIcon, "Календарь" );
    m_tab->addTab( m_phonebook, noteIcon, "Контакты" );
    m_tab->addTab( m_alarm, alarmIcon, "Будильник" );
}


Organizer::~Organizer()
{
    delete m_tab;
}
