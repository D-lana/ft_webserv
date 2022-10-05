#!/usr/local/bin/python3

import os
import random
import resource

def getRandomFile(path):
  """
  Returns a random filename, chosen among the files of the given path.
  """
#   path = "../../resources/graphics"
  files = os.listdir(path)
  index = random.randrange(0, len(files))
  return files[index]

try:
    f = getRandomFile("../../resources/graphics")
except OSError:
    print("NOT OPEN FILE!")



# 	html_template1 = """<html>
#         <head>
#         <title>Cookies done</title>
#         </head>
#         <body>
#         <h2>You've done cookies!</h2>

#         <div>
#         <a href=""><img src="cook.jpg" width="300" height="250" alt="Место для котика"/></a>
# 	    </div>
        
#         <p>To check in google chrome - chrome://settings/siteData </p>
        
#         </body>
#         </html>
#         """

# 	html_template2 = getRandomFile("../../resources/graphics")
# 	html_template3 = """</body>
#         </html>
#         """
# try:
#     #!!! НЕЛЬЗЯ СОЗДАТЬ ФАЙЛ cookies.html
#     with open('site_example/cgi-bin/randomizer.html', 'wt') as file:
#         print(html_template1, file=file)
# 		print(html_template2, file=file)
# 		print(html_template3, file=file)

#     file.close()