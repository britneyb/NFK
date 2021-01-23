
<?php
$btn_click=isset($_POST['btn_get_txt']) ? $_POST['btn_get_txt'] : '';
$msg=isset($_POST['the_txt']) ? $_POST['the_txt'] : '';

if($btn_click){

$serialDevice = fopen("/dev/ttyACM0","r");

echo "funk";
$response=fread($serialDevice,48);

echo $response;

}
$serialDevice = fopen("/dev/ttyACM0","w");
fwrite($serialDevice,$msg);

fclose($serialDevice);

?>

<html>
<body>
<form method="POST" action="Demo.php">
<input type="text"  name="the_txt"><br>
<input type="submit" value="Send" name="btn_submit" > 
<input type="submit" value="Get Text" name="btn_get_txt" > 



<form/>

<html/>
<body/>

