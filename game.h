#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <QTimer>
#include <QVector>

struct Task
{
    Task(int aScoreValue = 1) {
        scoreValue = aScoreValue;
    }

    Task(QString aQuestion, QString aAnswer, QString wrongAnswer1, QString wrongAnswer2, QString wrongAnswer3)
        : question(aQuestion), answer(aAnswer), scoreValue(1) {
        possibleAnswers.append(wrongAnswer1);
        possibleAnswers.append(wrongAnswer2);
        possibleAnswers.append(wrongAnswer3);
    }

    QString question;
    QString answer;
    QVector<QString> possibleAnswers;
    int scoreValue;
};

class Game : public QObject
{
    Q_OBJECT
public:
    explicit Game(QObject *parent = 0);

signals:
    void remainingTimeChanged(int timeInSeconds);
    void scoreChanged(int score);
    void userMessage(const QString &reason);
    void nextTaskPossible();
    void end(int score);
public:
    void setTasks(const QVector<Task> &tasks);
    void reset(int intervalInSeconds = 20);
    QString nextTask();
    bool checkAnswer(const QString &answer);
    QVector<QString> possibleAnswers() const;
    int score();
    int intervall();
private slots:
    void update();

private:
    void setScore(int score);
    QTimer m_secondsTimer;
    QVector<Task> m_tasks;
    int m_score;
    int m_remainingTime;
    int m_taskIntervalTime;
    int m_currentTask;
    bool m_isInCheckAnswer;
};

#endif // GAME_H
