#include "phonebook.h"
#include "input_dialog.h"

#include <QtWidgets>
#include <QtXml/qdom.h>


//QString Phonebook::m_ItemChangeBuff;

/*********************************************************************/

Phonebook::Phonebook( QWidget *parent )
    : QWidget( parent )
{
    /*----------------------------------------------------*/

   // setFixedSize( 200, 350 );

    /*----------------------------------------------------*/

    parsing();
    createDataList();

    QVBoxLayout * pVButtonLayout = new QVBoxLayout;
    createButtons( pVButtonLayout );

    /*----------------------------------------------------*/

    connect ( m_list, SIGNAL( itemDoubleClicked( QListWidgetItem* ) ), SLOT( showContactData( QListWidgetItem * ) ) );

    /*----------------------------------------------------*/

    QHBoxLayout * pMainLayout = new QHBoxLayout;

    pMainLayout->addWidget( m_list );
    pMainLayout->addLayout( pVButtonLayout );

    pMainLayout->setMargin( 30 );
    pMainLayout->setSpacing( 50 );

    setLayout( pMainLayout );
}

/*********************************************************************/


void Phonebook::createButtons( QVBoxLayout * _l )
{

    /*----------------------------------------------------*/

    QPushButton * pAddContact = new QPushButton( "Добавить контакт", this );
    pAddContact->move( this->width() / 6, m_list->height() + 30 );
    //pAddContact->resize( 130, 30 );

    connect( pAddContact, SIGNAL( clicked( bool ) ), SLOT( showAddContactDialog() ) );

    /*----------------------------------------------------*/


    QPushButton * pDeleteContact = new QPushButton( "Удалить контакт", this );
    pDeleteContact->resize( pAddContact->size() );
    //pDeleteContact->move( pAddContact->pos().x(), pAddContact->pos().y() + 30 );

    connect( pDeleteContact, SIGNAL( clicked( bool ) ), SLOT( deleteContactSlot() ) );

    /*----------------------------------------------------*/

    QPushButton * pEditContact = new QPushButton( "Редактировать", this );
    pEditContact->resize( pAddContact->size() );
    //pEditContact->move( pAddContact->pos().x(), pDeleteContact->pos().y() + 30 );

    connect( pEditContact, SIGNAL( clicked( bool ) ), SLOT( showEditContactDialog() ) );

    /*----------------------------------------------------*/

    _l->addWidget( pAddContact );
    _l->addWidget( pDeleteContact );
    _l->addWidget( pEditContact );
    _l->setSpacing( 10 );
}


/*********************************************************************/


void Phonebook::parsing()
{
    /*----------------------------------------------------*/

    m_base = new QFile( "../Qt_Organizer/Phonebook/Contacts.xml" );

    if( !m_base->open( QFile::ReadOnly ) )
        qDebug() << "Ошибка открытия файла!";


    /*------------------------------------------*/

    m_parser = new DomParser( m_base );

    if( !m_parser->documentElement().isNull() )
    {
        QDomElement domElement = m_parser->documentElement();
        Q_ASSERT( !domElement.isNull() );

        m_parser->traverseNode( domElement, &m_data );
    }

    m_base->close();

    /*------------------------------------------*/
}


/*********************************************************************/


void Phonebook::createDataList()
{
    /*----------------------------------------------------*/


    m_list = new QListWidget( this );
    m_list->setFixedSize( 180, 200 );
    m_list->setFrameStyle( QFrame::StyledPanel | QFrame::Plain );
    m_list->move( 10, 0 );

    //отображение хранит все контакты
    QMap< QString, QString >::iterator it = m_data.begin();

    //проходим по каждому существующему контаку
    for(; it != m_data.end(); it++)
    {
       //для каждого имени создаем элемент списка
       QListWidgetItem * item = new QListWidgetItem ( it.key() );
       //добавляет функциональность: выделение и реакцию на двойное нажатие
       item->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled );

       //добавляем в список
       m_list->addItem( item );

    }

    /*----------------------------------------------------*/

}


/*********************************************************************/


Phonebook::~Phonebook()
{
    /*----------------------------------------------------*/

    m_parser->createPhonebookStruct( m_data );
    m_parser->inputDataInFile( m_base );

    delete m_base;
    delete m_list;
    delete m_parser;

    /*----------------------------------------------------*/
}


/*********************************************************************/


void Phonebook::showAddContactDialog()
{
    /*-----------------------------------------------------*/

    InputDialog * pDialog = new InputDialog( this );
    pDialog->show();

    connect( pDialog,
             SIGNAL( sent( QString const &, QString const & ) ),
             SLOT( addContact( QString const &, QString const & ) )
             );

    /*-----------------------------------------------------*/

}


/*********************************************************************/


void Phonebook::showEditContactDialog()
{
    /*-----------------------------------------------------*/
    QListWidgetItem * pCurrentItem = m_list->currentItem();

    if( !pCurrentItem->isSelected() )
        QMessageBox::information(
                   0,
                    "Контакт не выбран",
                    "Для редактирования необходимо выбрать контакт"
                    );
    else
    {
        InputDialog * pDialog = new InputDialog( this );
        pDialog->show();

        connect( pDialog,
                 SIGNAL( sent( QString const &, QString const & ) ),
                 SLOT( editContactName( QString const &,QString const &) )
              );
    }

    /*-----------------------------------------------------*/

}


/*********************************************************************/


void Phonebook::addContact( QString const & _name, QString const & _number )
{
    /*-----------------------------------------------------*/

    if( m_data.find( _name ) != m_data.end() )
    {
        QMessageBox::information(
                    0,
                    "Контакт существует",
                    "Контакт с таким именем уже существует"
                    );

    }
    else if( _name.isEmpty() || _number.isEmpty() )
    {
        QMessageBox::information(
                   0,
                    "Пустое поле",
                    "Не все поля заполнены"
                    );
    }
    else
    {
        /*-----------------------------------------------------*/

        m_data[ _name ] = _number;

        m_list->addItem(
                new QListWidgetItem( _name )
                );

        /*-----------------------------------------------------*/

    }

    /*-----------------------------------------------------*/

}


/*********************************************************************/


void Phonebook::deleteContactSlot()
{
    QListWidgetItem * pCurrentItem = m_list->currentItem();

    if( !pCurrentItem->isSelected() )
        QMessageBox::information(
                   0,
                    "Контакт не выбран",
                    "Для удаления необходимо выбрать контакт"
                    );
    else
        {
            m_data.erase( m_data.find( m_list->currentItem()->text() ) );
            delete pCurrentItem;
        }
}


/*********************************************************************/


void Phonebook::editContactName( const QString &_name, const QString &_number )
{

    /*-----------------------------------------------------*/

    if( m_data.find( _name ) != m_data.end() )
    {
        QMessageBox::information(
                    0,
                    "Контакт существует",
                    "Контакт с таким именем уже существует"
                    );

    }
    else
    {
        /*-----------------------------------------------------*/

        if( _name.isEmpty() && !_number.isEmpty() )
        {
            m_data[ m_list->currentItem()->text() ] = _number;
        }
        else if ( !_name.isEmpty() && _number.isEmpty() )
        {
            m_data.insert( _name, m_data.find( m_list->currentItem()->text() ).value() );
            m_data.erase( m_data.find( m_list->currentItem()->text() ) );
            m_list->currentItem()->setText( _name );
        }
        else if( !_name.isEmpty() && !_number.isEmpty() )
        {
            m_data.insert( _name, _number );
            m_data.erase( m_data.find( m_list->currentItem()->text() ) );
            m_list->currentItem()->setText( _name );
        }

        /*-----------------------------------------------------*/

    }

    /*-----------------------------------------------------*/

}


/*********************************************************************/


void Phonebook::showContactData( QListWidgetItem * _item )
{
    QMessageBox::information(
                0,
                "Контакт",
                "Имя: " + _item->text() +
                "\nНомер: " + m_data.find( _item->text() ).value()
                );
}


/*********************************************************************/
