#ifndef CLASSGENERATORWINDOW_H
#define CLASSGENERATORWINDOW_H

#include <QtWidgets>


class ClassGeneratorWindow : public QWidget
{
    Q_OBJECT

public:
    ClassGeneratorWindow();


public slots:
    void generateCode();

private:
    QLabel *classNameLabel;
    QLabel *headerClassNameLabel;
    QLabel *motherClassNameLabel;

    QLineEdit *className;
    QLineEdit *headerClassName;
    QLineEdit *motherClassName;

    QGroupBox *attrAndMethGroup;
    QCheckBox *headerProtection;
    QCheckBox *constructorGenerate;
    QCheckBox *destructorGenerate;
    QCheckBox *includeIOstream;

    QLabel *authorLabel;
    QLabel *dateLabel;
    QLabel *organisationLabel;
    QLabel *descriptionLabel;

    QRadioButton *btnArray[5];

    QLineEdit *attrOrMethName;
    QCheckBox *isStatic;
    QCheckBox *isFriend;
    QCheckBox *isVirtual;
    QCheckBox *isPureVirtual;

    QPushButton *validateNewItem;
    QListView *viewUserAttrAndMeth;

    QGroupBox *commentsBox;
    QLineEdit *author;
    QDateEdit *date;
    QLineEdit *organisation;
    QTextEdit *description;

    QPushButton *done;
    QPushButton *quit;

};


#endif // CLASSGENERATORWINDOW_H
