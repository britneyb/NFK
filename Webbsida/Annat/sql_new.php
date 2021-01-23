
<?php

class MyDB extends SQLite3
{
   function __construct($stringDB)
   {
      $this->open($stringDB);
   }
}


getSchedule();

function getSchedule(){
   $name = $_REQUEST["name"];
   $db = new MyDB("sqltemptime.db");
   if(!$db){
      echo $db->lastErrorMsg();
   }
   $sql = <<<EOF
      SELECT * FROM mashschedule WHERE name = "$name";
EOF;
   $ret = $db->query($sql);
   
   $row=$ret->fetchArray();
   
   for ($i = 0; $i < 3; $i++) {
      print($row[$i]." ");
   }
   $db->close();
}

?>