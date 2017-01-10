#include "WebServer.h"
#include "nlohmann/json.hpp"

static mg_serve_http_opts s_http_server_opts;

using json = nlohmann::json;

namespace triangulum {
namespace web {

WebServer::WebServer()
: m_mgr()
, m_connection()
, m_opts()
{
}

WebServer::~WebServer()
{
   mg_mgr_free(&m_mgr);
}

void WebServer::init()
{
   mg_mgr_init(&m_mgr, NULL);

   m_connection = mg_bind(&m_mgr, "8080", event_handler);

   mg_set_protocol_http_websocket(m_connection);

   s_http_server_opts.document_root = "../../client/";

   s_http_server_opts.enable_directory_listing = "yes";
}

void WebServer::process()
{
   mg_mgr_poll(&m_mgr, 50);
}

void WebServer::event_handler(mg_connection *nc, int ev, void *ev_data)
{
   switch (ev) {
   case MG_EV_WEBSOCKET_HANDSHAKE_DONE: {
         json j;

         j["msg"] = "Welcome!";

         std::string welcome_msg = j.dump(3);

         mg_send_websocket_frame(nc,
                                 WEBSOCKET_OP_TEXT,
                                 welcome_msg.c_str(),
                                 welcome_msg.size());
         break;
      }
   case MG_EV_WEBSOCKET_FRAME: {
        // Something are a little bit off here... but almost?
         struct websocket_message* wm = (struct websocket_message*) ev_data;

         const char* data = (const char*) wm->data;

         std::cout << "Got string: " << data << "\n";

         auto j = json::parse(data);

         std::cout << "JSON size: " << j.size() << "\n";

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
