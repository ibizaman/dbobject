dbobject
========

dbobject is a mix between an Object Relational Mapper and SQL writer
helper, for C++. The ORM part maps C++ classes to tables in a SQL
database:

Database | C++
--- | ---
table | class
column | class' attribute (or setter/getter method)
row | class instance

The SQL writer helper allows you to write and execute SQL queries in
native C++ which is syntactically verified at compile-time. Input and
output parameters are mapped to tuple of vectors or vector of tuples,
depending on your need.

The main advantage of using dbobject to create queries is to avoid most
of syntax mistakes: forgetting quotes (') and backticks (\`) around
values and SQL names, mixing the order of SQL clauses, etc. But also,
this allows you to build queries at different parts in your code, e.g.
specifying first the WHERE clause and later on the table name.

Both part of dbobject are based on variadic templates, available only in
the latest C++ compilers' versions. This means everything is done at
compile time without the need for macros. Also, dbobject is
non-intrusive: no need to modify the classes themselves. See the
examples for more details.

dbobject supports only MySQL as a backend for now.


Disclaimer
----------

*In its current state, dbobject is not ready for production.* I use it
for my own projects and it works well for my use cases but it is not
battle-tested.


Why Yet Another ORM For C++ ?
-----------------------------

No other ORM fitted my need: either they are intrusive, or they rely on
macros or I didn't like their API. But most of all, I wanted to be able
to write complex SQL queries, independently of the ORM part, and map the
results to vector of tuples or the inverse.

Also, I wanted the library to rely only on C++ compile-time features
like variadic templates and it was a good occasion to learn recent C++
features.

To be clear, I am not saying that the libraries I compared are not good,
quite the contrary. They are all well fitted for production use. Here
are the list of ORMs I compared:

* [ODB](http://www.codesynthesis.com/products/odb/)
* [YB.ORM](https://github.com/vnaydionov/yb-orm)
* [StactiveRecord](http://findingscience.com/StactiveRecord/)
* [hiberlite](https://github.com/paulftw/hiberlite)
* [SOCI](http://soci.sourceforge.net/)
* [QxOrm](http://www.qxorm.com/qxorm_fr/quick_sample.html)


Compilation
-----------
First install the required dependencies:

* [cmake](http://www.cmake.org/)
* [boost](http://www.boost.org/)
* [mysql-connector-c++](https://dev.mysql.com/downloads/connector/cpp/)

Then, build the project:
```sh
cmake <source-directory>
make
```

Out-of-source builds are preferred with CMake, but not required.


Run tests
---------

Tests use [CTest](http://www.cmake.org/Wiki/CMake/Testing_With_CTest).
Launching all the tests is as simple as:

```sh
make test
```


Contributing
------------
Any contribution is very welcomed! Just post an issue or make a pull
request.

For ease of use, there is a Vagrantfile so you can run the following
commands and be set up automatically:

```sh
vagrant up
vagrant ssh
cd build
make
# Run the tests to make sure everything went okay
make test
```

See the [vagrant](https://www.vagrantup.com/)
website for more information.


ORM Example
-----------

