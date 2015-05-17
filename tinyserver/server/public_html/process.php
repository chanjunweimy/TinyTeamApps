<?php
error_reporting(E_ALL);

$json_file = file_get_contents('php://input');
$jfo = json_decode($json_file, true);

if ($json_file === NULL) {
	echo "FAIL!\n";
	die;
}

$str = file_get_contents('../busRequests.json');
$json = json_decode($str, true); // decode the JSON into an associative array

if ($jfo['role'] === 'driver') {
	echo $json;
} else if ($jfo['role'] === 'customer') {
  foreach ($json['busRequests'] as $key => $value) {
	echo $key . '<br/>';
	echo $value;
  }
}
?> 
