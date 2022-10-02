#!/usr/local/bin/python3
try:
    f = open("site_example/cgi-bin/hello.html", "w")
except OSError:
    print("NOT OPEN FILE!")

# the html code which will go in the file GFG.html
html_template = """<html>
<head>
<title>Title</title>
</head>
<body>
<h2>Welcome To TEST!</h2>
  
<p>Default code has been loaded into the Editor.</p>
  
</body>
</html>
"""
  
# writing the code into the file
f.write(html_template)

# close the file
f.close()