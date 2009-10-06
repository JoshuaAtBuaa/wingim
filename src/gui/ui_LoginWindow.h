/********************************************************************************
** Form generated from reading ui file 'LoginWindow.ui'
**
** Created: Tue Oct 6 13:20:50 2009
**      by: Qt User Interface Compiler version 4.5.2
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_LOGINWINDOW_H
#define UI_LOGINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LoginWindow
{
public:
    QLabel *accLabel;
    QLabel *passLabel;
    QLineEdit *accInput;
    QLineEdit *pwdInput;
    QComboBox *statusBox;
    QCheckBox *remeberBox;
    QPushButton *loginBtn;
    QLabel *picLabel;

    void setupUi(QWidget *LoginWindow)
    {
        if (LoginWindow->objectName().isEmpty())
            LoginWindow->setObjectName(QString::fromUtf8("LoginWindow"));
        LoginWindow->resize(380, 265);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(LoginWindow->sizePolicy().hasHeightForWidth());
        LoginWindow->setSizePolicy(sizePolicy);
        LoginWindow->setMinimumSize(QSize(380, 265));
        LoginWindow->setMaximumSize(QSize(380, 265));
        LoginWindow->setStyleSheet(QString::fromUtf8(""));
        accLabel = new QLabel(LoginWindow);
        accLabel->setObjectName(QString::fromUtf8("accLabel"));
        accLabel->setGeometry(QRect(25, 116, 61, 21));
        accLabel->setStyleSheet(QString::fromUtf8(""));
        passLabel = new QLabel(LoginWindow);
        passLabel->setObjectName(QString::fromUtf8("passLabel"));
        passLabel->setGeometry(QRect(25, 177, 61, 18));
        accInput = new QLineEdit(LoginWindow);
        accInput->setObjectName(QString::fromUtf8("accInput"));
        accInput->setGeometry(QRect(25, 144, 145, 25));
        sizePolicy.setHeightForWidth(accInput->sizePolicy().hasHeightForWidth());
        accInput->setSizePolicy(sizePolicy);
        accInput->setMinimumSize(QSize(145, 25));
        accInput->setMaximumSize(QSize(145, 25));
        pwdInput = new QLineEdit(LoginWindow);
        pwdInput->setObjectName(QString::fromUtf8("pwdInput"));
        pwdInput->setGeometry(QRect(25, 200, 145, 25));
        sizePolicy.setHeightForWidth(pwdInput->sizePolicy().hasHeightForWidth());
        pwdInput->setSizePolicy(sizePolicy);
        pwdInput->setMinimumSize(QSize(145, 25));
        pwdInput->setMaximumSize(QSize(145, 25));
        pwdInput->setEchoMode(QLineEdit::Password);
        statusBox = new QComboBox(LoginWindow);
        statusBox->setObjectName(QString::fromUtf8("statusBox"));
        statusBox->setGeometry(QRect(180, 144, 68, 25));
        sizePolicy.setHeightForWidth(statusBox->sizePolicy().hasHeightForWidth());
        statusBox->setSizePolicy(sizePolicy);
        statusBox->setMinimumSize(QSize(0, 25));
        statusBox->setMaximumSize(QSize(16777215, 25));
        remeberBox = new QCheckBox(LoginWindow);
        remeberBox->setObjectName(QString::fromUtf8("remeberBox"));
        remeberBox->setGeometry(QRect(180, 200, 81, 25));
        sizePolicy.setHeightForWidth(remeberBox->sizePolicy().hasHeightForWidth());
        remeberBox->setSizePolicy(sizePolicy);
        remeberBox->setMinimumSize(QSize(0, 25));
        remeberBox->setMaximumSize(QSize(16777215, 25));
        loginBtn = new QPushButton(LoginWindow);
        loginBtn->setObjectName(QString::fromUtf8("loginBtn"));
        loginBtn->setGeometry(QRect(265, 227, 70, 26));
        picLabel = new QLabel(LoginWindow);
        picLabel->setObjectName(QString::fromUtf8("picLabel"));
        picLabel->setGeometry(QRect(18, 10, 340, 100));
        QWidget::setTabOrder(accInput, statusBox);
        QWidget::setTabOrder(statusBox, pwdInput);
        QWidget::setTabOrder(pwdInput, remeberBox);
        QWidget::setTabOrder(remeberBox, loginBtn);

        retranslateUi(LoginWindow);

        QMetaObject::connectSlotsByName(LoginWindow);
    } // setupUi

    void retranslateUi(QWidget *LoginWindow)
    {
        LoginWindow->setWindowTitle(QApplication::translate("LoginWindow", "Login", 0, QApplication::UnicodeUTF8));
        accLabel->setText(QApplication::translate("LoginWindow", "account:", 0, QApplication::UnicodeUTF8));
        passLabel->setText(QApplication::translate("LoginWindow", "passwd:", 0, QApplication::UnicodeUTF8));
        remeberBox->setText(QApplication::translate("LoginWindow", "remeber", 0, QApplication::UnicodeUTF8));
        loginBtn->setText(QApplication::translate("LoginWindow", "login", 0, QApplication::UnicodeUTF8));
        loginBtn->setShortcut(QApplication::translate("LoginWindow", "Return", 0, QApplication::UnicodeUTF8));
        picLabel->setText(QString());
        Q_UNUSED(LoginWindow);
    } // retranslateUi

};

namespace Ui {
    class LoginWindow: public Ui_LoginWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINWINDOW_H
