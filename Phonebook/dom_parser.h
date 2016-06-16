#ifndef DOMPARSER_H
#define DOMPARSER_H

#include <QWidget>
#include <QtXml/QDomElement>


class QDomDocument;
class QDomNode;
class QFile;


class DomParser
        : public QWidget
{
    Q_OBJECT
public:
    explicit DomParser( QString const & _title, QWidget *parent = 0 );
    explicit DomParser( QFile * _file );

    ~DomParser();

private:

    QDomDocument * m_parser;
    QDomElement * m_mainElement;

public:

    bool setContent( QIODevice * _source );

    QDomElement documentElement() const;

    void traverseNode ( const QDomNode & _node, QMap< QString, QString > *_data );

private:

    QDomElement makeElement( const QString & _strName,
                               const QString & _strText = QString(),
                               const QString & _strAtr = QString() );

    QDomElement contact( const QString & _strName,
                         const QString & _strText );

public:

    void addContact( const QString & _strName,
                    const QString & _strText );

    void inputDataInFile( QIODevice * _source );

    QDomElement * findElement( QString const & _name );

    void createPhonebookStruct( QMap< QString, QString > & _data );

public slots:

  //  void deleteElement( QString const & _name );
  //  void renameElement( QString const & _oldName, QString const & _newName );
};

#endif // DOMPARSER_H
