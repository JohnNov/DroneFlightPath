#!/usr/bin/php

<?php echo "Fetching Image";

function fetchTheImage(){

 #$genURL = 'http://192.168.0.101/html/media/'; Dan's pi
 $genURL = 'http://192.168.0.106/media/'; #Teresa's pi

 $specificURL = $genURL.$argv[1];
	
 echo $specificURL;	# Evaluates to http://192.168.0.106/media/'

 var_dump($argv); 
 $output = $argv[1]; 	#This is coming up as null
echo "OUTPUT ISSSSSS ";
 echo $output;

 file_put_contents($output, file_get_contents($specificURL));

}

fetchTheImage();

if (fetchTheImage() === FALSE)
	echo "Failed";

else
	echo "Success!";

?>
