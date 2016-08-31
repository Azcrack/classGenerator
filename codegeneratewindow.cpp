#include "codegeneratewindow.h"

CodeGenerateWindow::CodeGenerateWindow(QString &headerCode, QString &cppCode, QString &className, QWidget *parent = 0) : QDialog(parent)
{
    headerCodeGenerate = new QTextEdit;
        headerCodeGenerate->setPlainText(headerCode);
        headerCodeGenerate->setFont(QFont("Courier"));
        headerCodeGenerate->setReadOnly(true);
        //headerCodeGenerate->setLineWrapMode(QTextEdit::NoWrap);
        headerCodeGenerate->setStyleSheet("background-color:#e2e2e2;border: 0px, solid, #e2e2e2");


    cppCodeGenerate = new QTextEdit;
        cppCodeGenerate->setPlainText(cppCode);
        cppCodeGenerate->setFont(QFont("Courier"));
        cppCodeGenerate->setReadOnly(true);
        cppCodeGenerate->setLineWrapMode(QTextEdit::NoWrap);
        cppCodeGenerate->setStyleSheet("background-color:#e2e2e2;border: 0px, solid, #e2e2e2");

    quit = new QPushButton("Quit");

    QString titleTab1 = className.toLower() + ".h";
    QString titleTab2 = className.toLower() + ".cpp";

    tabWidget = new QTabWidget;
        tabWidget->insertTab(0, headerCodeGenerate, titleTab1);
        tabWidget->insertTab(1, cppCodeGenerate, titleTab2);



    QVBoxLayout *rootLayout = new QVBoxLayout;
        rootLayout->addWidget(tabWidget);
        rootLayout->addWidget(quit);

    setFixedSize(570, 580);
    setLayout(rootLayout);
    setWindowTitle("Code generate");

    QObject::connect(quit, SIGNAL(clicked()), this, SLOT(close()));
}
