#!/usr/bin/python
from mininet.topo import Topo
from mininet.net import Mininet
from mininet.cli import CLI
from mininet.link import TCLink

class MyTopology(Topo):
    """
    A basic topology
    """
    def __init__(self):
        Topo.__init__(self)

        # SWITCHES
        switch1 = self.addSwitch('Switch_1')  # Adds a Switch
        switch2 = self.addSwitch('Switch_2')  # Adds a Switch
        switch3 = self.addSwitch('Switch_3')  # Adds a Switch
        switch4 = self.addSwitch('Switch_4')  # Adds a Switch

        # HOSTS
        host1 = self.addHost('siri', ip='10.1.0.1')      # Adds a Host with IP address
        host2 = self.addHost('desktop', ip='10.2.0.1')    # Adds a Host with IP address
        host3 = self.addHost('fridge', ip='10.2.0.2')     # Adds a Host with IP address
        host4 = self.addHost('alexa', ip='10.3.0.1')      # Adds a Host with IP address
        host5 = self.addHost('smarttv', ip='10.3.0.2')    # Adds a Host with IP address
        host6 = self.addHost('server', ip='10.4.0.1')     # Adds a Host with IP address

        # LINKS
        self.addLink(host1, switch1)  # Add a link
        self.addLink(host2, switch2)  # Add a link
        self.addLink(host3, switch2)  # Add a link
        self.addLink(host4, switch3)  # Add a link
        self.addLink(host5, switch3)  # Add a link
        self.addLink(host6, switch4)  # Add a link
        self.addLink(switch1, switch2)  # Add a link
        self.addLink(switch2, switch3)  # Add a link
        self.addLink(switch3, switch4)  # Add a link

if __name__ == '__main__':
    topo = MyTopology()  # Creates the topology
    net = Mininet(topo=topo, link=TCLink)  # Loads the topology
    net.start()  # Starts Mininet

    # Commands here will run on the simulated topology
    CLI(net)
    net.stop()  # Stops Mininet
