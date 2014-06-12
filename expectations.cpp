#include "expectations.h"

Expectations::Expectations()
{
    QVBoxLayout* mainLayout = new QVBoxLayout;
    setLayout(mainLayout);

    // Select or create expectations
    QLabel* expSelectLabel = new QLabel("Mes prévisions :");
    expSelect_ = new QComboBox;
    expSelect_->setInsertPolicy(QComboBox::InsertAlphabetically);
    expSelect_->setFixedWidth(150);
    QHBoxLayout* h1 = new QHBoxLayout;
    h1->addWidget(expSelectLabel);
    h1->addWidget(expSelect_);
    h1->insertStretch(-1);
    mainLayout->addLayout(h1);

    // Exp panel
    expScrollArea_ = new QScrollArea;
    expScrollArea_->setWidgetResizable(true);
    QWidget* w = new QWidget;
    expScrollArea_->setWidget(w);
    expLayout_ = new QVBoxLayout;
    w->setLayout(expLayout_);

    mainLayout->insertStretch(-1);
    updateExpComboBox();
}

void Expectations::updateExpComboBox()
{
    expSelect_->clear();

    Student* student = UVManager::instance().student();
    if(!student)
    {qDebug() << "nop";
        return;
    }

    const QList<Expectation*> &exp = student->exp();
    for(int i = 0; i < exp.size(); i++)
    {
        expSelect_->addItem(exp.at(i)->name());
    }

    expSelect_->insertItem(0,"Nouvelle prévision");
    expSelect_->setCurrentIndex(0);
}

void Expectations::updateExpPanel()
{

}
