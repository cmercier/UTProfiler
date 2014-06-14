#include "connection.h"

Connection::Connection()
{
    QVBoxLayout* mainLayout = new QVBoxLayout;
    setLayout(mainLayout);

    int width = 80;

    QHBoxLayout* h1 = new QHBoxLayout;
    QLabel* connectionLabel = new QLabel("Veuillez entrer votre login :");
    h1->addWidget(connectionLabel);
    h1->insertStretch(-1);
    mainLayout->addLayout(h1);

    QHBoxLayout* h2 = new QHBoxLayout;
    connectionEdit_ = new QLineEdit;
    connectionEdit_->setFixedWidth(width);
    h2->addWidget(connectionEdit_);
    h2->insertStretch(-1);
    mainLayout->addLayout(h2);

    QHBoxLayout* h3 = new QHBoxLayout;
    QPushButton* submit = new QPushButton("Se connecter");
    submit->setFixedWidth(width);
    h3->addWidget(submit);
    h3->insertStretch(-1);
    mainLayout->addLayout(h3);
    QObject::connect(submit,SIGNAL(clicked()),this,SLOT(login()));

    mainLayout->insertStretch(-1);
}

void Connection::login()
{
    QString id = connectionEdit_->text();
    if(id.size() != 8)
        QMessageBox::warning(this,"Login non valide","Veuillez entrer votre login à 8 lettres.",QMessageBox::Ok);
    else
    {
        if(UTManager::instance().connect(id))
            QMessageBox::information(this,"Connexion réussie","Vous êtes connecté(e).\nVous pouvez consulter et modifier votre profil et vos prévisions.");
        else
        {
            UTManager::instance().addStudent(id);
            QMessageBox::information(this,"Bienvenue","Vous avez été ajouté(e) à la base.\nVous pouvez compléter votre profil et réaliser des prévisions.");
        }

        emit connected();
    }
}
