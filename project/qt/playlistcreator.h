#ifndef PLAYLISTCREATOR_H
#define PLAYLISTCREATOR_H

#include <QWidget>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QPushButton>
#include <QHBoxLayout>
#include <QButtonGroup>
#include "MainWindow.h"
#include <QGroupBox>
#include <QCheckBox>
#include <QRadioButton>

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
    QList<QLineEdit*>* PlaylistFields;
    QList<QLineEdit*>* SongFields;
    QList<QRadioButton*>* fromPlatformList;
    QList<QCheckBox*>* toPlatformList;

private
    slots:
            void SubmitPlaylist();
            void AddPlaylist();
            void AddSong();
private:

     QGroupBox *createExclusiveGroup(QList<QRadioButton*>& list);
           // QGroupBox *createSecondExclusiveGroup();
     QGroupBox *createNonExclusiveGroup(QList<QCheckBox*>& list);
          //  QGroupBox *createPushButtonGroup();
     QLabel *createLable(QString name);

     QLineEdit* createLinedEdit(QString placeHolder);

     unsigned int rawCounter = 0;

     bool ShowErrorMessage(bool error, QString errorBody);
};

#endif // PLAYLISTCREATOR_H
