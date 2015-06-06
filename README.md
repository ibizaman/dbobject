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


SQL Example
-----------

Build a fairly complex SELECT query:
```c++
auto query = SQL::Query::select({"colA"_c, "colB"_c, "colC"_c})
    .limit(10)
    .from("MyTable")
    .orderBy({
            "colA"_c,
            "colB"_c | SQL::Direction::DESC,
            "colC"_c | SQL::Direction::ASC
        })
    .where(("colA"_c == "A"_l && "colB"_c == "B"_l) || "colC"_c == "C"_l)

assert(query.getSQL() == "SELECT * FROM `MyTable`"
                         "WHERE `colA` = 'A' AND `colB` = 'B' OR `colC` = 'C'"
                         "ORDER BY `colA`, `colB` DESC, `colC`"
                         "LIMIT 10"
```

As you can see, the order of calls has no importance and the query is
always well-formed.


Tuple Example
-------------

Store a vector of tuples:
```c++
std::vector<std::tuple<bool, int, std::string>> to_store{
    std::make_tuple(true, 365, "hello"),
    std::make_tuple(false, 320, "hi"),
    std::make_tuple(false, 250, "howdy")
};

db.store("MyTable", to_store);
// you can also specify explicitely the column names
db.store("MyTable", {"a", "b", "c"}, to_store);
```

Store a tuple of vectors:
```c++
std::tuple<std::vector<bool>, std::vector<int>, std::vector<std::string>> to_store{
    {true, false, false},
    {365, 320, 250},
    {"hello", "hi", "howdy"}
};

db.store("MyTable", to_store);
```


ORM Example
-----------

Here we'll see how to retrieve and store a class in the database. This
example requires a bit more preparation.

Let's say we have the following class with two private attributes and
associated setters and getters and one public attribute:
```c++
class MyObject
{
public:
    void setBool(bool b) {_b = b;}
    int getBool() const {return _b;}
    void setInt(int i) {_i = i;}
    int getInt() const {return _i;}

    std::string s;

private:
    bool _b;
    int _i;
};
```

You then need to specialize the `Object::Properties` struct to inform
dbobject how to fill in and extract values from the class:
```c++
template<> struct Object::Properties<MyObject>
{
    typedef std::tuple<bool, int, std::string> tuple;
    static const SQL::List<SQL::ColumnName> fields;
    static const SQL::TableName table;

    static Ptr<MyObject>::type fromTuple(const tuple& t)
    {
        return mapOnSetters<MyObject>(
                t,
                &MyObject::setBool,
                &MyObject::setInt,
                &MyObject::s
            );
    }

    static tuple toTuple(const Ptr<MyObject>::type& o)
    {
        return mapOnGetters<tuple>(
                o,
                &MyObject::getBool,
                &MyObject::getInt,
                &MyObject::s
            );
    }
};

const SQL::List<SQL::ColumnName> Object::Properties<MyObject>::fields = {
    "bool", "int", "string"
};
const SQL::TableName Object::Properties<MyObject>::table("MyTable");
```

We can retrieve one object with a WHERE clause:
```c++
auto o = db->getOne<DummyObject>("string"_c == "hello"_l);
```

We can also retrieve a list of objects:
```c++
auto list = db->getList<DummyObject>();
```

We can store an object:
```c++
Ptr<DummyObject>::type o(new DummyObject);
o->setBool(false);
o->setInt(3);
o->s = "hello";

db.storeOne<MyObject>(o);
```

We can also store multiple objects at once:
```c++
Ptr<MyObject>::type o1(new MyObject);
o1->setBool(true);
o1->setInt(3);
o1->s = "hello";

Ptr<MyObject>::type o2(new MyObject);
o2->setBool(false);
o2->setInt(4);
o2->s = "hi";

List<MyObject>::type list;
list.push_back(o1);
list.push_back(o2);

db->storeList<MyObject>(list);
```

