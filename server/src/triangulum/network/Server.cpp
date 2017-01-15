#include "triangulum/network/Server.h"
#include "nlohmann/json.hpp"

static mg_serve_http_opts s_http_server_opts;

namespace triangulum {
namespace network {

Server::Server()
: m_connection_list()
, m_mgr()
, m_connection()
, m_buffer()
//, m_opts()
{
   memset(m_buffer, 0, BUFFER_SIZE);

   mg_mgr_init(&m_mgr, NULL);

   Callback<void(mg_connection*, int, void*)>::func = std::bind(&Server::event_handler,
                                                                this, std::placeholders::_1,
                                                                std::placeholders::_2,
                                                                std::placeholders::_3);

   callback_t func = static_cast<callback_t>(Callback<void(mg_connection*, int, void*)>::callback);

   m_connection = mg_bind(&m_mgr, "8080", func);

   mg_set_protocol_http_websocket(m_connection);

   s_http_server_opts.document_root = "../../client/";

   s_http_server_opts.enable_directory_listing = "yes";
}

Server::~Server()
{
   mg_mgr_free(&m_mgr);
}

void Server::process_input()
{
   mg_mgr_poll(&m_mgr, 10);
}

void Server::handle_pending_connections(std::function<bool(IConnection*)> do_accept)
{
   for (auto& connection : m_connection_list)
   {
      nlohmann::json dummy_msg;

      if (!connection->is_accepted() && connection->peek_msg("login", dummy_msg))
      {
         if (do_accept(connection.get()))
         {
            connection->set_accepted(true);
         }
      }
   }
}

void Server::event_handler(mg_connection *nc, int ev, void *ev_data)
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

         memset(m_buffer, 0, BUFFER_SIZE);

         strncpy(m_buffer, (const char*) wm->data, wm->size);

         Json msg;

         try
         {
            msg = nlohmann::json::parse(m_buffer);
         }
         catch (std::invalid_argument)
         {
            std::cout << "Failed to parse: " << m_buffer << "\n";
         }

         if (msg["type"].is_string())
         {
            std::string msg_type = msg["type"];

            auto it(find_connection(nc));

            if (it != end(m_connection_list))
            {
               (*it)->set_msg(msg_type, msg);
            }
            else
            {
               auto connection(std::make_unique<Connection>(nc));

               connection->set_msg(msg_type, msg);

               m_connection_list.push_back(std::move(connection));
            }
         }
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
            remove_connection(nc);
         }
         break;
      }
   }
}

void Server::remove_connection(mg_connection* nc)
{
   auto it(find_connection(nc));

   if (it != end(m_connection_list))
   {
      m_connection_list.erase(it);
   }
}

std::vector<std::unique_ptr<Connection>>::iterator Server::find_connection(mg_connection *nc)
{
   // Find the connection
   return std::find_if(begin(m_connection_list),
                       end(m_connection_list),
                       [=](const std::unique_ptr<Connection>& c) {
                          return c->raw() == nc;
                       });

}

} // namespace network
} // namespace triangulum
