.. Next: \ `Predefined Variables and
.. Functions <#Predefined-Variables-and-Functions>`_,
.. Previous: \ :ref:`Statements and Expressions <#Statements-and-Expressions>`,
.. Up: \ :ref:`Top <#Top>`

.. _#Global-and-Local-Variables:

Global and Local Variables
----------------------------

.. Up: \ :ref:`Global and Local Variables <#Global-and-Local-Variables>`

.. _#Variables-Overview:

Variables Overview
~~~~~~~~~~~~~~~~~~~~~~

Bro variables can be complicated to understand because they have a
number of possibilities and features. They can be global or local in
scope; modifiable or constant (unchangeable); explicitly or implicitly
typed; optionally initialized; defined to have additional *attributes*;
and, for global variables, *redefined* to have a different
initialization or different attributes from their first declaration.

Rather than giving the full syntax for variable declarations, which is
messy, in the following sections we discuss each of these facets of
variables in turn, illustrating them with the minimal necessary syntax.
However, keep in mind that the features can be combined as needed in a
variable declaration.

.. Next: \ `Assignment & call
.. semantics <#Assignment-_0026-call-semantics>`_, Up: \ `Variables
.. Overview <#Variables-Overview>`_

.. _#Scope:

Scope
^^^^^^^^^^^

*Global* variables are available throughout your policy script (once
declared), while the scope of *local* variables is confined to the
function or event handler in which they're declared. You indicate the
variable's type using a corresponding keyword:

    `global` *name* `:` *type* `;`

or

    `local` *name* `:` *type* `;`

which declares *name* to have the given type and the corresponding
scope.

You can intermix function/event handler definitions with declarations of
global variables, and, indeed, they're in fact the same thing (that is,
a function or event handler definition is equivalent to defining a
global variable of type `function` or `event` and associating its
initial value with that of the function or event handler). So the
following is fine:

::

             global a: count;
         
             function b(p: port): string
                 {
                 if ( p < 1024/tcp )
                     return "privileged";
                 else
                     return "ephemeral";
                 }
         
             global c: addr;

However, you cannot mix declarations of global variables with global
statements; the following is not allowed:

::

             print "hello, world";
             global a: count;

Local variables, on the other hand, can *only* be declared within a
function or event handler. (Unlike for global statements, these
declarations *can* come after statements.) Their scope persists to the
end of the function. For example:

::

             function b(p: port): string
                 {
                 if ( p < 1024/tcp )
                     local port_type = "privileged";
                 else
                     port_type = "ephemeral";
         
                 return port_type;
                 }

.. Next: \ :ref:`Modifiability <#Modifiability>`,
.. Previous: \ :ref:`Scope <#Scope>`, Up: \ `Variables
.. Overview <#Variables-Overview>`_

Assignment & call semantics
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Assignments of aggregate types (such as records, tables, or vectors) are
always *shallow*, that is, they are performed *by reference*. So when
you assign a record or table value to another variable, any
modifications you make to members become visible in both variables (see
also :ref:`Record Assignment <#Record-Assignment>`, :ref:`Table
Assignment <#Table-Assignment>`).

The same holds for function calls: an aggregate value passed into a
function is passed by reference, thus any modifications made to the
value inside the function remain effective after the function returns.

It is important to be aware of the fact that events triggered using the
`event` statement remain on the event queue until they are processed,
and that any aggregate values passed as arguments to `event` can be
modified at any time before the event handlers are executed. If this is
not desirable, you have to copy the values before passing them to
`event`. The model that applies here is one of *reference counting*,
not local scope or deep copying. If deep copies are desirable, use the
clone operator “copy()” explained in :ref:`Expressions <#Expressions>`.

Therefore, if an event handler triggering a new event modifies the
arguments after the `event` statement, these changes will be visible
inside the event handlers running later. This also affects the lifetime
of a value. If an aggregate is for example stored in a table and
referenced nowhere else, then retrieved and passed to an `event`
statement, and removed from the table before the event handlers execute,
it does remain in existence until the event handlers are executed.

Furthermore, if multiple event handlers exist for a single event type,
any changes to the arguments made by an event handler will be visible in
other event handlers still to follow.

.. Next: \ :ref:`Typing <#Typing>`, Previous: \ `Assignment & call
.. semantics <#Assignment-_0026-call-semantics>`_, Up: \ `Variables
.. Overview <#Variables-Overview>`_

.. _#Modifiability:

Modifiability
^^^^^^^^^^^^^^^^^^^

For both global and local variables, you can declare that the variable
*cannot be modified* by declaring it using the const keyword rather than
global or local:

::

             const response_script = "./scripts/nuke-em";

Note that `const` variables *must* be initialized (otherwise, of
course, there's no way for them to ever hold a useful value).

The utility of marking a variable as unmodifiable is for clarity in
expressing your script—making it explicit that a particular value will
never change—and also allows Bro to possibly optimize accesses to the
variable (though it does little of this currently).

Note that const variables *can* be redefined via redef.

.. Next: \ :ref:`Initialization <#Initialization>`,
.. Previous: \ :ref:`Modifiability <#Modifiability>`, Up: \ `Variables
.. Overview <#Variables-Overview>`_

.. _#Typing:

Typing
^^^^^^^^^^^^

When you define a variable, you can *explicitly* type it by specifying
its type after a colon. For example,

::

             global a: count;

directly indicates that a's type is `count`.

However, Bro can also *implicitly* type the variable by looking at the
type of the expression you use to initialize the variable:

::

             global a = 5;

also declares a's type to be `count`, since that's the type of the
initialization expression (the constant 5). There is no difference
between this declaration and:

::

             global a: count = 5;

except that it is more concise both to write and to read. In particular,
Bro remains *strongly* typed, even though it also supports *implicit*
typing; the key is that once the type is implicitly inferred, it is
thereafter strongly enforced.

Bro's *type inference* is fairly powerful: it can generally figure out
the type whatever initialization expression you use. For example, it
correctly infers that:

::

             global c = { [21/tcp, "ftp"], [[80/tcp, 8000/tcp, 8080/tcp], "http"], };

specifies that c's type is set[port, string]. But for still more
complicated expressions, it is not always able to infer the correct
type. When this occurs, you need to explicitly specify the type.

.. Next: \ :ref:`Attributes <#Attributes>`, Previous: \ :ref:`Typing <#Typing>`,
.. Up: \ :ref:`Variables Overview <#Variables-Overview>`

.. _#Initialization:

Initialization
^^^^^^^^^^^^^^^^^^^^

When defining a variable, you can optionally specify an initial value
for the variable:

::

             global a = 5;

indicates that the initial value of `a` is the value `5` (and also
implicitly types a as type count, per :ref:`Typing <#Typing>`).

The syntax of an initialization is “= *expression*\ ”, where the given
expression must be assignment-compatible with the variable's type (if
explicitly given). Tables and sets also have special initializer forms,
which are discussed in :ref:`Initializing Tables <#Initializing-Tables>` and
:ref:`Sets <#Sets>`.

.. Next: \ :ref:`Refinement <#Refinement>`,
.. Previous: \ :ref:`Initialization <#Initialization>`, Up: \ `Variables
.. Overview <#Variables-Overview>`_

.. _#Attributes:

Attributes
^^^^^^^^^^^^^^^^

When defining a variable, you can optionally specify a set of
*attributes* associated with the variable, which specify additional
properties associated with it. Attributes have two forms:

    `&` *attr*

for attributes that are specified simply using their name, and

    `&` *attr* `=` *expr*

for attributes that have a value associated with them.

The attributes `&redef` `&add_func` and `&delete_func`, pertain to
redefining variables; they are discussed in :ref:`Refinement <#Refinement>`.

The attributes `&default`, `&create_expire`, `&read_expire`,
`&write_expire`, and `&expire_func` are for use with table's and
set's. See :ref:`Table Attributes <#Table-Attributes>` for discussion.

The attribute `&optional` specifies that a `record` field is
optional. See for discussion.

Finally, to specify multiple attributes, you do *not* separate them with
commas (doing so would actually make Bro's grammar ambiguous), but just
list them one after another. For example:

::

             global a: table[port] of string &redef &default="missing";

.. Previous: \ :ref:`Attributes <#Attributes>`, Up: \ `Variables
.. Overview <#Variables-Overview>`_

.. _#Refinement:

Refinement
^^^^^^^^^^^^^^^^

To do: &redef &add func &delete func


