
#include "WebServer.h"

static mg_serve_http_opts s_http_server_opts;

using json = nlohmann::json;

namespace triangulum {
namespace web {

using namespace message;

WebServer::WebServer(MessageManager& msg_manager)
: m_msg_manager(msg_manager)
, m_mgr()
, m_connection()
//, m_opts()
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
}

WebServer::~WebServer()
{
   mg_mgr_free(&m_mgr);
}

void WebServer::process_input()
{
   mg_mgr_poll(&m_mgr, 10);
}

void WebServer::process_output()
{
   for_all_msg(m_msg_manager.output_map(), [this](const Message& msg) {
      std::string json_msg = msg.second.dump(0);

      mg_send_websocket_frame(msg.first,
                              WEBSOCKET_OP_TEXT,
                              json_msg.c_str(),
                              json_msg.size());
   });
}

void WebServer::event_handler(mg_connection *nc, int ev, void *ev_data)
{
   switch (ev) {
   case MG_EV_WEBSOCKET_HANDSHAKE_DONE:
      break;
   case MG_EV_WEBSOCKET_FRAME:
      {
         struct websocket_message* wm = (struct websocket_message*) ev_data;

         if (wm->size > BUFFER_SIZE)
         {
            // TODO: Log this!
            return;
         }

         strncpy(m_buffer, (const char*) wm->data, wm->size);

         m_msg_manager.parse_buffer(nc, m_buffer);

         break;
      }
   case MG_EV_HTTP_REQUEST:
      {
         mg_serve_http(nc, (struct http_message*)ev_data, s_http_server_opts);
         break;
      }
   case MG_EV_CLOSE:
      {
         if (nc->flags & MG_F_IS_WEBSOCKET) {
            std::cout << "Client connection lost\n";
         }
         break;
      }
   }
}

} // namespace web
} // namespace triangulum
