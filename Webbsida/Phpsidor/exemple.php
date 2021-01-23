<?php


$verz="1.0";
$comPort = "/dev/ttyACM0"; /*change to correct com port */

if (isset($_POST["rcmd"])) {
$rcmd = $_POST["rcmd"];
switch ($rcmd) {
     case Stop:
        $fp =fopen($comPort, "w");
  fwrite($fp, 1); /* this is the number that it will write */
  fclose($fp);
  break;
     case Slow:
        $fp =fopen($comPort, "w");
  fwrite($fp, 2); /* this is the number that it will write */
  fclose($fp);
  break;
  case Medium:
        $fp =fopen($comPort, "w");
  fwrite($fp, 3); /* this is the number that it will write */
  fclose($fp);
  break;
  case Fast:
        $fp =fopen($comPort, "w");
  fwrite($fp, 4); /* this is the number that it will write */
  fclose($fp);
  break;
case Right:
        $fp =fopen($comPort, "w");
  fwrite($fp, 5); /* this is the number that it will write */
  fclose($fp);
  break;
case Left:
        $fp =fopen($comPort, "w");
  fwrite($fp, 6); /* this is the number that it will write */
  fclose($fp);
  break;
default:
  die('Crap, something went wrong. The page just puked.');
}

}
?>
<html>
<body>

<center><h1>Arduino from PHP Example</h1><b>Version <?php echo $verz; ?></b></center>

<form method="post" action="<?php echo $PHP_SELF;?>">
&nbsp&nbsp&nbsp&nbsp
<input type="submit" value="Left" name="rcmd">
&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp
<input type="submit" value="Right" name="rcmd"><br/>
<br />
&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp
<input type="submit" value="Stop" name="rcmd"><br/>
<br />
&nbsp&nbsp&nbsp
<input type="submit" value="Slow" name="rcmd">
<input type="submit" value="Medium" name="rcmd">
<input type="submit" value="Fast" name="rcmd">
<br />
<br />
<br />
<br />
<br />
<br />

</form>
</body>
</html>