#include "notebook.h"
#include "QtWidgets"



Notebook::Notebook(QWidget *parent)
    : QWidget(parent), m_textEdit( this )
{

    setFixedSize( 300, 350 );
    m_textEdit.resize( 300, 300 );

    /*----------------------------------------------------*/

    m_file = new QFile( "../Qt_Organizer/Calendar/Notes.xml" );

    if( !m_file->open( QFile::ReadOnly ) )
        qDebug() << "Ошибка открытия файла!";

    Q_ASSERT( m_file->isOpen() );

    /*------------------------------------------*/

    m_parser = new NotebookParser( m_file );

    if( !m_parser->documentElement().isNull() )
    {
        QDomElement domElement = m_parser->documentElement();
        Q_ASSERT( !domElement.isNull() );

        m_parser->traverseNode( domElement, &m_datesWithNotes );
    }

    m_file->close();

    /*------------------------------------------*/

    QPushButton * buttonOK = new QPushButton( "Принять", this );
    buttonOK->resize( 100, 40 );
    buttonOK->move( this->width()/2 - buttonOK->width()/2, 305 );


    connect( buttonOK, SIGNAL( clicked(bool) ), SLOT( updateNotes() ) );

    /*------------------------------------------*/

    connect(&m_textEdit, SIGNAL( textChanged() ), SLOT( updateBuffers() ) );
}


Notebook::~Notebook()
{
    m_parser->createNotebookStruct( m_datesWithNotes );
    m_parser->inputDataInFile( m_file );

    delete m_file;
    delete m_parser;
}


void Notebook::showTextEdit( QString const & _date )
{
    clearBuffers();
    m_bufferDate = _date;

    /*------------------------------------------*/

    //производим поиск заметок по укзанной дате
    QMap< QString, QString >::iterator it = m_datesWithNotes.find( m_bufferDate );

    //если поиск успешен - выводим на экран заметку
    if( it != m_datesWithNotes.end() )
        m_textEdit.setPlainText( it.value() );
    else //в противном случае очищаем текстовую область
        m_textEdit.clear();

    /*------------------------------------------*/

    window()->setWindowTitle( "Note" );
    show();
}


void Notebook::updateBuffers()
{
   QTextEdit* temp = (QTextEdit *)sender();
   m_bufferText =  temp->toPlainText();
}


void Notebook::updateNotes()
{
    /*------------------------------------------*/

    if( !m_bufferText.isEmpty() )
    {
        m_datesWithNotes[ m_bufferDate ] = m_bufferText;
    }

     /*------------------------------------------*/

    hide();
}

bool Notebook::checkDate( QString const &  _date )
{
    return m_datesWithNotes.find( _date ) != m_datesWithNotes.end();
}
