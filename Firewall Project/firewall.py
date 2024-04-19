# controller skeleton 

from pox.core import core
import pox.openflow.libopenflow_01 as of

log = core.getLogger()

class Firewall (object):
    """
    A Firewall object is created for each switch that connects.
    A Connection object for that switch is passed to the __init__ function.
    """
    def __init__ (self, connection):
        # Keep track of the connection to the switch so that we can
        # send it messages!
        self.connection = connection

        # This binds our PacketIn event listener
        connection.addListeners(self)

    def do_firewall(self, packet, packet_in):
        # The code in here will be executed for every packet

        def accept():
            # Write code for an accept function
            msg = of.ofp_flow_mod()
            msg.data = packet_in
            msg.match = of.ofp_match.from_packet(packet_in)
            msg.actions.append(of.ofp_action_output(port=of.OFPP_FLOOD))
            msg.idle_timeout = 45
            msg.hard_timeout = 400
            self.connection.send(msg)
            print("Packet Accepted - Flow Table Installed on Switches")

        def drop():
            # Write code for a drop function
            msg = of.ofp_flow_mod()
            msg.data = packet_in
            msg.match = of.ofp_match.from_packet(packet_in)
            msg.idle_timeout = 45
            msg.hard_timeout = 400
            self.connection.send(msg)
            print("Packet Dropped - Flow Table Installed on Switches")

        ipv4 = packet.find("ipv4")


        # Hard-coded firewall rules
        if ipv4 is None:
            accept()  # Non-IPv4 packet (e.g., ARP)
        elif packet.find('icmp'):                       #For Ping Attack on DNS Server Security Addition #10A
            if ipv4.dstip == '10.0.100.4':            #For Ping Attack on DNS Server Security Addition #10A
                drop()  # ICMP packet                   #For Ping Attack on DNS Server Security Addition #10A
            else:
                accept()
        elif packet.find('tcp'):
            if ipv4.srcip == ['10.0.1.2' or '10.0.2.3' or '10.0.3.2'] and ipv4.dstip == '10.0.100.3':
                accept()  # Rule #2: Web Traffic
            elif ipv4.srcip == ['10.0.1.2' or '10.0.1.4'] and ipv4.dstip == '10.0.100.2':
                accept()  # Rule #3: Faculty Access
            elif ipv4.srcip == ['10.0.3.2' or '10.0.3.3'] and ipv4.dstip == ['10.0.1.2' or '10.0.1.4' or '10.0.2.3' or '10.0.2.2' or '10.0.3.2' or '10.0.3.3']:
                accept()  # Rule #4: IT Management
            #elif ipv4.srcip == ['10.0.1.3'] and ipv4.dstip == ['10.0.203.2' or '10.0.198.2']:
                #drop()  # Rule #10B: Printer Management (Printer Source) going to trustedPC or guestPC (DROP)
            #elif ipv4.srcip == ['10.0.203.2' or '10.0.198.2'] and ipv4.dstip == ['10.0.1.3']:
               #drop()  # Rule #10B: Printer Management (Printer Destination) coming from trustedPC or guestPC (DROP)
            else:
                drop()  # Default Deny for TCP traffic
        elif packet.find('udp'):
            if ipv4.srcip == ['10.0.1.2' or '10.0.1.4'] and ipv4.dstip == '10.0.100.4':
                accept()  # Rule #5: DNS Traffic
            else:
                drop()  # Default Deny for UDP traffic
        else:
            drop()  # Default Deny for other IPv4 packets

    def _handle_PacketIn(self, event):
        """
        Handles packet in messages from the switch.
        """

        packet = event.parsed # This is the parsed packet data.
        if not packet.parsed:
            log.warning("Ignoring incomplete packet")
            return

        packet_in = event.ofp # The actual ofp_packet_in message.
        self.do_firewall(packet, packet_in)

def launch():
    """
    Starts the components
    """
    def start_switch(event):
        log.debug("Controlling %s" % (event.connection,))
        Firewall(event.connection)
    core.openflow.addListenerByName("ConnectionUp", start_switch)
