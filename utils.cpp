#include "utils.h"
#include <QMessageBox>


Utils::Utils()
{

}

bool Utils::MessageYesORNo(QWidget* pt, QString titulo, QString msg, QString msgYes, QString msgNo){
    QMessageBox messageBox(QMessageBox::Question,titulo,
                           msg ,
                           QMessageBox::Yes | QMessageBox::No,
                           pt
                           );

    QFont font;
    font.setPointSize(12);
    messageBox.setFont(font);
    messageBox.setButtonText(QMessageBox::Yes, msgYes);
    messageBox.setButtonText(QMessageBox::No, msgNo);

    if(messageBox.exec() == QMessageBox::No){
        return false;
    }
    else{
        return true;
    }
}

void Utils::MessageOk(QWidget* pt, QString titulo, QString msg, QString msgOk, QMessageBox::Icon type){

    QFont font;
    font.setPointSize(12);

    QMessageBox messageBox(type,
                           titulo,
                           msg ,
                           QMessageBox::Ok,
                           pt
                           );
    messageBox.setButtonText(QMessageBox::Ok, msgOk);
    messageBox.setFont(font);
    messageBox.exec();

}
