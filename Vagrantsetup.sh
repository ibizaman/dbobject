#!/bin/bash

sudo pacman -Syu --noconfirm --needed cmake clang boost mariadb mysql-connector-c++

sudo mysql_install_db --user=mysql --basedir=/usr --datadir=/var/lib/mysql

sudo systemctl start mysqld
sudo systemctl enable mysqld

mysqladmin -u root password root

echo "CREATE DATABASE dbobject_test;" | mysql -uroot -proot

cp /vagrant/test/parameters.conf.sample /vagrant/test/parameters.conf

mkdir build
cd build
cmake /vagrant

