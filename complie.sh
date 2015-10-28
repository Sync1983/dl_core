#!/bin/bash

echo "Make install ... \r\n"
make && make install

echo "Chmod"
chmod -R 777 *
chown -R sync1983:sync1983 *

echo "Test"
php test.php
