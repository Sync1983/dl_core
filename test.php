<?php

include "rows.php";

$b = [
    19 => [
      'text'  => '',
      'id'    => 18
    ],
    18 => [
      'text'  => 'ad',
      'id'    => 18
    ],
    20 => [
      'text'  => 'abc',
      'id'    => 18
    ],
    21 => [
      'text'  => 'abcd',
      'id'    => 18
    ],
    15 => [
      'text'  => 'abcdf',
      'id'    =>  15,
      'distance' => 0
    ]
  ];
$b = $rows;
$text = 'ПОРШЕН';
echo "Rows: " . count($rows) ."\r\n";
$time = microtime(true);
$result =  dl_array($b,$text,0,4);
$result =  dl_array($b,$text,3,4);
$answer =  dl_filter($b, $result, 5);
/*usort($b,function($A,$B){
  return $A['distance'] > $B['distance'];
});*/
$time = microtime(true) - $time;
echo "Time is $time ms  Min distance = $result \r\n";
var_dump($answer);
