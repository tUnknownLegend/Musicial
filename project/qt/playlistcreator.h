#ifndef PLAYLISTCREATOR_H
#define PLAYLISTCREATOR_H

#include <QWidget>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QPushButton>
#include <QHBoxLayout>
#include <QButtonGroup>
//#include "CustomWidgets.h"
#include "MainWindow.h"

class PlaylistCreator : public QWidget {
    Q_OBJECT
public:
    explicit PlaylistCreator(MainWindow *_parent = nullptr);

    QLineEdit *Text;
    QVBoxLayout *Layout;
    QPushButton *submitBtn;
    MainWindow *parent;
private
    slots:
            void SubmitPlaylist();
private:

};

#endif // PLAYLISTCREATOR_H
