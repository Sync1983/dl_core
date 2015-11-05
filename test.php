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
$text = 'КЛАПОНЫ';
$time = microtime(true);
$result =  dl_array($b,$text,3);
usort($b,function($A,$B){
  return $A['distance'] > $B['distance'];
});
$time = microtime(true) - $time;
echo "Time is $time ms \r\n";
$answer = array_splice($b,0,10);
var_dump($answer);
