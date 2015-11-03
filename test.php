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
$text = 'AНОМЕР';
$text = 'abcdf';
$result =  dl_array($b,$text,0);
var_dump($b);
