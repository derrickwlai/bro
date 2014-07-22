
.. Next: \ :ref:`Values <#Values>`,
.. Previous: \ :ref:`Introduction <#Introduction>`, Up: \ :ref:`Top <#Top>`

.. _#Getting-Started:

Getting Started
-----------------

This chapter gives an overview of how to get started with operating Bro:
*(i)* compiling it, *(ii)* running it interactively, on live network
traffic, and on recorded traces, *(iii)* how Bro locates the policy
files it should evaluate and how to modify them, *(iv)* the arguments
you can give it to control its operation, and *(v)* some helper
utilities also distributed with Bro that you'll often find handy.

.. Next: \ :ref:`Helper utilities <#Helper-utilities>`, Up: \ `Getting
.. Started <#Getting-Started>`_

.. _#Running-Bro:

Running Bro
~~~~~~~~~~~~~~~

This section discusses how to build and install Bro, running it
interactively (mostly useful for building up familiarity with the policy
language, not for traffic analysis), running it on live and recorded
network traffic, modifying Bro policy scripts, and the different
run-time flags.

.. Next: \ :ref:`Using Bro interactively <#Using-Bro-interactively>`,
.. Up: \ :ref:`Running Bro <#Running-Bro>`

.. _#Building-and-installing-Bro:

Building and installing Bro
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. Next: \ :ref:`Bro source code distribution <#Bro-source-code-distribution>`,
.. Up: \ :ref:`Building and installing Bro <#Building-and-installing-Bro>`

Supported platforms
'''''''''''''''''''''''''''

Bro builds on a number of types of Unix: *FreeBSD, Solaris, Linux*,
though not all versions. It does *not* build under non-Unix operating
systems such as Windows NT.

.. Next: \ :ref:`Installing Bro <#Installing-Bro>`, Previous: \ `Supported
.. platforms <#Supported-platforms>`_, Up: \ `Building and installing
.. Bro <#Building-and-installing-Bro>`_

The Bro source code distribution
''''''''''''''''''''''''''''''''''''''''

You can get the latest public release of Bro from the Bro web page,
`http://www.bro.org/ <http://www.bro.org/>`_. Bro is distributed
as a *gzip*'d Unix *tar* archive, which you can unpack using:

::

    gzcat tar-file | tar xf -

or, on some :Unix systems:

::

    tar zxf tar-file

This creates a subdirectory `+bro-+`\ *XXX*\ `+-+`\ *version*, where
*XXX* is a tag such as pub for public releases and priv for private
releases, and *version* reflects a version and possibly a subversion,
such as `0.8a20` for version *0.8* and subversion *a20*.

To build Bro, change to the Bro directory and enter:

::

    ./configure
     make

Bro configuration is described in the `User Manual <https://www.bro.org/sphinx/index.html>`_

.. Next: \ :ref:`Tuning BPF <#Tuning-BPF>`, Previous: \ `Bro source code
.. distribution <#Bro-source-code-distribution>`_, Up: \ `Building and
.. installing Bro <#Building-and-installing-Bro>`_

.. _#Installing-Bro:

Installing Bro
''''''''''''''''''''''

You install Bro by issuing:

::

    make install

.. Previous: \ :ref:`Installing Bro <#Installing-Bro>`, Up: \ `Building and
.. installing Bro <#Building-and-installing-Bro>`_

.. _#Tuning-BPF:

Tuning BPF
''''''''''''''''''

Bro is written using libpcap, the portable packet-capture library
available from `ftp://ftp.ee.lbl.gov/libpcap.tar.Z`. While *libpcap*
knows how to use a wide range of Unix packet filters, it far and away
performs most efficiently used in conjunction with the Berkeley Packet
Filter (BPF) and with BPF descendants (such as the Digital Unix packet
filter). Although BPF is available from
`ftp://ftp.ee.lbl.gov/bpf.tar.Z`, installing it involves modifying
your kernel, and perhaps requires significant porting work. However, it
comes as part of several operating systems, such as FreeBSD, NetBSD, and
OpenBSD.

For BPF systems, you should be aware of the following tuning and
configuration issues:

‘BPF kernel support’

You need to make sure that kernel support for BPF is enabled. In
addition, some systems default to configuring kernel support for only
one BPF device. This often proves to be a headache because it means you
cannot run more than one Bro at a time, nor can you run it at the same
time as

‘/dev/bpf devices’

Related to the previous item, on BPF systems access to the packet filter
is via special */dev/bpf* devices, such as */dev/bpf0*. Just as you need
to make sure that the kernel's configuration supports multiple BPF
devices, so to must you make sure that an equal number of device files
reside in */dev/*.

‘packet filter permissions’

On systems for which access to the packet filter is via the file system,
you should consider whether you want to only allow root access, or
instead create a Unix *group* for which you enable read access to the
device file(s). The latter allows you to run Bro as a user other than
root, which is *strongly recommended*!

‘large BPF buffers’

While running with BPF is often necessary for high performance, it's not
necessarily sufficient. By default, BPF programs use very modest kernel
buffers for storing packets, which leads to high context switch overhead
as the kernel very often has to deliver packets to the user-level Bro
process. Minimizing the overhead requires increasing the buffer sizes.
This can make a *large* difference!

Under FreeBSD, the configuration variable to increase is
`debug.bpf_bufsize`, which you can set via *sysctl*. We recommend
creating a script run at boot-up time that increases it from its small
default value to something on the order of 100 KB–2 MB, depending on how
fast (heavily loaded) is the link being monitored, and how much physical
memory the monitor machine has at its disposal.

*libpcap buffer size patch*: *Important note*: some versions of have
internal code that limits the maximum buffer size to 32 KB. For these
systems, you should apply the patch included in the Bro distribution in
the file `libpcap.patch`.

Finally, once you have increased the buffer sizes, you should *check*
that running Bro does indeed consume the amount of kernel memory you
expect. You can do this under FreeBSD using *vmstat -m* and searching in
the output for the summary of BPF memory. You should find that the
*MemUse* statistic goes up by twice the buffer size for every concurrent
Bro or tcpdump you run. (Providing that these programs have been recompiled
with the corrected *libpcap* noted above.) The reason the increase is
by twice the buffer size is because Bro uses double-buffering to avoid
dropping packets when the buffer fills up.

.. Next: \ :ref:`Specifying policy scripts <#Specifying-policy-scripts>`,
.. Previous: \ `Building and installing
.. Bro <#Building-and-installing-Bro>`_, Up: \ `Running
.. Bro <#Running-Bro>`_

.. _#Using-Bro-interactively:

Using Bro interactively
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Once you've built Bro, you can run it interactively to try out simple
facets of the policy language. Note that in this mode, Bro is *not*
reading network traffic, so you cannot do any traffic analysis; this
mode is simply to try out Bro language features.

You run Bro interactively by simply executing “bro” without any
arguments. It then reads from *stdin* and writes to *stdout*.

Try typing the following to it:

::

    print "hello, world";
    ^D *(i.e., end of file)*

(The end-of-file is critical to remember. It's also a bit annoying for
interactive evaluation, but reflects the fact that Bro is not actually
meant for interactive use, it simply works as a side-effect of Bro's
structure.)

Bro will respond by printing:

::

    hello, world

to *stdout* and exiting.

You can further declare variables and print expressions, for example:

::

    global a = telnet;
    print a, a > ftp;
    print www.microsoft.com;

will print

::

    23/tcp, T
    207.46.230.229, 207.46.230.219, 207.46.230.218

(FIXME: this example needs to be updated. Format has changed.)

where 23/tcp reflects the fact that telnet is a predefined variable
whose value is TCP port 23, which is larger than TCP port 21 (i.e.,
ftp); and the DNS name *www.microsoft.com* currently returns the above
three addresses.

You can also define functions:

::

    function top18bits(a: addr): addr
        {
        return mask_addr(a, 18);
        }
         
    print top18bits(128.3.211.7);

prints

::

    128.3.192.0

and even event handlers:

::

    event bro_done()
        {
        print "all done!";
        }

which prints “all done!” when Bro exits.

.. Next: \ `Running Bro on network
.. traffic <#Running-Bro-on-network-traffic>`_, Previous: \ `Using Bro
.. interactively <#Using-Bro-interactively>`_, Up: \ `Running
.. Bro <#Running-Bro>`_

.. _#Specifying-policy-scripts:

Specifying policy scripts
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Usually, rather than running Bro interactively you want it to execute a
policy script or a set of policy scripts. You do so by specifying the
names of the scripts as command-line arguments, such as:

::

    bro ~/my-policy.bro ~/my-additional-policy.bro

Bro provides several mechanisms for simplifying how you specify which
policies to run.

First, if a policy file doesn't exist then it will try again using .bro
as a suffix, so the above could be specified as:

::

    bro ~/my-policy ~/my-additional-policy

Second, Bro consults the colon-separated search path to locate policy
scripts. If your home directory was listed in $BROPATH, then you could
have invoked it above using:

::

     bro my-policy my-additional-policy

*Note:* If you define $BROPATH, you *must* include *bro-dir*/policy,
where *bro-dir* is where you have built or installed Bro, because it has
to be able to locate *bro-dir*/policy/bro.init to initialize itself at
run-time.

Third, the `@load` directive can be used in a policy script to
indicate the Bro should at that point process another policy script
(like C's include directive; see ). So you could have in *my-policy*:

::

     @load my-additional-policy

and then just invoke Bro using:

::

     bro my-policy

providing you *always* want to load *my-additional-policy* whenever you
load *my-policy*.

Note that the predefined Bro module `brolite` loads almost all of the
other standard Bro analyzers, so you can pull them in with simply:

::

     @load brolite

or by invoking Bro using “bro brolite *my-policy*\ ”.

.. Next: \ :ref:`Modifying Bro policy <#Modifying-Bro-policy>`,
.. Previous: \ :ref:`Specifying policy scripts <#Specifying-policy-scripts>`,
.. Up: \ :ref:`Running Bro <#Running-Bro>`

Running Bro on network traffic
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

There are two ways to run Bro on network traffic: on traffic captured
live by the network interface(s), and on traffic previously recorded
using the `-w` flag of `tcpdump` or Bro itself.

.. Next: \ :ref:`Traffic traces <#Traffic-traces>`, Up: \ `Running Bro on
.. network traffic <#Running-Bro-on-network-traffic>`_

.. _#Live-traffic:

Live traffic
''''''''''''''''''''

Bro reads live traffic from the local network interface whenever you
specify the `-i` flag. As mentioned below, you can specify multiple
instances to read from multiple interfaces simultaneously, however the
interfaces must all be of the same link type (e.g., you can't mix
reading from a Fast Ethernet with reading from an FDDI link, though you
can mix a 10 Mbps Ethernet interface with a 100 Mbps Ethernet).

In addition, Bro will read live traffic from the interface(s) listed in
the `interfaces` variable, *unless* you specify the `-r` flag (and
do not specify `-i`). So, for example, if your policy script contains:

::

    const interfaces += "sk0";
    const interfaces += "sk1";

then Bro will read from the *sk0* and *sk1* interfaces, and you don't
need to specify `-i`.

.. Previous: \ :ref:`Live traffic <#Live-traffic>`, Up: \ `Running Bro on
.. network traffic <#Running-Bro-on-network-traffic>`_

.. _#Traffic-traces:

Traffic traces
''''''''''''''''''''''

To run on recorded traffic, you use the `-r` flag to indicate the
trace file Bro should read. As with `-i`, you can use the flag
multiple times to read from multiple files; Bro will merge the packets
from the files into a single packet stream based on their timestamps.

The Bro distribution includes an example trace that you can try out,
*example.ftp-attack.trace*. If you invoke Bro using:

::

    bro -r example.ftp-attack.trace brolite

you'll see that it generates a connection summary to *stdout*, a summary
of the FTP sessions to ftp.example, a copy of what would have been
real-time alarms had Bro been running on live traffic to
`alarm.example`, and a summary of unusual traffic anomalies (none in
this trace) to `weird.example`.

.. Next: \ `Bro flags and run-time
.. environment <#Bro-flags-and-run_002dtime-environment>`_,
.. Previous: \ `Running Bro on network
.. traffic <#Running-Bro-on-network-traffic>`_, Up: \ `Running
.. Bro <#Running-Bro>`_

.. _#Modifying-Bro-policy:

Modifying Bro policy
^^^^^^^^^^^^^^^^^^^^^^^^^^

One way to alter the policy Bro executes is of course to directly edit
the scripts. When this can be avoided, however, that is preferred, and
Bro provides a pair of related mechanisms to help you specify
*refinements* to existing policies in separate files.

The first such mechanism is that you can define *multiple* handlers for
a given event. So, for example, even though the standard ftp analyzer
(*bro-dir*\ `/policy/ftp.bro`) defines a handler for `ftp.request`,
you can define another handler if you wish in your own policy script,
even if that policy script loads (perhaps indirectly, via the
`brolite` module) the `ftp` analyzer. When the event engine
generates an ftp\_request event, *both* handlers will be invoked.

*Deficiency: Presently, you do not have control over the order in which
they are invoked; you also cannot completely override one handler with
another, preventing the first from being invoked.*

Second, the standard policy scripts are often written in terms of
*redefinable* variables. For example, `ftp.bro` contains a variable
`ftp_guest_ids` that defines a list of usernames the analyzer will
consider to reflect guest accounts:

::

    const ftp_guest_ids = { "anonymous", "ftp", "guest", } &redef;

While “\ `const`\ ” marks this variables as constant at run-time, the
attribute “\ `&redef`\ ” specifies that its value can be redefined.

For example, in your own script you could have:

::

    redef ftp_guest_ids = { "anonymous", "guest", "visitor", "student" };

instead. (Note the use of “redef” rather than “const”, to indicate that
you realize you are redefining an existing variable.)

In addition, for most types of variables you can specify *incremental*
changes to the variable, either new elements to add or old ones to
subtract. For example, you could instead express the above as:

::

    redef ftp_guest_ids += { "visitor", "student" };
    redef ftp_guest_ids -= "ftp";

The potential advantage of incremental refinements such as these are
that if any *other* changes are made to ftp.bro's original definition,
your script will automatically inherit them, rather than replacing them
if you used the first definition above (which explicitly lists all four
names to include in the variable). Sometimes, however, you don't want
this form of inheriting later changes; you need to decide on a
case-by-case basis, though our experience is that generally the
incremental approach works best.

Finally, the use of *prefixes* provides a way to specify a whole set of
policy scripts to load in a particular context. For example, if you set
`$BRO_PREFIXES` to “dialup”, then a load of `ftp.bro` will *also*
load dialup.ftp.bro automatically (if it exists). See :ref:`Run-time
environment <#Run_002dtime-environment>` for further discussion.

.. Previous: \ :ref:`Modifying Bro policy <#Modifying-Bro-policy>`,
.. Up: \ :ref:`Running Bro <#Running-Bro>`

Bro flags and run-time environment
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. Next: \ :ref:`Run-time environment <#Run_002dtime-environment>`, Up: \ `Bro
.. flags and run-time
.. environment <#Bro-flags-and-run_002dtime-environment>`_

.. _#Flags:

Flags
'''''''''''''

When invoking Bro, you can control its behavior using a large number of
flags and arguments. Most options can be specified using either a more
readable long version (starting with two dashes), or a more compact but
sometimes less intuitive short version (single dash followed by a single
letter). Arguments can be provided after whitespace (i.e., “-r
file.pcap” or “--readfile file.pcap”) and also using an equation mark
when the long version is used (i.e., “--readfile=file.pcap”).
Single-letter flags without arguments can be combined into a single
option element (i.e., “-dWF” is the same as “-d -W -F”).

‘\ `-d|--debug-policy`\ ’

Activates policy file debugging. See :ref:`Interactive
Debugger <#Interactive-Debugger>` for details.

.. TODO_LINK: 9 Interactive Debugger

‘\ `-e|--exec <Bro statements>`\ ’

Adds the given Bro policy statements to the loaded policy. Use for
manual :ref:`refinement <#Refinement>`, or for verifying the resulting value
of a given variable. Note that you can omit trailing semi-colons.

.. TODO_LINK: 5.1.7 Refinement 

‘\ `-f|--filter filter`\ ’

Use *filter* as the tcpdump filter for capturing packets, rather than
the combination of and `restrict_filter`, or the default of “tcp or
udp” .

‘\ `-h|--help|-?`\ ’

Generate a help message summarizing Bro's options and environment
variables, and exit.

‘\ `-g|--dump-config`\ ’

Writes out the current configuration into the persistent state directory
configured through the `state_dir` variable, defined in
:ref:`bro.init <#Bro-init-file>` and subject to :ref:`refinement <#Refinement>`.

.. TODO_LINK: 10.18 Bro init file 

.. TODO_LINK: 5.1.7 Refinement 


‘\ `-i|--iface <interface>`\ ’

Add *interface* to the list of interfaces from which Bro should read
:ref:`network traffic <#Live-traffic>`. You can use this flag multiple times
to direct Bro to read from multiple interfaces. You can also, or in
addition, use refinements of the variable to specify interfaces.

.. TODO_LINK: 2.1.4.1 Live traffic    

Note that if no interfaces are specified, then Bro will not read any
network traffic. It does *not* have a notion of a “default” interface
from which to read.

‘\ `-p|--prefix <prefix>`\ ’

Add *prefix* to the list of prefixes searched by Bro when loading a
script. You can also, or in addition, use *prefix* to specify search
prefixes. See :ref:`prefixes <#use-of-prefixes>` for discussion.

‘\ `-r|--readfile <readfile>`\ ’

Add *readfile* to the list of tcpdump save files that Bro should read.
You can use this flag multiple times to direct Bro to read from multiple
save files; it will merge the packets read from the different files
based on their timestamps. Note that if the save files contain only
packet headers and not contents, then of course Bro's analysis of them
will be limited.

Note that use of `-r` is *mutually exclusive* with use of `-i`.
However, you can use `-r` when running scripts that refine
`interfaces`, in which case the -r option takes precedence and Bro
performs off-line analysis.

‘\ `-s|--rulefile <signaturefile>`\ ’

Add *signaturefile* to the list of files containing signatures to match
against the network traffic. See :ref:`Signatures <#Signatures>` for more
information.

‘\ `-t|--tracefile <tracefile>`\ ’

Enables tracing of Bro script execution. See :ref:`Execution
tracing <#Execution-tracing>`.

‘\ `-w|--writefile <writefile>`\ ’

Write a tcpdump save file to the file *writefile*. Bro will record all
of the packets it captures, including their contents, except as
controlled by calls to set\_record\_packets. *Note:* One exception is
that unless you are analyzing HTTP events (for example, by loading the
ref\ `http` analyzer), Bro does *not* record the *contents* of HTTP
SYN/FIN/RST packets to the trace file. The reason for this is that HTTP
FIN packets often contain a large amount of data, which is not of any
interest if you are not using HTTP analysis, and due to the very high
volume of HTTP traffic at many sites, removing this data can
significantly reduce the size of the save file. *Deficiency: Clearly,
this should not be hardwired into Bro but under user control.*

Save files written using `-w` are of course readable using `-r`.
Accordingly, you will generally want to use `-w` when running Bro on
live network traffic so you can rerun it off-line later to understand
any problems that arise, and also to experiment with the effects of
changes to the policy scripts.

You can also combine `-r` with `-w` to both read a save file(s) and
write another. This is of interest when using multiple instances of
`-r`, as it provides a way to merge tcpdump save files.

‘\ `-v|--version`\ ’

Print the version of Bro and exit.

‘\ `-x|--print-state <Bro state file>`\ ’

Reads the contents of the specified Bro state file, prints them to the
console, and exits.

‘\ `-z|--analyze <analysis>`\ ’

Runs the specified analyzer over the configured policy. See :ref:`Policy
analyzers <#Policy-analyzers>`.

‘\ `-A|--transfile <writefile>`\ ’

Write transformed trace to the tcpdump file given. See :ref:`Trace
rewriting <#Trace-rewriting>`.

‘\ `-C|--no-checksums`\ ’

Incorrect IP, TCP, or UDP checksums normally trigger different variants
of `net_weird` and `conn_weird` events (see also :ref:`Events handled by
net\_weird <#Events-handled-by-net_005fweird>`, :ref:`Events handled by
conn\_weird <#Events-handled-by-conn_005fweird>`, and :ref:`weird
variables <#weird-variables>`). This flag causes Bro to ignore
incorrect checksums.

‘\ `-D|--dfa-size <size>`\ ’

Sets the cache size of deterministic finite automata (used extensively
for :ref:`signatures <#Signatures>`) to the given number of entries. The
default is 10,000.

‘\ `-F|--force-dns`\ ’

Instructs Bro that it *must* resolve all hostnames out of its private
DNS cache. If the script refers to a hostname not in the cache, then Bro
*exits* with a fatal error.

The point behind this option is to ensure that Bro starts quickly,
rather than possibly stalling for an undetermined amount of time
resolving a hostname. Fast startup simplifies checkpointing a running
Bro—you can start up a new Bro and then killing off the old one shortly
after. You'd like this to occur in a manner such that there's no period
during which neither Bro is watching the network (the older because you
killed it off too early, the newer because it's stuck resolving
hostnames).

‘\ `-I|--print-id <name>`\ ’

Looks up the variable identified by “name” in the global scope (see
:ref:`Scope <#Scope>`) and prints it to the console.

‘\ `-K|--md5-hashkey <hashkey>`\ ’

Allows you to specify a fixed seed for MD5 initialization. MD5 is used
by default for hashing elements in the Bro core, and by default some
randomness is gathered at Bro startup before PRNG initialization.

*Note: This means that by default repeated runs of Bro on identical
inputs do*\ **not**\ *necessarily yield identical output. If you want to
ensure determinism, use
the*\ `--save-seeds`\ *and*\ `--load-seeds`\ *options.*

‘\ `-L|--rule-benchmark`\ ’

XXX
See :ref:`Rule benchmarking <#Rule-benchmarking>`.

‘\ `-O|--optimize`\ ’

Turns on Bro's optimizer for improving its internal representation of
the policy script. *Note:* Currently, the amount of improvement is
modest, and there's (as always) a risk of an optimizer bug introducing
errors into the execution of the script, so the optimizer is not enabled
by default.

‘\ `-P|--prime-dns`\ ’

Instructs Bro to *prime* its private DNS cache. It does so by parsing
the policy scripts, but not executing them. Bro looks up each hostname's
address(es) and records them in the private cache. The idea is that once
bro -P finishes, you can then use bro -F to start up Bro quickly because
it will read all the information it needs from the cache.

‘\ `-S|--debug-rules`\ ’

Prints debugging output for the rules used in signature matching. See
also :ref:`Signatures <#Signatures>`.

‘\ `-T|--re-level <level>`\ ’

Sets the level in the tree of rules at which regular expressions are
built. Default is 4.

‘\ `-W|--watchdog`\ ’

Instructs Bro to activate its internal *watchdog*. The watchdog provides
self-monitoring to enable Bro to detect if its processing is wedged.

Bro only activates the watchdog if it is reading live network traffic.
The watchdog consists of a periodic timer that fires every
`WATCHDOG_INTERVAL` seconds. (*Deficiency:clearly this should be a
user-definable value.*) At that point, the watchdog checks to see
whether Bro is still working on the same packet as it was the last time
the watchdog expired. If so, then the watchdog logs this fact along with
some information regarding when Bro began processing the current packet
and how many events it processed after handling the packet. Finally, it
prints the packet drop information for the different interfaces Bro was
reading from, and aborts execution.

‘\ `--save-seeds <file>`\ ’

Writes the seeds used for initializing the PRNGs in Bro to the given
file. This can be combined with `-K|--md5-hashkey`, and is intended to
be used with `--load-seeds` in future Bro runs.

‘\ `--save-seeds <file>`\ ’

Seeds the PRNGs in Bro using a file produced by `--save-seeds` in an
earlier Bro invocation.

.. Previous: \ :ref:`Flags <#Flags>`, Up: \ `Bro flags and run-time
.. environment <#Bro-flags-and-run_002dtime-environment>`_

.. _#Run_002dtime-environment:

Run-time environment
''''''''''''''''''''''''''''

Bro is also sensitive to the following environment variables:

‘$BROPATH’

A colon-separated list of directories that Bro searches whenever you
load a policy file. It loads the first instance it finds (though see
$BRO\_PREFIXES for how a single load can lead to Bro loading multiple
files).

Default: if you don't set this variable, then Bro uses the path:

::

    .:policy:policy/local:/usr/local/lib/bro

That is, the current directory, any *policy/* and *policy/local/*
subdirectories, and */usr/local/lib/bro/*.

‘$BRO\_PREFIXES’

A colon-separate lists of *prefixes* that Bro should apply to each name
in a `@load` directive. For a given prefix and load-name, Bro
constructs the filename:

::

    *prefix*.\ *load-name*.bro

(where it doesn't add .bro if *load-name* already ends in .bro). It then
searches for the filename using $BROPATH and loads it if its found.
Furthermore, it *repeats* this process for all of the other prefixes
(left-to-right), and loads *each* file it finds for the different
prefixes. *Note:* Bro *also* first attempts to load the filename without
any prefix at all. If this load fails, then Bro exits with an error
complaining that it can't open the given `@load` file.

For example, if you set $BRO\_PREFIXES to:

::

    mysite:mysite.wan

and then issue “@load ftp”, Bro will attempt to load each of the
following scripts in the following order:

::

    ftp.bro
    mysite.ftp.bro
    mysite.wan.ftp.bro

Default: if you don't specify a value for $BRO\_PREFIXES, it defaults to
empty, and for the example above Bro would only attempt to @load
ftp.bro.

.. Previous: \ :ref:`Running Bro <#Running-Bro>`, Up: \ `Getting
.. Started <#Getting-Started>`_

.. _helper-utilities:

.. _#Helper-utilities:

Helper utilities
~~~~~~~~~~~~~~~~~~~~

.. Next: \ :ref:`hf utility <#hf-utility>`, Up: \ `Helper
.. utilities <#Helper-utilities>`_

.. _#Scripts:

Scripts
^^^^^^^^^^^^^

Documentation missing.

.. Next: \ :ref:`cf utility <#cf-utility>`, Previous: \ :ref:`Scripts <#Scripts>`,
.. Up: \ :ref:`Helper utilities <#Helper-utilities>`

The hf utility
^^^^^^^^^^^^^^^^^^^^^^^^

The *hf* utility reads text on *stdin* and attempts to convert any
“dotted quads” it sees to hostnames. It is very convenient for running
on Bro log files to generate human-readable forms. See the manual page
included with the distribution for details.

.. Previous: \ :ref:`hf utility <#hf-utility>`, Up: \ `Helper
.. utilities <#Helper-utilities>`_

The cf utility
^^^^^^^^^^^^^^^^^^^^^^^^

The *cf* utility reads Unix timestamps at the beginning of lines on
*stdin* and converts them to human-readable form. For example, for the
input line:

::

    972499885.784104 #26 131.243.70.68/1899 > 64.55.26.206/ftp start

it will generate:

::

    Oct 25 11:51:25 #26 131.243.70.68/1899 > 64.55.26.206/ftp start

It takes two flags:

‘-l’

specifies the *long* human-readable form, which includes the year. For
example, on the above input, the output would instead be:

::

    Oct 25 11:51:25 2000 #26 131.243.70.68/1899 > 64.55.26.206/ftp start

‘-s’

specifies *strict* checking to ensure that the number at the beginning
of a line is a plausible timestamp: it must have at least 9 digits, at
most one decimal, and must have a decimal if there are 10 or more
digits.

Without -s, an input like:

::

    131.243.70.68 > 64.55.26.206

generates the output:

::

    Dec 31 16:02:11 > 64.55.26.206

which, needless to say, is not very helpful.

*Deficiency: It seems clear that -s should be the default behavior.*


