#!/usr/local/bin/python3 

# -*- coding: utf-8 -*-
import time
import pathlib 
# import cv2
import os

try:
    if os.path.isfile('site_example/cgi-bin/cookies.html'): 
        os.remove('site_example/cgi-bin/cookies.html')
    f = open("site_example/cgi-bin/cookies.html", "w")
except OSError:
    print("NOT OPEN FILE!")

try:
    txt = open("site_example/cgi-bin/cookies.txt", "w")
except OSError:
    print("NOT OPEN FILE!")


time = time.asctime(time.localtime())

txt.write("200 OK\r\n")
txt.write("Content-type: text/html\r\n")
txt.write("Set-cookie: lastvisit=")
txt.write(time)
txt.write("; name=Somebody; path=../cookie_tmp/; Secure; HttpOnly\r\n")
txt.write("Done cookies!\r\n\r\n")
txt.close()


html_template = """
        <html>
        <head>
        <title> Cookies done </title>
        </head>
        <body>
        <center>
        <h2> You've done cookies! </h2>
        <div>
        <a href=""><img src="../cook.jpg" width="300" height="250" alt="Место для котика"/></a>
	    </div>
        
        <p>To check in google chrome - chrome://settings/siteData </p>
        </center>
        </body>
        </html>
        """

# writing the code into the file
f.write(html_template)

# close the file
f.close()