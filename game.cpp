#include "game.h"

#include <QDateTime>

#include <algorithm>
#include <random>

Game::Game(QObject *parent)
    : QObject(parent)
    , m_score(0)
    , m_remainingTime(0)
    , m_taskIntervalTime(0)
    , m_currentTask(0)
    , m_isInCheckAnswer(false)

{
    m_score = 0;
    m_remainingTime = 0;
    m_currentTask = 0;
    m_secondsTimer.setInterval(1000);
    connect(&m_secondsTimer, SIGNAL(timeout()), this, SLOT(update()));

}

void Game::reset(int intervalInSeconds)
{
    shuffleContainer(m_tasks);
    m_taskIntervalTime = intervalInSeconds;
    setScore(0);
    m_secondsTimer.stop();
    m_currentTask = 0;
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
    shuffleContainer(answers);
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
    if (m_remainingTime < 0 && !m_isInCheckAnswer) {
        m_secondsTimer.stop();
        emit userMessage("Zeit zu ende - verloren");
        emit end(m_score);
    }
    emit remainingTimeChanged(m_remainingTime--);
}

void Game::setScore(int score)
{
    m_score = score;
    emit scoreChanged(m_score);
}

bool Game::checkAnswer(const QString &answer)
{
    bool result = false;
    m_isInCheckAnswer = true;
    const Task currentTask = m_tasks.value(m_currentTask);
    if (currentTask.answer == answer) {
        setScore(m_score + (m_remainingTime + 2)/10 + currentTask.scoreValue);
        emit userMessage("richtig");
        result = true;
    } else {
        setScore(m_score - (m_remainingTime + 2)/10 + currentTask.scoreValue);
        emit userMessage(QString("leider falsch - %1 = %2").arg(
            currentTask.question, currentTask.answer));
    }
    m_currentTask++;
    if (m_tasks.count() > m_currentTask)
        QTimer::singleShot(2000, this, SIGNAL(nextTaskPossible()));
    else {
        m_secondsTimer.stop();
        emit userMessage("alles geschaft, super!");
        emit end(m_score);
    }
    m_isInCheckAnswer = false;
    return result;
}

void Game::setTasks(const QVector<Task> &tasks)
{
    m_tasks = tasks;
}
