#ifndef MOBILENUMBERVALIDATOR_H
#define MOBILENUMBERVALIDATOR_H

#include <QValidator>


class MobileNumberValidator
    : public QValidator
{
    Q_OBJECT

public:

    MobileNumberValidator( QObject * _parent = 0 )
        : QValidator( _parent )
    {
    }

    ~MobileNumberValidator() = default;

    virtual State validate( QString & _text, int & _pos ) const
    {

       QRegExp rxp = QRegExp( "[0-9]" );

        if( ( _text.contains( rxp ) ) )
        {

            if( _text.size() < 11 )
                return Intermediate;

            if ( _text.size() >= 14 )
                return Invalid;

            return Acceptable;
        }
        else if( _text[0] == '+' && _text.size() == 1 )
            return Acceptable;
        else
            return Invalid;
    }
};


#endif // MOBILENUMBERVALIDATOR_H
