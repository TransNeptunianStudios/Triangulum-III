#ifndef _WEB_SERVER_H
#define _WEB_SERVER_H

#include "mongoose.h"

namespace triangulum {
namespace web {

class WebServer
{
public:
   WebServer();

   ~WebServer();
   
   void init();

   void process();

private:

   static void event_handler(mg_connection* nc, int ev, void* ev_data);

   mg_mgr m_mgr;

   mg_connection* m_connection;

   mg_serve_http_opts m_opts;
};

} // namesapce web
} // namespace triangulum

#endif
