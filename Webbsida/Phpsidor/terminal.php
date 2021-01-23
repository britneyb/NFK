<?php

      $fp = fopen("/dev/ttyACM1", "w");

      //sleep(1);
	fwrite($fp,1);

      $data = fgets($fp);

      print $data;
print " test";
      fclose($fp);

?>