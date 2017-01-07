
// std
#include <stdio.h>
#include <string.h>

// mongoose
#include "mongoose.h"

// parson
#include "parson.h"

struct mg_serve_http_opts s_http_server_opts;

void event_handler(struct mg_connection* nc, int ev, void* ev_data)
{
   switch (ev)
   {
   case MG_EV_WEBSOCKET_HANDSHAKE_DONE:
      {
         // New web socket connection
         printf("New web socket connection\n");

         char* welcome_msg = NULL;
        
         JSON_Value* root = json_value_init_object();

         JSON_Object* root_obj = json_value_get_object(root);

         json_object_set_string(root_obj, "msg", "Welcome!");

         welcome_msg = json_serialize_to_string_pretty(root);

         mg_send_websocket_frame(nc,
                                 WEBSOCKET_OP_TEXT,
                                 welcome_msg,
                                 strlen(welcome_msg));

         json_free_serialized_string(welcome_msg);

         json_value_free(root);

         break;
      }
   case MG_EV_WEBSOCKET_FRAME:
      {
         struct websocket_message* wm = (struct websocket_message*) ev_data;
         struct mg_str s = { (char*) wm->data, wm->size };
         printf("Got: %s\n", s.p);

         break;
      }
   case MG_EV_HTTP_REQUEST:
      {
         mg_serve_http(nc, (struct http_message*)ev_data, s_http_server_opts);
         break;
      }
   case MG_EV_CLOSE:
      {
         if (nc->flags & MG_F_IS_WEBSOCKET)
         {
            printf("Client connection lost\n");
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

   printf("Starting web server on port 8080\n");

   for (;;)
   {
      mg_mgr_poll(&mgr, 50);
   }

   mg_mgr_free(&mgr);

   return 0;
}
