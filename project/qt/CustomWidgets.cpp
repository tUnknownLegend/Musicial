#include "CustomWidgets.h"
#include <QButtonGroup>
#include <QPixmap>
#include <QScrollArea>
#include <QVBoxLayout>
//#include "net_tools.h"
//#include "builtLibs"

ChatSelectorButton::ChatSelectorButton(QButtonGroup *_parent, const QString &_name) {
    setFixedSize(235, 50);
    //setFixedSize(200, 50);
    _parent->addButton(this);
    setText(_name);
    //AllChatsGroup->addWidget(ChatSelector->button(i));

}

Message::Message(const bool &_IsUserOwner, const QString &text, const QString &pathToPic) : IsUserOwner(_IsUserOwner) {
    container = new QGroupBox();
    container->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    UserID = IsUserOwner;

    mainText = new QLabel(container);
    mainText->setText(text);
    //mainText->setFrameStyle(QFrame::Box);
    mainText->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    mainText->setAlignment(Qt::AlignTop | Qt::AlignRight);
    mainText->setMargin(5);

    if (pathToPic != "") {
        avatar = new QLabel(container);
        QPixmap pix(pathToPic);
        //avatar->setStyleSheet("border-image:url(:/2.png);");
        avatar->setPixmap(pix);
    }

    if (IsUserOwner) {
        container->setStyleSheet(
                "QGroupBox {width: 50px;border: 2px solid gray;border-radius: 3px;background-color: white;padding: 0px 5px 10px 15px;}");
        container->setAlignment(Qt::AlignTop | Qt::AlignRight);
    } else {
        container->setStyleSheet(
                "QGroupBox {border: 1px solid gray;border-radius: 2px;background-color: lightGray;padding: 0px 5px 10px 15px;}");
        container->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    }
}

Message::~Message() {
    delete mainText;
    delete avatar;
    delete container;
    delete scrollArea;
}

MessageSendBox::MessageSendBox(QWidget *_parent) {
    //box = new QGroupBox(_parent);
    //QVBoxLayout layout = new QVBoxLayout(box);
    //box->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    //box->setAlignment(Qt::AlignBottom | Qt::AlignRight);
    Text = new QLineEdit(_parent);
    Text->setPlaceholderText(QString("Enter Playlist URL"));

    //send = new QPushButton(box);

    //sendMusic = new QPushButton();

    //text->setAlignment(setAlignment);
    Text->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    //send->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);

}
