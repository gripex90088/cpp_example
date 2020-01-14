<?php 

$a = '0a';
echo str_pad(decbin(ord(hex2bin($a))), 8, 0, STR_PAD_LEFT) . "\n";

?>