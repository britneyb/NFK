
<?php


$serialDevice = fopen("/dev/ttyACM1","w");

echo fgets($serialDevice);
fclose($serialDevice);

?>

<html>
<body>
<form method="POST" action="test123.php">
<input type="text"  name="the_txt"><br>
<input type="submit" value="Send" name="btn_submit" > 


<form/>

<html/>
<body/>

