/*
    This file is part of Leela Zero.
    Copyright (C) 2017-2018 Gian-Carlo Pascutto and contributors

    Leela Zero is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Leela Zero is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Leela Zero.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef TCP_SERVER_H_INCLUDED
#define TCP_SERVER_H_INCLUDED

#include <memory>
#include <chrono>
#include <cstdio>
#include <cstdio>
#include <string>
#include <exception>
#include <boost/asio.hpp>

#include "GTP.h"
#include "config.h"

using boost::asio::ip::tcp;

struct ClientConnection {
    tcp::iostream stream;

    ClientConnection(tcp::socket &&_socket);
};

class TCPServer {
public:
    static TCPServer& get_instance() {
        static TCPServer instance{cfg_ngtp_port};
        return instance;
    }

    std::shared_ptr<ClientConnection> accept_connection();
    std::shared_ptr<ClientConnection> get_active_connection() const;

private:
    TCPServer(const ushort port);

    boost::asio::io_service m_io_service;
    tcp::acceptor m_acceptor;
    std::shared_ptr<ClientConnection> m_active_connection;
};

#endif
