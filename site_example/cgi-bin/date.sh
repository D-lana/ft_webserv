#!/bin/bash
rm -f site_example/cgi-bin/date.txt;
echo "200 OK 
Content-type: text/html

" > site_example/cgi-bin/date.txt;

rm -f site_example/cgi-bin/date.html;
echo '<center><br />'  >> 		site_example/cgi-bin/date.html;
echo '<pre>' >> 		site_example/cgi-bin/date.html;
echo "<h1> " >> 		site_example/cgi-bin/date.html;
ncal >> 		site_example/cgi-bin/date.html;
echo "</h1> " >> 		site_example/cgi-bin/date.html;

echo "<div>" >> 		site_example/cgi-bin/date.html;
echo        '<a href=""><img src="../graphics/calendar.png" width="300" height="250" alt="Место для котика"/></a>' >> 		site_example/cgi-bin/date.html;
echo    "</div>" >> 		site_example/cgi-bin/date.html;

echo "<h2> " >> 		site_example/cgi-bin/date.html;
date +%c >>     site_example/cgi-bin/date.html;
echo " </h2>" >> 		site_example/cgi-bin/date.html;
echo '</pre>' >> 		site_example/cgi-bin/date.html;
echo '</center>' >> 		site_example/cgi-bin/date.html;
