.. Next: \ :ref:`Missing Documentation <#Missing-Documentation>`,
.. Previous: \ :ref:`Signatures <#Signatures>`, Up: \ :ref:`Top <#Top>`

.. _#Interactive-Debugger:

Interactive Debugger
----------------------

.. Next: \ :ref:`A Sample Session <#A-Sample-Session>`, Up: \ `Interactive
.. Debugger <#Interactive-Debugger>`_

Debugger Overview
~~~~~~~~~~~~~~~~~~~~~

Bro's interactive debugger is intended to aid in the development,
testing, and maintenance of policy scripts. The debugger's interface has
been modeled after the popular `gdb` debugger; the command syntax is
virtually identical. While at present the Bro debugger supports only a
small subset of `gdb`'s features, these were chosen to be the most
commonly used commands. Additional features beyond those of `gdb`,
such as wildcarding, have been added to specifically address needs
created by Bro policy scripts.

.. Next: \ :ref:`Usage <#Usage>`, Previous: \ `Debugger
.. Overview <#Debugger-Overview>`_, Up: \ `Interactive
.. Debugger <#Interactive-Debugger>`_

.. _#A-Sample-Session:

A Sample Session
~~~~~~~~~~~~~~~~~~~~

The transcript below should look very familiar to those familiar with
`gdb`. The debugger's command prompt accepts debugger commands; before
each prompt, the line of policy code that is next to be executed is
displayed.

First we activate the debugger with the `-d` command-line switch.

::

         bobcat:~/bro/bro$ ./bro -d -r slice.trace brolite
         Policy file debugging ON.
         In bro_init() at policy/ftp.bro:437
         437             have_FTP = T;

Next, we set a breakpoint in the `connection_finished` event handler
[reference this somehow]. A breakpoint causes the script's execution to
stop when it reaches the specified function. In this case, there are
many event handlers for the `connection_finished` event, so we are
given a choice.

::

         (Bro [0]) break connection_finished
         Setting breakpoint on connection_finished:
         
         There are multiple definitions of that event handler.
         Please choose one of the following options:
         [1] policy/conn.bro:268
         [2] policy/active.bro:14
         [3] policy/ftp.bro:413
         [4] policy/demux.bro:40
         [5] policy/login.bro:496
         [a] All of the above
         [n] None of the above
         Enter your choice: 1
         Breakpoint 1 set at connection_finished at policy/conn.bro:268

Now we resume execution; when the breakpoint is reached, execution stops
and the debugger prompt returns.

::

         (Bro [1]) continue
         Continuing.
         Breakpoint 1, connection_finished(c = '[id=[orig_h=1.0.0.163,
         orig_p=2048/tcp, resp_h=1.0.0.6, resp_p=23/tcp], orig=[size=0,
         state=5], resp=[size=46, state=5], start_time=929729696.316166,
         duration=0.0773319005966187, service=, addl=, hot=0]') at
         policy/conn.bro:268
         In connection_finished(c = '[id=[orig_h=1.0.0.163, orig_p=2048/tcp,
         resp_h=1.0.0.6, resp_p=23/tcp], orig=[size=0, state=5], resp=[size=46,
         state=5], start_time=929729696.316166, duration=0.0773319005966187,
         service=, addl=, hot=0]') at policy/conn.bro:268
         268             if ( c$orig$size == 0 || c$resp$size == 0 )

We now step through a few lines of code and into the
`record_connection` call.

::

         (Bro [2]) step
         274             record_connection(c, "finished");
         (Bro [3]) step
         In record_connection(c = '[id=[orig_h=1.0.0.163, orig_p=2048/tcp,
         resp_h=1.0.0.6, resp_p=23/tcp], orig=[size=0, state=5], resp=[size=46,
         state=5], start_time=929729696.316166, duration=0.0773319005966187,
         service=, addl=, hot=0]', disposition = 'finished') at
         policy/conn.bro:162
         162             local id = c$id;
         (Bro [4]) step
         163             local local_init = to_net(id$orig_h) in local_nets;

We now print the value of the `id` variable, which was set in the
previously executed statement `local id = c$id;`. We follow that with
a backtrace (`bt`) call, which prints a trace of the
currently-executing functions and event handlers (along with their
actual arguments). We then remove the breakpoint and continue execution
to its end (the remaining output has been trimmed off).

::

         (Bro [5]) print id
         [orig_h=1.0.0.163, orig_p=2048/tcp, resp_h=1.0.0.6, resp_p=23/tcp]
         (Bro [6]) bt
         #0 In record_connection(c = '[id=[orig_h=1.0.0.163, orig_p=2048/tcp,
          resp_h=1.0.0.6, resp_p=23/tcp], orig=[size=0, state=5],
          resp=[size=46, state=5], start_time=929729696.316166,
          duration=0.0773319005966187, service=, addl=, hot=0]', disposition =
          'finished') at policy/conn.bro:163
         #1 In connection_finished(c = '[id=[orig_h=1.0.0.163, orig_p=2048/tcp,
          resp_h=1.0.0.6, resp_p=23/tcp], orig=[size=0, state=5],
          resp=[size=46, state=5], start_time=929729696.316166,
          duration=0.0773319005966187, service=, addl=, hot=0]') at
          policy/conn.bro:274
         (Bro [7]) delete
         Breakpoint 1 deleted
         (Bro [8]) continue
         Continuing.
         ...

.. Next: \ :ref:`Notes and Limitations <#Notes-and-Limitations>`,
.. Previous: \ :ref:`A Sample Session <#A-Sample-Session>`, Up: \ `Interactive
.. Debugger <#Interactive-Debugger>`_

.. _#Usage:

Usage
~~~~~~~~~

The Bro debugger is invoked with the `-d` command-line switch. It is
strongly recommended that the debugger be used with a tcpdump capture
file as input (the `-r` switch) rather than in “live” mode, so that
results are repeatable.

Execution tracing is a feature which generates a complete record of
which code statements are executed during a given run. It is enabled
with the `-t` switch, whose argument specifies a file which will
contain the trace.

Debugger commands all are a single word, though many of them take
additional arguments. Commands may be abbreviated with a prefix (e.g.,
`fin` for `finish`); if the same prefix matches multiple commands,
the debugger will list all that match. Certain very frequently-used
commands, such as `next`, have been given specific one-character
shortcuts (in this case, `n`). For more details on all the debugger
commands, see the Reference in section :ref:`Reference <#Reference>`, below.

The debugger's prompt can be activated in three ways. First, when the
`-d` switch is supplied, Bro stops in the `bro_init` initialization
function (more precisely, after global-scope code has been executed; see
section :ref:`Notes and Limitations <#Notes-and-Limitations>`). It is also
activated when a breakpoint is hit. Breakpoints are set with the
`break` command (see the Reference). The final way to invoke the
debugger's prompt is to interrupt execution by pressing Ctrl-C (sending
an Interrupt signal to the process). Execution will be suspended after
the currently-executing line is completed.

.. Next: \ :ref:`Reference <#Reference>`, Previous: \ :ref:`Usage <#Usage>`,
.. Up: \ :ref:`Interactive Debugger <#Interactive-Debugger>`

.. _#Notes-and-Limitations:

Notes and Limitations
~~~~~~~~~~~~~~~~~~~~~~~~~

-  Statements at global scope, i.e., those executed before the
   `bro_init` function, may not be debugged at present. This is
   because those statements load declarations for other functions needed
   for the debugger to function properly.

.. Previous: \ :ref:`Notes and Limitations <#Notes-and-Limitations>`,
.. Up: \ :ref:`Interactive Debugger <#Interactive-Debugger>`

.. _#Reference:

Reference
~~~~~~~~~~~~~

**large Summary of Commands** Note: all commands may be abbreviated with
a unique prefix. Shortcuts below are special exceptions to this rule.

+---------------+----------------+----------------------------------------------------------------+
| **Command**   | **Shortcut**   | **Description**                                                |
+---------------+----------------+----------------------------------------------------------------+
| help          |                | Get help with debugger commands                                |
+---------------+----------------+----------------------------------------------------------------+
| quit          |                | Exit Bro                                                       |
+---------------+----------------+----------------------------------------------------------------+
| next          | n              | Step to the following statement, skipping function calls       |
+---------------+----------------+----------------------------------------------------------------+
| step          | s              | Step to following statements, stepping in to function calls    |
+---------------+----------------+----------------------------------------------------------------+
| continue      | c              | Resume execution of the policy script                          |
+---------------+----------------+----------------------------------------------------------------+
| finish        |                | Run until the currently-executing function completes           |
+---------------+----------------+----------------------------------------------------------------+
| break         | b              | Set a breakpoint                                               |
+---------------+----------------+----------------------------------------------------------------+
| condition     |                | Set a condition on an existing breakpoint                      |
+---------------+----------------+----------------------------------------------------------------+
| delete        | d              | Delete the specified breakpoints; delete all if no arguments   |
+---------------+----------------+----------------------------------------------------------------+
| disable       |                | Turn off the specified breakpoint; do not delete permanently   |
+---------------+----------------+----------------------------------------------------------------+
| enable        |                | Undo a prior \`disable' command                                |
+---------------+----------------+----------------------------------------------------------------+
| info          |                | Get information about the debugging environment                |
+---------------+----------------+----------------------------------------------------------------+
| print         | p              | Evaluate an expression and print the result                    |
+---------------+----------------+----------------------------------------------------------------+
| set           |                | Alias for \`print'                                             |
+---------------+----------------+----------------------------------------------------------------+
| backtrace     | bt             | Print a stack trace                                            |
+---------------+----------------+----------------------------------------------------------------+
| frame         |                | Select frame number N                                          |
+---------------+----------------+----------------------------------------------------------------+
| up            |                | Select the stack frame one level up from the current one       |
+---------------+----------------+----------------------------------------------------------------+
| down          |                | Select the stack frame one level down from the current one     |
+---------------+----------------+----------------------------------------------------------------+
| list          | l              | Print source lines surrounding specified context               |
+---------------+----------------+----------------------------------------------------------------+
| trace         |                | Turn on or off execution tracing                               |
+---------------+----------------+----------------------------------------------------------------+

**Table 9.1: Debugger Commands**

**Getting Help**

‘help’

Help for each command may be invoked with the `help` command. Calling
the command with no arguments displays a one-line summary of each
command.

**Command-Line Options**

‘\ `-d` switch’

The `-d` switch enables the Bro script debugger.

‘\ `-t` switch’

The `-t` enables execution tracing. There is an argument to the
switch, which indicates a file that will contain the result of the
trace. Trace output consists of the source code lines executed, indented
for each nested function invocation.

**Example.** The following command invokes Bro, using `tcpdump_file`
for the input packets and outputting the result of the trace to
`execution_trace`.

::

                ./bro -t execution_trace -r tcpdump_file policy_script.bro

**Example.** If the argument to `-t` is a single dash character
(“\ `-`\ ”), then the trace output is sent to `stderr`.

::

                ./bro -t - -r tcpdump_file policy_script.bro

**Example.** Lastly, execution tracing may be combined with the
debugger. Here we send output to `stderr`, so it will be intermingled
with the debugger's output. Tracing may be turned off and on in the
debugger using the `trace` command.

::

                ./bro -d -t - -r tcpdump_file policy_script.bro

**Running the Script**

‘quit’

Exit Bro, aborting execution of the currently executing script.

‘restart (r)’

*(Currently Unimplemented)* Restart the execution of the script,
rewinding to the beginning of the input file(s), if appropriate.
Breakpoints and other debugger state are preserved.

‘continue (c)’

Resume execution of the script file. The script will continue running
until interrupted by a breakpoint or a signal.

‘next (n)’

Execute one statement, without entering any subroutines called in that
statement.

‘step (s)’

Execute one statement, but stop on entry to any called subroutine.

‘finish’

Run until the currently executing function returns.

**Breakpoints**

‘break (b)’

Set a breakpoint. A breakpoint suspend execution when execution reaches
a particular location and returns control to the debugger. Breakpoint
locations may be specified in a number of ways:

+---------------------------+----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
| `break`                   | With no argument, the current line is used.                                                                                                                                                                                                                                                                                                                    |
+---------------------------+----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
| `break` *[FILE:]LINE*     | The specified line in the specified file; if no policy file is specified, the current file is implied.                                                                                                                                                                                                                                                         |
+---------------------------+----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
| `break` *FUNCTION*        | The first line of the specified function or event handler. If more than one event handler matches the name, a choice will be presented.                                                                                                                                                                                                                        |
+---------------------------+----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
| `break` *WILDCARD*        | Similar to *FUNCTION*, but a POSIX-compliant regular expression (see the `regex(3)` man page )is supplied, which is matched against all functions and event handlers. One exception to the the POSIX syntax is that, as in the shell, the `*` character may be used to match zero or more of any character without a preceding period character (`.`).         |
+---------------------------+----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+

‘condition *N expression*\ ’

The numeric argument $N$ indicates which breakpoint to add a condition
to, and the expression is the conditional expression. A breakpoint with
a condition will only stop execution when the supplied condition is
true. The condition will be evaluated in the context of the breakpoint's
location when it is reached.

‘enable’

With no arguments, enable all breakpoints previously disabled with the
`disable` command. If numeric arguments separated by spaces are
provided, the breakpoints with those numbers will be enabled.

‘disable’

With no arguments, disable all breakpoints. Disabled breakpoints will
not stop execution, but will be retained to be enabled later. If numeric
arguments separated by spaces are provided, the breakpoints with those
numbers will be disabled.

‘delete (d)’

With no arguments, permanently delete all breakpoints. If numeric
arguments separated by spaces are provided, the breakpoints with those
numbers will be deleted.

**Debugger State**

‘\ **info**\ ’

Give information about the current script and debugging environment. A
subcommand should follow the `info` command to indicate which
information is desired. At present, the following subcommands are
available:

+------------------+-----------------------------------------+
| `info break`     | List all breakpoints and their status   |
+------------------+-----------------------------------------+

**Inspecting Program State**

‘print (p) / set’

The `print` command and its alias, `set`, are used to evaluate any
expression in the policy script language. The result of the evaluation
is printed out. Results of the evaluation affect the current execution
environment; expressions may include things like assignment. The
expression is evaluated in the context of the currently selected stack
frame. The `frame`, `up`, and `down` commands (below) are used to
change the currently selected frame, which defaults to the innermost
one.

‘backtrace (bt)’

Print a description of all the stack frames (function invocations) of
the currently executing script.\\ With no arguments, prints out the
currently selected stack frame.\\ With a numeric argument *+/- N*,
prints the innermost *N* frames if the argument is positive, or the
outermost $N$ frames if the argument is negative.

‘frame’

With no arguments, prints the currently selected frame. \\ With a
numeric argument $N$, selects frame $N$. Frame numbers are numbered
inside-out from 0; the

‘up’

Select the stack frame that called the currently selected one. If a
numeric argument $N$ is supplied, go up that many frames.

‘down’

Select the stack frame called by the currently selected one. If a
numeric argument $N$ is supplied, go down that many frames.

‘list (l)’

With no argument, print the ten lines of script source code following
the previous listing. If there was no previous listing, print ten lines
surrounding the next statement to be executed. If an argument is
supplied, ten lines are printed around the location it describes. The
argument may take one of the following forms:

*[FILE:]LINE* The specified line in the specified file; if no policy
file is specified, the current file is implied. \\ *FUNCTION* The first
line of the specified function or event handler. If more than one event
handler matches the name, a choice will be presented. \\ $\\pm N$ With a
numeric argument preceded by a plus or minus sign, the line at the
supplied offset from the previously selected line.


