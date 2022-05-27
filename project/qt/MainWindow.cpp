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
#include "playlistcreator.h"
#include "CustomWidgets.h"

MainWindow::MainWindow(QWidget *parent) :
        QWidget(parent) {
    this->setMinimumSize(500, 483);
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

    scrollArea->setAlignment(Qt::AlignRight);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    scrollArea->setWidgetResizable(true);

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

    client::MessageGroup messages(text.toStdString(), USER_ID, sharedLib::None);
    messages.send([this](const std::vector<sharedLib::Message>::iterator & mBegin, const std::vector<sharedLib::Message>::iterator & mEnd) {
        SendMessageF(mBegin, mEnd);
    }
    );
}

void MainWindow::SendPlaylistClicked() {
    PlaylistCreator *playlistCreator = new PlaylistCreator(this);
    playlistCreator->show();
}

void MainWindow::SumbitPlaylist(client::MessageGroup& messages) {
    messages.send([this](const std::vector<sharedLib::Message>::iterator & mBegin, const std::vector<sharedLib::Message>::iterator & mEnd){
            SendPlaylistF(mBegin, mEnd);
    }
    );
}

void MainWindow::SendMessageF(const std::vector<sharedLib::Message>::iterator & mBegin, const std::vector<sharedLib::Message>::iterator & mEnd){
    for (auto i = mBegin; i != mEnd; ++i) {
        // recive
        Message *message = new Message(i->ownerID, QString::fromStdString(i->text), i->ownerID == USER_ID);
        TextMessanges->push_back(message);
        ChatList->addWidget(message->mainText);
    }
}

void MainWindow::SendPlaylistF(const std::vector<sharedLib::Message>::iterator & mBegin, const std::vector<sharedLib::Message>::iterator & mEnd){
    for (auto i = mBegin; i != mEnd; ++i) {
        Message *message = new Message(i->ownerID, QString::fromStdString(i->text), i->ownerID == USER_ID);
        TextMessanges->push_back(message);
        ChatList->addWidget(message->mainText);

        for (auto& j : i->playlists) {
            Message *message = new Message(i->ownerID, QString::fromStdString(j.ref.link), i->ownerID == USER_ID);
            message->mainText->setWordWrap(true);
            QString platformName = QString::fromStdString(client::getPlatform(j.platform));
            message->mainText->setText(platformName + " <a href=\"" +
                                                       QString::fromStdString(j.ref.link) + "\">" +
                                                       QString::fromStdString(j.ref.link) + "</a>");
            //message->mainText->setText(platformName + " <a href=\"" +
            //                           QString::fromStdString(j.ref.link.erase(j.ref.link.size() - 1)) + "\">" +
            //                           QString::fromStdString(j.ref.link) + "</a>");
            //message->mainText->setText("Google: <a href=\"https://www.google.com/\">Click Here!</a>");
            message->mainText->setOpenExternalLinks(true);
            TextMessanges->push_back(message);
            ChatList->addWidget(message->mainText);
        }
    }
}

MainWindow::~MainWindow() {
    for (auto &i : *TextMessanges) {
        delete(i);
    }
    delete(TextMessanges);
}
