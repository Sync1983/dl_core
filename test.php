<?php
$b = [
    15 => [
      'text'  => 'abcdf',
      'id'    =>  15,
      'distance' => 55
    ],
    18 => [
      'text'  => 'b',
      'id'    => 18
    ]
  ];

$result =  dl_array($b,'adf',0);
var_dump($result);
var_dump($b);
