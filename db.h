#ifndef DB_H
#define DB_H

/* ! BD functions prototypes, may not be included in final project (requires architecture
 * solution how to store it) */

#include <string>
#include <vector>
#include <iostream>
#include <boost/format.hpp>
#include <libpq-fe.h>
//#include <pqxx/pqxx>

#include "teammates_classes.h"
#include "Client.h"
#include "configs.h"

using namespace std;
using namespace boost;
using namespace client;

// get user from db
User	get_user(uint64_t id);

// add user
void	add_user(const User *user);


// get chat info
//Chat	get_chat(uint64_t id);
vector<Chat>	get_chat(uint64_t user_id);

// add chat
void	add_chat(const Chat *chat);


// get message
//Message get_message(uint64_t id);
vector<Message> get_message(uint64_t user_id);

// add message
void	add_message(const Message *message, uint64_t user_id);


#endif
