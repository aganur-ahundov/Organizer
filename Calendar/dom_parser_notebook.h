#ifndef DOMPARSER_H
#define DOMPARSER_H

#include <QWidget>
#include <QtXml/QDomElement>


class QDomDocument;
class QDomNode;
class QFile;


class NotebookParser
        : public QWidget
{
    Q_OBJECT
public:
    explicit NotebookParser( QString const & _title, QWidget *parent = 0 );
    explicit NotebookParser( QFile * _file );

    ~NotebookParser();

private:

    QDomDocument * m_parser;
    QDomElement * m_mainElement;

public:

    bool setContent( QIODevice * _source );

    QDomElement documentElement() const;

    void traverseNode ( const QDomNode & _node, QMap < QString, QString > *_data );

private:

    QDomElement makeElement( const QString & _strName,
                               const QString & _strText = QString() );

    QDomElement note( const QString & _strDate,
                         const QString & _strText );

public:

    void addNote( const QString & _strName,
                    const QString & _strText );

    void inputDataInFile( QIODevice * _source );

    QDomElement * findElement( QString const & _name );

    void createNotebookStruct( QMap< QString, QString > & _data );

public slots:

  //  void deleteElement( QString const & _name );
  //  void renameElement( QString const & _oldName, QString const & _newName );
};

#endif // DOMPARSER_H
