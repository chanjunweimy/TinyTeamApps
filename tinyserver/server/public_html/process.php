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
	echo json_encode($json);
} else if ($jfo['role'] === 'customer') {
  foreach ($json['busRequests'] as $key => $value) {
	if ($value['busStopNumber'] === $jfo['busStopNumber']
			&& $value['busServiceNumber'] === $jfo['bus']) {
		$value['numberOfRequest'] += 1;
	}
  }
}

foreach ($json['busRequests'] as $key => $value) {
	if (!is_array($value)) {
		echo $key . '=>' . $value . '<br/>';
	} else {
		foreach ($value as $key => $val) {
			echo $key . '=>' . $val . '<br/>';
		}
	}
}

$fp = fopen('../busRequests.json', 'w');
fwrite($fp, json_encode($json));
fclose($fp);
?> 
