#include "CustomWidgets.h"
#include <QButtonGroup>
#include <QPixmap>
#include <QScrollArea>
#include <QVBoxLayout>

ChatSelectorButton::ChatSelectorButton(QButtonGroup *_parent, const QString &_name) {
    setFixedSize(235, 50);
    _parent->addButton(this);
    setText(_name);
}

Message::Message(const unsigned int& _UserID, const QString &text, const bool isUserOwner, QVBoxLayout& _layout) : UserID(_UserID) {
    mainText = new QLabel();
    mainText->setText(text);
    mainText->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    mainText->setMargin(5);
    mainText->setTextFormat(Qt::RichText);
    mainText->setWordWrap(true);

    if (!isUserOwner) {
        mainText->setStyleSheet(
                "QLabel {border: 2px solid gray; border-style: inset; border-radius: 10px;background-color: white;padding: 5px 5px 5px 5px;}");
    } else {
        mainText->setStyleSheet(
                "QLabel {border: 1px solid gray; border-style: outset;border: 10px;background-color: lightGray;padding: 5px 5px 5px 5px;}");
    }
}

Message::~Message() {
    delete mainText;
}

MessageSendBox::MessageSendBox(QWidget *_parent) {
    Text = new QLineEdit(_parent);
    Text->setPlaceholderText(QString("Enter Message"));
    Text->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
}
