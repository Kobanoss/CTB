#include "inputwidget.h"
#include "ui_inputwidget.h"

// Конструктор нашего виджета для ввода текста
InputWidget::InputWidget(QWidget *parent) : QWidget(parent), ui(new Ui::InputWidget) {
    ui->setupUi(this);
    global = new Globals();

    timer = new QTimer();
    update_timer = new QTimer();
    move_timer = new QTimer();

    connect(move_timer,&QTimer::timeout,this, &InputWidget::moveButton);
    connect(update_timer,&QTimer::timeout,this, &InputWidget::update);
    connect(timer, &QTimer::timeout, this, &InputWidget::stopGame);

    ui->pushButton_input_save->setVisible(false);
    ui->pushButton_active->setVisible(false);
}

// Деструктор нашего виджета
InputWidget::~InputWidget() {
    delete ui;
}

// Слот для приема передаваемых величин из главного окна
void InputWidget::setValues(QString username,QString speed, QString execution_time) {
    this->username = username;
    this->speed = speed;
    this->execution_time = execution_time;
    this->speed_current_per_min = 0;

    this->time_remains = this->execution_time.toDouble()*60;
    ui->label_input_time_remains->setText(QString::number(time_remains));
    update();
}




// Выгрузка данных в файл статистики
void InputWidget::dataToFile() {
    QJsonDocument json_dump = global->loadJson(global->stat_filename);
    QJsonObject json_obj = json_dump.object();

    QJsonObject new_obj;
    new_obj["time"] = execution_time;
    new_obj["speed"] = speed.toFloat()/4;
    new_obj["amount"] = clicks_count;
    new_obj["cpm"]= qRound(ui->label_input_speed_current_per_min->text().toFloat());

    json_obj[this->username] = new_obj;
    json_dump.setObject(json_obj);

    global->saveJson(global->stat_filename, json_dump);
}



// Перемещение кнопки
void InputWidget::moveButton() {
    ui->pushButton_active->setVisible(true);
    ui->pushButton_active->setGeometry(global->genRandomInt(0, 650), global->genRandomInt(0, 175), 50, 50);
}


// Обновление всех полей скорости, времени и ошибок
void InputWidget::update() {
    ui->label_input_time_remains->setText(timer_remains.isValid()?QString::number(time_remains-((timer_remains.elapsed())/1000)):QString::number(time_remains));

    ui->label_input_speed_current_per_min->setText(timer_remains.isValid()?
                                                       (QString::number(clicks_count*60/(clicks_count>1?((timer_remains.elapsed())/1000):1))):QString("0"));

    ui->label_input_amount_clicks->setText(QString::number(clicks_count));
}


void InputWidget::on_pushButton_active_clicked() {
    clicks_count++;
    update();
    ui->pushButton_active->setVisible(false);
}

// Запуск игры
void InputWidget::startGame() {
    ui->pushButton_active->setVisible(true);
    ui->pushButton_input_start->setVisible(false);
    moveButton();
}

// Остановка игры путем закрытия окна, вызывается в купе с переходом на старое окно.
void InputWidget::stopGame() {
    ui->pushButton_input_save->setVisible(true);
    timer->stop();
    update_timer->stop();
    move_timer->stop();
}

// Сохранение результата
void InputWidget::saveResult() {
    dataToFile();
}

// Отмена результата
void InputWidget::cancelResult() {
    timer->stop();
    update_timer->stop();

    speed_current_per_min = 0;
    time_remains = 0;
    clicks_count = 0;
    update();
}

// Действие при нажатии кнопки старта
void InputWidget::on_pushButton_input_start_clicked() {
    startGame();
    this->timer_remains.start();
    timer->start(this->execution_time.toInt() * 60 * 1000);
    update_timer->start(100);
    move_timer->start(2000/speed.toInt());
}

// Действие при нажатии кнопки сохранения
void InputWidget::on_pushButton_input_save_clicked() {
    saveResult();
    this->close();
    emit changeWindow();
}

// Действие при нажатии кнопки выхода
void InputWidget::on_pushButton_input_quit_clicked() {
    cancelResult();
    this->close();
    emit changeWindow();
}






