/********************************************************************************
** Form generated from reading UI file 'textinputdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TEXTINPUTDIALOG_H
#define UI_TEXTINPUTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLineEdit>

QT_BEGIN_NAMESPACE

class Ui_TextInputDialog
{
public:
    QGridLayout *gridLayout;
    QDialogButtonBox *buttonBox;
    QLineEdit *lineEdit;

    void setupUi(QDialog *TextInputDialog)
    {
        if (TextInputDialog->objectName().isEmpty())
            TextInputDialog->setObjectName(QString::fromUtf8("TextInputDialog"));
        TextInputDialog->resize(371, 74);
        gridLayout = new QGridLayout(TextInputDialog);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        buttonBox = new QDialogButtonBox(TextInputDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 1, 0, 1, 1);

        lineEdit = new QLineEdit(TextInputDialog);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        gridLayout->addWidget(lineEdit, 0, 0, 1, 1);


        retranslateUi(TextInputDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), TextInputDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), TextInputDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(TextInputDialog);
    } // setupUi

    void retranslateUi(QDialog *TextInputDialog)
    {
        TextInputDialog->setWindowTitle(QCoreApplication::translate("TextInputDialog", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TextInputDialog: public Ui_TextInputDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TEXTINPUTDIALOG_H
