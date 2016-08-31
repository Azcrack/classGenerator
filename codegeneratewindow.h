#ifndef CODEGENERATEWINDOW_H
#define CODEGENERATEWINDOW_H

#include <QtWidgets>

class CodeGenerateWindow : public QDialog
{
public:
    CodeGenerateWindow(QString &headerCode, QString &cppCode, QString &className, QWidget *parent);

private:
    QTextEdit *headerCodeGenerate;
    QTextEdit *cppCodeGenerate;
    QPushButton *quit;

    QTabWidget *tabWidget;
};

#endif // CODEGENERATEWINDOW_H
