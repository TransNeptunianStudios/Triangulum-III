#ifndef _WEB_SERVER_H
#define _WEB_SERVER_H

#include <functional>

#include "mongoose.h"

#include "moodycamel/readerwriterqueue.h"

#include "triangulum/component/PlayerInfo.h"

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
   WebServer(moodycamel::ReaderWriterQueue<component::PlayerInfo>& player_info_queue,
             moodycamel::ReaderWriterQueue<int>& input_queue,
             moodycamel::ReaderWriterQueue<int>& output_queue);

   ~WebServer();

   void run();

private:
   void process_input();

   void process_output();

   void event_handler(mg_connection* nc, int ev, void* ev_data);

   moodycamel::ReaderWriterQueue<component::PlayerInfo>& m_player_info_queue;

   moodycamel::ReaderWriterQueue<int>& m_input_queue;

   moodycamel::ReaderWriterQueue<int>& m_output_queue;

   mg_mgr m_mgr;

   mg_connection* m_connection;

   mg_serve_http_opts m_opts;   
};

} // namesapce web
} // namespace triangulum

#endif
