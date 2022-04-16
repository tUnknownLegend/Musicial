#ifndef BD_H
#define BD_H

/* ! BD functions prototypes, may not be included in final project (requires architecture
 * solution how to store it) */

#include <string>
using namespace std;


// get info about user
User	get_user(string first_name, string last_name);
User	get_user(uint64_t id);

// update user info
void	update_user(const User *user);

uint64_t	get_user_chats(uint64_t user_id);  //returns chat_id
Chat	get_user_chats(uint64_t user_id); // return Chat

// get chat info
Chat	get_chat(uint64_t id);
Chat	get_chat(uint64_t user_id);

// adding chat
void	add_chat(const Chat *chat);

// get message
Message get_message(uint64_t id);
Message get_message(uint64_t user_id);

// adding message
void	add_message(const Message *message, uint64_t user_id);


#endif
