<?php
error_reporting(E_ALL);

$json_file = file_get_contents('php://input');
$jfo = json_decode($json_file, true);

if ($json_file === NULL) {
	echo "FAIL!\n";
	die;
}

if ($jfo['role'] === 'driver') {
	
} else if ($jfo['role'] === 'customer') {
	
}
?> 
