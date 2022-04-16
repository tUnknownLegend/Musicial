#include <gtest/gtest.h>
#include "gmock/gmock.h"
#include "Client.h"
#include <string.h>

//Text text = {{"black", "white"}, "123ABC!"}

class MockMessage: public Message {
public:
    MOCK_METHOD0(MsendDB, void());
    MOCK_METHOD0(Msend, void());

    bool sendDB() {
        Message::sendDB();
        MsendDB();
        return false; 
    };

    bool sendNet() {
        Message::sendNet();
        Msend();
        return false;
    };
};

TEST(ButtonSendMessage, Mock) {
    MockMessage message;
    
    EXPECT_CALL(message, MsendDB()).Times(1);
    EXPECT_CALL(message, Msend()).Times(1);

    client::ButtonSendMessage btn;

    EXPECT_EQ(btn.action(message), true);
}

TEST(ButtonAuth, Mock) {
    std::string login = "FISRT";
    std::string pwd = "s!e2$c@!ASDa_";
    
    //EXPECT_CALL(message, sendDB()).Times(1);
    //EXPECT_CALL(message, sendDB()).Times(1);

    client::ButtonAuth btn;

    EXPECT_EQ(btn.action(login, pwd), true);
}

class MSongGroup : public client::SongGroup {
public:
    
    MOCK_METHOD0(MgetDB, void());
    MOCK_METHOD0(MreceiveNet, void());
    MOCK_METHOD0(MsendDB, void());
    MOCK_METHOD0(MsendNet, void());

    bool getDB() { 
        client::SongGroup::getDB();
        MgetDB();
        return false;
    };

    bool receiveNet() {
        client::SongGroup::receiveNet();
        MreceiveNet();
        return false;
    };

    bool sendDB() {
        client::SongGroup::sendDB();
        MsendDB();
        return false;
    };

    bool sendNet() {
        client::SongGroup::sendNet();
        MsendNet();
        return false;
    };
};

TEST(ButtonCreatePlaylist, Mock) {
    MSongGroup list;
    
    EXPECT_CALL(list, MsendDB()).Times(1);
    EXPECT_CALL(list, MsendNet()).Times(1);
    EXPECT_CALL(list, MgetDB()).Times(1);
    EXPECT_CALL(list, MreceiveNet()).Times(1);

    client::ButtonCreatePlaylist btn;

    EXPECT_EQ(btn.action(list), true);
}

class mMessageGroup : public client::MessageGroup {
public:
    MOCK_METHOD0(MockgetDB, void());
    MOCK_METHOD0(MockreceiveNet, void());
    MOCK_METHOD0(MocksendDB, void());
    MOCK_METHOD0(MocksendNet, void());

    bool getDB() { 
        client::MessageGroup::getDB();
        MockgetDB();
        return false;
    };

    bool receiveNet() {
        client::MessageGroup::receiveNet();
        MockreceiveNet();
        return false;
    };

    bool sendDB() {
        client::MessageGroup::sendDB();
        MocksendDB();
        return false;
    };

    bool sendNet() {
        client::MessageGroup::sendNet();
        MocksendNet();
        return false;
    };
};

TEST(ButtonGetDialog, Mock) {
    mMessageGroup messages;

    EXPECT_CALL(messages, MocksendDB()).Times(1);
    EXPECT_CALL(messages, MocksendNet()).Times(1);
    EXPECT_CALL(messages, MockgetDB()).Times(1);
    EXPECT_CALL(messages, MockreceiveNet()).Times(1);

    client::ButtonGetDialog btn;

    EXPECT_EQ(btn.action(messages), true);
}