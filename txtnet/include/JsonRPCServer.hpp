#pragma once

#include <string>
#include <iostream>

#include <httplib.h>
#include <jsonrpccxx/iclientconnector.hpp>
#include <jsonrpccxx/server.hpp>

#include "../JsonOptionalAddon.hpp"

namespace txt::net {

/**
 * This function is used to get a function pointer that can be used by the jsonrpc_server.
 */
template<typename... Args>
auto get_handle(Args&&... args) -> decltype(jsonrpccxx::GetHandle(std::forward<Args>(args)...))
{
    return jsonrpccxx::GetHandle(std::forward<Args>(args)...);
}

/**
 * This class combines a jsonrpccxx::JsonRpcServer and a httplib::Server together.
 */
class jsonrpc_server {

public:
    /**
     * Constructs a new jsonrpc_server.
     *
     * @param port the port for the http server to listen on.
     * @param path the pattern/path for the POST request handler.
     * @param host the interface to listen on or "0.0.0.0" to listen on any interface.
     */
    explicit jsonrpc_server(int port, std::string path, std::string host = "0.0.0.0") :
        port(port), path(path), host(host), http_server(), rpc_server()
    {
        http_server.Post(
            path, [this](const httplib::Request& req, httplib::Response& res) { this->handle_post_action(req, res); });
    }

    virtual ~jsonrpc_server() { stop_listening(); }

    /**
     * Add a jsonrpc method to the server.
     * This only works before the server started listening.
     */
    bool add_method(const std::string& name, jsonrpccxx::MethodHandle callback,
        const jsonrpccxx::NamedParamMapping& mapping = jsonrpccxx::NAMED_PARAM_MAPPING)
    {
        if (http_server.is_running()) {
            return false;
        }

        return rpc_server.Add(name, callback, mapping);
    }

    /**
     * Add a jsonrpc notification to the server.
     * This only works before the server started listening.
     */
    bool add_notification(const std::string& name, jsonrpccxx::NotificationHandle callback,
        const jsonrpccxx::NamedParamMapping& mapping = jsonrpccxx::NAMED_PARAM_MAPPING)
    {
        if (http_server.is_running()) {
            return false;
        }

        return rpc_server.Add(name, callback, mapping);
    }

    /**
     * Starts the http server.
     * @note This will block the current thread.
     */
    bool start_listening()
    {
        if (http_server.is_running()) {
            return false;
        }

        return http_server.listen(host, port);
    }

    /**
     * Stop the http server.
     */
    void stop_listening()
    {
        if (http_server.is_running()) {
            http_server.stop();
        }
    }

private:
    void handle_post_action(const httplib::Request& req, httplib::Response& res)
    {
        res.status = 200;
        auto result = rpc_server.HandleRequest(req.body);
        res.set_content(result, "application/json");
    }

private:
    jsonrpccxx::JsonRpc2Server rpc_server;

    httplib::Server http_server;

    int port;
    std::string path;
    std::string host;
};

}