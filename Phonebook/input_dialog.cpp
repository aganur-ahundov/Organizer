#include "input_dialog.h"
#include "mobile_number_validator.h"

#include <QtWidgets>


/***********************************************************************/

InputDialog::~InputDialog()
{
    delete m_pNameEdit;
    delete m_pNumberEdit;
}

/***********************************************************************/

InputDialog::InputDialog( QWidget * _parent )
    :QDialog( _parent, Qt::WindowTitleHint | Qt::WindowSystemMenuHint    )
{
    /*------------------------------------------------*/

    m_pNameEdit = new QLineEdit;
    m_pNumberEdit = new QLineEdit;

    m_pNumberEdit->setValidator( new MobileNumberValidator() );


    QLabel * pNameLbl = new QLabel( "&Имя: " );
    QLabel * pNumberLbl = new QLabel ( "&Номер телефона: " );

    /*------------------------------------------------*/

    pNameLbl->setBuddy( m_pNameEdit );
    pNumberLbl->setBuddy( m_pNumberEdit );

    /*------------------------------------------------*/

    QPushButton * pAddButton = new QPushButton( "Добавить" );
    QPushButton * pCancelButton = new QPushButton( "Отмена" );

    connect( pAddButton, SIGNAL( clicked( bool ) ), SLOT( sentData() ) );
    connect( pCancelButton, SIGNAL( clicked( bool ) ), SLOT( close() ) );

    /*------------------------------------------------*/

    QGridLayout * pGridLayout = new QGridLayout;

    pGridLayout->addWidget( pNameLbl, 0, 0 );
    pGridLayout->addWidget( m_pNameEdit, 0 , 1 );
    pGridLayout->addWidget( pNumberLbl, 1, 0 );
    pGridLayout->addWidget( m_pNumberEdit, 1, 1 );
    pGridLayout->addWidget( pAddButton, 2, 0 );
    pGridLayout->addWidget( pCancelButton, 2, 1 );

    /*------------------------------------------------*/

    setModal( true );
    setLayout( pGridLayout );

    /*------------------------------------------------*/

}

/***********************************************************************/

QString InputDialog::getName() const
{
    return m_pNameEdit->text();
}

/***********************************************************************/

QString InputDialog::getNumber() const
{
    return m_pNumberEdit->text();
}

/***********************************************************************/


void InputDialog::sentData()
{

    close();

    emit sent( getName(), getNumber() );

}

/***********************************************************************/
