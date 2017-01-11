
#include "WebServer.h"
#include "nlohmann/json.hpp"

#include "triangulum/component/PlayerInfo.h"

static mg_serve_http_opts s_http_server_opts;

using namespace moodycamel;

using json = nlohmann::json;

namespace triangulum {
namespace web {

using namespace component;

WebServer::WebServer(ReaderWriterQueue<component::PlayerInfo>& player_info_queue,
                     ReaderWriterQueue<int>& input_queue,
                     ReaderWriterQueue<int>& output_queue)
: m_player_info_queue(player_info_queue)
, m_input_queue(input_queue)
, m_output_queue(output_queue)
, m_mgr()
, m_connection()
, m_opts()
{

}

WebServer::~WebServer()
{
   mg_mgr_free(&m_mgr);
}

void WebServer::run()
{
   mg_mgr_init(&m_mgr, NULL);

   Callback<void(mg_connection*, int, void*)>::func = std::bind(&WebServer::event_handler,
                                                                this, std::placeholders::_1,
                                                                std::placeholders::_2,
                                                                std::placeholders::_3);

   callback_t func = static_cast<callback_t>(Callback<void(mg_connection*, int, void*)>::callback);

   m_connection = mg_bind(&m_mgr, "8080", func);

   mg_set_protocol_http_websocket(m_connection);

   s_http_server_opts.document_root = "../../client/";

   s_http_server_opts.enable_directory_listing = "yes";

   while (1)
   {
      process_input();
      process_output();
   }
}

void WebServer::process_input()
{
   mg_mgr_poll(&m_mgr, 10);
}

void WebServer::process_output()
{
}

void WebServer::event_handler(mg_connection *nc, int ev, void *ev_data)
{
   switch (ev) {
   case MG_EV_WEBSOCKET_HANDSHAKE_DONE: {
         static int cntr = 0;

         json j;

         j["msg"] = "Welcome!";

         std::string welcome_msg = j.dump(3);

         mg_send_websocket_frame(nc,
                                 WEBSOCKET_OP_TEXT,
                                 welcome_msg.c_str(),
                                 welcome_msg.size());

         m_input_queue.try_enqueue(cntr++);

         break;
      }
   case MG_EV_WEBSOCKET_FRAME: {
        // Something are a little bit off here... but almost?
         struct websocket_message* wm = (struct websocket_message*) ev_data;

         char buf[100];

         snprintf(buf, wm->size+1, "%s", (const char*) wm->data);

         std::cout << "Got string: " << buf << "\n";

         auto j = json::parse(buf);

         if (j["type"] == "login")
         {
            PlayerInfo player_info;

            player_info.connection = nc;

            player_info.name = j["name"];

            m_player_info_queue.enqueue(player_info);
         }

         break;
      }
   case MG_EV_HTTP_REQUEST: {
         mg_serve_http(nc, (struct http_message*)ev_data, s_http_server_opts);
         break;
      }
   case MG_EV_CLOSE: {
         if (nc->flags & MG_F_IS_WEBSOCKET) {
            std::cout << "Client connection lost\n";
         }
         break;
      }
   }
}

} // namespace web
} // namespace triangulum
