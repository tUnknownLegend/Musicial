#include <QApplication>
//#include <QPushButton>
#include "MainWindow.h"
#include "net_tools.h"

int main(int argc, char **argv) {
    QApplication app(argc, argv);
/*
 //QPushButton button;

 QWidget window;
 window.setFixedSize(200, 520);

 QPushButton *button = new QPushButton("Hello World", &window);
 button->setGeometry(30, 30, 100, 30);

 button->setText("My text");
 button->setToolTip("A tooltip");
 QFont font ("Courier");
 button->setFont(font);
 //QIcon icon ("/path/to/my/icon/icon.png");
 //button.setIcon(icon);
 //button.setIcon(QIcon::fromTheme("face-smile"));
 QPushButton button2 ("other", button);
 //button.show();


 window.show();
 return app.exec();
*/

    MainWindow mainWindow;
    mainWindow.show();

    return app.exec();
}
