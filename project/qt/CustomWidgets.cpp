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

Message::Message(const unsigned int& _UserID, const QString &text, const bool isUserOwner, QVBoxLayout& _layout) : UserID(_UserID) {

    //UserID = IsUserOwner;

    mainText = new QLabel();
    mainText->setText(text);
    mainText->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
   // mainText->setAlignment(Qt::AlignTop | Qt::AlignRight);
    mainText->setMargin(5);
    mainText->setTextFormat(Qt::RichText);
   // mainText->openExternalLinks;
    //_parent.ensureWidgetVisible(container, 1, 1);
    //_parent.setWidgetResizable(true);
    //mainText->setMaximumWidth(container->width());
    //mainText->adjustSize();
    mainText->setTextInteractionFlags(Qt::TextBrowserInteraction);
    mainText->setOpenExternalLinks(true);


    if (!isUserOwner) {
        mainText->setStyleSheet(
                "QLabel {border: 2px solid gray; border-style: inset; border-radius: 10px;background-color: white;padding: 5px 5px 5px 5px;}");
        //container->setAlignment(Qt::AlignTop | Qt::AlignRight);
        //container->setGeometry(container->x(), container->y(), _parent.width() - 20, container->height());
    } else {
        mainText->setStyleSheet(
                "QLabel {border: 1px solid gray; border-style: outset;border: 10px;background-color: lightGray;padding: 5px 5px 5px 5px;}");
        //container->setAlignment(Qt::AlignTop | Qt::AlignLeft);
        //container->setContentsMargins(50, 50, 50, 50);
        //container->setGeometry(container->x(), container->y(), _parent.width() - 20, container->height());
    }
    //_parent.setAlignment(Qt::AlignLeft);
    //container->setGeometry(0, 0, mainText->x() - mainText->width(), mainText->y() - mainText->height());
    //mainText->setGeometry(0, 0, 0, 0);
    //container->setMinimumSize(mainText->width(), mainText->height());
}

Message::~Message() {
    delete mainText;
    //delete avatar;
    //delete container;
    //delete scrollArea;
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
