#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QPushButton>
#include "CustomWidgets.h"
#include <QScrollBar>
#include "lib/include/mainlib.h"

class MainWindow : public QWidget {
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

    void SumbitPlaylist(client::MessageGroup& messages);

    ~MainWindow();

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

    QList<Message*>* TextMessanges;

    void SendMessageF(const std::vector<sharedLib::Message>::iterator & mBegin,
                      const std::vector<sharedLib::Message>::iterator & mEnd);
    void SendPlaylistF(const std::vector<sharedLib::Message>::iterator & mBegin,
                       const std::vector<sharedLib::Message>::iterator & mEnd);
private
    slots:

    void SendMessageClicked();

    void SendPlaylistClicked();

    void SendMessageReleased();
};

#endif // MAINWINDOW_H
