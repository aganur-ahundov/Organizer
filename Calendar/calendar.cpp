#include "calendar.h"
#include "day.h"
#include "notebook.h"
#include <QSpacerItem>
#include <QtWidgets>



/***************************************************************************************/

Calendar::Calendar(QWidget *parent)
    : QWidget(parent)
{
    //setFixedSize( 300, 200 );

    m_currentDate = new QDate( QDate::currentDate() );
    m_notebook = new Notebook();


    /*--------------------------------------------------------------------------*/

    QHBoxLayout * hLayout = new QHBoxLayout();
    constructHDateSpinBoxs( hLayout );

    constructDays();
    constructHBoxDayTitles( );

    /*--------------------------------------------------------------------------*/

    m_MonthLayout = new QGridLayout;
    changeDaysPosition();

    /*--------------------------------------------------------------------------*/

    m_MainLayout = new QVBoxLayout;

    m_MainLayout->setSpacing( 40 );
    m_MainLayout->setMargin( 10 );

    m_MainLayout->addLayout( hLayout );
    m_MainLayout->addLayout(m_MonthLayout);

    setLayout( m_MainLayout );
}

/***************************************************************************************/

void Calendar::constructDays()
{
    /*--------------------------------------------------------------------------*/

    m_days = new Day * [31];
    for( int i = 0; i < 31; i++ )
    {
       m_days[i] = new Day( "<h5>" + QString::number( i+1 ) + "</h5>" );
       m_days[i]->setFrameStyle( QFrame::Raised | QFrame::Box );
       QBrush b(Qt::blue);
       QPalette p(Qt::blue);
       //p.setBrush( m_days[i]->backgroundRole(), b );
       m_days[i]->setPalette(p);
       connect( m_days[i], SIGNAL( clicked() ), SLOT ( noteByDay() ) );
    }

    /*--------------------------------------------------------------------------*/
}

/***************************************************************************************/

void Calendar::constructHBoxDayTitles( )
{
    /*--------------------------------------------------------------------------*/

    const QString daysTitle[] = {"Пн","Вт", "Ср", "Чт", "Пт", "Сб", "Вс" };


    for( int i = 0; i < DAYS_IN_WEEK; i++)
    {
        QLabel * plabels = new QLabel( "<h2><tt>" + daysTitle[i] + "</tt></h2>", this );
         plabels->move( 25 + i * 55, 40 );
    }

    /*--------------------------------------------------------------------------*/
}


/***************************************************************************************/

void Calendar::constructHDateSpinBoxs( QHBoxLayout * _l )
{
    /*--------------------------------------------------------------------------*/

    QLabel *pMonthLabel = new QLabel( "<h2><tt>Месяц: </tt></h2>", this );

    QSpinBox * pBoxMonth = new QSpinBox( this );
    pBoxMonth->setRange( 1, 12 );

    /*--------------------------------------------------------------------------*/

    QLabel * pYearLabel = new QLabel( "<h2><tt>Год: </tt></h2>", this );

    QSpinBox * pBoxYear = new QSpinBox( this );
    pBoxYear->setRange(1900, 2100);

    /*--------------------------------------------------------------------------*/

    pBoxMonth->setValue( m_currentDate->month() );
    pBoxYear->setValue( m_currentDate->year() );

    connect( pBoxMonth, SIGNAL( valueChanged( int ) ), SLOT( changeMonth(int) ) );
    connect ( pBoxYear, SIGNAL ( valueChanged( int ) ), SLOT ( changeYear( int ) ) );

    /*--------------------------------------------------------------------------*/

    _l->addWidget( pMonthLabel );
    _l->addWidget( pBoxMonth );
    _l->addWidget( pYearLabel );
    _l->addWidget( pBoxYear );

    /*--------------------------------------------------------------------------*/

}

/***************************************************************************************/

void Calendar::changeDaysPosition()
{
    /*--------------------------------------------------------------------------*/

    m_MonthLayout->setSpacing(0);

    int weeks = weeksInMonth();
    int dayPosition = QDate( m_currentDate->year(), m_currentDate->month(), 1 ).dayOfWeek();
    int currentDate = 1;
    int daysInMonth = m_currentDate->daysInMonth();

    /*--------------------------------------------------------------------------*/

    for( int i = 0; i < weeks; i++ )
    {
        for( int j = dayPosition - 1; j < DAYS_IN_WEEK; j++ )
        {
            if( ( currentDate - 1 ) == daysInMonth )
                break;

          m_MonthLayout->addWidget( m_days[ currentDate - 1 ], i , j );
          currentDate++;
        }

        dayPosition = 1;
    }

    /*--------------------------------------------------------------------------*/

    for(int i = currentDate; i <= 31; i++)
        m_days[i-1]->setVisible(false);

    /*--------------------------------------------------------------------------*/

}

/***************************************************************************************/

int Calendar::weeksInMonth() const
{
    /*--------------------------------------------------------------------------*/

    if( m_currentDate->daysInMonth() == 31 )
    {
        QDate firstDay( m_currentDate->year(), m_currentDate->month(), 1 );

        if( firstDay.dayOfWeek() <= 5 )
        {
            return 5;
        }
        else
            return 6;
    }
    else if( m_currentDate->daysInMonth() == 30 )
    {
        QDate firstDay( m_currentDate->year(), m_currentDate->month(), 1 );

        if( firstDay.dayOfWeek() <= 6 )
        {
            return 5;
        }
        else
            return 6;
    }
    else
        return 5;

    /*--------------------------------------------------------------------------*/

}

/***************************************************************************************/

void Calendar::changeMonth( int _month )
{
    /*--------------------------------------------------------------------------*/

    m_currentDate->setDate( m_currentDate->year(), _month, m_currentDate->day() );

    for(int i = 28; i < 31; i++)
        m_days[i]->setVisible(true);

   changeDaysPosition();

   /*--------------------------------------------------------------------------*/

}

/***************************************************************************************/

void Calendar::changeYear( int _year )
{
    /*--------------------------------------------------------------------------*/

    m_currentDate->setDate( _year, m_currentDate->month(), m_currentDate->day() );

    for(int i = 28; i < 31; i++)
        m_days[i]->setVisible(true);

   changeDaysPosition();

   /*--------------------------------------------------------------------------*/
}

/***************************************************************************************/

void Calendar::noteByDay()
{
   QLabel * senderW = (QLabel*)sender();
   QString str = senderW->text();

   m_notebook->showTextEdit( str + "/" + QString::number( m_currentDate->month() ) + "/" +  QString::number( m_currentDate->year() ) );

}

/***************************************************************************************/

Calendar::~Calendar()
{

    for(int i = 0; i < 31; i++)
        delete m_days[i];

    delete [] m_days;

    delete m_currentDate;
    delete m_MonthLayout;
    delete m_MainLayout;
    delete m_notebook;
}
