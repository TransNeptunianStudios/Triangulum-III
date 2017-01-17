#ifndef _I_CONNECTION_MANAGER_H
#define _I_CONNECTION_MANAGER_H

namespace triangulum {
namespace network {

class IConnection;

class IConnectionManager
{
public:
   virtual ~IConnectionManager() {}

   virtual void accept_connections(std::function<bool(std::shared_ptr<IConnection>)> accept_function) = 0;
};

} // namespace system
} // namespace triangulum

#endif
