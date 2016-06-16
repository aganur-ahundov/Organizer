#ifndef NOTEBOOK_H
#define NOTEBOOK_H

#include <QWidget>
#include <QTextEdit>
#include <QCloseEvent>

#include "dom_parser_notebook.h"



class QFile;


class Notebook
        : public QWidget
{

    Q_OBJECT
public:
    explicit Notebook(QWidget *parent = 0);
    ~Notebook();

private:

    QTextEdit           m_textEdit;     //окно для ввода текста
    QFile*              m_file;         //класс для манипулирования(ввода/ввывода) информацией из файла
    NotebookParser*     m_parser;       //пользовательский класс для парсинга файла

    QString        m_bufferText;        //буффер
    QString        m_bufferDate;        //буффер


    QMap < QString, QString > m_datesWithNotes; //контейнер, для хранения данных (дата, заметка)


private:

    void clearBuffers() { m_bufferDate.clear(); m_bufferText.clear(); }     //очищаем буфферы


public:

    void showTextEdit( QString const & _date );     //отоброжает окно для ввода заметки
    bool checkDate( QString const &  _date );       //есть ли заметка для данной даты

private slots:

    void updateBuffers();                           //записывает введеную информацию в буффер
    void updateNotes();                             //добавляет введеную информацию в контейнер

};

#endif // NOTEBOOK_H
