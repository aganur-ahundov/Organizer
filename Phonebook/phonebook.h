#ifndef PHONEBOOK_H
#define PHONEBOOK_H

#include <QWidget>
#include <QMap>
#include "dom_parser.h"

class QFile;
class QListWidget;
class QListWidgetItem;
class QVBoxLayout;


class Phonebook
        : public QWidget
{
    Q_OBJECT


public:

    Phonebook(QWidget *parent = 0);
    ~Phonebook();

private:

    void updateData();

private:

    DomParser * m_parser;               //пользовательский класс для парсинга контактов в файле
    QListWidget * m_list;               //отображение данных в форме списка(список контактов)
    QMap< QString, QString > m_data;    //контейнер. хранит данные (имя,номер)
    QFile * m_base;                     //файл, куда сохраняем и откуда считываем контакты


private:

    void createButtons( QVBoxLayout * _l ); //создаем интерфейс. функционирующие кнопки и добавляем их в окно
    void parsing();                         //считываем данные из файла. работаем с DomParser
    void createDataList();                  //создаем интерфейс. создаем список и заполняем его контактами


private slots:

    void showAddContactDialog();            //выводит диалог для добавления контакта
    void showEditContactDialog();           //выводит диалог для редактирования контакта

    void addContact( QString const &, QString const & );    //добавляет контакт в список(интерфейс) и базу(контейнер)
    void editContactName( QString const & _name = QString(), QString const & _number = QString() ); //редактируем контакт

    void deleteContactSlot();   //удаляем всю информацию о контакте
    void showContactData( QListWidgetItem * );  //выводит информацию о контакте
};


#endif // PHONEBOOK_H
