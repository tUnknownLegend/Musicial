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

    Message(const bool &_IsUserOwner, const QString &text);

    ~Message();

    //net_tools::Message

    bool IsUserOwner;
    unsigned int UserID;
    QGroupBox *container;
    QLabel *mainText;
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

class BorderLayout : public QLayout {
public:
    enum Position { West, North, South, East, Center };

    explicit BorderLayout(QWidget *parent, const QMargins &margins = QMargins(), int spacing = -1);
    BorderLayout(int spacing = -1);
    ~BorderLayout();

    void addItem(QLayoutItem *item) override;
    void addWidget(QWidget *widget, Position position);
    Qt::Orientations expandingDirections() const override;
    bool hasHeightForWidth() const override;
    int count() const override;
    QLayoutItem *itemAt(int index) const override;
    QSize minimumSize() const override;
    void setGeometry(const QRect &rect) override;
    QSize sizeHint() const override;
    QLayoutItem *takeAt(int index) override;

    void add(QLayoutItem *item, Position position);

private:
    struct ItemWrapper
    {
        ItemWrapper(QLayoutItem *i, Position p) {
            item = i;
            position = p;
        }

        QLayoutItem *item;
        Position position;
    };

    enum SizeType { MinimumSize, SizeHint };
    QSize calculateSize(SizeType sizeType) const;

    QList<ItemWrapper *> list;
};

#endif // CUSTOMWIDGETS_H
