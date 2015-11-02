<?php
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

$result =  dl_array($b,'adf',0);
var_dump($b);
$result =  dl_array($b,'adf',1);
var_dump($b);
$result =  dl_array($b,'adf',2);
var_dump($b);
