#ifndef SCOREFORM_H
#define SCOREFORM_H

#include <QDialog>
#include <QSettings>

namespace Ui {
class ScoreForm;
}

class ScoreForm : public QDialog
{
    Q_OBJECT
    
public:
    explicit ScoreForm(QWidget *parent = 0);
    ~ScoreForm();
    void setScore(int score);
private slots:
    void addScore();
    void updateName();
    
private:
    void updateScoreList();
    Ui::ScoreForm *ui;
    QSettings m_settings;
};

#endif // SCOREFORM_H
