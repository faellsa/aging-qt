#ifndef UTILS_H
#define UTILS_H

#include <QMessageBox>
#include <QWidget>

class Utils
{
public:
    Utils();
    static bool MessageYesORNo(QWidget *pt, QString titulo, QString msg, QString msgYes, QString msgNo);
    static void MessageOk(QWidget *pt, QString titulo, QString msg, QString msgOk, QMessageBox::Icon type);
};

#endif // UTILS_H
