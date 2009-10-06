/********************************************************************************
** Form generated from reading ui file 'MainWindow.ui'
**
** Created: Tue Oct 6 13:20:50 2009
**      by: Qt User Interface Compiler version 4.5.2
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QSpacerItem>
#include <QtGui/QToolButton>
#include <QtGui/QTreeWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_2;
    QFrame *frame;
    QGridLayout *gridLayout;
    QToolButton *portrait;
    QVBoxLayout *verticalLayout_2;
    QLabel *nickName;
    QLabel *signature;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *spacerItem;
    QToolButton *skinBtn;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QTreeWidget *contactTreeView;
    QToolButton *menuBtn;

    void setupUi(QWidget *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(222, 535);
        QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMinimumSize(QSize(222, 512));
        MainWindow->setMaximumSize(QSize(222, 16777215));
        verticalLayout_3 = new QVBoxLayout(MainWindow);
        verticalLayout_3->setSpacing(4);
        verticalLayout_3->setMargin(4);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(4);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setSizeConstraint(QLayout::SetFixedSize);
        frame = new QFrame(MainWindow);
        frame->setObjectName(QString::fromUtf8("frame"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
        frame->setSizePolicy(sizePolicy1);
        frame->setMinimumSize(QSize(71, 71));
        frame->setMaximumSize(QSize(71, 71));
        frame->setSizeIncrement(QSize(0, 0));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        gridLayout = new QGridLayout(frame);
        gridLayout->setSpacing(0);
        gridLayout->setMargin(2);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        portrait = new QToolButton(frame);
        portrait->setObjectName(QString::fromUtf8("portrait"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(portrait->sizePolicy().hasHeightForWidth());
        portrait->setSizePolicy(sizePolicy2);
        portrait->setMinimumSize(QSize(0, 0));
        portrait->setCursor(QCursor(Qt::PointingHandCursor));
        portrait->setIconSize(QSize(85, 85));

        gridLayout->addWidget(portrait, 0, 0, 1, 1);


        horizontalLayout_2->addWidget(frame);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        nickName = new QLabel(MainWindow);
        nickName->setObjectName(QString::fromUtf8("nickName"));
        nickName->setTextInteractionFlags(Qt::LinksAccessibleByMouse);

        verticalLayout_2->addWidget(nickName);

        signature = new QLabel(MainWindow);
        signature->setObjectName(QString::fromUtf8("signature"));

        verticalLayout_2->addWidget(signature);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        spacerItem = new QSpacerItem(40, 16, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(spacerItem);

        skinBtn = new QToolButton(MainWindow);
        skinBtn->setObjectName(QString::fromUtf8("skinBtn"));
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(skinBtn->sizePolicy().hasHeightForWidth());
        skinBtn->setSizePolicy(sizePolicy3);
        skinBtn->setMaximumSize(QSize(20, 20));

        horizontalLayout->addWidget(skinBtn);


        verticalLayout_2->addLayout(horizontalLayout);

        verticalLayout_2->setStretch(0, 1);
        verticalLayout_2->setStretch(1, 1);
        verticalLayout_2->setStretch(2, 1);

        horizontalLayout_2->addLayout(verticalLayout_2);


        verticalLayout_3->addLayout(horizontalLayout_2);

        widget = new QWidget(MainWindow);
        widget->setObjectName(QString::fromUtf8("widget"));
        sizePolicy3.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy3);
        verticalLayout = new QVBoxLayout(widget);
#ifndef Q_OS_MAC
        verticalLayout->setSpacing(6);
#endif
        verticalLayout->setMargin(1);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        contactTreeView = new QTreeWidget(widget);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QString::fromUtf8("1"));
        contactTreeView->setHeaderItem(__qtreewidgetitem);
        contactTreeView->setObjectName(QString::fromUtf8("contactTreeView"));
        contactTreeView->setTextElideMode(Qt::ElideLeft);

        verticalLayout->addWidget(contactTreeView);


        verticalLayout_3->addWidget(widget);

        menuBtn = new QToolButton(MainWindow);
        menuBtn->setObjectName(QString::fromUtf8("menuBtn"));

        verticalLayout_3->addWidget(menuBtn);

        verticalLayout_3->setStretch(1, 20);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QWidget *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "WING", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_STATUSTIP
        portrait->setStatusTip(QString());
#endif // QT_NO_STATUSTIP
        portrait->setText(QString());
        nickName->setText(QString());
        signature->setText(QString());
#ifndef QT_NO_TOOLTIP
        skinBtn->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        skinBtn->setText(QString());
        menuBtn->setText(QApplication::translate("MainWindow", "menu", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(MainWindow);
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
