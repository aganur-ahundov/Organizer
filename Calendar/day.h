#ifndef DAY_H
#define DAY_H

#include <QLabel>
#include <QMouseEvent>

class Day
        : public QLabel
{
    Q_OBJECT

public:
    explicit Day( QString const & _str, QWidget * _parent = 0 )
        : QLabel( _str, _parent )
    {
        QPalette p;

        p.setBrush(this->backgroundRole(), QBrush(Qt::blue) );
        setPalette(p);

    }


signals:

    void clicked();

protected:

    void mouseDoubleClickEvent( QMouseEvent *_event )
    {
        if( _event->button() & Qt::LeftButton )
        {
           //setTextInteractionFlags(Qt::TextSelectableByMouse);
           // setStyleSheet("color: blue");
            emit clicked( );
        }
    }
};

#endif // DAY_H
