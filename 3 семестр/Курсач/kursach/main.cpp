#include <QApplication>
#include <QFile>
#include <QTextStream>
#include <QStyleFactory>
#include "ui/MainWindow.h"


int main(int argc, char *argv[]) {
    QApplication app(argc, argv);              // Создать объект приложения Qt
    
    // Установить стиль приложения
    app.setStyle(QStyleFactory::create("Fusion"));  
    
    // Загрузка стилей из файла
    QFile styleFile("ui/styles.qss");          // Открыть файл со стилями
    if (styleFile.open(QFile::ReadOnly | QFile::Text)) {  
        QTextStream stream(&styleFile);        // Создать поток для чтения файла
        QString style = stream.readAll();      // Прочитать все содержимое файла стилей
        app.setStyleSheet(style);              // Применить стили к приложению
        styleFile.close();                     // Закрыть файл
    }
    
    MainWindow window;                          
    window.show();                              
    
    return app.exec();                          
}

