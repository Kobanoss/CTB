#include "src/menuwidget.h"
#include "src/globals.h"

#include <QApplication>


// Функция, реализующая проверку на существование необходимого файла с данными, создает его при необходимости
void createFiles(){
    Globals global;

    global.createIfNotExist(global.stat_filename);
}


// Тело основной функции
int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    createFiles();

    MenuWidget  menu;

    menu.show();


    return app.exec();
}
