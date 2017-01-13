#ifndef _MESSAGE_MANAGER_H
#define _MESSAGE_MANAGER_H

#include "mongoose.h"
#include "triangulum/message/MessageMap.h"

namespace triangulum {
namespace message {

class MessageManager
{
public:
   MessageManager();

   void parse_buffer(mg_connection* nc, const char* buffer);

   void add_output(std::string msg_type, const Message& msg);

   MessageMap& input_map();

   MessageMap& output_map();

private:

   void reg_input_msg(std::string msg_type);

   void reg_output_msg(std::string msg_type);

   MessageMap m_msg_input;

   MessageMap m_msg_output;
};

} // namespace message
} // namespace triangulum

#endif
