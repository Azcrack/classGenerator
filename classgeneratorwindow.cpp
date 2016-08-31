#include "classgeneratorwindow.h"
#include "codegeneratewindow.h"

ClassGeneratorWindow::ClassGeneratorWindow()
{
    validateNewItem = new QPushButton("Validate");


    QStringList attrMethList;
//    attrMethList << "int x" << "int y" << "void count()" << "int getX()" << "int getY()" << "void setX(int x)" << "void setY(int y)";

    QStringListModel *mod = new QStringListModel(attrMethList);

    viewUserAttrAndMeth = new QListView();
        viewUserAttrAndMeth->setStyleSheet("background-color:#e2e2e2;border: 0px, solid, #e2e2e2");
        viewUserAttrAndMeth->setModel(mod);


    className       = new QLineEdit;
    headerClassName = new QLineEdit;
    motherClassName = new QLineEdit;

    classNameLabel = new QLabel("Name of class:");
    headerClassNameLabel = new QLabel("Name of header:");
    motherClassNameLabel = new QLabel("Name of mother class:");

    QFont font;
        font.setCapitalization(QFont::AllUppercase);

    headerClassName->setFont(font);
    headerClassName->setReadOnly(true);

    QVBoxLayout *classDefinitionLayout = new QVBoxLayout;
        classDefinitionLayout->addWidget(classNameLabel);
        classDefinitionLayout->addWidget(className);
        classDefinitionLayout->addWidget(headerClassNameLabel);
        classDefinitionLayout->addWidget(headerClassName);
        classDefinitionLayout->addWidget(motherClassNameLabel);
        classDefinitionLayout->addWidget(motherClassName);


    QGroupBox *classDefinitionGroup = new QGroupBox("Definition of the class");
        classDefinitionGroup->setLayout(classDefinitionLayout);

    headerProtection    = new QCheckBox("Protect the header against the multiples inclusions.");
        headerProtection->setChecked(true);
    constructorGenerate = new QCheckBox("Generate a default constructor.");
        constructorGenerate->setChecked(true);
    destructorGenerate  = new QCheckBox("Generate a default destructor.");
        destructorGenerate->setChecked(true);
    includeIOstream = new QCheckBox("Include iostream lib. in header.");


    QVBoxLayout *optionClassLayout = new QVBoxLayout;
        optionClassLayout->addWidget(headerProtection);
        optionClassLayout->addWidget(constructorGenerate);
        optionClassLayout->addWidget(destructorGenerate);
        optionClassLayout->addWidget(includeIOstream);

    QGroupBox *optionClassGroup = new QGroupBox("Options");
        optionClassGroup->setLayout(optionClassLayout);


    QHBoxLayout *topBoxLayout = new QHBoxLayout;
        topBoxLayout->addWidget(classDefinitionGroup);
        topBoxLayout->addWidget(optionClassGroup);

    QString typeArray[] = { "int", "double", "float", "char", "string", "void" };

    for (int i(0); i <= 5; i++) btnArray[i] = new QRadioButton(typeArray[i]);

    QVBoxLayout *typeLayout = new QVBoxLayout;
        typeLayout->addWidget(btnArray[0]);
        typeLayout->addWidget(btnArray[1]);
        typeLayout->addWidget(btnArray[2]);
        typeLayout->addWidget(btnArray[3]);
        typeLayout->addWidget(btnArray[4]);
        typeLayout->addWidget(btnArray[5]);

    QGroupBox *typeGroup = new QGroupBox("Type:");
        typeGroup->setLayout(typeLayout);


    attrOrMethName = new QLineEdit;
    attrOrMethName->setPlaceholderText("Enter the new method or attribute name");

    isStatic = new QCheckBox("static");
        isStatic->setToolTip("Define as static.");
    isFriend = new QCheckBox("friend");
        isFriend->setToolTip("Define as friend.");
    isVirtual = new QCheckBox("virtual");
        isVirtual->setToolTip("Define as virtual.");
    isPureVirtual = new QCheckBox("pure");
        isPureVirtual->setToolTip("Define as pure virtual.");

    QHBoxLayout *optionalSetting = new QHBoxLayout;
        optionalSetting->addWidget(isStatic);
        optionalSetting->addWidget(isFriend);
        optionalSetting->addWidget(isVirtual);
        optionalSetting->addWidget(isPureVirtual);

    QVBoxLayout *attrAndMethNameLayout = new QVBoxLayout;
        attrAndMethNameLayout->addLayout(optionalSetting);
        attrAndMethNameLayout->addWidget(attrOrMethName);
        attrAndMethNameLayout->addWidget(validateNewItem);

    QGroupBox *attrAndMethNameGroup = new QGroupBox("Name and others settings:");
        attrAndMethNameGroup->setLayout(attrAndMethNameLayout);

    QHBoxLayout *attrAndMethLayout = new QHBoxLayout;
        attrAndMethLayout->addWidget(typeGroup);
        attrAndMethLayout->addWidget(attrAndMethNameGroup);
        attrAndMethLayout->addWidget(viewUserAttrAndMeth);


    attrAndMethGroup = new QGroupBox("Attributes and methods");
    attrAndMethGroup->setLayout(attrAndMethLayout);

    authorLabel = new QLabel("Author:");
    dateLabel = new QLabel("Date:");
    organisationLabel = new QLabel("Organisation:");
    descriptionLabel = new QLabel("Description:");

    author = new QLineEdit;
    date   = new QDateEdit(QDate::currentDate());
    organisation = new QLineEdit;
    description   = new QTextEdit;

    QGridLayout *commentsLayout = new QGridLayout;
        commentsLayout->addWidget(authorLabel, 0, 0);
        commentsLayout->addWidget(author, 0, 1);
        commentsLayout->addWidget(organisationLabel, 0, 2);
        commentsLayout->addWidget(organisation, 0, 3);
        commentsLayout->addWidget(dateLabel, 0, 4);
        commentsLayout->addWidget(date, 0, 5);

        commentsLayout->addWidget(descriptionLabel, 1, 0);
        commentsLayout->addWidget(description, 1, 1, 4, 3);

    commentsBox = new QGroupBox("Add comments");
        commentsBox->setCheckable(true);
        commentsBox->setChecked(false);
        commentsBox->setLayout(commentsLayout);

    done = new QPushButton("Generate", this);
    quit = new QPushButton("Quit", this);

    QHBoxLayout *buttonsLayout = new QHBoxLayout;
        buttonsLayout->setAlignment(Qt::AlignRight);
        buttonsLayout->addWidget(done);
        buttonsLayout->addWidget(quit);


    QVBoxLayout *rootLayout = new QVBoxLayout;
        rootLayout->addLayout(topBoxLayout);
        //rootLayout->addWidget(optionClassGroup);
        rootLayout->addWidget(attrAndMethGroup);
        rootLayout->addWidget(commentsBox);
        rootLayout->addLayout(buttonsLayout);


    QObject::connect(className, SIGNAL(textChanged(QString)), headerClassName, SLOT(setText(QString)));
    QObject::connect(quit, SIGNAL(clicked()), qApp, SLOT(quit()));
    QObject::connect(done, SIGNAL(clicked()), this, SLOT(generateCode()));

    setFixedSize(572, 720);
    setLayout(rootLayout);
    setWindowTitle("Class Generator");

}

void ClassGeneratorWindow::generateCode()
{
    if (className->text().isEmpty())
    {
        QMessageBox::critical(this, "Error", "Invalid class name.");
        return;
    }

    if (destructorGenerate->isChecked() && !constructorGenerate->isChecked())
    {
        QMessageBox::critical(this, "Error", "You can not create a destructor without constructor.");
        return;
    }

    QString headerCode;
    QString cppCode;

    if (commentsBox->isChecked())
    {
        headerCode += "/******************************\n";
        headerCode += " * $Author:\t" + author->text() + "\n";
        headerCode += " * $Organisation:\t" + organisation->text() + "\n";
        headerCode += " * $Date:\t\t" + date->date().toString() + "\n";
        headerCode += " * $Description:\t" + description->toPlainText() + "\n";
        headerCode += " *****************************/\n\n\n";
    }

    if (headerProtection->isChecked())
    {
        headerCode += "#ifndef " + headerClassName->text().toUpper() + "_H\n";
        headerCode += "#define " + headerClassName->text().toUpper() + "_H\n\n";
    }

    if (includeIOstream->isChecked())
        headerCode += "#include <iostream>\n\n\n";

    headerCode += "class " + className->text();
    cppCode += "#include \"" + className->text().toLower() + ".h\"";

    if (!motherClassName->text().isEmpty())
    {
        headerCode += " : public " + motherClassName->text();
        cppCode += "\n#include \"" + motherClassName->text().toLower() + ".h\"";
    }


    headerCode += "\n{\n";

    if (constructorGenerate->isChecked())
    {
        cppCode += "\n\n\n" + className->text() + "::" + className->text() + "()\n{\n}\n\n";

        headerCode += "public:\n";
        headerCode += "    " + className->text() + "();\n";
        if (destructorGenerate->isChecked())
        {
            headerCode += "    ~" + className->text() + "();\n";
            cppCode += className->text() + "::~" + className->text() + "()\n{\n}\n\n";
        }
    }

    headerCode += "};\n";

    if (headerProtection->isChecked())
        headerCode += "\n\n#endif //" + headerClassName->text().toUpper() + "_H";

    QString cName = className->text();

    CodeGenerateWindow *codeWindow = new CodeGenerateWindow(headerCode, cppCode, cName, this);
    codeWindow->exec();
}
