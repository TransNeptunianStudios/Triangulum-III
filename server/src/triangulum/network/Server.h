#ifndef _WEB_SERVER_H
#define _WEB_SERVER_H

#include <functional>
#include <vector>
#include "mongoose.h"
#include "triangulum/network/Connection.h"

namespace triangulum {
namespace network {

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

class Server
{
public:
   Server();

   ~Server();

   void process_input();

   void handle_pending_connections(std::function<bool(IConnection*)> do_accept);

private:
   void event_handler(mg_connection* nc, int ev, void* ev_data);

   void remove_connection(mg_connection* nc);

   std::vector<std::unique_ptr<Connection>>::iterator find_connection(mg_connection* nc);

   std::vector<std::unique_ptr<Connection>> m_connection_list;

   mg_mgr m_mgr;

   mg_connection* m_connection;

   // TODO: Remove?
   //mg_serve_http_opts m_opts;

   static const size_t BUFFER_SIZE = 256;

   char m_buffer[BUFFER_SIZE];
};

} // namesapce network
} // namespace triangulum

#endif