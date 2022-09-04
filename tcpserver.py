#!/usr/bin/env python3
# -*- coding: utf-8 -*-
import socket
import keyboard
import time
HOST = '0.0.0.0'
PORT = 3000
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
s.bind((HOST, PORT))
s.listen(5)

print('server start at: %s:%s' % (HOST, PORT))
print('wait for connection...')
#f=open('1.txt','w')
while True:
    conn, addr = s.accept()
    print('connected by ' + str(addr))
    state = 1
    indata = ''
    while True:
        try:
            if state==1:
                indata = conn.recv(12)
                if len(indata) == 0: # connection closed
                    conn.close()
                    print('client closed connection.') #print(indata)
                data = indata.decode().strip('\r').strip('\n')
                if data!='':
                   print('<< ' ,data)
                   #f.write('<< '+data+'\n')
                state = 0
            else:
                outdata = 'echo ' + data +"\n"
                conn.send(outdata.encode())
                state = 1
            if keyboard.is_pressed('q'):break
        except:break
        time.sleep(0.1)
    #f.close()
    break
