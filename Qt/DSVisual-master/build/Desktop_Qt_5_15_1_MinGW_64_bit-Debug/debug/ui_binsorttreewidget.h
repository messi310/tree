/********************************************************************************
** Form generated from reading UI file 'binsorttreewidget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BINSORTTREEWIDGET_H
#define UI_BINSORTTREEWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BinSortTreeWidget
{
public:
    QGridLayout *gridLayout;
    QLabel *label_nodeCount;
    QLabel *label;
    QGraphicsView *graphicsView;
    QPushButton *button_order;
    QSpacerItem *verticalSpacer;
    QLabel *label_treeDepth;
    QSpacerItem *verticalSpacer_2;
    QPushButton *button_find;

    void setupUi(QWidget *BinSortTreeWidget)
    {
        if (BinSortTreeWidget->objectName().isEmpty())
            BinSortTreeWidget->setObjectName(QString::fromUtf8("BinSortTreeWidget"));
        BinSortTreeWidget->resize(400, 300);
        gridLayout = new QGridLayout(BinSortTreeWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_nodeCount = new QLabel(BinSortTreeWidget);
        label_nodeCount->setObjectName(QString::fromUtf8("label_nodeCount"));

        gridLayout->addWidget(label_nodeCount, 5, 1, 1, 1);

        label = new QLabel(BinSortTreeWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setStyleSheet(QString::fromUtf8(""));
        label->setMargin(0);

        gridLayout->addWidget(label, 0, 1, 1, 1);

        graphicsView = new QGraphicsView(BinSortTreeWidget);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));

        gridLayout->addWidget(graphicsView, 0, 0, 7, 1);

        button_order = new QPushButton(BinSortTreeWidget);
        button_order->setObjectName(QString::fromUtf8("button_order"));

        gridLayout->addWidget(button_order, 2, 1, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 4, 1, 1, 1);

        label_treeDepth = new QLabel(BinSortTreeWidget);
        label_treeDepth->setObjectName(QString::fromUtf8("label_treeDepth"));

        gridLayout->addWidget(label_treeDepth, 6, 1, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout->addItem(verticalSpacer_2, 1, 1, 1, 1);

        button_find = new QPushButton(BinSortTreeWidget);
        button_find->setObjectName(QString::fromUtf8("button_find"));

        gridLayout->addWidget(button_find, 3, 1, 1, 1);


        retranslateUi(BinSortTreeWidget);

        QMetaObject::connectSlotsByName(BinSortTreeWidget);
    } // setupUi

    void retranslateUi(QWidget *BinSortTreeWidget)
    {
        BinSortTreeWidget->setWindowTitle(QCoreApplication::translate("BinSortTreeWidget", "Form", nullptr));
        label_nodeCount->setText(QCoreApplication::translate("BinSortTreeWidget", "   \344\272\214\345\217\211\346\240\221\347\273\223\347\202\271\346\225\260:0", nullptr));
        label->setText(QCoreApplication::translate("BinSortTreeWidget", "\344\272\214\345\217\211\346\216\222\345\272\217\346\240\221\345\217\257\350\247\206\345\214\226", nullptr));
        button_order->setText(QCoreApplication::translate("BinSortTreeWidget", "\345\215\207\345\272\217\351\201\215\345\216\206", nullptr));
        label_treeDepth->setText(QCoreApplication::translate("BinSortTreeWidget", "   \344\272\214\345\217\211\346\240\221\346\267\261\345\272\246:0", nullptr));
        button_find->setText(QCoreApplication::translate("BinSortTreeWidget", "\346\237\245\346\211\276\347\273\223\347\202\271", nullptr));
    } // retranslateUi

};

namespace Ui {
    class BinSortTreeWidget: public Ui_BinSortTreeWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BINSORTTREEWIDGET_H
