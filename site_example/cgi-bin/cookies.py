#!/usr/local/bin/python3
import time

time = time.asctime(time.localtime())
print("Set-cookie: lastvisit=' + time + "\r"; name=Somebody"; path=/cgi-bin/; httponly)

print("Content-type: text/html\n")
print("Done cookies!")