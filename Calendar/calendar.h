#ifndef CALENDAR_H
#define CALENDAR_H

#include <QWidget>

class Day;
class QDate;
class QVBoxLayout;
class QGridLayout;
class QHBoxLayout;
class QString;
class QSpinBox;


class Notebook;


class Calendar : public QWidget
{
    Q_OBJECT

public:
    Calendar(QWidget *parent = 0);
    ~Calendar();

private:

    Day **        m_days;           //блок памяти, хранящий указатели на все дни месяца
    QDate *       m_currentDate;    //указатель на класс, позволяющий манипулировать датой
    QVBoxLayout * m_MainLayout;     //класс-компоновщик (по вертикали), ответственный за внешний вид окна
    QGridLayout * m_MonthLayout;    //класс-компоновщик (координатная таблица), устанавливает позиции для дней-виджетов в окне
    Notebook *    m_notebook;       //пользовательский класс, позволяющий делать заметки

private:

    void changeDaysPosition();                          //изменяет расположение дней с изменением месяца
    int weeksInMonth() const;                           //возвращает кол-во недель в выбранном месяце
    void constructHDateSpinBoxs( QHBoxLayout * _l );    //создает и размещает спин-боксы (выбор месяца и года)
    void constructDays();                               //создает все классы-дни
    void constructHBoxDayTitles( );                     //создает и размещает лэйблы с названием дней неделе

public slots:

    void changeMonth( int _month );                     //устанавливает введеную месяц и изменяет расположение дней
    void changeYear( int _year );                       //устанавливает введеный год и изменяет расположение дней
    void noteByDay( );                                  //создает окно ввода текста (заметки)


private:

    static const int DAYS_IN_WEEK = 7;  //количество дней в неделе, исп. для повышения читабельности кода

};

#endif // CALENDAR_H
