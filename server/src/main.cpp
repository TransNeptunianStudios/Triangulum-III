
// std
#include <iostream>

// external
#include "mongoose.h"
#include "nlohmann/json.hpp"

// application
#include "Game.h"

struct mg_serve_http_opts s_http_server_opts;

using json = nlohmann::json;

void event_handler(struct mg_connection* nc, int ev, void* ev_data) {
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

int main(int argc, char* argv[])
{
   struct mg_mgr mgr;

   struct mg_connection* nc;

   mg_mgr_init(&mgr, NULL);

   nc = mg_bind(&mgr, "8080", event_handler);

   mg_set_protocol_http_websocket(nc);

   s_http_server_opts.document_root = "../../client/";

   s_http_server_opts.enable_directory_listing = "yes";

   std::cout << "Starting web server on port 8080\n";

   for (;;) {
      mg_mgr_poll(&mgr, 50);
   }

   mg_mgr_free(&mgr);

   return 0;
}
