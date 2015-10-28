#!/bin/bash
clear

cur_dir=$(pwd)
php_dir=/home/php-src/usr/bin/bin/php
module="$cur_dir/modules/dl_core.so"
ini="$cur_dir/php.ini"
php_cmd="$php_dir -c $ini test.php"

echo "Make install ... \r\n"
make && make install

#echo "Update current php.ini"
#eval 'echo "extension = $module" > $ini'

echo "Test"
eval "$php_cmd"
