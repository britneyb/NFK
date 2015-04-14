<?php
$fp = fopen("/dev/ttyACM0","w");
if(!$fp){
	//echo "Can't find /dev/ttyACM0";
	$fp = fopen("/dev/ttyACM1","w");
	if(!$fp){
		echo "Can't find /dev/ttyACM1";
	}
}
//sleep(1);
$msg=$_POST["the_txt"];
fwrite($fp,$msg);
//usleep(1000);
$response = fread($fp, 16);
echo $response;
fclose($fp);

?>

<html>
	<body>
		<form method="POST" action="test.php">
			<input type="text"  name="the_txt"><br />
			<input type="submit" value="Send" name="btn_submit" > 
		</form>
	</body>
</html>
