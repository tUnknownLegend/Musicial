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

class ChatSelectorButton : public QPushButton {
    Q_OBJECT
public:
    ChatSelectorButton() = delete;

    ChatSelectorButton(QButtonGroup *_parent = nullptr, const QString &_name = "");
};

class Message {
public:
    Message() = delete;

    Message(const unsigned int& _UserID, const QString &text, const bool isUserOwner);

    ~Message();

    unsigned int UserID;
    QLabel *mainText;
    QVBoxLayout* Layout;
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
