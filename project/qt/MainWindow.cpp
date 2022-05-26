#include "MainWindow.h"
#include <QApplication>
#include <QLabel>
#include <QList>
#include "CustomWidgets.h"
#include "lib/include/mainlib.h"
#include "lib/src/mainlib.cpp"
#include "playlistcreator.h"
#include <QMessageBox>
#include <QAbstractScrollArea>
#include <QScrollBar>
#include <QScrollArea>
#include "CustomWidgets.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
//#include <libserverLib>
//#include "net_tools.h"
//#include "../web/project/server/include/net_tools.h"


MainWindow::MainWindow(QWidget *parent) :
        QWidget(parent) {
    this->setMinimumSize(500, 500);

    MainSectorLayout = new QHBoxLayout(this);
    MainSectorLayout->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    MainSectorLayout->setSpacing(0);
    MainSectorLayout->setContentsMargins(0,0,0,0);

    MainSectorWidget = new QWidget();
    MainSectorLayout->addWidget(MainSectorWidget);
    MainSectorWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    RightSectorWidget = new QGroupBox("RightSectorWidget");
    ChatLayout = new QVBoxLayout(MainSectorWidget);
    ChatLayout->addWidget(RightSectorWidget);
    ChatLayout->setSpacing(0);
    ChatLayout->setContentsMargins(1,1,1,1);

    RightSectorWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    scrollArea = new QScrollArea(RightSectorWidget);

    scrollArea->setStyleSheet("QScrollBar:vertical { ""width: 10px;""}");
    //scrollArea->setMinimumSize(400, 400);

    scrollArea->setAlignment(Qt::AlignRight);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    scrollArea->setWidgetResizable(true);


    //scrollArea->setLayout(ChatList);

    ChatListWidget = new QGroupBox(scrollArea);
    scrollArea->setWidget(ChatListWidget);
    //ChatListWidget->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    ChatList = new QVBoxLayout(ChatListWidget);
    ChatList->setSizeConstraint(QLayout::SetMinimumSize);
    //ChatList->setAlignment(Qt::AlignRight);
    ChatListWidget->setLayout(ChatList);

    sendBox = new MessageSendBox(RightSectorWidget);
    SendMessage = new QPushButton("M", RightSectorWidget);
    SendPlaylist = new QPushButton("P", RightSectorWidget);

    connect(SendMessage, SIGNAL(clicked()), this, SLOT(SendMessageClicked()));
    connect(SendMessage, SIGNAL(released()), this, SLOT(SendMessageReleased()));
    connect(SendPlaylist, SIGNAL(clicked()), this, SLOT(SendPlaylistClicked()));
    SendMessage->setGeometry(0, 25, 45, 50);
    SendPlaylist->setGeometry(0, 25, 45, 50);
    sendBox->Text->setGeometry(0, 25, 450, 50);
    this->resize(MainSectorWidget->geometry().width(), MainSectorWidget->geometry().height());
    //this->resize(MainSectorWidget->geometry().width(), MainSectorWidget->geometry().height());
}

void MainWindow::SendMessageReleased() {
    scrollArea->verticalScrollBar()->setSliderPosition(scrollArea->verticalScrollBar()->maximum());
}


void MainWindow::resizeEvent(QResizeEvent*) {
   SendMessage->setGeometry(RightSectorWidget->width() - SendMessage->width(), RightSectorWidget->height() - SendMessage->height(), SendMessage->width(), SendMessage->height());
   SendPlaylist->setGeometry(RightSectorWidget->x(), RightSectorWidget->height() - SendPlaylist->height(), SendPlaylist->width(), SendPlaylist->height());
   sendBox->Text->setGeometry(SendPlaylist->width(), RightSectorWidget->height() - sendBox->Text->height(), SendMessage->x() - SendPlaylist->width(), sendBox->Text->height());
   scrollArea->resize(RightSectorWidget->width(), SendMessage->y());
}

void MainWindow::SendMessageClicked() {
    if (sendBox->Text->displayText() == "")
        return;

    QString text = sendBox->Text->displayText();

    client::MessageGroup messages(text.toStdString(), 0, false);
    messages.send([this](const std::vector<Message>::iterator & mBegin, const std::vector<Message>::iterator & mEnd){

        for (auto i = mBegin; i != mEnd; ++i) {
            // recive
            Message *message = new Message(i->ownerID, QString::fromStdString(i->text), true, *ChatList);
            message->mainText->setWordWrap(true);
            ChatList->addWidget(message->mainText);
        }
    }
    );

    //messages.Messages

    //quit();

    //SendMessage(text.toStdString(), UserID);
}

void MainWindow::SendPlaylistClicked() {
    PlaylistCreator *playlistCreator = new PlaylistCreator(this);
    playlistCreator->show();
}

void MainWindow::SumbitPlaylist(QString text) {

    //if (sendBox->Text->displayText() == "")
    //    return;

    client::MessageGroup messages(text.toStdString(), 0, false);
    messages.send([this](const std::vector<Message>::iterator & mBegin, const std::vector<Message>::iterator & mEnd){

        for (auto i = mBegin; i != mEnd; ++i) {
            // recive
            Message *message = new Message(i->ownerID, QString::fromStdString(i->text), true, *ChatList);
            message->mainText->setWordWrap(true);
            ChatList->addWidget(message->mainText);
        }
    }
    );
}

void MainWindow::UpdateChatList() {  
    /*
    client::ButtonGetDialog updateContainer;
    updateContainer.action();

    QList < Message * > MessageList;
    for (auto &i: updateContainer.Messages) {
        Message *message = new Message(!i.ownerID, QString::fromStdString(i.text));
        MessageList.append(message);
    }

    for (auto i: MessageList) {
        ChatList->addWidget(i->container);
    }

    scrollArea->verticalScrollBar()->setSliderPosition(scrollArea->verticalScrollBar()->maximum());
*/
}
