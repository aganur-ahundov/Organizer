#include "dom_parser.h"
#include <QtWidgets>
#include <QtXml/qdom.h>

/***********************************************************************/

DomParser::DomParser( QString const & _title, QWidget *parent)
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


DomParser::DomParser( QFile *_file )
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


DomParser::~DomParser()
 {
    /*-----------------------------------------------------*/

    delete m_parser;
    delete m_mainElement;

    /*-----------------------------------------------------*/

}


/***********************************************************************/


QDomElement DomParser::contact( const QString &_strName, const QString &_strText )
{

    QDomElement domElement = makeElement( "contact" );

    /*-----------------------------------------------------*/

    domElement.appendChild( makeElement( "name", _strName ) );
    domElement.appendChild( makeElement( "mobile", _strText ) );

    /*-----------------------------------------------------*/

    return domElement;
}


/***********************************************************************/


QDomElement DomParser::makeElement( const QString &_strName,
                                    const QString &_strText,
                                    const QString &_strAtr
                                   )
{
    QDomElement domElement = m_parser->createElement( _strName );

    /*-----------------------------------------------------*/

    if( !_strAtr.isEmpty() )
    {
        QDomAttr domAttr = m_parser->createAttribute( "number" );
        domAttr.setValue( _strAtr );
        domElement.setAttributeNode( domAttr );
    }

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


void DomParser::traverseNode( const QDomNode & _node,
                              QMap<QString, QString> * _data )
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
                QString nameBuff;
                QString numberBuff;

                /*-----------------------------------------------------*/

                if( domElement.tagName() == "name" )
                {
                    nameBuff = domElement.text();

                    if ( domElement.nextSibling().toElement().tagName() == "mobile" )
                        numberBuff = domElement.nextSibling().toElement().text();
                }

                /*-----------------------------------------------------*/

                if( ( !nameBuff.isEmpty() ) && ( !numberBuff.isEmpty() ) )
                    _data->insert( nameBuff, numberBuff );

                /*-----------------------------------------------------*/

            }
        }

        traverseNode( domNode, _data );
        domNode = domNode.nextSibling();

        /*-----------------------------------------------------*/

    }

    /*-----------------------------------------------------*/

}


/***********************************************************************/


bool DomParser::setContent( QIODevice * _source )
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


QDomElement DomParser::documentElement() const
{
    return m_parser->documentElement();
}


/***********************************************************************/


void DomParser::addContact( const QString &_strName,
                           const QString &_strText )
{
    /*-----------------------------------------------------*/

    m_mainElement->appendChild(
                contact( _strName, _strText )
                );

    /*-----------------------------------------------------*/
}


/***********************************************************************/


void DomParser::inputDataInFile( QIODevice * _source )
{
    if( _source->open( QFile::WriteOnly | QFile::Truncate ) )
    {
         QTextStream( _source ) << m_parser->toString();
        _source->close();
    }
}


/***********************************************************************/


void DomParser::createPhonebookStruct( QMap< QString, QString > & _data )
{

    /*----------------------------------------------------*/

    m_parser->clear();

    delete m_mainElement;
    m_mainElement = new QDomElement(
                m_parser->createElement( "phonebook" )
                );

    m_parser->appendChild( *m_mainElement );


    /*----------------------------------------------------*/


    QMap< QString, QString >::iterator it = _data.begin();

    while( it != _data.end() )
    {
        addContact( it.key(), it.value() );
        it++;

    }


    /*----------------------------------------------------*/
}
