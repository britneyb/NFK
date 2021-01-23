<?php
$serialDevice = fopen("/dev/ttyACM0","r");
if(!$serialDevice){
	$serialDevice = fopen("/dev/ttyACM1","r");
	if(!$serialDevice){
		$serialDevice = fopen("/dev/ttyACM2","r");	//Ansluter till arduinon och testar 3 olika id.
		if(!$serialDevice){
			echo "Can't find /dev/ttyACM2";
		}
	}
}
$response = fread($serialDevice, 48);						//Lyssnar på porten eftermeddelande från arduinon.
preg_match("/\w+\s+(\w+)\s*\w+\s/", $response, $first);		//Använder regex för att bara skriva ut meddelandet en gång.
echo $first[1];
fclose($serialDevice);