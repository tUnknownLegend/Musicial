#include "MainWindow.h"
#include <QApplication>
#include <QLabel>
#include <QList>
#include "CustomWidgets.h"
#include "lib/include/mainlib.h"
#include "lib/src/mainlib.cpp"
#include "playlistcreator.h"


MainWindow::MainWindow(QWidget *parent) :
        QWidget(parent) {
    setGeometry(0, 0, 800, 500);

    MainSectorWidget = new QWidget(this);
    MainSectorLayout = new QHBoxLayout(MainSectorWidget);
    MainSectorLayout->setAlignment(Qt::AlignTop);
    AllChatsGroup = new QVBoxLayout();
    AllChatsGroup->setAlignment(Qt::AlignTop);
    MainSectorLayout->addLayout(AllChatsGroup);
    ChatSelector = new QButtonGroup(AllChatsGroup);

    //ChatListGroup->addWidget(ChatSelector);
    for (int i = 0; i < 1; ++i) {
        ChatSelectorButton *ChatSelectorBtn = new ChatSelectorButton(ChatSelector, "Saved Messages");
        //ChatSelectorBtn->setFixedSize(200, 50);
        ChatSelector->addButton(ChatSelectorBtn, i);
        AllChatsGroup->addWidget(ChatSelector->button(i));
        //connect(ChatSelectorBtn, SIGNAL (clicked()), QApplication::instance(), SLOT (quit()));
        connect(ChatSelectorBtn, SIGNAL(clicked()), this, SLOT(UpdateChatList()));
    }




    //QWidget *widget = new QWidget(this);
    ///widget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    //QBoxLayout lay;
    //lay->
    //QWidget* RightSectorWidget = new QWidget(MainSectorWidget);
    //RightSectorWidget->setAlignment(Qt::AlignTop);
    RightSectorWidget = new QGroupBox(this);
    RightSectorWidget->setAlignment(Qt::AlignRight);
    RightSectorWidget->setGeometry(250, 0, width() - 250, height());
    RightSectorWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    scrollArea = new QScrollArea(RightSectorWidget);
    //scrollArea->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    //scrollArea->s

    //QGroupBox * ChatListWidget = new QGroupBox(scrollArea);
    //scrollArea->setWidget(ChatListWidget);
    // MainSectorGroup->addWidget(ChatListWidget);
    //ChatListWidget->setAlignment(Qt::AlignRight);
    //ChatList = new QVBoxLayout(ChatListWidget);
    //ChatList->setAlignment(Qt::AlignRight);



    //  scrollArea->setWidgetResizable(true);
    scrollArea->setStyleSheet("QScrollBar:vertical { ""width: 10px;""}");
    scrollArea->setGeometry(0, 0, width() - 250, height() - 50);
    scrollArea->setMinimumSize(300, 200);

    scrollArea->setAlignment(Qt::AlignRight);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    scrollArea->setWidgetResizable(true);

    ChatListWidget = new QGroupBox(this);
    scrollArea->setWidget(ChatListWidget);
    ChatListWidget->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    //ChatListWidget->setAlignment(Qt::AlignRight);
    //ChatListWidget->resize();
    //ChatListWidget->setGeometry(205, 100, 205, 200 );


    ChatList = new QVBoxLayout();
    //MainSectorLayout->addLayout(ChatList);
    ChatList->setAlignment(Qt::AlignRight);
    //MainSectorGroup->addLayout(ChatList);
    ChatListWidget->setLayout(ChatList);


    //sestCentralWidget(scrollArea);
    //MainSectorGroup->addWidget(scrollArea);

    //scrollArea = QScrollArea(this);
    //layout = QVBoxLayout(scrollarea);
    //scrollArea->setWidget(layout.widget());
/*
    for (auto i : MessageList) {
        //Message *message = new Message(1, "first line (not)second line");
        //MessageList.append(message);
        ChatList->addWidget(i->container);
        //scrollArea->setWidget(message->container);
    }
*/
    sendBox = new MessageSendBox(RightSectorWidget);
    sendBox->Text->setGeometry(0, 445, 450, 50);
    QPushButton *SendMessage = new QPushButton("M", RightSectorWidget);
    QPushButton *SendPlaylist = new QPushButton("P", RightSectorWidget);
    SendMessage->setGeometry(495, 445, 45, 50);
    SendPlaylist->setGeometry(450, 445, 45, 50);

    // sig = sendBox->text->displayText();

    connect(SendMessage, SIGNAL(clicked()), this, SLOT(SendMessageClicked()));
    //connect(SendPlaylist, SIGNAL (clicked()), QApplication::instance(), SLOT (SendPlaylist(sendBox->text->displayText())));
    connect(SendPlaylist, SIGNAL(clicked()), this, SLOT(SendPlaylistClicked()));

    /*
    QList<QLabel*> LabelList;
    QLabel *label = new QLabel();
    LabelList.append(label);
    label->setFrameStyle(QFrame::Box);
    label->setText("first line\nsecond line");
    label->setAlignment(Qt::AlignTop | Qt::AlignRight);
    label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    ChatList->addWidget(label);
    */
}

void MainWindow::ChatSelectorCliked(bool clicked) {
    if (clicked) {
        RightSectorWidget->hide();
    } else {
        RightSectorWidget->hide();
    }
}


void MainWindow::SendMessageClicked() {
    if (sendBox->Text->displayText() == "")
        return;

    QString text = sendBox->Text->displayText();
    client::MessageGroup messages(text.toStdString(), 0, false);
    messages.send();

    //text = QString::fromStdString(messages.Messages[0].text);
    QList < Message * > MessageList;
    //Message m(1, "first line (not)second line");

    for (auto &i: messages.Messages) {
        Message *message = new Message(0, sendBox->Text->displayText());
        MessageList.append(message);
        message = new Message(!i.owner_id, QString::fromStdString(i.text));
        MessageList.append(message);
    }

    //Message *message = new Message(1, text);
    //MessageList.append(message);

    for (auto &i: MessageList) {
        ChatList->addWidget(i->container);
        scrollArea->minimumHeight();
    }

    //messages.Messages

    //quit();

    //SendMessage(text.toStdString(), UserID);
}

void MainWindow::SendPlaylistClicked() {
    PlaylistCreator *playlistCreator = new PlaylistCreator(this);
    playlistCreator->show();
}

void MainWindow::SumbitPlaylist(QString text) {
    client::MessageGroup messages(text.toStdString(), 0, true);
    messages.send();

    //text = QString::fromStdString(messages.Messages[0].text);
    QList < Message * > MessageList;
    //Message m(1, "first line (not)second line");

    for (auto &i: messages.Messages) {
        Message *message = new Message(0, text);
        MessageList.append(message);
        message = new Message(!i.owner_id, QString::fromStdString(i.playlists.Ref));
        MessageList.append(message);
    }

    for (auto &i: MessageList) {
        ChatList->addWidget(i->container);
        //scrollArea->maximumHeight();
    }




    //SendPlaylist(text.toStdString(), UserID);
}

void MainWindow::UpdateChatList() {
    client::ButtonGetDialog updateContainer;
    updateContainer.action();

    QList < Message * > MessageList;
    for (auto &i: updateContainer.Messages) {
        Message *message = new Message(!i.owner_id, QString::fromStdString(i.text));
        MessageList.append(message);
    }

    for (auto i: MessageList) {
        ChatList->addWidget(i->container);
    }
}

/*
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent) :
 QWidget(parent)
{
 // Set size of the window
 //setFixedSize(100, 50);
 setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
 // Create and position the button
 m_button = new QPushButton("Hello World", this);
 m_button->setGeometry(10, 10, 80, 30);
 m_button->setCheckable(true);

connect(m_button, SIGNAL (clicked(bool)), this, SLOT (slotButtonClicked(bool)));
}

void MainWindow::slotButtonClicked(bool checked)
{
 if (checked) {
 m_button->setText("Checked");
 } else {
 m_button->setText("Hello World");
 }
}

*/
/*
MainWindow::MainWindow(QWidget *parent) :
 QWidget(parent)
 {
 // Set size of the window
 //setFixedSize(1000, 1000);
  setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
 // Create and position the button
 m_button = new QPushButton("Hello World", this);
 m_button->setGeometry(10, 10, 80, 30);
 connect(m_button, SIGNAL (clicked()), QApplication::instance(), SLOT (quit()));
}
*/
/*
#include <QApplication>
#include <QProgressBar>
#include <QSlider>

int main(int argc, char **argv)
{
 QApplication app (argc, argv);

 // Create a container window
 QWidget window;
 window.setFixedSize(200, 80);

 // Create a progress bar
 // with the range between 0 and 100, and a starting value of 0
 QProgressBar *progressBar = new QProgressBar(&window);
 progressBar->setRange(0, 100);
 progressBar->setValue(0);
 progressBar->setGeometry(10, 10, 180, 30);

 // Create a horizontal slider
 // with the range between 0 and 100, and a starting value of 0
 QSlider *slider = new QSlider(&window);
 slider->setOrientation(Qt::Horizontal);
 slider->setRange(0, 100);
 slider->setValue(0);
 slider->setGeometry(10, 40, 180, 30);

 window.show();

 // Connection
 // This connection set the value of the progress bar
 // while the slider's value changes
 QObject::connect(slider, SIGNAL (valueChanged(int)), progressBar, SLOT (setValue(int)));

 return app.exec();
}
*/
