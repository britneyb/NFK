<?php 

 if (isset($_POST['shuttDown_btn']))
{	$test=$_SERVER['HTTP_HOST'];
	echo $test;
}
	
?>



<!DOCTYPE html>
<html>
<head>
	<title>stang av Test</title>
</head>


<form method="post" action="testIP.php">
<body>
<input type="submit" value="Get Ip " name="shuttDown_btn"></input>



</body>

 
</form>
</html>





