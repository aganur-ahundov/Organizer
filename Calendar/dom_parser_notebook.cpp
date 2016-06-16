#include "dom_parser_notebook.h"
#include <QtWidgets>
#include <QtXml/qdom.h>

/***********************************************************************/

NotebookParser::NotebookParser( QString const & _title, QWidget *parent)
    : QWidget( parent )
{
    m_parser = new QDomDocument();

    /*-----------------------------------------------------*/

    m_mainElement = new QDomElement(
                m_parser->createElement( _title )
                );

    m_parser->appendChild( *m_mainElement );


    /*-----------------------------------------------------*/

    Q_ASSERT( !m_parser->isNull() );
    Q_ASSERT( !m_mainElement->isNull() );

    /*-----------------------------------------------------*/

}


/***********************************************************************/


NotebookParser::NotebookParser( QFile *_file )
{
    m_parser = new QDomDocument();

    /*-----------------------------------------------------*/

    QString error;

    if ( !m_parser->setContent( _file, &error ) )
    {
         qDebug() << error;
    }

    /*-----------------------------------------------------*/

    QDomElement root = m_parser->documentElement();
    m_mainElement = new QDomElement(
                root
                );

    /*-----------------------------------------------------*/

    Q_ASSERT( !m_parser->isNull() );
    Q_ASSERT( !m_mainElement->isNull() );

    /*-----------------------------------------------------*/

}


/***********************************************************************/


NotebookParser::~NotebookParser()
 {
    /*-----------------------------------------------------*/

    delete m_parser;
    delete m_mainElement;

    /*-----------------------------------------------------*/

}


/***********************************************************************/


QDomElement NotebookParser::note( const QString &_strDate, const QString &_strText )
{

    QDomElement domElement = makeElement( "note" );

    /*-----------------------------------------------------*/

    domElement.appendChild( makeElement( "date", _strDate ) );
    domElement.appendChild( makeElement( "text", _strText ) );

    /*-----------------------------------------------------*/

    return domElement;
}


/***********************************************************************/


QDomElement NotebookParser::makeElement( const QString &_strName,
                                    const QString &_strText
                                   )
{
    QDomElement domElement = m_parser->createElement( _strName );

    /*-----------------------------------------------------*/

    if( !_strText.isEmpty() )
    {
        QDomText domText = m_parser->createTextNode( _strText );
        domElement.appendChild( domText );
    }

    /*-----------------------------------------------------*/

    return domElement;
}


/***********************************************************************/


void NotebookParser::traverseNode( const QDomNode & _node,
                              QMap < QString, QString > * _data )
{
    QDomNode domNode = _node.firstChild();

    /*-----------------------------------------------------*/

    while( !domNode.isNull() )
    {
        /*-----------------------------------------------------*/

        if( domNode.isElement() )
        {
            QDomElement domElement = domNode.toElement();

            if( !domElement.isNull() )
            {

                QString dateBuffer;
                QString textBuffer;
                /*-----------------------------------------------------*/

                if( domElement.tagName() == "date" )
                {
                    dateBuffer = domElement.text();

                    if ( domElement.nextSibling().toElement().tagName() == "text" )
                        textBuffer = domElement.nextSibling().toElement().text();

                }
                /*-----------------------------------------------------*/

                _data->insert( dateBuffer, textBuffer );
            }
        }

        traverseNode( domNode, _data );
        domNode = domNode.nextSibling();

        /*-----------------------------------------------------*/

    }

    /*-----------------------------------------------------*/

}


/***********************************************************************/


bool NotebookParser::setContent( QIODevice * _source )
{
    QString error;

    /*-----------------------------------------------------*/

      if( !m_parser->setContent( _source, false, &error ) )
      {
          qDebug() << error;
          return false;
      }
     else
      return true;

      /*-----------------------------------------------------*/

}


/***********************************************************************/


QDomElement NotebookParser::documentElement() const
{
    return m_parser->documentElement();
}


/***********************************************************************/


void NotebookParser::addNote( const QString &_strDate,
                           const QString &_strText )
{
    /*-----------------------------------------------------*/

    m_mainElement->appendChild(
                note( _strDate, _strText )
                );

    /*-----------------------------------------------------*/
}


/***********************************************************************/


void NotebookParser::inputDataInFile( QIODevice * _source )
{
    if( _source->open( QFile::WriteOnly | QFile::Truncate ) )
    {
         QTextStream( _source ) << m_parser->toString();
        _source->close();
    }
}


/***********************************************************************/


void NotebookParser::createNotebookStruct( QMap< QString, QString > & _data )
{

    /*----------------------------------------------------*/

    m_parser->clear();

    delete m_mainElement;
    m_mainElement = new QDomElement(
                m_parser->createElement( "notebook" )
                );

    m_parser->appendChild( *m_mainElement );


    /*----------------------------------------------------*/


    QMap< QString, QString >::iterator it = _data.begin();

    while( it != _data.end() )
    {
        addNote ( it.key(), it.value() );
        it++;

    }


    /*----------------------------------------------------*/
}
