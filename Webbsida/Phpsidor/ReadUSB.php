<html>
<head>
</head>
<body>
<?php

	$module = 'win_serial';

	if (extension_loaded($module)) {
		$str = "Module loaded";
	} else {
		$str = "Module $module is not compiled into PHP";
		die("Module $module is not compiled into PHP");
	}
	echo "$str<br>";

	$functions = get_extension_funcs($module);
	echo "Functions available in the $module extension:<br>\n";
	foreach($functions as $func) {
		echo $func."<br>";
	}
	echo "<br>";

	echo "Version ".ser_version();
	echo "<br>";

	ser_open( "COM6", 9600, 8, "None", "1", "None" );

	echo "<br>";
	if (ser_isopen()) 
		echo "Port is open!.";

	echo "<br>";
	echo "Write light to serial port";
	ser_write("light");

	echo "<br>";
	$str = ser_read();
	echo "Received: $str";

	echo "<br>";
	echo "flush serial port";
	ser_flush(true,true);

	echo "<br>";
	ser_close();
	echo "Serial Port Closed";

	echo "<br>";

?>
</body>
</html>
