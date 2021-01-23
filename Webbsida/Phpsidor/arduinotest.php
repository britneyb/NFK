<html>
<body>
<form method="GET" action="arduinotest.php">
<input type="text"  name="the_txt"><br>

<button name="sendMsg" value="send" onclick="sendMsg()">send</button>

<form/>

<html/>
<body/>





<?php

function sendMsg(){
echo "test";
#fwrite($serialDevice, "Hello world3");
}

$usbDevice = "/dev/ttyACM2";

#$serialDevice = fopen("/dev/ttyACM2","w");

if(!$fp)
{
echo "error";
}

sleep(3);

#fclose($serialDevice);

?>

