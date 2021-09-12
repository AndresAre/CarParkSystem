<?php
  header('Access-Control-Allow-Origin: *');

        //mysqli_connect(host,username,password,dbname,port,socket);
  $link = mysqli_connect("localhost","root","", "parking");
  
  if(mysqli_connect_error()) {
    die("There was an error");
  }

  $cmd = $_GET['cmd'];

  $query = "UPDATE parkinglots SET cmd=" . "'". $cmd . "'";
  
  if($result = mysqli_query($link, $query)) {  
    echo "success";
  } else {
    echo "Error updating record: " . $link->error;
  }

  $link->close();
?>