#!/usr/bin/php

<?php echo "Fetching GPS"; ?>

<?php #$genURL = 'http://192.168.0.101/html/media/'; #This is Dans pi ?>
<?php #$genURL = 'http://192.168.0.106./media/';	#This is Teresa's pi ?>
<?php $genURL = fopen('http://192.168.0.200/gps_all.txt','r') or die("Can't open");?>

<?php #echo fread($genURL, filesize("http://192.168.0.200/gps_all.txt"));?>

<?php 
	if(!copy("http://192.168.0.200/gps_all.txt", "GPS_Information.txt")){
		echo "Failed to copy";}
;?>


<?php $myFile = fopen("GPS_Info.txt", "w") or die("Unable to open file!");?>

