#pragma once

#include <string>
#include <iostream>

#include <httplib.h>
#include <jsonrpc/server.hpp>

#include "json_txtlib_addon.hpp"
#include "json_optional_addon.hpp"

namespace txt::net {

using jsonrpc::get_handle;

/**
 * This class combines a jsonrpc::server and a httplib::Server together.
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
    bool add_method(const std::string& name, jsonrpc::method_handle callback,
        jsonrpc::parameter_mapping mapping = jsonrpc::empty_parameter_mapping)
    {
        if (http_server.is_running()) {
            return false;
        }

        return rpc_server.add_method(name, callback, mapping);
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
        auto result = rpc_server.handle_request(req.body);
        res.set_content(result, "application/json");
    }

private:
    jsonrpc::server rpc_server;
    httplib::Server http_server;

    int port;
    std::string path;
    std::string host;
};

}