// checksum 0xa193 version 0x30001
/*
  This file was generated by the Mobile Qt Application wizard of Qt Creator.
  MainWindow is a convenience class containing mobile device specific code
  such as screen orientation handling.
  It is recommended not to modify this file, since newer versions of Qt Creator
  may offer an updated version of it.
*/

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "scoreform.h"


#include <QtCore/QCoreApplication>
#include <QDebug>

#include <algorithm>
#include <random>

int randomNumber(int from, int to) {
    std::uniform_int_distribution<int> distribution(from, to);
    static std::random_device randomDevice;
    static std::mt19937 engine(randomDevice());
    return distribution(engine);
}

int randomResult()
{
    return randomNumber(1, 9) * randomNumber(1, 9);
}

QString similarButWrongWrongAnswer(const QString &answer)
{
    QString similarAnswer;
    do {
        similarAnswer.clear();
        std::vector<QChar> chars(answer.begin(), answer.end());
        Game::shuffleContainer(chars);
        for (QChar ch : chars) {
            similarAnswer.append(ch);
        }
    } while (similarAnswer == answer);
    return similarAnswer;
}

class MultiplicationTask : public Task
{
    public:
        MultiplicationTask(int x, int y)
            : Task() {
            question = QString("%1 x %2").arg(x).arg(y);
            answer = QString::number(x*y);
            if (answer.size() > 1)
                possibleAnswers.append(similarButWrongWrongAnswer(answer));
            while (possibleAnswers.count() != 3) {
                const QString possibleAnswer = QString::number(randomNumber(1, 9)*randomNumber(1, 9));
                if (!possibleAnswers.contains(possibleAnswer) && possibleAnswer != answer && possibleAnswer.size() == 2)
                    possibleAnswers.append(possibleAnswer);
            }
        }
};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    QVector<Task> tasks;
    tasks.append(MultiplicationTask(5,5));
    tasks.append(MultiplicationTask(6,6));
    tasks.append(MultiplicationTask(6,7));
    tasks.append(MultiplicationTask(7,7));
    tasks.append(MultiplicationTask(7,6));
    tasks.append(MultiplicationTask(8,8));
    tasks.append(MultiplicationTask(7,8));
    tasks.append(MultiplicationTask(8,7));
    tasks.append(MultiplicationTask(8,6));
    tasks.append(MultiplicationTask(6,8));
    tasks.append(MultiplicationTask(5,9));
    tasks.append(MultiplicationTask(6,9));
    tasks.append(MultiplicationTask(7,9));
    tasks.append(MultiplicationTask(8,9));
    tasks.append(MultiplicationTask(9,5));
    tasks.append(MultiplicationTask(9,6));
    tasks.append(MultiplicationTask(9,7));
    tasks.append(MultiplicationTask(9,8));
    tasks.append(MultiplicationTask(9,9));

    m_game.setTasks(tasks);

    ui->setupUi(this);

    connect(ui->startReset, SIGNAL(clicked()),
        this, SLOT(startResetGame()));
    connect(ui->box1, SIGNAL(clicked()),
        this, SLOT(checkBox1()));
    connect(ui->box2, SIGNAL(clicked()),
        this, SLOT(checkBox2()));
    connect(ui->box3, SIGNAL(clicked()),
        this, SLOT(checkBox3()));
    connect(ui->box4, SIGNAL(clicked()),
        this, SLOT(checkBox4()));

    connect(&m_game, (SIGNAL(userMessage(QString))),
        ui->userMessage, SLOT(setText(QString)));
    connect(&m_game, (SIGNAL(scoreChanged(int))),
            this, SLOT(updateScore(int)));
    connect(&m_game, SIGNAL(remainingTimeChanged(int)),
        this, SLOT(updateRemainingTime(int)));
    connect(&m_game, SIGNAL(nextTaskPossible()),
        this, SLOT(updateToNextTask()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::startResetGame()
{
    if (m_game.score() != 0) {
        openScoreList(m_game.score());
    } else {
        m_game.reset();
        ui->progressBar->setMaximum(m_game.intervall());
        ui->progressBar->setValue(m_game.intervall());
        updateToNextTask();
    }
}

void MainWindow::updateRemainingTime(int seconds)
{
    ui->progressBar->setValue(seconds);
}

void MainWindow::updateScore(int score)
{
    ui->scoreValue->setText(QString::number(score));
}

void MainWindow::checkBox1()
{
    m_game.checkAnswer(ui->box1->text());
}

void MainWindow::checkBox2()
{
    m_game.checkAnswer(ui->box2->text());
}

void MainWindow::checkBox3()
{
    m_game.checkAnswer(ui->box3->text());
}

void MainWindow::checkBox4()
{
    m_game.checkAnswer(ui->box4->text());
}

void MainWindow::updateToNextTask()
{
    ui->userMessage->setText(m_game.nextTask());
    const QVector<QString> answers = m_game.possibleAnswers();
    ui->box1->setText(answers.value(0));
    ui->box2->setText(answers.value(1));
    ui->box3->setText(answers.value(2));
    ui->box4->setText(answers.value(3));
}

void MainWindow::openScoreList(int score)
{
    ScoreForm *form = new ScoreForm();
    connect(form, SIGNAL(destroyed()), this, SLOT(startResetGame()));
    form->setAttribute(Qt::WA_DeleteOnClose);
    if (score != 0)
        form->setScore(score);
    m_game.reset();
    form->exec();
    startResetGame();
}
