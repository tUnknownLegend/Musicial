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
#include <QGroupBox>
//#include <QLabel>

class PlaylistCreator : public QWidget {
    Q_OBJECT
public:
    explicit PlaylistCreator(MainWindow *_parent = nullptr);

    QGridLayout* grid;
    QGridLayout* gridButtons;
    QPushButton *submitBtn;
    QPushButton *AddSongBtn;
    QPushButton *AddPlaylistBtn;
    MainWindow *parent;
    QLineEdit* text;
    QWidget* FieldsWidget;
    QVBoxLayout *Layout;
    QList<QLineEdit*>* TextFields;

private
    slots:
            void SubmitPlaylist();
            void AddPlaylist();
            void AddSong();
private:

     QGroupBox *createFirstExclusiveGroup();
           // QGroupBox *createSecondExclusiveGroup();
     QGroupBox *createNonExclusiveGroup();
          //  QGroupBox *createPushButtonGroup();
     QLabel *createLable(QString name);

     QLineEdit* createLinedEdit(QString placeHolder);

     unsigned int rawCounter = 0;
};

#endif // PLAYLISTCREATOR_H
