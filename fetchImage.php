#!/usr/bin/php

<?php echo "Fetching Image"; ?>

<?php #http://stackoverflow.com/questions/2259857/how-to-do-an-if-statement-on-a-function-in-php ?>


<?php #$genURL = 'http://192.168.0.101/html/media/'; #This is Dans pi ?>
<?php $genURL = 'http://192.168.0.106./media/';	#This is Teresa's pi ?>


<?php $specificURL = $genURL.$argv[1]; ?>
<?php echo "specificURL is: ";?>
<?php echo $specificURL;?>


<?php var_dump($argv); ?>
<?php $output = $argv[1]; ?>

<?php echo "Output is: ";?>
<?php echo $output ;?>


<?php $myFile = fopen("booleanFile.txt", "w") or die("Unable to open file!");?>


<?php if(file_put_contents($output, file_get_contents($specificURL)))

	$txt = "True";

      else
	$txt = "False";
?>

<?php	fwrite($myFile, $txt);
	fclose($myFile);
?>










