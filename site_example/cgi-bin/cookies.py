#!/usr/local/bin/python3
# -*- coding: utf-8 -*-
import time
# import cv2
# import os

try:
    txt = open("site_example/cgi-bin/cookies.txt", "w")
    time = time.asctime(time.localtime())

    txt.write("200 OK\r\n")
    txt.write("Content-type: text/html\r\n")
    txt.write("Set-cookie: lastvisit=")
    txt.write(time)
    txt.write("; name=Somebody; path=../cookie_tmp/; Secure; HttpOnly\r\n")
    txt.write("Done cookies!\r\n\r\n")
    txt.close()
except OSError:
    print("NOT OPEN FILE TXT!")

html_template = """
        <html>
        <head>
        <title> Cookies done </title>
        </head>
        <body>
        <h2> You've done cookies! </h2>
        <div>
        <a href=""><img src="../cook.jpg" width="300" height="250" alt="Место для котика"/></a>
	    </div>
        
        <p>To check in google chrome - chrome://settings/siteData </p>
        
        </body>
        </html>
        """
try:
    #!!! НЕЛЬЗЯ СОЗДАТЬ ФАЙЛ cookies.html
    with open('site_example/cgi-bin/cookies.html', 'wt') as file:
        print(html_template, file=file)

    file.close()
except OSError:
    print("NOT OPEN FILE HTML!")