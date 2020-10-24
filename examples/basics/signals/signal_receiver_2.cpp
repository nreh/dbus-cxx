/***************************************************************************
 *   Copyright (C) 2007,2008,2009,2010 by Rick L. Vinyard, Jr.             *
 *   rvinyard@cs.nmsu.edu                                                  *
 *                                                                         *
 *   This file is part of the dbus-cxx library.                            *
 *                                                                         *
 *   The dbus-cxx library is free software; you can redistribute it and/or *
 *   modify it under the terms of the GNU General Public License           *
 *   version 3 as published by the Free Software Foundation.               *
 *                                                                         *
 *   The dbus-cxx library is distributed in the hope that it will be       *
 *   useful, but WITHOUT ANY WARRANTY; without even the implied warranty   *
 *   of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU   *
 *   General Public License for more details.                              *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this software. If not see <http://www.gnu.org/licenses/>.  *
 ***************************************************************************/
#include <dbus-cxx.h>
#include <iostream>
#include <unistd.h>

/**
 * This example demonstrates a dispatched signal receiver.
 *
 * The created signal is connected to the print function, leaving the
 * details of the message unpacking within the created signal.
 */

void print( std::string s );

int main()
{
  std::shared_ptr<DBus::Dispatcher> dispatcher = DBus::StandaloneDispatcher::create();

  std::shared_ptr<DBus::Connection> connection = dispatcher->create_connection( DBus::BusType::SESSION );

  std::shared_ptr<DBus::SignalProxy<void(std::string)>> signal = connection->create_signal_proxy<void(std::string)>(
                                            DBus::SignalMatchRule::create()
                                            .setPath("/test/signal/Object")
                                            .setInterface("test.signal.Type")
                                            .setMember("Test"),
                                    DBus::ThreadForCalling::DispatcherThread );

  signal->connect( sigc::ptr_fun(print) );

  std::cout << "Running" << std::flush;
  
  for (int i=0; i < 10; i++)
  {
    std::cout << "." << std::flush;
    sleep(1);
  }
  
  std::cout << std::endl;

  return 0;
}

void print( std::string val )
{
  std::cout << "Got Signal with value " << val << std::endl;
}
