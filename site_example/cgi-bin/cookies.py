#!/usr/local/bin/python3
import time

try:
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
txt.write("Set-cookie: lastvisit=' + time + \r; name=Somebody; path=/cgi-bin/; httponly\r\n")
txt.write("Done cookies!\r\n\r\n")

txt.close()

html_template = """<html>
<head>
<title>Title</title>
</head>
<body>
<h2>Welcome To TEST!</h2>
  
<p>EEEEEEE!!!!</p>
  
</body>
</html>
"""

# writing the code into the file
f.write(html_template)

# close the file
f.close()