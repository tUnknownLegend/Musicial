#ifndef CUSTOMWIDGETS_H
#define CUSTOMWIDGETS_H

#include <QPushButton>
#include <QButtonGroup>
#include <QLabel>
#include <QGroupBox>
#include <QScrollArea>
#include <QLineEdit>
#include <QVBoxLayout>

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

    Message(const bool &_IsUserOwner, const QString &text, const QString &pathToPic = "");

    ~Message();

    bool IsUserOwner;
    int unsigned UserID;
    QGroupBox *container;
    QLabel *mainText;
    QLabel *avatar;
    QScrollArea *scrollArea;
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
