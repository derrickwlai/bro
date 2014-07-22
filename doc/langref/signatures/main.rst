.. Next: \ :ref:`Interactive Debugger <#Interactive-Debugger>`,
.. Previous: \ :ref:`Analyzers and Events <#Analyzers-and-Events>`,
.. Up: \ :ref:`Top <#Top>`

.. _#Signatures:

Signatures
------------

.. Next: \ :ref:`Signature language <#Signature-language>`,
.. Up: \ :ref:`Signatures <#Signatures>`

.. _#Overview:

Overview
~~~~~~~~~~~~

In addition to the policy language, Bro provides another language which
is specifically designed to define *signatures*. Signatures precisely
describe how network traffic looks for certain, well-known attacks. As
soon as a attack described by a signature is recognized, Bro may
generate an event for this *signature match* which can then be analyzed
by a policy script. To define signatures, Bro's language provides
several powerful constructs like regular expressions and dependencies
between multiple signatures.

Signatures are independent of Bro's policy scripts and, therefore, are
put into their own file(s). There two ways to specify which files
contain signatures: By using the `-s` flag when you invoke Bro, or by
extending the Bro variable `signatures_files` using the `+=`
operator. If a signature file is given without a path, it is searched
along . The default extension of the file name is `.sig` which Bro
appends automatically.

.. Next: \ :ref:`snort2bro <#snort2bro>`, Previous: \ :ref:`Overview <#Overview>`,
.. Up: \ :ref:`Signatures <#Signatures>`

.. _#Signature-language:

Signature language
~~~~~~~~~~~~~~~~~~~~~~

Each individual signature has the format

    `signature `\ *id*\ ` { `\ *attribute-set*\ ` } `

`id` is an unique label for the signature. There are two types of
attributes: *conditions* and *actions*. The conditions define *when* the
signature matches, while the actions declare *what to do* in the case of
a match. Conditions can be further divided into four types: *header*,
*content*, *dependency*, and *context*. We will discuss these in more
detail in the following subsections.

This is an example of a signature:

::

         signature formmail-cve-1999-0172 {
           ip-proto == tcp
           dst-ip == 1.2.0.0/16
           dst-port = 80
           http /.*formmail.*\?.*recipient=[^&]*[;|]/
           event "formmail shell command"
           }

.. Next: \ :ref:`Actions <#Actions>`, Up: \ `Signature
.. language <#Signature-language>`_

.. _#Conditions:

Conditions
^^^^^^^^^^^^^^^^

.. Next: \ :ref:`Content conditions <#Content-conditions>`,
.. Up: \ :ref:`Conditions <#Conditions>`

.. _#Header-conditions:

Header conditions
'''''''''''''''''''''''''

Header conditions limit the applicability of the signature to a subset
of traffic that contains matching packet headers. For TCP, this match is
performed only for the first packet of a connection. For other
protocols, it is done on each individual packet. There are pre-defined
header conditions for some of the most used header fields:

‘\ *address-list*\'

Destination address of IP packet (may include CIDR masks for specifying
networks)

‘\ *integer-list*\'

Destination port of TCP or UDP packet

‘\ *protocol-list*\'

IP protocol; *protocol* may be `tcp`, `udp`, or `icmp`.

‘\ *address-list*\'

Source address of IP packet (may include CIDR masks for specifying
networks)

‘\ *integer-list*\'

Source port of TCP or UDP packet

*comp* is one of `==`, `!=`, `<`, `<=`, `>`, `>=`. All lists
are comma-separated values of the given type which are sequentially
compared against the corresponding header field. If at least one of the
comparisons evaluates to true, the whole header condition matches
(exception: if *comp* is `!=`, the header condition only matches if
*all* values differ). *address* is an dotted IP address optionally
followed by a CIDR/mask to define a subnet instead of an individual
address. *protocol* is either one of `ip`, `tcp`, `udp` and
`icmp`, or an integer.

In addition to this pre-defined short-cuts, a general header condition
can be defined either as

    `header `\ *proto*\ `[`\ *offset*\ `:`\ *size*\ `]`\ *comp*
    *value-list*

or as

    `header `\ *proto*\ `[`\ *offset*\ `:`\ *size*\ `] &`\ *integer* *comp* *value-list*

This compares the value found at the given position of the packet header
with a list of values. *offset* defines the position of the value within
the header of the protocol defined by *proto* (which can `ip`,
`tcp`, `udp` or `icmp`). *size* is either 1, 2, or 4 and specifies
the value to have a size of this many bytes. If the optimal
`& `\ *integer* is given, the packet's value is first masked with the
*integer* before it is compared to the value-list. *comp* is one of
`==`, `!=`, `<`, `<=`, `>`, `>=`. *value-list* is a list of
comma-separated integers similar to those described above. The integers
within the list may be followed by an additional `/`\ *mask* where
*mask* is a value from 0 to 32. This corresponds to the CIDR notation
for netmasks and is translated into a corresponding bitmask which is
applied to the packet's value prior to the comparison (similar to the
optional `&`\ *integer*).

Putting all together, this is an example which is equivalent to
`dst-ip == 1.2.3.4/16, 5.6.7.8/24`:

    `header ip[16:4] == 1.2.3.4/16, 5.6.7.8/24`

.. Next: \ :ref:`Dependency conditions <#Dependency-conditions>`,
.. Previous: \ :ref:`Header conditions <#Header-conditions>`,
.. Up: \ :ref:`Conditions <#Conditions>`

.. _#Content-conditions:

Content conditions
''''''''''''''''''''''''''

Content conditions are defined by regular expressions. We differentiate
two kinds of content conditions: first, the expression may be declared
with the `payload` statement, in which case it is matched against the
raw payload of a connection (for reassembled TCP streams) or of a each
packet. Alternatively, it may be prefixed with an analyzer-specific
label, in which case the expression is matched against the data as
extracted by the corresponding analyzer.

A `payload` condition has the form

    `payload /`\ *regular expression*\ `/`

Currently, the following analyzer-specific content conditions are
defined (note that the corresponding analyzer has to be activated by
loading its policy script):

‘\ `http-request`\ */regular expression/*\'

The regular expression is matched against decoded URIs of the HTTP
requests.

‘\ `http-request-header`\ */regular expression/* ’

The regular expression is matched against client-side HTTP headers.

‘\ `http-reply-header`\ */regular expression/* ’

The regular expression is matched against server-side HTTP headers.

‘\ `ftp`\ */regular expression/* ’

The regular expression is matched against the command line input of FTP
sessions.

‘\ `finger`\ */regular expression/*\'

The regular expression is matched against the finger requests.

For example, `http /(etc/(passwd|shadow)/` matches any URI containing
either `etc/passwd` or `etc/shadow`.

.. Next: \ :ref:`Context conditions <#Context-conditions>`,
.. Previous: \ :ref:`Content conditions <#Content-conditions>`,
.. Up: \ :ref:`Conditions <#Conditions>`

.. _#Dependency-conditions:

Dependency conditions
'''''''''''''''''''''''''''''

To define dependencies between different signatures, there are two
conditions:

‘requires-signature [! *id*]’

Defines the current signature to match only if the signature given by
*id* matches for the same connection. Using \`\ `!`' negates the
condition: The current signature only matches if *id* does not match for
the same connection (this decision is necessarily deferred until the
connection terminates).

‘requires-reverse-signature [! *id*]’

Similar to `requires-signature`, but *id* has to match for the other
direction of the same connections than the current signature. This
allows to model the notion of requests and replies.

.. Previous: \ :ref:`Dependency conditions <#Dependency-conditions>`,
.. Up: \ :ref:`Conditions <#Conditions>`

.. _#Context-conditions:

Context conditions
''''''''''''''''''''''''''

Context conditions pass the match decision on to various other
components of Bro. They are only evaluated if all other conditions have
already matched. The following context conditions are defined:

‘\`eval`\ *policy function*\'

The given policy function is called and has to return a boolean
indicating the match result. The function has to be of the type
`function cond(state: signature_state): bool`. See
\\f{fig:signature-state} for the definition of `signature_state`.

::

              type signature_state: record {
                  id: string;          # ID of the signature
                  conn: connection;    # Current connection
                  is_orig: bool;       # True if current endpoint is originator
                  payload_size: count; # Payload size of the first pkt of curr. endpoint
                  };

**Figure 8.1: Definition of the `signature_state` record**

‘\ `ip-options`\'

Not implemented currently.

‘\`payload-size`\ *comp\_integer*\'

Compares the integer to the size of the payload of a packet. For
reassembled TCP streams, the integer is compared to the size of the
first in-order payload chunk. Note that the latter is not well defined.

‘\ `same-ip`\'

Evaluates to true if the source address of the IP packets equals its
destination address.

‘\`tcp-state`\ *state-list*\'

Poses restrictions on the current TCP state of the connection.
*state-list* is a comma-separated list of `established` (the three-way
handshake has already been performed), `originator` (the current data
is send by the originator of the connection), and `responder` (the
current data is send by the responder of the connection).

.. Previous: \ :ref:`Conditions <#Conditions>`, Up: \ `Signature
.. language <#Signature-language>`_

.. _#Actions:

Actions
^^^^^^^^^^^^^

Actions define what to do if a signature matches. Currently, there is
only one action defined: `event `\ *string* raises a
`signature_match` event. The event handler has the following type:

    `event signature_match(state: signature_state, msg: string, data: string)`

See \\f{fig:signature-state} for a description of `signature_state`.
The given string is passed as `msg`, and data is the current part of
the payload that has eventually lead to the signature match (this may be
empty for signatures without content conditions).

.. Previous: \ :ref:`Signature language <#Signature-language>`,
.. Up: \ :ref:`Signatures <#Signatures>`

.. _#snort2bro:

snort2bro
~~~~~~~~~~~~~

The open-source IDS Snort provides an extensive library of signatures.
The Python script {snort2bro} converts Snort's signature into Bro
signatures. Due to different internal architectures of Bro and Snort, it
is not always possible to keep the exact semantics of Snort's
signatures, but most of the time it works very well.

To convert Snort signatures into Bro's format, `snort2bro` needs a
workable Snort configuration file (`snort.cfg`) which, in particular,
defines the variables used in the Snort signatures (usually things like
`$EXTERNAL_NET` or `$HTTP_SERVERS`). The conversion is performed by
calling `snort2bro [-I `\ *dir*\ `] snort.cfg` where the directory
optionally given by `-I` contains the files imported by Snort's
`include` statement. The converted signature set is written to
standard output and may be redirected to a file. This file can then be
evaluated by Bro using the `-s` flag or the `signatures_files`
variable.

*Deficiency:*\ `snort2bro`\ *does not know about some of the newer
Snort signature options and ignores them (but it gives a warning).*

-
