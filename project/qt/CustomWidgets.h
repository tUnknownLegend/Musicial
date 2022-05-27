#ifndef CUSTOMWIDGETS_H
#define CUSTOMWIDGETS_H

#include <QPushButton>
#include <QButtonGroup>
#include <QLabel>
#include <QGroupBox>
#include <QScrollArea>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QMargins>
#include <QWidget>
#include <QLayoutItem>
#include <QLayout>
//#include "../web/project/server/include/net_tools.h"

class ChatSelectorButton : public QPushButton {
    Q_OBJECT
public:
    ChatSelectorButton() = delete;

    ChatSelectorButton(QButtonGroup *_parent = nullptr, const QString &_name = "");
    //QWidget *parent;
};

class Message {
public:
    Message() = delete;

    Message(const unsigned int& _UserID, const QString &text, const bool isUserOwner, QVBoxLayout& _layout);

    ~Message();

    //net_tools::Message

    //bool IsUserOwner;
    unsigned int UserID;
    //QGroupBox *container;
    QLabel *mainText;
    QVBoxLayout* Layout;
    //QLabel *avatar;
    //QScrollArea *scrollArea;
};


class MessageSendBox {
public:
    MessageSendBox(QWidget *_parent);

    QGroupBox *box;
    QLineEdit *Text;
    QPushButton *sendMessage;
    QPushButton *sendMusic;
};

#endif // CUSTOMWIDGETS_H
