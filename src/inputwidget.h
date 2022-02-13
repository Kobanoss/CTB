#ifndef INPUTWIDGET_H
#define INPUTWIDGET_H

#include <QWidget>
#include <QTime>
#include <QTimer>
#include <QVector>
#include <QPushButton>
#include "globals.h"


QT_BEGIN_NAMESPACE
namespace Ui { class InputWidget; }
QT_END_NAMESPACE

// Класс окна игры, нет смысла в комментариях
// Так как в данном файле происходит лишь объявление переменных и функций этого класса
// Реализация находится в .cpp

class InputWidget : public QWidget {
    Q_OBJECT

public:
    explicit InputWidget(QWidget *parent = nullptr);
    ~InputWidget();

private:
    Ui::InputWidget *ui;

    Globals *global;

    QString username;
    QString speed;
    QString execution_time;


    QTimer *timer;
    QElapsedTimer timer_remains;

    QTimer *update_timer;
    QTimer *move_timer;

    double time_remains;

    QPushButton *active_button;
    int clicks_count = 0;

    double speed_current_per_min;

    QJsonDocument statistics_json;

    void dataToFile();

    void moveButton();

    void update();

    void startGame();
    void stopGame();

    void saveResult();
    void cancelResult();

signals:
    void changeWindow();

public slots:
    void setValues(QString username,QString speed, QString execution_time);

private slots:
    void on_pushButton_input_save_clicked();
    void on_pushButton_input_quit_clicked();

    void on_pushButton_input_start_clicked();
    void on_pushButton_active_clicked();
};

#endif // INPUTWIDGET_H
