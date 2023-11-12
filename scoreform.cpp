#include "scoreform.h"
#include "ui_scoreform.h"

#include <QStringListModel>
#include <QDebug>

bool moreThan( const QString& v1, const QString& v2 )
{
    return v1.toInt() > v2.toInt();
}

ScoreForm::ScoreForm(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ScoreForm)
    , m_settings("Trainer", "Multiplication")
{
    ui->setupUi(this);

    connect(ui->addButton, SIGNAL(clicked()), this, SLOT(addScore()));
    connect(ui->nameLineEdit, SIGNAL(textChanged(QString)),
        this, SLOT(updateName()));
    connect(ui->closeButton, SIGNAL(clicked()),
            this, SLOT(close()));
    updateScoreList();
}

ScoreForm::~ScoreForm()
{
    delete ui;
}

void ScoreForm::setScore(int score)
{
    ui->score->setText(QString::number(score));
    ui->nameLineEdit->setText(m_settings.value("LastName").toString());
    ui->nameLineEdit->setEnabled(true);
}

void ScoreForm::addScore()
{
    m_settings.setValue(ui->score->text(), ui->nameLineEdit->text());
    m_settings.setValue("LastName", ui->nameLineEdit->text());
    m_settings.sync();
    updateScoreList();
    ui->nameLineEdit->setEnabled(false);
    ui->addButton->setEnabled(false);
}

void ScoreForm::updateName()
{
    ui->addButton->setEnabled(ui->nameLineEdit->text().size() != 0);
}

void ScoreForm::updateScoreList()
{
    QStringList scores = m_settings.allKeys();
    scores.removeAll("LastName");

    std::sort(scores.begin(), scores.end(), moreThan);

    QStringList nameWithScoreList;
    foreach (const QString &score, scores) {
        nameWithScoreList.append(QString("%1 - %2 Punkte").arg(m_settings.value(score).toString(), score));
    }

    ui->listView->setModel(new QStringListModel(nameWithScoreList));
}
