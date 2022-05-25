#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QPushButton>
#include <QHBoxLayout>
#include <QButtonGroup>
#include "CustomWidgets.h"
#include <QScrollBar>

class MainWindow : public QWidget {
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

    void SumbitPlaylist(QString text);

private:

    QWidget *MainSectorWidget;
    QHBoxLayout *MainSectorLayout;

    QVBoxLayout *ChatList;
    QVBoxLayout *ChatLayout;

    QGroupBox *RightSectorWidget;
    QGroupBox *ChatListWidget;
    QScrollArea *scrollArea;

    MessageSendBox *sendBox;

    void resizeEvent(QResizeEvent*);

    QPushButton *SendMessage;
    QPushButton *SendPlaylist;

private
    slots:

    void SendMessageClicked();

    void SendPlaylistClicked();

    void UpdateChatList();

    void SendMessageReleased();
};

#endif // MAINWINDOW_H
