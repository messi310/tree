/********************************************************************************
** Form generated from reading UI file 'thrdbintreewidget.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_THRDBINTREEWIDGET_H
#define UI_THRDBINTREEWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ThrdBinTreeWidget
{
public:
    QGridLayout *gridLayout;
    QSpacerItem *verticalSpacer;
    QSpacerItem *verticalSpacer_2;
    QLabel *label_nodeCount;
    QPushButton *button_postorder;
    QLabel *label_treeDepth;
    QPushButton *button_preorder;
    QLabel *label;
    QPushButton *button_inorder;
    QGraphicsView *graphicsView;

    void setupUi(QWidget *ThrdBinTreeWidget)
    {
        if (ThrdBinTreeWidget->objectName().isEmpty())
            ThrdBinTreeWidget->setObjectName("ThrdBinTreeWidget");
        ThrdBinTreeWidget->resize(400, 335);
        gridLayout = new QGridLayout(ThrdBinTreeWidget);
        gridLayout->setObjectName("gridLayout");
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 9, 1, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout->addItem(verticalSpacer_2, 1, 1, 1, 1);

        label_nodeCount = new QLabel(ThrdBinTreeWidget);
        label_nodeCount->setObjectName("label_nodeCount");

        gridLayout->addWidget(label_nodeCount, 10, 1, 1, 1);

        button_postorder = new QPushButton(ThrdBinTreeWidget);
        button_postorder->setObjectName("button_postorder");

        gridLayout->addWidget(button_postorder, 8, 1, 1, 1);

        label_treeDepth = new QLabel(ThrdBinTreeWidget);
        label_treeDepth->setObjectName("label_treeDepth");

        gridLayout->addWidget(label_treeDepth, 11, 1, 1, 1);

        button_preorder = new QPushButton(ThrdBinTreeWidget);
        button_preorder->setObjectName("button_preorder");

        gridLayout->addWidget(button_preorder, 6, 1, 1, 1);

        label = new QLabel(ThrdBinTreeWidget);
        label->setObjectName("label");
        label->setStyleSheet(QString::fromUtf8(""));
        label->setTextFormat(Qt::AutoText);
        label->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label, 0, 1, 1, 1);

        button_inorder = new QPushButton(ThrdBinTreeWidget);
        button_inorder->setObjectName("button_inorder");

        gridLayout->addWidget(button_inorder, 7, 1, 1, 1);

        graphicsView = new QGraphicsView(ThrdBinTreeWidget);
        graphicsView->setObjectName("graphicsView");

        gridLayout->addWidget(graphicsView, 0, 0, 13, 1);


        retranslateUi(ThrdBinTreeWidget);

        QMetaObject::connectSlotsByName(ThrdBinTreeWidget);
    } // setupUi

    void retranslateUi(QWidget *ThrdBinTreeWidget)
    {
        ThrdBinTreeWidget->setWindowTitle(QCoreApplication::translate("ThrdBinTreeWidget", "Form", nullptr));
        label_nodeCount->setText(QCoreApplication::translate("ThrdBinTreeWidget", "   \344\272\214\345\217\211\346\240\221\347\273\223\347\202\271\346\225\260:1", nullptr));
        button_postorder->setText(QCoreApplication::translate("ThrdBinTreeWidget", "\345\220\216\345\272\217\351\201\215\345\216\206", nullptr));
        label_treeDepth->setText(QCoreApplication::translate("ThrdBinTreeWidget", "   \344\272\214\345\217\211\346\240\221\346\267\261\345\272\246:1", nullptr));
        button_preorder->setText(QCoreApplication::translate("ThrdBinTreeWidget", "\345\205\210\345\272\217\351\201\215\345\216\206", nullptr));
        label->setText(QCoreApplication::translate("ThrdBinTreeWidget", "\344\272\214\345\217\211\346\240\221\345\217\257\350\247\206\345\214\226", nullptr));
        button_inorder->setText(QCoreApplication::translate("ThrdBinTreeWidget", "\344\270\255\345\272\217\351\201\215\345\216\206", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ThrdBinTreeWidget: public Ui_ThrdBinTreeWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_THRDBINTREEWIDGET_H
