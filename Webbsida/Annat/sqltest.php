<?php
   class MyDB extends SQLite3
   {
      function __construct($stringDB)
      {
         $this->open($stringDB);
      }
   }

   $db = new MyDB("test.db");

   if(!$db){
      echo $db->lastErrorMsg();
   } else {
      echo "Opened database successfully\n";
   }

$temp = $REQUEST["temp"];

print "\r\n test \r\n test2\n";

   $sql =<<<EOF
      CREATE TABLE COMPANY
      (ID INT PRIMARY KEY     NOT NULL,
      NAME           TEXT    NOT NULL,
      AGE            INT     NOT NULL,
      ADDRESS        CHAR(50),
      SALARY         REAL);
EOF;

   $ret = $db->exec($sql);
   if(!$ret){
      echo $db->lastErrorMsg();
   } else {
      echo "Table created successfully\n";
   }
   $db->close();
?>








$sql =<<<EOF
      INSERT INTO mashschedule (temp,time)
      VALUES (1, 'Paul', 32, 'California', 20000.00 );

EOF;

   $ret = $db->exec($sql);
   if(!$ret){
      echo $db->lastErrorMsg();
   } else {
      echo "Records created successfully\n";
   }
   $db->close();
?>