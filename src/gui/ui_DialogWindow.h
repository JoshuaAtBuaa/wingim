/********************************************************************************
** Form generated from reading ui file 'DialogWindow.ui'
**
** Created: Tue Oct 6 13:20:50 2009
**      by: Qt User Interface Compiler version 4.5.2
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_DIALOGWINDOW_H
#define UI_DIALOGWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTextEdit>
#include <QtGui/QToolButton>
#include <QtGui/QWidget>
#include "WingTabWidget.h"

QT_BEGIN_NAMESPACE

class Ui_DialogWindow
{
public:
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    WingTabWidget *tabWidget;
    QWidget *tab;
    QWidget *tab_2;
    QHBoxLayout *horizontalLayout_2;
    QToolButton *toolButton;
    QToolButton *toolButton_2;
    QSpacerItem *horizontalSpacer_2;
    QTextEdit *textInput;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *clearButton;
    QPushButton *sendButton;

    void setupUi(QWidget *DialogWindow)
    {
        if (DialogWindow->objectName().isEmpty())
            DialogWindow->setObjectName(QString::fromUtf8("DialogWindow"));
        DialogWindow->resize(540, 400);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(DialogWindow->sizePolicy().hasHeightForWidth());
        DialogWindow->setSizePolicy(sizePolicy);
        gridLayout_2 = new QGridLayout(DialogWindow);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setMargin(6);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(0);
        gridLayout->setMargin(0);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setSizeConstraint(QLayout::SetMinimumSize);
        tabWidget = new WingTabWidget(DialogWindow);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        sizePolicy.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy);
        tabWidget->setContextMenuPolicy(Qt::NoContextMenu);
        tabWidget->setStyleSheet(QString::fromUtf8("QTabBar::tab \n"
"{\n"
"	min-width: 100px;\n"
"	max-width: 100px;\n"
"}"));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        tabWidget->addTab(tab_2, QString());

        gridLayout->addWidget(tabWidget, 0, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        toolButton = new QToolButton(DialogWindow);
        toolButton->setObjectName(QString::fromUtf8("toolButton"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(toolButton->sizePolicy().hasHeightForWidth());
        toolButton->setSizePolicy(sizePolicy1);

        horizontalLayout_2->addWidget(toolButton);

        toolButton_2 = new QToolButton(DialogWindow);
        toolButton_2->setObjectName(QString::fromUtf8("toolButton_2"));

        horizontalLayout_2->addWidget(toolButton_2);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        gridLayout->addLayout(horizontalLayout_2, 1, 0, 1, 1);

        textInput = new QTextEdit(DialogWindow);
        textInput->setObjectName(QString::fromUtf8("textInput"));
        sizePolicy.setHeightForWidth(textInput->sizePolicy().hasHeightForWidth());
        textInput->setSizePolicy(sizePolicy);

        gridLayout->addWidget(textInput, 2, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        clearButton = new QPushButton(DialogWindow);
        clearButton->setObjectName(QString::fromUtf8("clearButton"));

        horizontalLayout->addWidget(clearButton);

        sendButton = new QPushButton(DialogWindow);
        sendButton->setObjectName(QString::fromUtf8("sendButton"));

        horizontalLayout->addWidget(sendButton);


        gridLayout->addLayout(horizontalLayout, 3, 0, 1, 1);

        gridLayout->setRowStretch(0, 20);
        gridLayout->setRowStretch(1, 1);
        gridLayout->setRowStretch(2, 5);
        gridLayout->setRowStretch(3, 1);

        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);


        retranslateUi(DialogWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(DialogWindow);
    } // setupUi

    void retranslateUi(QWidget *DialogWindow)
    {
        DialogWindow->setWindowTitle(QApplication::translate("DialogWindow", "DialogWindow", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("DialogWindow", "Tab 1", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("DialogWindow", "Tab 2", 0, QApplication::UnicodeUTF8));
        toolButton->setText(QApplication::translate("DialogWindow", "...", 0, QApplication::UnicodeUTF8));
        toolButton_2->setText(QApplication::translate("DialogWindow", "...", 0, QApplication::UnicodeUTF8));
        clearButton->setText(QApplication::translate("DialogWindow", "clear", 0, QApplication::UnicodeUTF8));
        sendButton->setText(QApplication::translate("DialogWindow", "send", 0, QApplication::UnicodeUTF8));
        sendButton->setShortcut(QApplication::translate("DialogWindow", "Ctrl+Return", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(DialogWindow);
    } // retranslateUi

};

namespace Ui {
    class DialogWindow: public Ui_DialogWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGWINDOW_H
