#!/usr/bin/php

<?php echo "Fetching Latitude"; ?>

<?php $url = 'http://192.168.0.106/positiveLat/';	#This is Teresa's pi ?>
<?php #$url = 'http://192.168.0.101/html/LAT.php';	#This is Dan's pi?>


<?php var_dump($argv); ?>
<?php $output = $argv[1]; ?>

<?php echo '$output: ';?>	
<?php echo $output;	?>
<?php echo '  ';?>	

<?php $trueURL = $url.$argv[1]; ?>

<?php echo '$trueURL: ';?>	
<?php echo $trueURL;	?>
<?php echo '  ';?>		

<?php $latName = 'lat';	#This needs to be an argument passed for number.  ?>

<?php $newFile = $argv[1]; ?>

<?php echo '$newFile is ';?>
<?php echo $newFile;?>

<?php $newFile = substr($newFile, 0, -4);		#Remove the '.php'?>	
<?php $newFile = $newFile.'.txt'			#Add the '.txt	?>			

<?php $direc = '/positiveLat/'.$newFile?>
<?php echo '$newFile is ';?>
<?php echo $newFile;?>

<?php $content = file_get_contents($trueURL); ?>

<?php file_put_contents($newFile, $content);?>








