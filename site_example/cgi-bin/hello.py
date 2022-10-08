#!/usr/local/bin/python3
try:
    f = open("site_example/cgi-bin/hello.html", "w")
except OSError:
    print("NOT OPEN FILE!")

try:
    txt_1 = open("site_example/cgi-bin/hello.txt", "w")
except OSError:
    print("NOT OPEN FILE!")

txt_1.write(" 200 OK\r\n")
txt_1.write("Content-type: text/html\r\n")
txt_1.write("\r\n\r\n")
txt_1.close()

# the html code which will go in the file GFG.html
html_template = """<html>
<head>
<title>Hello cgi</title>
</head>
<body>
<h2>Welcome to hello!</h2>
  
<p>Default code has been loaded into the Editor.</p>
  
</body>
</html>
"""
  
# writing the code into the file
f.write(html_template)

# close the file
f.close()