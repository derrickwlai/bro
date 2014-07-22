.. Next: \ :ref:`Statements and Expressions <#Statements-and-Expressions>`,
.. Previous: \ :ref:`Getting Started <#Getting-Started>`, Up: \ :ref:`Top <#Top>`

Values, Types, and Constants
------------------------------

.. Next: \ :ref:`Booleans <#Booleans>`, Up: \ :ref:`Values <#Values>`

Values Overview
~~~~~~~~~~~~~~~~~~~

We begin with an overview of the types of values supported by Bro,
giving a brief description of each type and introducing the notions of
type conversion and type inference. 

.. Next: \ :ref:`Type Conversions <#Type-Conversions>`, Up: \ `Values
.. Overview <#Values-Overview>`_

.. _#Bro-Types:

Bro Types
^^^^^^^^^^^^^^^

There are 18 (XXX check this) types of values in the Bro type system:

-  `bool` for Booleans;
-  `count`, `int`, and `double` types, collectively called
   *numeric*, for arithmetic and logical operations, and comparisons;
-  `enum` for enumerated types similar to those in C;
-  `string`, character strings that can be used for comparisons and to
   index tables and sets;
-  `pattern`, regular expressions that can be used for pattern
   matching;
-  `time` and `interval`, for absolute and relative times,
   collectively termed *temporal*;
-  `port`, a TCP or UDP port number;
-  `addr`, an IP address;
-  `net`, a network prefix;
-  `record`, a collection of values (of possibly different types),
   each of which has a name;
-  `table`, an associative array, indexed by tuples of scalars and
   yielding values of a particular type;
-  `set`, a collection of tuples-of-scalars, for which a particular
   tuple's membership can be tested;
-  `file`, a disk file to write or append to;
-  `function`, a function that when called with a list of values
   (arguments) returns a value;
-  `event`, an event handler that is invoked with a list of values
   (arguments) any time an event occurs.

Every value in a Bro script has one of these types. For most types there
are ways of specifying *constants* representing values of the type. For
example, `2.71828` is a constant of type `double`, and `80/tcp` is
a constant of type `port`. The discussion of types below includes a
description of how to specify constants for the types.

Finally, even though Bro variables have *static* types, meaning that
their type is fixed, often their type is *inferred* from the value to
which they are initially assigned when the variable is declared. For
example,

::

             local a = "hi there";

fixes `a`'s type as `string`, and

::

             local b = 6;

sets `b`'s type to `count`. 

.. Previous: \ :ref:`Bro Types <#Bro-Types>`, Up: \ `Values
.. Overview <#Values-Overview>`_

.. _#Type-Conversions:

Type Conversions
^^^^^^^^^^^^^^^^^^^^^^

Some types will be automatically converted to other types as needed. For
example, a `count` value can always be used where a `double` value
is expected. The following:

::

             local a = 5;
             local b = a * .2;

creates a local variable `a` of type `count` and assigns the
`double` value `1.0` to `b`, which will also be of type
`double`. Automatic conversions are limited to converting between
*numeric* types. The rules for how types are converted are given below.

.. Next: \ :ref:`Numeric Types <#Numeric-Types>`, Previous: \ `Values
.. Overview <#Values-Overview>`_, Up: \ :ref:`Values <#Values>`

.. _#Booleans:

Booleans
~~~~~~~~~~~~

The `bool` type reflects a value with one of two possible meanings:
*true* or *false*.

.. Next: \ :ref:`Logical Operators <#Logical-Operators>`,
.. Up: \ :ref:`Booleans <#Booleans>`

.. _#Boolean-Constants:

Boolean Constants
^^^^^^^^^^^^^^^^^^^^^^^

There are two `bool` constants: `T` and `F`. They represent the
values of “true" and “false", respectively.

.. Previous: \ :ref:`Boolean Constants <#Boolean-Constants>`,
.. Up: \ :ref:`Booleans <#Booleans>`

.. _#Logical-Operators:

Logical Operators
^^^^^^^^^^^^^^^^^^^^^^^

Bro supports three logical operators: `&&`, `||`, and `!` are
Boolean “and,” “or,” and “not,” respectively. `&&` and `||` are
“short circuit” operators, as in C: they evaluate their right-hand
operand only if needed.

The `&&` operator returns `F` if its first operand evaluates to
*false*, otherwise it evaluates its second operand and returns `T` if
it evaluates to *true*. The `||` operator evaluates its first operand
and returns `T` if the operand evaluates to *true*. Otherwise it
evaluates its second operand, and returns `T` if it is *true*, `F`
if *false*.

The unary `!` operator returns the boolean negation of its argument.
So, `! T` yields `F`, and `! F` yields `T`.

The logical operators are left-associative. The `!` operator has very
high precedence, the same as unary `+` and `-`; see The `||`
operator has precedence just below `&&`, which in turn is just below
that of the comparison operators (see :ref:`Comparison
Operators <#Comparison-Operators>`).

.. Next: \ :ref:`Enumerations <#Enumerations>`,
.. Previous: \ :ref:`Booleans <#Booleans>`, Up: \ :ref:`Values <#Values>`

.. _#Numeric-Types:

Numeric Types
~~~~~~~~~~~~~~~~~

`int`, `count`, and `double` types should be familiar to most
programmers as integer, unsigned integer, and double-precision
floating-point types.

These types are referred to collectively as *numeric*. *Numeric* types
can be used in arithmetic operations (see below) as well as in
comparisons (:ref:`Comparison Operators <#Comparison-Operators>`).

.. Next: \ :ref:`Mixing Numeric Types <#Mixing-Numeric-Types>`, Up: \ `Numeric
.. Types <#Numeric-Types>`_

.. _#Numeric-Constants:

Numeric Constants
^^^^^^^^^^^^^^^^^^^^^^^

`count` constants are just strings of digits: `1234` and `0` are
examples.

`integer` constants are strings of digits preceded by a `+` or `-`
sign: `-42` and `+5` for example. Because digit strings without a
sign are of type `count`, occasionally you need to take care when
defining a variable if it really needs to be of type `int` rather than
`count`. Because of type inferencing , a definition like:

::

             local size_difference = 0;

will result in `size_difference` having type `count` when `int` is
what's instead needed (because, say, the size difference can be
negative). This can be resolved either by using an `int` constant in
the initialization:

::

             local size_difference = +0;

or explicitly indicating the type:

::

             local size_difference: int = 0;

You write floating-point constants in the usual ways, a string of digits
with perhaps a decimal point and perhaps a scale-factor written in
scientific notation. Optional `+` or `-` signs may be given before
the digits or before the scientific notation exponent. Examples are
`-1234.`, `-1234e0`, `3.14159`, and `.003e-23`. All
floating-point constants are of type `double`.

.. Next: \ :ref:`Arithmetic Operators <#Arithmetic-Operators>`,
.. Previous: \ :ref:`Numeric Constants <#Numeric-Constants>`, Up: \ `Numeric
.. Types <#Numeric-Types>`_

.. _#Mixing-Numeric-Types:

Mixing Numeric Types
^^^^^^^^^^^^^^^^^^^^^^^^^^

You can freely intermix *numeric* types in expressions. When intermixed,
values are promoted to the “highest" type in the expression. In general,
this promotion follows a simple hierarchy: `double` is highest,
`int` comes next, and `count` is lowest. (Note that `bool` is not
a numeric type.)

.. Next: \ :ref:`Comparison Operators <#Comparison-Operators>`,
.. Previous: \ :ref:`Mixing Numeric Types <#Mixing-Numeric-Types>`,
.. Up: \ :ref:`Numeric Types <#Numeric-Types>`

.. _#Arithmetic-Operators:

Arithmetic Operators
^^^^^^^^^^^^^^^^^^^^^^^^^^

For doing arithmetic, Bro supports `+` `-` `*` `/` and `%` .
In general, binary operators evaluate their operands after converting
them to the higher type of the two and return a result of that type.
However, subtraction of two `count` values yields an `int` value.
Division is integral if its operands are `count` and/or `int`.

`+` and `-` can also be used as unary operators. If applied to a
`count` type, they yield an `int` type.

`%` computes a *modulus*, defined in the same way as in the C
language. It can only be applied to `count` or `int` types, and
yields `count` if both operands are `count` types, otherwise
`int`.

Binary `+` and `-` have the lowest precedence, `*`, `/`, and
`%` have equal and next highest precedence. The unary `+` and `-`
operators have the same precedence as the `!` operator :ref:`Logical
Operators <#Logical-Operators>`. See , for a table of the precedence of
all Bro operators.

All arithmetic operators associate from left-to-right.

.. Previous: \ :ref:`Arithmetic Operators <#Arithmetic-Operators>`,
.. Up: \ :ref:`Numeric Types <#Numeric-Types>`

.. _#Comparison-Operators:

Comparison Operators
^^^^^^^^^^^^^^^^^^^^^^^^^^

Bro provides the usual comparison operators: `==` , `!=` , `<` ,
`<=` , `>` , and `>=` . They each take two operands, which they
convert to the higher of the two types (see :ref:`Mixing Numeric
Types <#Mixing-Numeric-Types>`). They return a `bool` corresponding
to the comparison of the operands. For example,

::

             3 < 3.000001

yields true.

The comparison operators are all non-associative and have equal
precedence, just below that of the just above that of the See , for a
general discussion of precedence.

.. Next: \ :ref:`Strings <#Strings>`, Previous: \ `Numeric
.. Types <#Numeric-Types>`_, Up: \ :ref:`Values <#Values>`

.. _#Enumerations:

Enumerations
~~~~~~~~~~~~~~~~

Enumerations allow you to specify a set of related values that have no
further structure, similar to `enum` types in C. For example:

::

             type color: enum { Red, White, Blue, };

defines the values `Red`, `White`, and `Blue`. A variable of type
`color` holds one of these values. Note that `Red` et al have
*global scope*. You *cannot* define a variable or type with those names.
(Also note that, as usual, the comma after `Blue` is optional.)

The only operations allowed on enumerations are comparisons for
equality. Unlike C enumerations, they do not have values or an ordering
associated with them.

You can extend the set of values in an enumeration using
`redef enum type-name += { values-list }`:

::

             redef enum color += { Black, Yellow };

.. Next: \ :ref:`Patterns <#Patterns>`,
.. Previous: \ :ref:`Enumerations <#Enumerations>`, Up: \ :ref:`Values <#Values>`

.. _#Strings:

Strings
~~~~~~~~~~~

The `string` type holds character-string values, used to represent and
manipulate text.

.. Next: \ :ref:`String Operators <#String-Operators>`,
.. Up: \ :ref:`Strings <#Strings>`

.. _#String-Constants:

String Constants
^^^^^^^^^^^^^^^^^^^^^^

You create string constants by enclosing text within double (`"`)
quotes. A backslash character (`\`) introduces an *escape sequence*.
The following ANSI C escape sequences are recognized: FIXME the 8-bit
ASCII character with code *hex-digits*. Bro string constants currently
*cannot* be continued across multiple lines by escaping newlines in the
input. This may change in the future. Any other character following a
`\` is passed along literally.

Unlike in C, strings are represented internally as a count and a vector
of bytes, rather than a NUL-terminated series of bytes. This difference
is important because NULs can easily be introduced into strings derived
from network traffic, either by the nature of the application,
inadvertently, or maliciously by an attacker attempting to subvert the
monitor. An example of the latter is sending the following to an FTP
server:

::

             USER nice\0USER root

where “\ `\0`\ ” represents a NUL. Depending on how it is written, the
FTP application receiving this text might well interpret it as two
separate commands, “\ `USER nice`\ ” followed by “\ `USER root`\ ”.
But if the monitoring program uses NUL-terminated strings, then it will
effectively see only “\ `USER nice`\ ” and have no opportunity to
detect the subversive action.

Note that Bro string constants are automatically NUL-terminated.

Note: While Bro itself allows NULs in strings, their presence in
arguments to many Bro functions results in a run-time error, as often
their presence (or, conversely, lack of a NUL terminator) indicates some
sort of problem (particularly for arguments that will be passed to C
functions). See section :ref:`Run-time errors for strings with
NULs <#Run_002dtime-errors-for-strings-with-NULs>` for discussion.

.. Previous: \ :ref:`String Constants <#String-Constants>`,
.. Up: \ :ref:`Strings <#Strings>`

.. _#String-Operators:

String Operators
^^^^^^^^^^^^^^^^^^^^^^

Currently the only string operators provided are the comparison
operators discussed in :ref:`Comparison Operators <#Comparison-Operators>`
and pattern-matching as discussed in :ref:`Pattern
Operators <#Pattern-Operators>`. These operators perform character by
character comparisons based on the native character set, usually ASCII.

Some functions for manipulating strings are also available. See .

.. Next: \ :ref:`Temporal Types <#Temporal-Types>`,
.. Previous: \ :ref:`Strings <#Strings>`, Up: \ :ref:`Values <#Values>`

.. _#Patterns:

Patterns
~~~~~~~~~~~~

The `pattern` type holds regular-expression patterns, which can be
used for fast text searching operations.

-  :ref:`Pattern Constants <#Pattern-Constants>`
-  :ref:`Pattern Operators <#Pattern-Operators>`

.. Next: \ :ref:`Pattern Operators <#Pattern-Operators>`,
.. Up: \ :ref:`Patterns <#Patterns>`

.. _#Pattern-Constants:

Pattern Constants
^^^^^^^^^^^^^^^^^^^^^^^

You create pattern constants by enclosing text within forward slashes
(`/`). The syntax is the same as for the *flex* version of the *lex*
utility. For example,

::

             /foo|bar/

specifies a pattern that matches either the text “foo” or the text
“bar”;

::

             /[a-zA-Z0-9]+/

matches one or more letters or digits, as will

::

             /[[:alpha:][:digit:]]+/

or

::

             /[[:alnum:]]+/

and the pattern

::

             /^rewt.*login/

matches any string with the text “rewt” at the beginning of a line
followed somewhere later in the line by the text “login”.

You can create disjunctions (patterns the match any of a number of
alternatives) both using the “{`|`\ }” regular expression operator
directly, as in the first example above, or by using it to join multiple
patterns. So the first example above could instead be written:

::

             /foo/ | /bar/

This form is convenient when constructing large disjunctions because
it's easier to see what's going on.

Note that the speed of the regular expression matching does *not* depend
on the complexity or size of the patterns, so you should feel free to
make full use of the expressive power they afford.

You can assign `pattern` values to variables, hold them in tables, and
so on. So for example you could have:

::

             global address_filters: table[addr] of pattern = {
                 [128.3.4.4] = /failed login/ | /access denied/,
                 [128.3.5.1] = /access timeout/
             };

and then could test, for example:

::

             if ( address_filters[c$id$orig_h] in msg )
                 skip_the_activity();

Note though that you cannot use create patterns dynamically. this form
(or any other) to create dynamic

.. Previous: \ :ref:`Pattern Constants <#Pattern-Constants>`,
.. Up: \ :ref:`Patterns <#Patterns>`

.. _#Pattern-Operators:

Pattern Operators
^^^^^^^^^^^^^^^^^^^^^^^

There are two types of pattern-matching operators: *exact* matching and
*embedded* matching.

-  :ref:`Exact Pattern Matching <#Exact-Pattern-Matching>`
-  :ref:`Embedded Pattern Matching <#Embedded-Pattern-Matching>`

.. Next: \ :ref:`Embedded Pattern Matching <#Embedded-Pattern-Matching>`,
.. Up: \ :ref:`Pattern Operators <#Pattern-Operators>`

.. _#Exact-Pattern-Matching:

Exact Pattern Matching
''''''''''''''''''''''''''''''

Exact matching tests for a string entirely matching a given pattern. You
specify exact matching by using the `==` equality relational with one
`pattern` operand and one `string` operand (order irrelevant). For
example,

::

             "foo" == /foo|bar/

yields true, while

::

             /foo|bar/ == "foobar"

yields false. The `!=` operator is the negation of the `==`
operator, just as when comparing strings or numerics.

Note that for exact matching, the `^` (anchor to beginning-of-line)
and `$` (anchor to end-of-line) regular expression operators are
redundant: since the match is *exact*, every pattern is implicitly
anchored to the beginning and end of the line.

.. Previous: \ :ref:`Exact Pattern Matching <#Exact-Pattern-Matching>`,
.. Up: \ :ref:`Pattern Operators <#Pattern-Operators>`

.. _#Embedded-Pattern-Matching:

Embedded Pattern Matching
'''''''''''''''''''''''''''''''''

Embedded matching tests whether a given pattern appears anywhere within
a given string. You specify embedded pattern matching using the `in`
operator. It takes two operands, the first (which must appear on the
left-hand side) of type `pattern`, the second of type `string`. For
example,

::

             /foo|bar/ in "foobar"

yields true, as does

::

             /oob/ in "foobar"

but

::

             /^oob/ in "foobar"

does not, since the text “oob” does not appear the beginning of the
string “foobar”. Note, though, that the `$` regular expression
operator (anchor to end-of-line) is not currently supported, so:

::

             /oob$/ in "foobar"

currently yields true. This is likely to change in the future. Finally,
the `!in` operator yields the negation of the `in` operator.

.. Next: \ :ref:`Port Type <#Port-Type>`, Previous: \ :ref:`Patterns <#Patterns>`,
.. Up: \ :ref:`Values <#Values>`

.. _#Temporal-Types:

Temporal Types
~~~~~~~~~~~~~~~~~~

Bro supports types representing *absolute* and *relative* times with the
`time` and `interval` types, respectively.

-  :ref:`Temporal Constants <#Temporal-Constants>`
-  :ref:`Temporal Operators <#Temporal-Operators>`

.. Next: \ :ref:`Temporal Operators <#Temporal-Operators>`, Up: \ `Temporal
.. Types <#Temporal-Types>`_

.. _#Temporal-Constants:

Temporal Constants
^^^^^^^^^^^^^^^^^^^^^^^^

There is currently no way to specify an absolute time as a constant
(though see the `current_time` and `network_time` functions in
:ref:`Functions for manipulating time <#Functions-for-manipulating-time>`).
You can specify `interval` constants, however, by appending a *time
unit* after a numeric constant. For example,

::

             3.5 min

denotes 210 seconds. The different time units are `usec`, `sec`,
`min`, `hr`, and `day`, representing microseconds, seconds,
minutes, hours, and days, respectively. The whitespace between the
numeric constant and the unit is optional, and the letter “s” may be
added to pluralize the unit (this has no semantic effect). So the above
example could also be written:

::

             3.5mins

or

::

             150 secs

.. Previous: \ :ref:`Temporal Constants <#Temporal-Constants>`, Up: \ `Temporal
.. Types <#Temporal-Types>`_

.. _#Temporal-Operators:

Temporal Operators
^^^^^^^^^^^^^^^^^^^^^^^^

You can apply arithmetic and relational operators to temporal values, as
follows.

-  :ref:`Temporal Negation <#Temporal-Negation>`
-  :ref:`Temporal Addition <#Temporal-Addition>`
-  :ref:`Temporal Subtraction <#Temporal-Subtraction>`
-  :ref:`Temporal Multiplication <#Temporal-Multiplication>`
-  :ref:`Temporal Division <#Temporal-Division>`
-  :ref:`Temporal Relationals <#Temporal-Relationals>`

.. Next: \ :ref:`Temporal Addition <#Temporal-Addition>`, Up: \ `Temporal
.. Operators <#Temporal-Operators>`_

 Temporal Negation
'''''''''''''''''''''''''

The unary `-` operator can be applied to an `interval` value to
yield another `interval` value. For example,

::

             - 12 hr

represents “twelve hours in the past.”

.. Next: \ :ref:`Temporal Subtraction <#Temporal-Subtraction>`,
.. Previous: \ :ref:`Temporal Negation <#Temporal-Negation>`, Up: \ `Temporal
.. Operators <#Temporal-Operators>`_

.. _#Temporal-Addition:

Temporal Addition
'''''''''''''''''''''''''

Adding two `interval` values yields another `interval` value. For
example,

::

             5 sec + 2 min

yields 125 seconds. Adding a `time` value to an `interval` yields
another `time` value.

.. Next: \ :ref:`Temporal Multiplication <#Temporal-Multiplication>`,
.. Previous: \ :ref:`Temporal Addition <#Temporal-Addition>`, Up: \ `Temporal
.. Operators <#Temporal-Operators>`_

.. _#Temporal-Subtraction:

Temporal Subtraction
''''''''''''''''''''''''''''

Subtracting a `time` value from another `time` value yields an
`interval` value, as does subtracting an `interval` value from
another `interval`, while subtracting an `interval` from a `time`
yields a `time`.

.. Next: \ :ref:`Temporal Division <#Temporal-Division>`, Previous: \ `Temporal
.. Subtraction <#Temporal-Subtraction>`_, Up: \ `Temporal
.. Operators <#Temporal-Operators>`_

.. _#Temporal-Multiplication:

Temporal Multiplication
'''''''''''''''''''''''''''''''

You can multiply an `interval` value by a *numeric* value to yield
another `interval` value. For example,

::

            5 min * 6.5

yields 1,950 seconds. `time` values cannot be scaled by multiplication
or division.

.. Next: \ :ref:`Temporal Relationals <#Temporal-Relationals>`,
.. Previous: \ :ref:`Temporal Multiplication <#Temporal-Multiplication>`,
.. Up: \ :ref:`Temporal Operators <#Temporal-Operators>`

.. _#Temporal-Division:

Temporal Division
'''''''''''''''''''''''''

You can also divide an `interval` value by a *numeric* value to yield
another `interval` value. For example,

::

            5 min / 2

yields 150 seconds. Furthermore, you can divide one `interval` value
by another to yield a `double`. For example,

::

            5 min / 30 sec

yields 10.

.. Previous: \ :ref:`Temporal Division <#Temporal-Division>`, Up: \ `Temporal
.. Operators <#Temporal-Operators>`_

.. _#Temporal-Relationals:

Temporal Relationals
''''''''''''''''''''''''''''

You may compare two `time` values or two `interval` values for
equality, and also for ordering, where times or intervals further in the
future are considered larger than times or intervals nearer in the
future, or in the past.

.. Next: \ :ref:`Address Type <#Address-Type>`, Previous: \ `Temporal
.. Types <#Temporal-Types>`_, Up: \ :ref:`Values <#Values>`

.. _#Port-Type:

Port Type
~~~~~~~~~~~~~

The `port` type corresponds to transport-level port numbers. Besides
TCP or UDP ports, these can also be ICMP “ports”, where the source port
is the ICMP message type and the destination port the ICMP message code.
Furthermore, the transport-level protocol of a port can remain
unspecified. In any case, a value of type `port` represents exactly
one of those four transport protocol choices.

-  :ref:`Port Constants <#Port-Constants>`
-  :ref:`Port Operators <#Port-Operators>`
-  :ref:`Port Functions <#Port-Functions>`

.. Next: \ :ref:`Port Operators <#Port-Operators>`, Up: \ `Port
.. Type <#Port-Type>`_

.. _#Port-Constants:

Port Constants
^^^^^^^^^^^^^^^^^^^^

There are two forms of `port` constants. The first consists of an
unsigned integer followed by one of “\ `/tcp`\ ”, “\ `/udp`\ ”,
“\ `/icmp`\ ”, or “\ `/unknown`\ ”. So, for example,
“\ `80/tcp`\ ” corresponds to TCP port 80 (typically used for the HTTP
protocol). The second form of constant is specified using a predefined
identifier, such as “\ `http`\ ”, equivalent to “\ `80/tcp`.” These
predefined identifiers are simply `const` variables defined in the Bro
initialization file, such as:

::

             const http = 80/tcp;

.. Next: \ :ref:`Port Functions <#Port-Functions>`, Previous: \ `Port
.. Constants <#Port-Constants>`_, Up: \ :ref:`Port Type <#Port-Type>`

.. _#Port-Operators:

Port Operators
^^^^^^^^^^^^^^^^^^^^

The only operations that can be applied to `port` values are
relationals. You may compare them for equality, and also for ordering.
For example,

::

              20/tcp < telnet

yields true because `telnet` is a predefined constant set to
`23/tcp`.

When comparing ports across transport-level protocols, the following
holds: unknown < TCP < UDP < ICMP. For example, “\ `65535/tcp`\ ” is
smaller than “\ `0/udp`\ ”.

.. Previous: \ :ref:`Port Operators <#Port-Operators>`, Up: \ `Port
.. Type <#Port-Type>`_

.. _#Port-Functions:

Port Functions
^^^^^^^^^^^^^^^^^^^^

You can obtain the transport-level protocol type of a port as an
`enum` constant of type `transport_proto` (defined in `bro.init`),
using the built-in function (see :ref:`Predefined
Functions <#Predefined-Functions>`)
`get_port_transport_proto(p: port): transport_proto`.

.. Next: \ :ref:`Net Type <#Net-Type>`, Previous: \ :ref:`Port Type <#Port-Type>`,
.. Up: \ :ref:`Values <#Values>`

.. _#Address-Type:

Address Type
~~~~~~~~~~~~~~~~

Another networking type provided by Bro is `addr`, corresponding to an
IP address. The only operations that can be performed on them are
comparisons for equality or inequality (also, a built-in function
provides masking, as discussed below).

When configuring the Bro distribution, if you specify `--enable-brov6`

then Bro will be built to support both IPv4 and IPv6 addresses, and an
`addr` can hold either. Otherwise, addresses are restricted to IPv4.

-  :ref:`Address Constants <#Address-Constants>`
-  :ref:`Address Operators <#Address-Operators>`

.. Next: \ :ref:`Address Operators <#Address-Operators>`, Up: \ `Address
.. Type <#Address-Type>`_

.. _#Address-Constants:

Address Constants
^^^^^^^^^^^^^^^^^^^^^^^

Constants of type `addr` have the familiar “dotted quad” format,
`A_1.A_2.A_3.A_4`, where the A\_i all lie between 0 and 255. If you
have configured for IPv6 support as discussed above, then you can also
use the colon-separated hexadecimal form described in RFC2373.

Often more useful are *hostname* constants. There is no Bro type
corresponding to Internet hostnames. Because hostnames can correspond to
multiple IP addresses, you quickly run into ambiguities if comparing one
hostname with another. Bro does, however, support hostnames as
constants. Any series of two or more identifiers delimited by dots forms
a hostname constant, so, for example, “\ `lbl.gov`\ ” and
“\ `www.microsoft.com`\ ” are both hostname constants (the latter, as
of this writing, corresponds to 5 distinct IP addresses). The value of a
hostname constant is a `list` of `addr` containing one or more
elements. These lists (as with the lists associated with certain
`port` constants, discussed above) cannot be used in Bro expressions;
but they play a central role in initializing Bro tables and sets.

.. Previous: \ :ref:`Address Constants <#Address-Constants>`, Up: \ `Address
.. Type <#Address-Type>`_

.. _#Address-Operators:

Address Operators
^^^^^^^^^^^^^^^^^^^^^^^

The only operations that can be applied to `addr` values are
comparisons for equality or inequality, using `==` and `!=`.
However, you can also operate on `addr` values using to mask off lower
address bits, and to convert an `addr` to a `net` (see below).

.. Next: \ :ref:`Records <#Records>`, Previous: \ `Address
.. Type <#Address-Type>`_, Up: \ :ref:`Values <#Values>`

.. _#Net-Type:

Net Type
~~~~~~~~~~~~~

Related to the `addr` type is `net`. `net` values hold address
prefixes. Historically, the IP address space was divided into different
*classes* of addresses, based on the uppermost components of a given
address: class A spanned the range 0.0.0.0 to 127.255.255.255; class B
from 128.0.0.0 to 191.255.255.255; class C from 192.0.0.0 to
223.255.255.255; class D from 224.0.0.0 to 239.255.255.255; and class E
from 240.0.0.0 to 255.255.255.255. Addresses were allocated to different
networks out of either class A, B, or C, in blocks of 2^24, 2^16, and
2^8 addresses, respectively.

Accordingly, `net` values hold either an 8-bit class A prefix, a
16-bit class B prefix, a 24-bit class C prefix, or a 32-bit class D
“prefix” (an entire address). Values for class E prefixes are not
defined (because no such addresses are currently allocated, and so
shouldn't appear in other than clearly-bogus packets).

Today, address allocations come not from class A, B or C, but instead
from *CIDR* blocks (CIDR = Classless Inter-Domain Routing), which are
prefixes between 1 and 32 bits long in the range 0.0.0.0 to
223.255.255.255. *Deficiency: Bro should deal just with CIDR prefixes,
rather than old-style network prefixes. However, these are more
difficult to implement efficiently for table searching and the like;
hence currently Bro only supports the easier-to-implement old-style
prefixes. Since these don't match current allocation policies, often
they don't really fit an address range you'll want to describe. But for
sites with older allocations, they do, which gives them some basic
utility.*

In addition, *Deficiency: IPv6 has no notion of old-style network
prefixes, only CIDR prefixes, so the lack of support of CIDR prefixes
impairs use of Bro to analyze IPv6 traffic.*

-  :ref:`Net Constants <#Net-Constants>`
-  :ref:`Net Operators <#Net-Operators>`

.. Next: \ :ref:`Net Operators <#Net-Operators>`, Up: \ :ref:`Net Type <#Net-Type>`

.. _#Net-Constants:

Net Constants
^^^^^^^^^^^^^^^^^^^^

You express constants of type `net` in one of two forms, either:

    `N_1.N_2.`

or

    `N_1.N_2.N_3`

where the N\_i all lie between 0 and 255. The first of these corresponds
to class B prefixes (note the trailing “\ `.`\ ” that's required to
distinguish the constant from a floating-point number), and the second
to class C prefixes. *Deficiency: There's currently no way to specify a
class A prefix.*

.. Previous: \ :ref:`Net Constants <#Net-Constants>`, Up: \ `Net
.. Type <#Net-Type>`_

.. _#Net-Operators:

Net Operators
^^^^^^^^^^^^^^^^^^^^

The only operations that can be applied to `net` values are
comparisons for equality or inequality, using `==` and `!=`.

.. Next: \ :ref:`Tables <#Tables>`, Previous: \ :ref:`Net Type <#Net-Type>`,
.. Up: \ :ref:`Values <#Values>`

.. _#Records:

Records
~~~~~~~~~~~~

A `record` is a collection of values. Each value has a name, referred
to as one of the record's *fields*, and a type. The values do not need
to have the same type, and there is no restriction on the allowed types
(i.e., each field can be *any* type).

-  :ref:`Defining records <#Defining-records>`
-  :ref:`Record Constants <#Record-Constants>`
-  :ref:`Accessing Fields Using $ <#Accessing-Fields-Using-_0024>`
-  :ref:`Record Assignment <#Record-Assignment>`

.. Next: \ :ref:`Record Constants <#Record-Constants>`,
.. Up: \ :ref:`Records <#Records>`

.. _#Defining-records:

Defining records
^^^^^^^^^^^^^^^^^^^^^^^

A definition of a record type has the following syntax:

::

         record { field^+ }

(that is, the keyword `record` followed by one-or-more *field*'s
enclosed in braces), where a *field* has the syntax:

::

         identifier : type field-attributes^*  ; identifier : type field-attributes^*  ,

Each field has a name given by the identifier (which can be the same as
the identifier of an existing variable or a field in another record).
Field names must follow the same syntax as that for Bro variable names
(see :ref:`Variables <#Variables-Overview>`), namely they must begin with a
letter or an underscore (“\ `_`\ ”) followed by zero or more letters,
underscores, or digits. Bro reserved words such as `if` or `event`
cannot be used for field names. Field names are case-sensitive.

Each field holds a value of the given type. We discuss the optional
Finally, you can use either a semicolon or a comma to terminate the
definition of a record field.

For example, the following record type:

::

             type conn_id: record {
                 orig_h: addr;  # Address of originating host.
                 orig_p: port;  # Port used by originator.
                 resp_h: addr;  # Address of responding host.
                 resp_p: port;  # Port used by responder.
             };

is used throughout Bro scripts to denote a connection identifier by
specifying the connections originating and responding addresses and
ports. It has four fields: `orig_h` and `resp_h` of type `addr`,
and `orig_p` of `resp_p` of type `port`.

.. Next: \ :ref:`Accessing Fields Using $ <#Accessing-Fields-Using-_0024>`,
.. Previous: \ :ref:`Defining records <#Defining-records>`,
.. Up: \ :ref:`Records <#Records>`

.. _#Record-Constants:

Record Constants
^^^^^^^^^^^^^^^^^^^^^^^

You can initialize values of type `record` using either assignment
from another, already existing `record` value; or element-by-element;
or using a

In a Bro function or event handler, we could declare a local variable
the `conn_id` type given above:

::

             local id: conn_id;

and then explicitly assign each of its fields:

::

             id$orig_h = 207.46.138.11;
             id$orig_p = 31337/tcp;
             id$resp_h = 207.110.0.15;
             id$resp_p = 22/tcp;

*Deficiency: One danger with this initialization method is that if you
forget to initialize a field, and then later access it, you will crash
Bro.*

Or we could use:

::

             id = [$orig_h = 207.46.138.11, $orig_p = 31337/tcp,
                   $resp_h = 207.110.0.15, $resp_p = 22/tcp];

This second form is no different from assigning a `record` value
computed in some other fashion, such as the value of another variable, a
table element, or the value returned by a function call. Such
assignments must specify *all* of the fields in the target (i.e., in
`id` in this example), unless the missing field has the `&optional`
or `&default` attribute.

.. Next: \ :ref:`Record Assignment <#Record-Assignment>`, Previous: \ `Record
.. Constants <#Record-Constants>`_, Up: \ :ref:`Records <#Records>`

Accessing Fields Using “\ `$`\ ”
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

You access and assign record fields using the “\ `$`\ ” (dollar-sign)
operator. As indicated in the example above, for the record `id` we
can access its `orig_h` field using:

::

             id$orig_h

which will yield the `addr` value `207.46.138.11`.

.. Previous: \ :ref:`Accessing Fields Using $ <#Accessing-Fields-Using-_0024>`,
.. Up: \ :ref:`Records <#Records>`

.. _#Record-Assignment:

Record Assignment
^^^^^^^^^^^^^^^^^^^^^^^^

You can assign one record value to another using simple assignment:

::

             local a: conn_id;
             ...
             local b: conn_id;
             ...
             b = a;

Doing so produces a *shallow* copy. That is, after the assignment, `b`
refers to the same record as does `a`, and an assignment to one of
`b`'s fields will alter the field in `a`'s value (and vice versa for
an assignment to one of `a`'s fields). However, assigning again to
`b` itself, or assigning to `a` itself, will break the connection.

In order to produce a *deep* copy, use the clone operator “copy()”. For
more details, see :ref:`Expressions <#Expressions>`.

You can also assign to a record another record that has fields with the
same names and types, even if they come in a different order. For
example, if you have:

::

             local b: conn_id;
             local c: record {
                 resp_h: addr, orig_h: addr;
                 resp_p: port, orig_p: port;
             };

then you can assign either `b` to `c` or vice versa.

You could *not*, however, make the assignment (in either direction) if
you had:

::

             local b: conn_id;
             local c: record {
                 resp_h: addr, orig_h: addr;
                 resp_p: port, orig_p: port;
                 num_notices: count;
             };

because the field `num_notices` would either be missing or excess.

However, when declaring a record you can associate attributes with the
fields. The relevant ones are `&optional`, which indicates that when
assigning to the record you can omit the field, and `&default = expr`,
which indicates that if the field is missing, then a reference to it
returns the value of the expression *expr*. So if instead you had:

::

             local b: conn_id;
             local c: record {
                 resp_h: addr, orig_h: addr;
                 resp_p: port, orig_p: port;
                 num_notices: count &optional;
             };

then you could execute `c = b` even though `num_notices` is missing
from b. You still could not execute `b = c`, though, since in that
direction, `num_notices` is an extra field (regardless of whether it
has been assigned to or not — the error is a type-checking error, not a
run-time error).

The same holds for:

::

             local b: conn_id;
             local c: record {
                 resp_h: addr, orig_h: addr;
                 resp_p: port, orig_p: port;
                 num_notices: count &default = 0;
             };

I.e., you could execute `c = b` but not `b = c`. The only difference
between this example and the previous one is that for the previous one,
access to `c$num_notices` without having first assigned to it results
in a run-time error, while in the second, it yields 0.

You can test for whether a record field exists using the `?$`
operator.

Finally, all of the rules for assigning records also apply when passing
a record value as an argument in a function call or an event handler
invocation.

.. Next: \ :ref:`Sets <#Sets>`, Previous: \ :ref:`Records <#Records>`,
.. Up: \ :ref:`Values <#Values>`

.. _#Tables:

Tables
~~~~~~~~~~~

`table`'s provide *associative arrays*: mappings from one set of
values to another. The values being mapped are termed the *index* (or
*indices*, if they come in groups of more than one) and the results of
the mapping the *yield*.

Tables are quite powerful, and indexing them is very efficient, boiling
down to a single hash table lookup. So you should take advantage of them
whenever appropriate.

-  :ref:`Declaring Tables <#Declaring-Tables>`
-  :ref:`Initializing Tables <#Initializing-Tables>`
-  :ref:`Table Attributes <#Table-Attributes>`
-  :ref:`Accessing Tables <#Accessing-Tables>`
-  :ref:`Table Assignment <#Table-Assignment>`
-  :ref:`Deleting Table Elements <#Deleting-Table-Elements>`

.. Next: \ :ref:`Initializing Tables <#Initializing-Tables>`,
.. Up: \ :ref:`Tables <#Tables>`

.. _#Declaring-Tables:

Declaring Tables
^^^^^^^^^^^^^^^^^^^^^^^

You declare tables using the following syntax:

    `table [` *type^+* `] of` *type*

where *type^+* is one or more types, separated by commas.

The indices can be of the following *scalar* types: *numeric*,
*temporal*, *enumerations*, *string*, *port*, *addr*, or *net*. The
yield can be of any type. So, for example:

::

             global a: table[count] of string;

declares `a` to be a table indexed by a `count` value and yielding a
`string` value, similar to a regular array in a language like C. The
yield type can also be more complex:

::

             global a: table[count] of table[addr, port] of conn_id;

declares `a` to be a table indexed by `count` and yielding another
table, which itself is indexed by an `addr` and a `port` to yield a
`conn_id` record.

This second example illustrates a *multi-dimensional* table, one indexed
not by a single value but by a *tuple* of values.

.. Next: \ :ref:`Table Attributes <#Table-Attributes>`, Previous: \ `Declaring
.. Tables <#Declaring-Tables>`_, Up: \ :ref:`Tables <#Tables>`

.. _#Initializing-Tables:

Initializing Tables
^^^^^^^^^^^^^^^^^^^^^^^^^^

You initialize tables by enclosing a set of initializers within braces.
Each initializer looks like:

    `[` *expr-list* `] =` *expr*

where *expr-list* is a comma-separated list of expressions corresponding
to an index of the table (so, for a table indexed by `count`, for
example, this would be a single expression of type `count`) and *expr*
is the yield value to assign to that index.

For example,

::

             global a: table[count] of string = {
                 [11] = "eleven",
                 [5] = "five",
             };

initializes the table `a` to have two elements, one indexed by `11`
and yielding the string `"eleven"` and the other indexed by `5` and
yielding the string `"five"`. (Note the comma after the last list
element; it is optional, similar to how C allows final commas in
declarations.)

You can also group together a set of indices together to initialize them
to the same value:

::

             type HostType: enum { DeskTop, Server, Router };
             global a: table[addr] of HostType = {
                 [[155.26.27.2, 155.26.27.8, 155.26.27.44]] = Server,
             };

is equivalent to:

::

             type HostType: enum { DeskTop, Server, Router };
             global a: table[addr] of HostType = {
                 [155.26.27.2] = Server,
                 [155.26.27.8] = Server,
                 [155.26.27.44] = Server,
             };

This mechanism also applies to which can be used in table
initializations for any indices of type `addr`. For example, if
`www.my-server.com` corresponded to the addresses 155.26.27.2 and
155.26.27.44, then the above could be written:

::

             global a: table[addr] of HostType = {
                 [[www.my-server.com, 155.26.27.8]] = Server,
             };

and if it corresponded to all there, then:

::

             global a: table[addr] of HostType = {
                 [www.my-server.com] = Server,
             };

You can also use multiple index groupings across different indices:

::

             global access_allowed: table[addr, port] of bool = {
                 [www.my-server.com, [21/tcp, 80/tcp]] = T,
             };

is equivalent to:

::

             global access_allowed: table[addr, port] of bool = {
                 [155.26.27.2, 21/tcp] = T,
                 [155.26.27.2, 80/tcp] = T,
                 [155.26.27.8, 21/tcp] = T,
                 [155.26.27.8, 80/tcp] = T,
                 [155.26.27.44, 21/tcp] = T,
                 [155.26.27.44, 80/tcp] = T,
             };

*Fixme: add example of cross-product initialization of sets*

.. Next: \ :ref:`Accessing Tables <#Accessing-Tables>`,
.. Previous: \ :ref:`Initializing Tables <#Initializing-Tables>`,
.. Up: \ :ref:`Tables <#Tables>`

.. _#Table-Attributes:

Table Attributes
^^^^^^^^^^^^^^^^^^^^^^^

When declaring a table, you can specify a number of attributes that
affect its operation:

‘\ `&default`\ ’

Specifies a value to yield when an index does not appear in the table.
Syntax:

    `&default =`\ *expr*

*expr* can have one of two forms. If it's type is the same as the
table's yield type, then *expr* is evaluated and returned. If it's type
is a `function` with arguments whose types correspond left-to-right
with the index types of the table, and which returns a type the same as
the yield type, then that function is called with the indices that
yielded the missing value to compute the default value.

For example:

::

                  global a: table[count] of string &default = "nothing special";

will return the string `"nothing special"` anytime `a` is indexed
with a `count` value that does not appear in `a`.

A more dynamic example:

::

                  function nothing_special(): string
                      {
                      if ( panic_mode )
                          return "look out!";
                      else
                          return "nothing special";
                      }
              
                  global a: table[count] of string &default = nothing_special;

An example of using a function that computes using the index:

::

                  function make_pretty(c: count): string
                      {
                      return fmt("**%d**", c);
                      }
              
                  global a: table[count] of string &default = make_pretty;

‘\ `&create_expire`\ ’

Specifies that elements in the table should be *automatically deleted*
after a given amount of time has elapsed since they were first entered
into the table. Syntax:

    `&create_expire =`\ *expr*

where *expr* is of type `interval`.

‘\ `&read_expire`\ ’

The same as `create_expire` except the element is deleted when the
given amount of time has lapsed since the last time the element was
accessed from the table.

‘\ `&write_expire`\ ’

The same as `&create_expire` except the element is deleted when the
given amount of time has lapsed since the last time the element was
entered or modified in the table.

‘\ `&expire_func`\ ’

Specifies a function to call when an element is due for expression
because of &create\_expire, &read\_expire, or &write\_expire. Syntax:

    `&expire_func =`\ *expr*

*expr* must be a function that takes two arguments: the first one is a
table with the same index and yield types as the associated table. The
second one is of type `any` and corresponds to the index(es) of the
element being expired. The function must return an `interval` value.
The `interval` indicates for how much longer the element should remain
in the table; returning `0 secs` or a negative value instructs Bro to
go ahead and delete the element.

*Deficiency: The use of an*\ `any`\ *type here is temporary and will
be changing in the future to a general tuple notion.*

You specify multiple attributes by listing one after the other,
*without* commas between them:

::

             global a: table[count] of string &default="foo" &write_expire=5sec;

Note that you can specify each type of attribute only once. You can,
however, specify more than one of &create\_expire, &read\_expire, or
&write\_expire. In that case, whenever any of the corresponding timers
expires, the element will be deleted.

.. Next: \ :ref:`Table Assignment <#Table-Assignment>`, Previous: \ `Table
.. Attributes <#Table-Attributes>`_, Up: \ :ref:`Tables <#Tables>`

.. _#Accessing-Tables:

Accessing Tables
^^^^^^^^^^^^^^^^^^^^^^^

As usual, you access the values in tables by indexing them with a value
(for a single index) or list of values (multiple indices) enclosed in
`[]`'s. *Deficiency: Presently, when indexing a multi-dimensional
table you must provide all of the relevant indices; you can't leave one
out in order to extract a sub-table.*

You can also index arrays using `record`'s, providing the record is
comprised of values whose types match that of the table's indices. (Any
record fields whose types are themselves records are recursively
unpacked to effect this matching.) For example, if we have:

::

             local b: table[addr, port] of conn_id;
             local c = 131.243.1.10;
             local d = 80/tcp;

then we could index `b` using `b[c, d]`, but if we had:

::

             local e = [$field1 = c, $field2 = d];

we could also index it using `a[d]`

You can test whether a table holds a given index using the `in`
operator:

::

             [131.243.1.10, 80/tcp] in b

or

::

             e in b

per the examples above. In addition, if the table has only a single
index (not multi-dimensional), then you can omit the `[]`'s:

::

             local active_connections: table[addr] of conn_id;
             ...
             if ( 131.243.1.10 in active_connections )
                 ...

.. Next: \ :ref:`Deleting Table Elements <#Deleting-Table-Elements>`,
.. Previous: \ :ref:`Accessing Tables <#Accessing-Tables>`,
.. Up: \ :ref:`Tables <#Tables>`

.. _#Table-Assignment:

Table Assignment
^^^^^^^^^^^^^^^^^^^^^^^

An indexed table can be the target of an assignment:

::

             b[131.243.1.10, 80/tcp] = c$id;

You can also assign to an entire table. For example, suppose we have the
global:

::

             global active_conn_count: table[addr, port] of count;

then we could later clear the contents of the table using:

::

             local empty_table: table[addr, port] of count;
             active_conn_count = empty_table;

Here the first statement declares a local variable `empty_table` with
the same type as `active_conn_count`. Since we don't initialize the
table, it starts out empty. Assigning it to `active_conn_count` then
replaces the value of `active_conn_count` with an empty table. Note:
As with `record`'s, assigning `table` values results in a *shallow
copy*. For *deep copies*, use the clone operator “copy()” explained in
:ref:`Expressions <#Expressions>`.

In addition to directly accessing an element of a table by specifying
its index, you can also loop over all of the indices in a table using
the statement.

.. Previous: \ :ref:`Table Assignment <#Table-Assignment>`,
.. Up: \ :ref:`Tables <#Tables>`

.. _#Deleting-Table-Elements:

Deleting Table Elements
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

You can remove an individual element from a table using the statement:

::

             delete active_host[c$id];

will remove the element in `active_host` corresponding to the
connection identifier `c$id` (which is a &conn\_id record). If the
element isn't present, nothing happens.

.. Next: \ :ref:`Files <#Files>`, Previous: \ :ref:`Tables <#Tables>`,
.. Up: \ :ref:`Values <#Values>`

.. _#Sets:

Sets
~~~~~~~~~

Sets are very similar to tables. The principle difference is that they
are simply a collection of indices; they don't yield any values. You
declare tables using the following syntax:

    `set [` *type^+* `]`

where, as with `table`\ s, *type^+* is one or more scalar types (or
records), separated by commas.

You initialize sets listing their elements in braces:

::

             global a = { 21/tcp, 23/tcp, 80/tcp, 443/tcp };

which implicitly types `a` as a `set[port]` and then initializes it
to contain the given 4 `port` values.

For multiple indices, you enclose each set of indices in brackets:

::

             global b = { [21/tcp, "ftp"], [23/tcp, "telnet"], };

which implicitly `b` as `set[port, string]` and then initializes it
to contain the given two elements. (As with tables, the comma after the
last element is optional.)

As with tables, you can group together sets of indices:

::

             global c = { [21/tcp, "ftp"], [[80/tcp, 8000/tcp, 8080/tcp], "http"], };

initializes `c` to contain 4 elements.

Also as with tables, you can use the &create\_expire, &read\_expire, and
&write\_expire attributes to control the automatic expiration of
elements in a set. *Deficiency: However, the attribute is not currently
supported.*

You can test for whether a particular member is in a set using the add
elements using the `add` statement:

::

             add c[443/tcp, "https"];

and can remove them using the `delete` statement:

::

             delete c[21/tcp, "ftp"];

Also, as with tables, you can assign to the entire set, which assigns a

Finally, as with tables, you can loop over all of the indices in a set
using the statement.

.. Next: \ :ref:`Functions <#Functions>`, Previous: \ :ref:`Sets <#Sets>`,
.. Up: \ :ref:`Values <#Values>`

.. _#Files:

Files
~~~~~~~~~~

*Deficiency: Bro currently supports only a very simple notion of files.
You can only write to files, you can't read from them: and files are
essentially untyped—the only values you can write to them
are*\ `string`\ *'s or values that can be converted
to*\ `string`\ *.*

You declare `file` variables simply as type `file`:

::

             global f: file;

You can create values of type `file` by using the function:

::

             f = open("suspicious_info.log");

will create (or recreate, if it already exists) the file
*suspicious\_info.log* and open it for writing. You can also use to
append to an existing file (or create a new one, if it doesn't exist).

You write to files using the `print` statement:

::

             print f, 5 * 6;

will print the text `30` to the file corresponding to the value of
`f`.

There is no restriction regarding how many files you can have open at a
given time. In particular, even if your system has a limit imposed by
RLIMIT\_NOFILE as set by the system call `setrlimit`. If, however, you
want to to close a file, you can do so using `close`, and you can test
whether a file is open using `active-file`.

Finally, you can control whether a file is buffered using `set-buf`,
and can flush the buffers of all open files using `flush-all`.

.. Next: \ :ref:`Event handlers <#Event-handlers>`,
.. Previous: \ :ref:`Files <#Files>`, Up: \ :ref:`Values <#Values>`

.. _#Functions:

Functions
~~~~~~~~~~~~~~

You declare a Bro `function` type using:

    `function(` *argument\** `)` `:` *type*

where *argument* is a (possibly empty) comma-separated list of
arguments, and the final “\ `:` *type*\ ” declares the return type of
the function. It is optional; if missing, then the function does not
return a value.

Each argument is declared using:

    *param-name* `:` *type*

So, for example:

::

             function(a: addr, p: port): string

corresponds to a function that takes two parameters, `a` of type
`addr` and `p` of type `port`, and returns a value of type
`string`.

You could furthermore declare:

::

             global generate_id: function(a: addr, p: port): string;

to define `generate_id` as a variable of this type. Note that the
declaration does *not* define the body of the function, and, indeed,
`generate_id` could have different function bodies at different times,
by assigning different function values to it.

When defining a function including its body, the syntax is slightly
different:

::

         function func-name ( argument* ) [ : type ] { statement* }

That is, you introduce *func-name*, the name of the function, between
the keyword `function` and the opening parenthesis of the argument
list, and you list the statements of the function within braces at the
end.

For the previous example, we could define its body using:

::

             function generate_id(a: addr, p: port): string
                 {
                 if ( a in local_servers )
                     # Ignore port, they're always the same.
                     return fmt("server %s", a);
         
                 if ( p < 1024/tcp )
                     # Privileged port, flag it.
                     return fmt("%s/priv-%s", a, p);
         
                 # Nothing special - default formatting.
                 return fmt("%s/%s", a, p);
                 }

We also could have omitted the first definition; a function definition
like the one immediately above automatically defines `generate_id` as
a function of type `function(a: addr, p: port): string`. Note though
that if *func-name* was indeed already declared, then the argument list
much match *exactly* that of the previous definition. This includes the
names of the arguments; *Unlike in C*, you cannot change the argument
names between their first (forward) definition and the full definition
of the function.

You can also define functions without using any name. These are referred
to as are a type of expression.

You can only do two things with functions: or assign them. As an example
of the latter, suppose we have:

::

             local id_funcs: table[conn_id] of function(p: port, a: addr): string;

would declare a local variable indexed by a

same type as in the previous example. You could then execute:

::

             id_funcs[c$id] = generate_id

or call whatever function is associated with a given `conn_id`:

::

             print fmt("id is: %s", id_funcs[c$id](80/tcp, 1.2.3.4));

.. Next: \ :ref:`any type <#any-type>`, Previous: \ :ref:`Functions <#Functions>`,
.. Up: \ :ref:`Values <#Values>`

.. _#Event-handlers:

Event handlers
~~~~~~~~~~~~~~~~~~~

Event handlers are nearly identical in both syntax and semantics to
functions, with the two differences being that event handlers have no
return type since they never return a value, and you cannot call an
event handler. You declare an event handler using:

    `event (` *argument\** `)`

So, for example,

::

             local eh: event(attack_source: addr, severity: count)

declares the local variable `eh` to have a type corresponding to an
event handler that takes two arguments, `attack_source` of type
`addr`, and `severity` of type `count`.

To declare an event handler along with its body, the syntax is:

    `event` *handler* `(` *argument* `)` `{` *statement* `}`

As with functions, you can assign event handlers to variables of the
same type. Instead of calling event handlers like functions, though,
instead they are *invoked*. This can happen in one of three ways:

‘From the event engine’

When the event engine detects an event for which you have defined a
corresponding event handler, it queues an event for that handler. The
handler is invoked as soon as the event engine finishes processing the
current packet (and invoking any other event handlers that were queued
first). The various event handlers known to the event engine are
discussed in Chapter N .

‘Via the `event` statement’

The `event` statement queues an event for the given event handler for
immediate processing. For example:

::

                  event password_exposed(c, user, password);

queues an invocation of the event handler `password_exposed` with the
arguments `c`, `user`, and `password`. Note that
`password_exposed` must have been previously declared as an event
handler with a compatible set of arguments.

Or, if we had a local variable `eh` as defined above, we could
execute:

::

                  event eh(src, how_severe);

if `src` is of type `addr` and `how_severe` of type `count`.

‘Via the `schedule` expression’

The expression queues an event for future invocation. For example:

::

                  schedule 5 secs { password_exposed(c, user, password) };

would cause `password_exposed` to be invoked 5 seconds in the future.

.. Previous: \ :ref:`Event handlers <#Event-handlers>`,
.. Up: \ :ref:`Values <#Values>`

The `any` type
~~~~~~~~~~~~~~~~~~~~~

The `any` type is a type used internally by Bro to bypass strong
typing. For example, the function takes arguments of type `any`,
because its arguments can be of different types, and of variable length.
However, the `any` type is not supported for use by the user; while
Bro lets you declare variables of type `any`, it does not allow
assignment to them. This may change in the future. Note, though, that
you can achieve some of the same effect using `record` values with
`&optional` fields.


