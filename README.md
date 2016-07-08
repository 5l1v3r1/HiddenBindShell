###Hidden Bind Shell: Keep your shellcode hidden from scans 


Credits : http://www.shelliscoming.com/2014/03/hidden-bind-shell-keep-your-shellcode.html


##Respond to our specific IP address

![alt tag](http://i.hizliresim.com/r9arLP.jpg)


##Respond to others


![alt tag](http://i.hizliresim.com/7vpzml.jpg)


---


The idea is that our shellcode responds with a RST to any connection attempt coming from an IP different than the one we set in the shellcode (defined by the variable AHOST, allowed Host). This is a good way to keep the shellcode hidden from scanning tools since our socket will appear as "CLOSED" (in Windows XP you won't even see anything locally from the netstat output).

To achieve this without implementing raw sockets I have used the setsockopt API setting the SO_CONDITIONAL_ACCEPT option to true. With this configuration whenever someone tries to establish a new connection, the TCP stack will not respond with a SYN-ACK (as it does by default) but its management is delegated to the shellcode itself which will decide, based on the source IP address, whether accept or not the connection. This condition can be defined by the conditional accept callback registered with WSAAccep. 
