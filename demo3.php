<?php
$serialDevice = fopen("/dev/ttyACM0","r");
if(!$serialDevice){
	//echo "Can't find /dev/ttyACM0";
	$serialDevice = fopen("/dev/ttyACM1","r");
	if(!$serialDevice){
		//echo "Can't find /dev/ttyACM1";
		$serialDevice = fopen("/dev/ttyACM2","r");
		if(!$serialDevice){
			//echo "Can't find /dev/ttyACM2";
		}
	}
}
$response = fread($serialDevice, 48);
preg_match("/\w+\s+(\w+)\s*\w+\s/", $response, $first);
echo $first[1];

fclose($serialDevice);