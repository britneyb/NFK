<?php
class MyDB extends SQLite3
{
   function __construct($stringDB)
   {
      $this->open($stringDB);
   }
}




$type = $_REQUEST["type"];

if($type == "checkName"){                 //sqlfunctions.php?type=checkName&name="namnet"
   checkName();
}
else if($type == "saveSchedule"){         //sqlfunctions.php?type=saveSchedule&name="namnet"&array="arrayen"
   saveSchedule();
}
else if ($type == "getSchedule") {        //sqlfunctions.php?type=getSchedule&name="namnet"
   getSchedule();
}
else if ($type == "getList") {            //sqlfunctions.php?type=getList
   getList();
}

function checkName(){
   $name = $_REQUEST["name"];
   $db = new MyDB("sqltemptime.db");
   if(!$db){
      echo $db->lastErrorMsg();
   }
   $sql = <<<EOF
      SELECT name FROM mashschedule WHERE name="$name";
EOF;
   $ret = $db->query($sql);
   $row = $ret->fetchArray(SQLITE3_ASSOC);
   if($row['name']){
      echo "fail";
   } else {
      echo "success";
   }
   $db->close();
}

function saveSchedule(){
   $array = json_decode($_REQUEST["array"]);
   $name = $_REQUEST["name"];
   if(!empty($array))
   {
      $temp = "";
      $time = "";
      for ($i = 0; $i < count($array); $i++)
      {
         $temp .= "/".$array[$i][0];
         $time .= "/".$array[$i][1];
      }
      writeData($name, $temp, $time);
   }
}

function getSchedule(){

}

function getList(){
   $db = new MyDB("sqltemptime.db");
   if(!$db){
      echo $db->lastErrorMsg();
   }
   $sql = <<<EOF
      SELECT name FROM mashschedule;
EOF;
   $ret = $db->query($sql);
   while($row=$ret->fetchArray()){
      print($row[0]."/");
   }
   $db->close();
}


function writeData($name, $temp, $time)
{
   $db = new MyDB("sqltemptime.db");

   if(!$db){
      echo $db->lastErrorMsg();
   }
   $sql = <<<EOF
      INSERT INTO mashschedule (name,temp,time)
      VALUES ('$name', '$temp', '$time');
EOF;

   $ret = $db->exec($sql);
   if(!$ret){
      echo $db->lastErrorMsg();
   } else {
      echo "Data insertet\n";
   }
   $db->close();
}

//function delete, readData, checkName
