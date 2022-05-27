#include "MainWindow.h"
#include <QApplication>
#include <QLabel>
#include <QList>
#include <QMessageBox>
#include <QAbstractScrollArea>
#include <QScrollBar>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "CustomWidgets.h"
//#include "lib/include/mainlib.h"
#include "lib/src/mainlib.cpp"
#include "playlistcreator.h"
#include "CustomWidgets.h"

MainWindow::MainWindow(QWidget *parent) :
        QWidget(parent) {
    this->setMinimumSize(500, 500);
    setWindowTitle("Musicial");

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

    RightSectorWidget->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

    scrollArea = new QScrollArea(RightSectorWidget);

    scrollArea->setStyleSheet("QScrollBar:vertical { ""width: 10px;""}");
    //scrollArea->setMinimumSize(400, 400);

    scrollArea->setAlignment(Qt::AlignRight);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    scrollArea->setWidgetResizable(true);


    //scrollArea->setLayout(ChatList);

    ChatListWidget = new QGroupBox(scrollArea);
    scrollArea->setWidget(ChatListWidget);
    ChatList = new QVBoxLayout(ChatListWidget);
    ChatList->setSizeConstraint(QLayout::SetMinimumSize);
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

    TextMessanges = new QList<Message*>;

    //SendMessage->setStyleSheet("qproperty-icon: url(:/resources/sendIcon.png);");
    //QPixmap sendIcon(":/resources/sendIcon.png");
    //QIcon SendMessageButtonIcon(":/resources/sendIcon.png");
    //SendMessage->setIcon(SendMessageButtonIcon);
    //SendMessage->show();
    //SendMessage->setIconSize(sendIcon.rect().size());
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
   //scrollArea->resize(RightSectorWidget->width(), scrollArea->height());
}

void MainWindow::SendMessageClicked() {
    if (sendBox->Text->displayText() == "")
        return;
    QString text = sendBox->Text->displayText();

    client::MessageGroup messages(text.toStdString(), USER_ID, sharedLib::None);
    messages.send([this](const std::vector<sharedLib::Message>::iterator & mBegin, const std::vector<sharedLib::Message>::iterator & mEnd){

        for (auto i = mBegin; i != mEnd; ++i) {
            // recive
            Message *message = new Message(i->ownerID, QString::fromStdString(i->text), i->ownerID == USER_ID, *ChatList);
            TextMessanges->push_back(message);
            ChatList->addWidget(message->mainText);
        }
    }
    );
}

void MainWindow::SendPlaylistClicked() {
    PlaylistCreator *playlistCreator = new PlaylistCreator(this);
    playlistCreator->show();
}

void MainWindow::SumbitPlaylist(client::MessageGroup& messages) {

    //if (sendBox->Text->displayText() == "")
    //    return;

    //client::MessageGroup messages(text.toStdString(), 0, false);

    messages.send([this](const std::vector<sharedLib::Message>::iterator & mBegin, const std::vector<sharedLib::Message>::iterator & mEnd){

        for (auto i = mBegin; i != mEnd; ++i) {

            Message *message = new Message(i->ownerID, QString::fromStdString(i->text), i->ownerID == USER_ID, *ChatList);
            TextMessanges->push_back(message);
            ChatList->addWidget(message->mainText);

            for (auto& j : i->playlists) {
                Message *message = new Message(i->ownerID, QString::fromStdString(j.ref.link), i->ownerID == USER_ID, *ChatList);
                message->mainText->setWordWrap(true);
                QString platformName = QString::fromStdString(client::getPlatform(j.platform));
                message->mainText->setText(platformName + " <a href=\"" +
                                                           QString::fromStdString(j.ref.link) + "\">" +
                                                           QString::fromStdString(j.ref.link) + "</a>");
                //message->mainText->setText(platformName + " <a href=\"" +
                //                           QString::fromStdString(j.ref.link.erase(j.ref.link.size() - 1)) + "\">" +
                //                           QString::fromStdString(j.ref.link) + "</a>");
                //message->mainText->setText("Google: <a href=\"https://www.google.com/\">Click Here!</a>");
                message->mainText->setTextInteractionFlags(Qt::TextBrowserInteraction);
                message->mainText->setOpenExternalLinks(true);                               
                TextMessanges->push_back(message);
                ChatList->addWidget(message->mainText);
            }
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
