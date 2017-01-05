
// std
#include <iostream>

// mongoose
#include "mongoose.h"

struct mg_serve_http_opts s_http_server_opts;

void event_handler(struct mg_connection* nc, int ev, void* ev_data)
{
   switch (ev)
   {
   case MG_EV_HTTP_REQUEST:
      mg_serve_http(nc, (http_message*)ev_data, s_http_server_opts);
      break;
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

   for (;;)
   {
      mg_mgr_poll(&mgr, 50);
   }

   mg_mgr_free(&mgr);

   return 0;
}
