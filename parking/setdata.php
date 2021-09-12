<?php
  header('Access-Control-Allow-Origin: *');

        //mysqli_connect(host,username,password,dbname,port,socket);
  $link = mysqli_connect("localhost","root","", "parking");
  
  if(mysqli_connect_error()) {
    die("There was an error");
  }

  $a = $_GET['a'];
  $b = $_GET['b'];
  $c = $_GET['c'];
  $d = $_GET['d'];
  $e = $_GET['e'];
  $f = $_GET['f'];
  $g = $_GET['g'];
  $h = $_GET['h'];

  $query = "UPDATE parkinglots SET a=" . "'". $a . "'" . ",".
  "b=". "'". $b . "'" . ",".
  "c=". "'". $c . "'" . ",".
  "d=". "'". $d . "'" . ",".
  "e=". "'". $e . "'" . ",".
  "f=". "'". $f . "'" . ",".
  "g=". "'". $g . "'" . ",".
  "h=". "'". $h . "'";
  
  if($result = mysqli_query($link, $query)) {  
    echo "success";
  } else {
    echo "Error updating record: " . $link->error;
  }

  $link->close();
?>