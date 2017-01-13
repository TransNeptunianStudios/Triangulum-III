#ifndef _WEB_SERVER_H
#define _WEB_SERVER_H

#include <functional>
#include "mongoose.h"
#include "triangulum/message/MessageManager.h"

namespace triangulum {
namespace web {

//*****************************************************************************
// Solution for passing a non-static member function as a C callback.
// See: http://stackoverflow.com/questions/1000663/using-a-c-class-member-function-as-a-c-callback-function
template <typename T>
struct Callback;

template <typename Ret, typename... Params>
struct Callback<Ret(Params...)> {
   template <typename... Args>
   static Ret callback(Args... args) {
      func(args...);
   }
   static std::function<Ret(Params...)> func;
};

template <typename Ret, typename... Params>
std::function<Ret(Params...)> Callback<Ret(Params...)>::func;

typedef void (*callback_t)(mg_connection*, int, void*);
//*****************************************************************************

class WebServer
{
public:
   WebServer(message::MessageManager& msg_manager);

   ~WebServer();

   void process_input();

   void process_output();

private:
   void event_handler(mg_connection* nc, int ev, void* ev_data);

   message::MessageManager& m_msg_manager;

   mg_mgr m_mgr;

   mg_connection* m_connection;

   // TODO: Remove?
   //mg_serve_http_opts m_opts;

   static const size_t BUFFER_SIZE = 256;

   char m_buffer[BUFFER_SIZE];
};

} // namesapce web
} // namespace triangulum

#endif
