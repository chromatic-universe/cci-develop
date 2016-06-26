from scapy.all import *


# ------------------------------------------------------------------------------------
if __name__ == '__main__' :

    ip = IP()
    ip.dst = '192.168.0.135'

    ping = ICMP()
    ping_request = ( ip/ping )

    ping_reply = sr1( ping_request , timeout = 1 )

