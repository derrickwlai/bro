.. Next: \ :ref:`Global and Local Variables <#Global-and-Local-Variables>`,
.. Previous: \ :ref:`Values <#Values>`, Up: \ :ref:`Top <#Top>`

.. _#Statements-and-Expressions:

Statements and Expressions
----------------------------

You express Bro's analysis of network traffic using *event handlers*,
which, as discussed in XX, are essentially subroutines written in Bro's
policy scripting language. In this chapter we discuss the different
types of statements and expressions available for expressing event
handlers and the auxiliary functions they use.

.. Next: \ :ref:`Expressions <#Expressions>`, Up: \ `Statements and
.. Expressions <#Statements-and-Expressions>`_

.. _#Statements:

Statements
~~~~~~~~~~~~~~

Bro functions and event handlers are written in an imperative style, and
the statements available for doing so are similar to those provided in
C. As in C, statements are terminated with a semi-colon. There are no
restrictions on how many lines a statement can span. Whitespace can
appear between any of the syntactic components in a statement, and its
presence always serves as a separator (that is, a single syntactic
component cannot in general contain embedded whitespace, unless it is
escaped in some form, such as appearing inside a string literal).

Bro provides the following types of statements:

expression

    Syntax:

        *expr* ;

    As in C, an expression by itself can also be used as a statement.
    For example, assignments, calling functions, and scheduling timers
    are all expressions; they also are often used as statements.

print

    Syntax:

        print *file* *expr-list* ;

    The expressions are converted to a list of strings, which are then
    printed as a comma-separated list. If the first expression is of
    type `file`, then the other expressions are printed to the corresponding
    file; otherwise they're written to *stdout*.

    For control over how the strings are formatted, see the `fmt`
    function.

alarm

    Syntax:

        alarm *expr-list* ;

    The expressions are converted to a list of strings, which are then
    logged as a comma-separated list. “Logging” means recording the
    values to bro-alarm-file. In addition, if Bro is reading *live*
    network traffic (as opposed to from a trace file), then the messages
    are also reported via *syslog(3)* at level *LOG\_NOTICE*. If the
    message does not already include a timestamp, one is added.

    See the `alarm` module for a discussion of controlling logging
    behavior from your policy script. In particular, an important
    feature of the `alarm` statement is that prior to logging the
    giving string(s), Bro first invokes alarm-hook to determine whether
    to suppress the logging.

event

    Syntax:

        event *expr* ( *expr-list\** ) ;

    Evaluates *expr* to obtain an event handler and queues an event for
    it with the value corresponding to the optional comma-separated list
    of values given by *expr-list*.

    *Note:* `event` statements look syntactically just like function
    calls, other than the keyword “\ `event`\ ”. However,
    function-call-expr, while queueing an event is not, since it does
    not return a value.

if

    Syntax:

        if ( *expr* ) *stmt*

        if ( *expr* ) *stmt* else *stmt2*

    Evaluates *expr*, which must yield a bool value. If true, executes
    *stmt*. For the second form, if false, executes *stmt2*.

for

    Syntax:

        for ( *var* in *expr* ) *stmt*

    Iterates over the indices of *expr*, which must evaluate to either a
    `set` or a `table`. For each iteration, *var* is set to one of
    the indices and *stmt* is executed. *var* needn't have been
    previously declared (in which case its type is implicitly inferred
    from that of the indices of *expr*), and must not be a global
    variable.

    If *expr* is a `set`, then the indices correspond to the members
    of the set. If *expr* is a `table`, then they correspond to the
    indices of the table.

    *Deficiency: You can only use*\ `for`\ *statements to iterate over
    sets and tables with a single, non-compound index type. You can't
    iterate over multi-dimensional or compound indices.*

    *Deficiency: Bro lacks ways of controlling the order in which it
    iterates over the indices.*

next

    Syntax:

        next ;

    Only valid within a `for` statement. When executed, causes the
    loop to proceed to the next iteration value (i.e., the next index
    value).

break

    Syntax:

        break ;

    Only valid within a `for` statement. When executed, causes the
    loop to immediately exit.

return

    Syntax:

        return *expr* ;

    Immediately exits the current function or event handler. For a
    function, returns the value *expr* (which is omitted if the function
    does not return a value, or for event handlers).

add

    Syntax:

        add *expr1* *expr2* ;

    Adds the element specified by *expr2* to the set given by *expr1*.
    For example,

    ::

                 global active_hosts: set[addr, port];
                 ...
                 add active_hosts[1.44.33.7, 80/tcp];

    adds an element corresponding to the pair 1.44.33.7 and 80/tcp to
    the set active\_hosts.

delete

    Syntax:

        delete *expr1* [*expr2*\ ] ;

    Deletes the corresponding value, where *expr1* corresponds to a set
    or table, and *expr2* an element/index of the set/table. If the
    element is not in the set/table, does nothing.

compound

    Compound statements are formed from a list of (zero or more)
    statements enclosed in `{}`'s:

        { *statement\** }

null

    A lone:

        ;

    denotes an empty, do-nothing statement.

local,const

    Syntax:

        local *var* : *type* = *initialization* *attributes* ;

        const *var* : *type* = *initialization* *attributes* ;

    Declares a local variable with the given type, initialization, and
    attributes, all of which are optional. The syntax of these fields is
    the same as for global-vars. The second form likewise declares a
    local variable, but one which is *constant*: trying to assign a new
    value to it results in an error. *Deficiency:Currently,
    this*\ `const`\ *restriction isn't detected/enforced.*

    *Unlike with C* the scope of a local variable is from the point of
    declaration to the end of the encompassing function or event
    handler.

.. Previous: \ :ref:`Statements <#Statements>`, Up: \ `Statements and
.. Expressions <#Statements-and-Expressions>`_

.. _#Expressions:

Expressions
~~~~~~~~~~~~~~~

Expressions in Bro are very similar to those in C, with similar
precedence:

parenthesized

    Syntax:

        ( *expr* )

    Parentheses are used as usual to override precedence.

constant

    Any constant value is an expression.

variable

    The name of a *variable* is an expression.

clone

    Syntax:

        copy( *expr* )

    Produces a clone, or deep copy, of the value produced by the
    expression it is applied to.

increment,decrement

    Syntax:

        ++ *expr*

        -– *expr*

    Increments or decrements the given expression, which must correspond
    to an assignable value (variable, table element, or record element)
    and of a number type.

    Yields the value of the expression after the increment.

    *Unlike with C, these operators only are defined for
    “pre”-increment/decrement; there is no post-increment/decrement.*

negation

    Syntax:

        ! *expr*

        `-` *expr*

    Yields the boolean or arithmetic negation for values of boolean or
    *numeric* (or *interval*) types, respectively.

positivation

    Syntax:

        `+` *expr*

    Yields the value of *expr*, which must be of type *numeric* or
    *interval*.

    The point of this operator is to explicitly convert a value of type
    count to int. For example, suppose you want to declare a local
    variable code to be of type int, but initialized to the value 2. If
    you used:

    ::

                 local code = 2;

    then Bro's implicit typing would make it of type count, because
    that's the type of a numeric-constants. You could instead use:

    ::

                 local code = +2;

    to direct the type inferencing to instead assign a type of int to
    code. Or, of course, you could specify the type explicitly:

    ::

                 local code:int = 2;

arithmetic

    Syntax:

        *expr1* + *expr2*

        *expr1* - *expr2*

        *expr1* \* *expr2*

        *expr1* / *expr2*

        *expr1* % *expr2*

    The usual C arithmetic operators, defined for numeric types, except
    modulus (`%`) is only defined for integral types.

logical

    Syntax:

        *expr1* `&&` *expr2*

        *expr1* `||` *expr2*

    The usual C logical operators, defined for boolean types.

equality

    Syntax:

        *expr1* `==` *expr2* \\ *expr1* `"!=` *expr2*

    rel-operators, Compares two values for equality or inequality,
    yielding a `bool` value. Defined for all non-compound types except
    pattern.

relational

    Syntax:

        *expr1* `<` *expr2* \\ *expr1* `<=` *expr2* \\ *expr1* `>`

        *expr2* \\ *expr1* `>=` *expr2*

    Compares two values for magnitude ordering, yielding a bool value.
    Defined for values of type *numeric*, time, interval, port, or addr.

    *Note:* TCP port values are considered less than UDP port values.

    *Note:* IPv4 addr values less than IPv6 addr values.

    *Deficiency: Should also be defined at for*\ string\ *values.*

conditional

    Syntax:

        *expr1* ? *expr2* : *expr3*

    Evaluates *expr1* and, if true, evaluates and yields *expr2*,
    otherwise evaluates and yields *expr3*. *expr2* and *expr3* must
    have compatible types.

assignment

    Syntax:

        *expr1* = *expr2*

    Assigns the value of *expr2* to the storage defined by *expr1*,
    which must be an assignable value (variable, table element, or
    record element). Yields the assigned value.

function call

    Syntax:

        *expr1* ( *expr-list2* )

    Evaluates *expr1* to obtain a value of type `function`, which is
    then invoked with its arguments bound left-to-right to the values
    obtained from the comma-separated list of expressions *expr-list2*.
    Each element of *expr-list2* must be assignment-compatible with the
    corresponding formal argument in the type of *expr1*. The list may
    (and must) be empty if the function does not take any parameters.

anonymous function

    Syntax:

        function ( *parameters* ) *body*

    Defines an *anonymous function*, which, in abstract terms, is how
    you specify a constant of type `function`. *parameters* has the
    syntax of parameter declarations for functions, as does *body*,
    which is just a list of statements enclosed in braces.

    Anonymous functions can be used anywhere you'd usually instead use a
    function declared in the usual direct fashion. For example, consider
    the function:

    ::

                 function demo(msg: string): bool
                     {
                     if ( msg == "do the demo" )
                         {
                         print "got it";
                         return T;
                         }
                     else
                         return F;
                     }

    You could instead declare demo as a global variable of type
    `function`:

    ::

             global demo: function(msg: string): bool;

    and then later assign to it an anonymous function:

    ::

                 demo = function (msg: string): bool
                     {
                     if ( msg == "do the demo" )
                         {
                         print "got it";
                         return T;
                         }
                     else
                         return F;
                     };

    You can even call the anonymous function directly:

    ::

                 (function (msg: string): bool
                     {
                     if ( msg == "do the demo" )
                         {
                         print "got it";
                         return T;
                         }
                     else
                         return F;
                     })("do the demo")

    though to do so you need to enclose the function in parentheses to
    avoid confusing Bro's parser.

    One particularly handy form of anonymous function is that used for
    &default.

event scheduling

    Syntax:

        schedule *expr1* `{` *expr2* ( *expr-list3* ) `}`

    Evaluates *expr1* to obtain a value of type interval, and schedules
    the event given by *expr2* with parameters *expr-list3* for that
    time. Note that the expressions are all evaluated and bound at the
    time of execution of the schedule expression; evaluation is *not*
    deferred until the future execution of the event handler.

    For example, we could define the following event handler:

    ::

                 event once_in_a_blue_moon(moon_phase: interval)
                     {
                     print fmt("wow, a blue moon - phase %s", moon_phase);
                     }

    and then we could schedule delivery of the event for 6 hours from
    the present, with a moon\_phase of 12 days, using:

    ::

                 schedule +6 hr { once_in_a_blue_moon(12 days) };

    *Note: The syntax is admittedly a bit clunky. In particular, it's
    easy to (i) forget to include the braces (which are needed to avoid
    confusing Bro's parser), (ii) forget the final semi-colon if the
    schedule expression is being used as an expression-statement, or
    (iii) erroneously place a semi-colon after the event specification
    but before the closing brace.*

    Timer invocation is inexact. In general, Bro uses arriving packets
    to serve as its clock (when reading a trace file off-line, this is
    still the case—the timestamp of the latest packet read from the
    trace is used as the notion of “now”). Once this clock reaches or
    passes the time associated with a queued event, Bro will invoke the
    event handler, which is termed “expiring” the timer. (However, Bro
    will only invoke max-timer-expires timers per packet, and these
    include its own internal timers for managing connection state, so
    this can also delay invocation.)

    It will also expire all pending timers (whose time has not yet
    arrived) when Bro terminates; if you don't want those event handlers
    to activate in this instance, you need to test done-with-network.

    You would think that `schedule` should just be a statement like
    event-invocation is, rather than an expression. But it actually does
    return a value, of the undocumented type timer. In the future, Bro
    may provide mechanisms for manipulating such timers; for example, to
    cancel them if you no longer want them to expire.

index

    Syntax:

        *expr1* [ *expr-list2* ]

    Returns the sub-value of *expr1* indexed by the value of
    *expr-list2*, which must be compatible with the index type of
    *expr1*.

    *expr-list2* is a comma-separated list of expressions (with at least
    one expression listed) whose values are matched left-to-right
    against the index types of *expr1*.

    The only type of value that can be indexed in this fashion is a
    table. *Note:* set's cannot be indexed because they do not yield any
    value. Use `in` to test for set membership.

membership

    Syntax:

        *expr1* in *expr2*

        *expr1* !in *expr2*

    Yields true (false, respectively) if the index *expr1* is present in
    the `table` or `set` *expr2*.

    For example, if notice\_level is a table index by an address and
    yielding a count:

    ::

                 global notice_level: table[addr] of count;

    then we could test whether the address 127.0.0.1 is present using:

    ::

                 127.0.0.1 in notice_level

    For table's and set's indexed by multiple dimensions, you enclose
    *expr1* in brackets. For example, if we have:

    ::

                 global connection_seen: set[addr, addr];

    then we could test for the presence of the element indexed by
    8.1.14.2 and 129.186.0.77 using:

    ::

                 [8.1.14.2, 129.186.0.77] in connection_seen

    We can also instead use a corresponding record type. If we had

    ::

                 local t = [$x = 8.1.14.2, $y = 129.186.0.77]

    then we could test:

    ::

                 t in connection_seen

pattern matching

    Syntax:

        *expr1* == *expr2*

        *expr1* != *expr2*

        *expr1* in *expr2*

        *expr1* !in *expr2*

    As discussed for pattern values. the first two forms yield true
    (false) if the `pattern` *expr1* exactly matches the string
    *expr2*. (You can also list the `string` value on the left-hand
    side of the operator and the `pattern` on the right.)

    The second two forms yield true (false) if the pattern *expr1* is
    present within the string *expr2*. (For these, you *must* list the
    pattern as the left-hand operand.)

record field access

    Syntax:

        *expr* $ *field-name*

    Returns the given field *field-name* of the record *expr*. If the
    record does not contain the given field, a compile-time error
    results.

record constructor

    Syntax:

        [ *field-constructor-list* ]

    Constructs a `record` value. The *field-constructor-list* is a
    comma-separated list of individual field constructors, which have
    the syntax:

        $ *field-name* = *expr*

    For example,

    ::

                 [$foo = 3, $bar = 23/tcp]

    yields a `record` with two fields, `foo` of type `count` and
    `bar` of type `port`. The values used in the constructor needn't
    be constants, however; they can be any expression of an assignable
    type.

record field test

    Syntax:

        *expr* `?$` *field-name*

    Returns true if the given field has been set in the record yielded
    by *expr*. Note that *field-name* *must* correspond to one of the
    fields in the record type of *expr* (otherwise, the expression would
    always be false). The point of this operator is to test whether an
    *&optional* field of a record has been assigned to.

    For example, suppose we have:

    ::

                 type rap_sheet: record {
                     num_scans: count &optional;
                     first_activity: time;
                 };
                 global the_goods: table[addr] of rap_sheet;

    and we want to test whether the address held in the variable perp
    exists in the\_goods and, if so, whether num\_scans has been
    assigned to, then we could use:

    ::

                 perp in the_goods && the_goods[perp]?$num_scans


