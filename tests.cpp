#include <gtest/gtest.h>
#include "bd.h"

Test::BasicTest {
  User = User();
  
  Test(get_user(User.id), User);
  }
  
  Test::BasicTest {
  User = User();
  
  update_user(User.id);
  Test(get_user(User.id), User);
  }
  
  Test::BasicTest {
  Chat = Chat();
  
  Test(get_chat(Chat.id), Chat);
  }
  
  Test::BasicTest {
  Chat = Chat();
  
  add_chat(&Chat);
  Test(get_chat(Chat.id), Chat);
  }

  Test::BasicTest {
  Message = Message();
  
  Test(get_message(Message.id), Message);
  }
  
  Test::BasicTest {
  Message = Message();
  
  add_message(&Message);
  Test(get_message(Message.id), Message);
  }