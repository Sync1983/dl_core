#!/bin/bash

echo "Make install ... \r\n"
make && make install

echo "Test"
php test.php
