#!/usr/bin/php

<?php echo "Fetching Image"; ?>

 <?php $genURL = 'http://192.168.0.101/html/media/'; This is Dans pi ?>
<?php#$genURL = 'http://192.168.9.106./html/';	#This is Teresa's pi ?>

<?php $specificURL = $genURL.$argv[1]; ?>
<?php echo $specificURL	?>

<?php var_dump($argv); ?>
<?php $output = $argv[1]; ?>
<?php echo $output?>

<?php file_put_contents($output, file_get_contents($specificURL));?>




