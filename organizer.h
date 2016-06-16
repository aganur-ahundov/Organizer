#ifndef ORGANIZER_H
#define ORGANIZER_H

#include <QWidget>

class Alarm;
class Calendar;
class Phonebook;
class QTabWidget;



class Organizer
        : public QWidget
{
    Q_OBJECT

public:
    explicit Organizer( QWidget *parent = 0 );
    ~Organizer();

private:

    Alarm*       m_alarm;       //пользовательский класс-будильник
    Calendar*    m_calendar;    //пользовательский класс-календарь
    Phonebook*   m_phonebook;   //пользовательский класс контактной книги

    QTabWidget*  m_tab;         //интерфейс приложения. позволяет создавать вкладки для каждой "подпрограммы"

};

#endif // ORGANIZER_H
