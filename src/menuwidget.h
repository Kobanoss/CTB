#ifndef MENUWIDGET_H
#define MENUWIDGET_H

#include <QWidget>
#include "globals.h"
#include "inputwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MenuWidget; }
QT_END_NAMESPACE

// Класс окна нашего основного меню, нет смысла в комментариях
// Так как в данном файле происходит лишь объявление переменных и функций этого класса
// Реализация находится в .cpp

class MenuWidget : public QWidget {
    Q_OBJECT

public:
    MenuWidget(QWidget *parent = nullptr);
    ~MenuWidget(); 

signals:
    void sendValues(QString username,QString speed, QString execution_time);

private slots:
    void on_pushButton_main_start_clicked();

    void updateStats();

private:
    Ui::MenuWidget *ui;
    InputWidget *AnotherWindow;
    Globals *global;

    QString username;
    QString speed;
    QString execution_time;


};
#endif // MENUWIDGET_H
