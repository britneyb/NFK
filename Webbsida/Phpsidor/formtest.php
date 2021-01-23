<html>
<body>

<input type="button" name="select" value="select" onclick="select()" />


<?php
$serialDevice = fopen("/dev/ttyACM2","w");
sleep(2);
fwrite($serialDevice, "Hello world4");

if($_GET){
    if(isset($_GET['select'])){
        select();
    }
}
?>
<?php
    function select()
    {
   echo "The select function is called.";
	fwrite($serialDevice, "Hello world3");
    	sleep(2);
	fclose($serialDevice);
    }

?>.