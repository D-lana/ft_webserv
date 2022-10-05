#!/bin/bash
rm -f site_example/cgi-bin/date.txt;
echo "200 OK\r\nContent-type: text/plain\r\n" > site_example/cgi-bin/date.txt;
ncal >> site_example/cgi-bin/date.txt;
echo "\r\n" >> site_example/cgi-bin/date.txt;

rm -f site_example/cgi-bin/date.html;
echo '<center><br />'  >> 		site_example/cgi-bin/date.html;
echo '<pre>' >> 		site_example/cgi-bin/date.html;
ncal >> 		site_example/cgi-bin/date.html;
echo '</pre>' >> 		site_example/cgi-bin/date.html;
echo '</center>' >> 		site_example/cgi-bin/date.html;