#!/usr/bin/php

<?php echo "Fetching Longitude";
 $file = 'long.txt';
 $url = 'http://192.168.9.106./html/LAT.php';	#This is Teresa's pi 
 #$url = 'http://192.168.0.101/html/LONG.php';	#This is Dan's pi
 $content = file_get_contents($url);
 file_put_contents($file, $content);?>
