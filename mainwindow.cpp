#include "mainwindow.h"

MainWindow::MainWindow():
    isCriteriaChange_(true),
    editCatalog_(false),
    selectedDegree_(0)
{
    try
    {
        UVManager::instance().loadUvs("UV_UTC.xml");
        UVManager::instance().loadDegrees("formations.xml");
    }
    catch(UTProfilerException e)
    {
        qDebug() << e.getInfo();
    }

    createStackedWidget();
}

void MainWindow::clearLayout(QLayout *layout)
{
    if(layout)
    {
        QLayoutItem* item;
        while( (item = layout->takeAt(0)) )
        {
            if(item->widget())
                item->widget()->deleteLater();
            if(item->layout())
            {
                clearLayout(item->layout());
                item->layout()->deleteLater();
            }
            delete item;
        }
    }
}

void MainWindow::createCatalog()
{
    catalog_ = new QWidget;
    QVBoxLayout* mainLayout = new QVBoxLayout;
    catalog_->setLayout(mainLayout);

    QVBoxLayout* l1 = new QVBoxLayout;

    // Degree
    QLabel* degreeLabel = new QLabel("Formation : ");
    degree_ = new QComboBox;
    const QList<Degree*> &degrees = UVManager::instance().degrees();
    degree_->insertItem(0,"Choix " + degrees.first()->type());
    int count = 1;
    for(int i = 0; i < degrees.size(); i++)
    {
        if(!degrees.at(i)->parent())
        {
            degree_->insertItem(count,degrees.at(i)->title());
            count++;
        }
    }
    QObject::connect(degree_,SIGNAL(activated(QString)),this,SLOT(selectDegree(QString)));
    QObject::connect(degree_,SIGNAL(activated(QString)),this,SLOT(criteriaChanged()));
    degreeLayout_ = new QHBoxLayout;
    degreeLayout_->addWidget(degreeLabel);
    degreeLayout_->addWidget(degree_);
    degreeLayout_->insertStretch(-1);
    l1->addLayout(degreeLayout_);

    // Season
    QLabel* seasonLabel = new QLabel("Semestre : ");
    spring_ = new QCheckBox("Printemps");
    spring_->setChecked(true);
    QObject::connect(spring_,SIGNAL(toggled(bool)),this,SLOT(criteriaChanged()));
    fall_ = new QCheckBox("Automne");
    fall_->setChecked(true);
    QObject::connect(fall_,SIGNAL(toggled(bool)),this,SLOT(criteriaChanged()));
    QHBoxLayout* l2 = new QHBoxLayout;
    l2->addWidget(seasonLabel);
    l2->addWidget(spring_);
    l2->addWidget(fall_);
    l2->insertStretch(-1);
    l1->addLayout(l2);

    // Category
    QLabel* categoryLabel = new QLabel("Catégorie : ");
    cs_ = new QCheckBox("CS");
    cs_->setChecked(true);
    QObject::connect(cs_,SIGNAL(toggled(bool)),this,SLOT(criteriaChanged()));
    tm_ = new QCheckBox("TM");
    tm_->setChecked(true);
    QObject::connect(tm_,SIGNAL(toggled(bool)),this,SLOT(criteriaChanged()));
    tsh_ = new QCheckBox("TSH");
    tsh_->setChecked(true);
    QObject::connect(tsh_,SIGNAL(toggled(bool)),this,SLOT(criteriaChanged()));
    sp_ = new QCheckBox("SP");
    sp_->setChecked(true);
    QObject::connect(sp_,SIGNAL(toggled(bool)),this,SLOT(criteriaChanged()));
    QHBoxLayout* l3 = new QHBoxLayout;
    l3->addWidget(categoryLabel);
    l3->addWidget(cs_);
    l3->addWidget(tm_);
    l3->addWidget(tsh_);
    l3->addWidget(sp_);
    l3->insertStretch(-1);
    l1->addLayout(l3);

    // Submit button
    submit_ = new QPushButton("Afficher les uvs");
    QObject::connect(submit_,SIGNAL(clicked()),this,SLOT(updateCatalog()));
    l1->addWidget(submit_);

    // Uvs
    uvsLayout_ = new QHBoxLayout;
    QWidget* widget = new QWidget;
    widget->setLayout(uvsLayout_);
    uvsScrollArea_ = new QScrollArea;
    uvsScrollArea_->setWidgetResizable(true);
    uvsScrollArea_->setWidget(widget);
    uvsScrollArea_->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);

    mainLayout->addLayout(l1);
    mainLayout->addWidget(uvsScrollArea_);
    //mainLayout->addStretch(-1);

    // Edit panel
    QHBoxLayout* l4 = new QHBoxLayout;
    QLabel* findLabel = new QLabel("Rechercher : ");
    l4->addWidget(findLabel);
    QLineEdit* findLineEdit = new QLineEdit;
    l4->addWidget(findLineEdit);
    QPushButton* edit = new QPushButton("Modifier");
    edit->setCheckable(true);
    edit->setChecked(false);
    QObject::connect(edit,SIGNAL(toggled(bool)),this,SLOT(editCatalog(bool)));
    l4->addStretch();
    l4->addWidget(edit);
    mainLayout->addLayout(l4);

    // By default display all uvs
    updateCatalog();
}

void MainWindow::createStackedWidget()
{
    // List of all items in the left navigation bar
    QListWidget* lw = new QListWidget(this);
    lw->setFixedWidth(100);
    lw->setSelectionMode(QAbstractItemView::SingleSelection);
    QListWidgetItem* catalogItem = new QListWidgetItem;
    catalogItem->setText("Catalogue Uvs");
    lw->insertItem(0,catalogItem);
    QListWidgetItem *userItem = new QListWidgetItem;
    userItem->setText("Espace perso");
    lw->insertItem(1,userItem);

    // Create the pages
    createCatalog();
    createUser();

    // Link the pages with the vertical navigation bar
    QStackedWidget* sw = new QStackedWidget;
    sw->addWidget(catalog_);
    sw->addWidget(user_);

    QHBoxLayout* mainLayout = new QHBoxLayout;
    mainLayout->addWidget(lw);
    mainLayout->addWidget(sw);

    QWidget* cw = new QWidget;
    cw->setLayout(mainLayout);
    setCentralWidget(cw);

    QObject::connect(lw,SIGNAL(currentRowChanged(int)),sw,SLOT(setCurrentIndex(int)));
}

void MainWindow::createUser()
{
    user_ = new QWidget;
    user_->setStyleSheet("background-color:green;");
}

void MainWindow::criteriaChanged()
{
    isCriteriaChange_ = true;
    submit_->setEnabled(true);
}

void MainWindow::editCatalog(bool edit)
{
    editCatalog_ = edit;
    isCriteriaChange_ = true;
    updateCatalog();
}

void MainWindow::selectDegree(const QString &title)
{
    /*
     * If the user selects another option in a higher combo box, remove the sub combo boxes
     * For exemple, if the current state is : Branche -> GI -> SRI
     * and the user selects Tronc Commun instead
     * GI and SRI will be removed and the new state will be : Tronc Commun
     */
    selectedDegree_ = UVManager::instance().degreeWithTitle(title);
    int depth;
    selectedDegree_ ? depth = selectedDegree_->depth() : depth = 0;
    while(degreeLayout_->count() > depth + 2)
    {
        QLayoutItem* item = degreeLayout_->takeAt(degreeLayout_->count() - 1);
        degreeLayout_->removeItem(item);
        delete item->widget();
        delete item;
    }
    degreeLayout_->update();

    /*
     * Add the sub combo box if there is one
     * For exemple, if the user selects Branche
     * A new combo box will show with the options :
     * PCB, SRI, ...
     */
    QList<const Degree*> children = UVManager::instance().degreesWithParent(title);
    if(!children.isEmpty())
    {
        QComboBox* subDegree = new QComboBox;
        subDegree->insertItem(0,"Choix " + children.first()->type());

        for(int i = 0; i < children.size(); i++)
        {
            subDegree->insertItem(i + 1,children.at(i)->title());
        }

        degreeLayout_->addWidget(subDegree);
        QObject::connect(subDegree,SIGNAL(activated(QString)),this,SLOT(selectDegree(QString)));
    }

    degreeLayout_->insertStretch(-1);
}

void MainWindow::updateCatalog()
{
    if(!isCriteriaChange_)
        return;

    isCriteriaChange_ = false;
    submit_->setEnabled(false);

    QList<const Uv*> uvs;
    selectedDegree_ ? uvs = selectedDegree_->uvs() : uvs = UVManager::instance().uvs();

    int i(0);
    while(i < uvs.size())
    {
        const Uv* uv = uvs.at(i);
        if(
                (
                    (fall_->isChecked() && uv->fall()) ||
                    (spring_->isChecked() && uv->spring())
                ) &&
                (
                    (cs_->isChecked() && uv->category() == CS) ||
                    (tsh_->isChecked() && uv->category() == TSH) ||
                    (tm_->isChecked() && uv->category() == TM) ||
                    (sp_->isChecked() && uv->category() == SP)
                )
           )
            i++;
        else
            uvs.removeAt(i);
    }

    // Create and populate new uvs layout
    QVBoxLayout* codeCol = new QVBoxLayout;
    QVBoxLayout* titleCol = new QVBoxLayout;
    QVBoxLayout* creditsCol = new QVBoxLayout;

    QLineEdit* test = 0;
    for(int i = 0; i < uvs.size(); i++)
    {
        const Uv* uv = uvs.at(i);

        QLineEdit* code = new QLineEdit(uv->code());
        code->setStyleSheet("QLineEdit:read-only {background: lightblue;}");
        code->setFixedWidth(50);
        code->setReadOnly(!editCatalog_);
        codeCol->addWidget(code);
        if(i == 100)
            test = code;
        QLineEdit* title = new QLineEdit(uv->title());
        title->setReadOnly(!editCatalog_);
        titleCol->addWidget(title);
        QLineEdit* credits = new QLineEdit(QString::number(uv->credits()));
        credits->setFixedWidth(50);
        credits->setEnabled(!editCatalog_);
        creditsCol->addWidget(credits);
    }

    codeCol->addStretch(-1);
    titleCol->addStretch(-1);
    creditsCol->addStretch(-1);

    // Refresh uvs layout
    clearLayout(uvsLayout_);
    uvsLayout_->addLayout(codeCol);
    uvsLayout_->addLayout(titleCol);
    uvsLayout_->addLayout(creditsCol);


    if(test)
    {
        qDebug() << "here";
        uvsScrollArea_->ensureWidgetVisible(test);
    }
}
