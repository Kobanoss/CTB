#ifndef GLOBALS_H
#define GLOBALS_H

#pragma once

#include <QWidget>
#include <QFile>
#include <QFileInfo>
#include <QDir>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>
#include <QRandomGenerator>
#include <QElapsedTimer>
#include <QTableWidgetItem>
#include <time.h>


class Globals {
public:
    // Ряд переменных с данными о файлах и различными связями между именами
    QString stat_filename = "stats.json";

    // Функция, реализующая загрузку JSON документа, принимает название этого документа
    QJsonDocument loadJson(QString filename) {
        QFile file(filename);

        if ((file.exists())&&(file.open(QFile::ReadOnly)))
            return QJsonDocument().fromJson(file.readAll());
        else {
            qDebug() << "Can't load from file: " << file.fileName();
            return QJsonDocument().fromJson("{}");
        }
    }
    // Функция, реализующая выгрузку JSON документа,
    // Принимает название этого документа и содержимое, которое необходимо выгрузить
    void saveJson(QString filename, QJsonDocument data) {
        QFile file(filename);

        if ((file.exists())&&(file.open(QFile::WriteOnly)))
            file.write(data.toJson());
        else
            qDebug() << "Can't save to file: " << file.fileName();
    }

    // Функция, реализующая проверку на существование файла
    // И создания его при отсутствии
    void createIfNotExist(QString filename) {
        QFile file(filename);
        QFileInfo file_info(file);
        QDir dir;

        QString file_path = file_info.path();
        dir.mkpath(file_path);

        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
           file.open(QIODevice::WriteOnly);

    }
    // Простейшая функция, создающая генератор случайных чисел и выдающий случайное целое число между lowest and highest
    int genRandomInt(int lowest, int highest){
        QRandomGenerator rand_obj;
        rand_obj.seed((long double)clock());
        return (highest-lowest > 0)?rand_obj.bounded(highest - lowest) + lowest:0;
    }
};

#endif // GLOBALS_H
