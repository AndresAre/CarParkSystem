<?php
  header('Access-Control-Allow-Origin: *');

        //mysqli_connect(host,username,password,dbname,port,socket);
  //$link = mysqli_connect("localhost","myuser","mypassword", "parking2");
  $link = mysqli_connect("localhost","root","", "parking");
  
  if(mysqli_connect_error()) {
    die("There was an error");
  }

  $query = "SELECT cmd FROM parkinglots";
  $rows = array();

  if($result = mysqli_query($link, $query)) {
    while($r = mysqli_fetch_row($result)) {
      echo $r[0];
    }
  }

  $link->close();
?>