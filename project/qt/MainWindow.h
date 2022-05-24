#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QPushButton>
#include <QHBoxLayout>
#include <QButtonGroup>
#include "CustomWidgets.h"
//#include "../web/project/server/include/net_tools.h"
#include <QScrollBar>

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
    //QAbstractScrollArea *scrollArea;

    MessageSendBox *sendBox;

    //QList<Message*> MessageList;
private
    slots:
            void ChatSelectorCliked(bool
    clicked);

    void SendMessageClicked();

    void SendPlaylistClicked();

    void UpdateChatList();

    void SendMessageReleased();
/*
    void DrawMessage(const std::vector<net_tools::Message>::iterator & mBegin, const std::vector<net_tools::Message>::iterator & mEnd) {
      std::for_each(mBegin, mEnd, [this, mBegin, mEnd]() {     QList < Message * > MessageList;

          for (auto i = mBegin; i != mEnd; ++i) {
              // recive
              Message *message = new Message(!i->ownerID, QString::fromStdString(i->text));
              MessageList.append(message);
          }

          for (auto &i: MessageList) {
              ChatList->addWidget(i->container);
          }

          scrollArea->verticalScrollBar()->setSliderPosition(scrollArea->verticalScrollBar()->maximum()); });
    }

*/
    //std::function<void(bool)> DrawMessageStd = [](bool) { qDebug() << "Button clicked."; };

   // void DrawMessage(const std::vector<net_tools::Message>::iterator & mBegin, const std::vector<net_tools::Message>::iterator & mEnd);

   // std::function<void(const std::vector<net_tools::Message>::iterator &, const std::vector<net_tools::Message>::iterator &)> DrawMessageStd =;

};

#endif // MAINWINDOW_H
