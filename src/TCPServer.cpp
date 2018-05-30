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

#include "TCPServer.h"
#include "config.h"

TCPServer::TCPServer(const unsigned short port) :
    m_io_service{},
    m_acceptor(m_io_service, tcp::endpoint(tcp::v4(), port)) {}

std::shared_ptr<ClientConnection> TCPServer::accept_connection() {
    auto connection = std::make_shared<ClientConnection>();
    m_acceptor.accept(*(connection->stream.rdbuf()));
    m_active_connection = connection;
    return connection;
}

std::shared_ptr<ClientConnection> TCPServer::get_active_connection() const {
    return m_active_connection;
}
