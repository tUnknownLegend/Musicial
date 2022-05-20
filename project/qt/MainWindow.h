#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QPushButton>
#include <QHBoxLayout>
#include <QButtonGroup>
#include "CustomWidgets.h"

//class QPushButton;
class MainWindow : public QWidget {
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

    void SumbitPlaylist(QString text);

private:

    QWidget *MainSectorWidget;
    QHBoxLayout *MainSectorLayout;
    QVBoxLayout *AllChatsGroup;

    QVBoxLayout *ChatList;
    QButtonGroup *ChatSelector;

    QGroupBox *ChatGroup;
    QGroupBox *RightSectorWidget;
    QGroupBox *ChatListWidget;
    QScrollArea *scrollArea;

    MessageSendBox *sendBox;

    //QList<Message*> MessageList;
private
    slots:
            void ChatSelectorCliked(bool
    clicked);

    void SendMessageClicked();

    void SendPlaylistClicked();

    void UpdateChatList();
};

#endif // MAINWINDOW_H
