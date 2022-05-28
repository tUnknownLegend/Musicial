#include <gtest/gtest.h>

#include "net_tools.h"
#include "shared_lib.h"

TEST(parseMessage, CorrectData) {
    sharedLib::Message message = {1, 2, "test",{}, 0, {}, 0, {}, 0};
    std::string strMessage = net_tools::Message2String(message);

    EXPECT_TRUE(strMessage == net_tools::Message2String(message));
}
