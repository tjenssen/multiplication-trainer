#include "game.h"

#include <algorithm>
#include <ctime>        // std::time
#include <cstdlib>      // std::rand, std::srand

#include <QDateTime>

Game::Game(QObject *parent)
    : QObject(parent)
    , m_taskIntervalTime(0)
{
    m_score = 0;
    m_remainingTime = 0;
    m_currentTask = 0;
    m_secondsTimer.setInterval(1000);
    connect(&m_secondsTimer, SIGNAL(timeout()), this, SLOT(update()));
}


void Game::reset(int intervalInSeconds)
{
    std::srand(QDateTime::currentDateTime().toTime_t());
    std::random_shuffle(m_tasks.begin(), m_tasks.end());
    m_taskIntervalTime = intervalInSeconds;
    m_score = 0;
    m_secondsTimer.stop();
    m_currentTask = 0;
    emit scoreChanged(m_score);
}

QString Game::nextTask()
{
    m_remainingTime = m_taskIntervalTime;
    m_secondsTimer.start();
    return m_tasks.value(m_currentTask).question;
}

QVector<QString> Game::possibleAnswers() const
{
    QVector<QString> answers = m_tasks.value(m_currentTask).possibleAnswers;
    answers.append(m_tasks.value(m_currentTask).answer);
    std::random_shuffle(answers.begin(), answers.end());
    return answers;
}

int Game::score()
{
    return m_score;
}

int Game::intervall()
{
    return m_taskIntervalTime;
}

void Game::update()
{
    if (m_remainingTime < 0) {
        m_secondsTimer.stop();
        emit userMessage("Zeit zu ende - verloren");
        emit end(m_score);
    }
    emit remainingTimeChanged(m_remainingTime--);
}

bool Game::checkAnswer(const QString &answer)
{
    bool result = false;
    if (m_tasks.value(m_currentTask).answer == answer) {
        m_score += m_remainingTime/10 + 1;
        emit scoreChanged(m_score);
        emit userMessage("richtig");
        result = true;
    } else {
        m_score -= m_remainingTime/10 + 1;
        emit userMessage(QString("leider falsch - %1 = %2").arg(
            m_tasks.value(m_currentTask).question, m_tasks.value(m_currentTask).answer));
    }
    m_currentTask++;
    if (m_tasks.count() > m_currentTask)
        QTimer::singleShot(2000, this, SIGNAL(nextTaskPossible()));
    else {
        m_secondsTimer.stop();
        emit userMessage("alles geschaft, super!");
        emit end(m_score);
    }
    return result;
}

void Game::setTasks(const QVector<Task> &tasks)
{
    m_tasks = tasks;
}
