<?php


$b = file_get_contents("./a.png");

echo base64_encode($b);

$a = file_get_contents("./base64.txt");

file_put_contents("./phpa.png", base64_decode($a));
?>
