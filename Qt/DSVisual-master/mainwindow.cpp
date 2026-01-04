#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_action_thrdBinTree_triggered()
{//二叉树线索化
    if(centralWidget() != nullptr) centralWidget()->setParent(nullptr);
    this->setCentralWidget(&m_ThrdBinTreeWidget);
}
