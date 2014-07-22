.. Next: \ :ref:`Analyzers and Events <#Analyzers-and-Events>`,
.. Previous: \ :ref:`Global and Local Variables <#Global-and-Local-Variables>`,
.. Up: \ :ref:`Top <#Top>`

Predefined Variables and Functions
------------------------------------

.. Next: \ :ref:`Predefined Functions <#Predefined-Functions>`,
.. Up: \ `Predefined Variables and
.. Functions <#Predefined-Variables-and-Functions>`_

.. _#Predefined-Variables:

Predefined Variables
~~~~~~~~~~~~~~~~~~~~~~~~

Bro predefines and responds to the following variables, organized by the
policy file in which they are contained. Note that you will only be able
to access the variables in a policy file if you `load` it or a policy
file which loads it.

.. Next: \ :ref:`anonbro <#anonbro>`, Up: \ `Predefined
.. Variables <#Predefined-Variables>`_

active.bro
^^^^^^^^^^^^^^^^

`active_conn : table[conn_id] of connection`

    A table of `connection` records corresponding to all active
    connections.

.. Next: \ :ref:`backdoorbro <#backdoorbro>`,
.. Previous: \ :ref:`activebro <#activebro>`, Up: \ `Predefined
.. Variables <#Predefined-Variables>`_

anon.bro
^^^^^^^^^^^^^^

`anon_log : file`

    The file into which anonymization *Fixme: Add a reference to doc on
    anonymization when it is available.* IP address mappings are
    written.

`preserved_subnet : set[subnet]`

    Addresses in these subnet are preserved when anonymization is being
    performed. See also `preserved_net`. NOTE: The variable `const`.
    so may only be changed via `redef`.

`preserved_net : set[net]`

    These Class A/B/C nets are preserved when anonymization is being
    performed. See also `preserved_subnet`.

.. Next: \ :ref:`broinit <#broinit>`, Previous: \ :ref:`anonbro <#anonbro>`,
.. Up: \ :ref:`Predefined Variables <#Predefined-Variables>`

backdoor.bro
^^^^^^^^^^^^^^^^^^

`backdoor_log : file`

    The file into which logs for backdoor servers () are written.

`backdoor_min_num_lines : count`

    The number of lines of *Fixme: must be telnet?* input and output
    must be more than this amount to trigger backdoor checking.
    Note: This variable is `const`, so may only be changed via `redef`.

`backdoor_min_normal_line_ratio : double`

    If the fraction of “normal” (less than a certain length) lines is
    below this value, then backdoor checking is not performed.
    Note: This variable is `const`, so may only be changed via `redef`.

`backdoor_min_bytes : count`

    The total number of bytes transferred on the connection must be at
    least this large in order for backdoor checking to be performed.
    Note: This variable is `const`, so may only be changed via `redef`.

`backdoor_min_7bit_ascii_ratio : double`

    The fraction of 7-bit ASCII characters out of all bytes transferred
    must be at least this large in order for backdoor checking to be
    performed.
    Note: This variable is `const`, so may only be changed via `redef`.

`backdoor_demux_disabled : bool`

    If T (the default), then suspected backdoor connections are not
    demuxed into sender and receiver streams.
    Note: This variable is `const`, so may only be changed via `redef`.

`backdoor_demux_skip_tags : set[string]`

    If the type of backdoor (the tag) is in this set, the connection
    will not be demuxed.
    Note: This variable is `const`, so may only be changed via `redef`.

`backdoor_ignore_src_addrs : table[string, addr] of bool`

    If the suspected backdoor name (“\*” for any) and source address (or
    its /16 or /24) subnet are in this table as a pair, then the
    backdoor will not be logged.
    Note: This variable is `const`, so may only be changed via `redef`.

`backdoor_ignore_dst_addrs : table[string, addr] of bool`

    If the suspected backdoor name (“\*” for any) and destination
    address (or its /16 or /24) subnet are in this table as a pair, then
    the backdoor will not be logged.
    Note: This variable is `const`, so may only be changed via `redef`.

`backdoor_ignore_ports : table[string, port] of bool`

    The following (signature, well-known port) pairs should not
    generated a backdoor notice.
    Note: This variable is `const`, so may only be changed via `redef`.

`backdoor_standard_ports : set[port]`

    See `backdoor_annotate_standard_ports`.

    Note: This variable is `const`, so may only be changed via `redef`.

`backdoor_stat_period : interval`

    A report on backdoor stats is generated at this interval.

    Note: This variable is `const`, so may only be changed via `redef`.

`backdoor_stat_backoff : interval`

    *Fixme: Not sure about the exact definition here* The backdoor
    report interval (`backdoor_stat_period`) is increased by this
    factor each time it is generated, except if the timers are
    artificially expired.
    Note: This variable is `const`, so may only be changed via `redef`.

`backdoor_annotate_standard_ports : bool`

    If T (the default), backdoor notices for those on
    `backdoor_standard_ports` should be annotated with the backdoor
    tag name.
    Note: This variable is `const`, so may only be changed via `redef`.

`ssh_sig_disabled : bool`

    If T (default = F), then matches against the SSH signature are
    ignored.
    Note: This variable is `const`, so may only be changed via `redef`.

`telnet_sig_disabled : bool`

    If T (default = F), then matches against the telnet signature are
    ignored.
    Note: This variable is `const`, so may only be changed via `redef`.

`telnet_sig_3byte_disabled : bool`

    If T (default = F), then matches against the 3-byte telnet signature
    are ignored.
    Note: This variable is `const`, so may only be changed via `redef`.

`rlogin_sig_disabled : bool`

    If T (default = F), then matches against the rlogin signature are
    ignored.
    Note: This variable is `const`, so may only be changed via `redef`.

`rlogin_sig_1byte_disabled : bool`

    If T (default = F), then matches against the 1-byte rlogin signature
    are ignored.
    Note: This variable is `const`, so may only be changed via `redef`.

`root_backdoor_sig_disabled : bool`

    If T (default = F), then matches against the root backdoor signature
    are ignored.
    Note: This variable is `const`, so may only be changed via `redef`.

`ftp_sig_disabled : bool`

    If T (default = F), then matches against the FTP signature are
    ignored.
    Note: This variable is `const`, so may only be changed via `redef`.

`napster_sig_disabled : bool`

    If T (default = F), then matches against the Napster signature are
    ignored.
    Note: This variable is `const`, so may only be changed via `redef`.

`gnutella_sig_disabled : bool`

    If T (default = F), then matches against the Gnutella signature are
    ignored.
    Note: This variable is `const`, so may only be changed via `redef`.

`kazaa_sig_disabled : bool`

    If T (default = F), then matches against the KaZaA signature are
    ignored.
    Note: This variable is `const`, so may only be changed via `redef`.


`http_sig_disabled : bool`

    If T (default = F), then matches against the HTTP signature are
    ignored.
    Note: This variable is `const`, so may only be changed via `redef`.


`http_proxy_sig_disabled : bool`

    If T (default = F), then matches against the HTTP proxy signature
    are ignored.
    Note: This variable is `const`, so may only be changed via `redef`.


`did_sigconns : table[conn_id] of set[string]`

    A table which indicates, for each connection, which backdoor server
    signatures were found in the connection's traffic, e.g., “ftp-sig”
    or “napster-sig”.

`rlogin_conns : table[conn_id] of rlogin_conn_info`

    A table that holds relevant state variables (an `rlogin_conn_info`
    record) for `rsh` connections.

`root_backdoor_sig_conns : set[conn_id]`

    The set of connections for which a root backdoor signature
    (“root-bd-sig”) has been detected.

`ssh_len_conns : set[conn_id]`

    The set of connections that are predicted to contain SSH traffic,
    based on the proportion of packets that meet the expected packet
    size distribution. Relevant parameters are `ssh_min_num_pkts` and
    `ssh_min_ssh_pkts_ratio`, which are local to `backdoor`.

`ssh_min_num_pkts : count`

    The minimum number of packets that look like SSH packets that allow
    a stream to be classified as such.

`ssh_min_ssh_pkts_ratio : double`

    The minimum fraction of packets in a stream that look like SSH
    packets that allow a stream to be classified as such.
    Note: This variable is `const`, so may only be changed via `redef`.


`telnet_sig_conns : table[conn_id] of count`

    The set of connections that are predicted to be Telnet connections,
    based on observation of the Telnet signature, the IAC byte (0xff).

`telnet_sig_3byte_conns : table[conn_id] of count`

    Similar to `telnet_sig_conns`, but the signature matched is a
    whole 3-byte Telnet command sequence.

.. Next: \ :ref:`code-redbro <#code_002dredbro>`,
.. Previous: \ :ref:`backdoorbro <#backdoorbro>`, Up: \ `Predefined
.. Variables <#Predefined-Variables>`_

.. _#Bro-init-file:

bro.init
^^^^^^^^^^^^^^

`ignore_checksums : bool`

    If T (default = F), packet checksums are not verified.

    Note: This variable is `const`, so may only be changed via `redef`.


`partial_connection_ok : bool`

    If T (the default), instantiate connection state when a partial
    connection (one missing its initial establishment negotiation) is
    seen.
    Note: This variable is `const`, so may only be changed via `redef`.


`tcp_SYN_ack_ok : bool`

    If T (the default), instantiate connection state when a SYN ack is
    seen but not the initial SYN (even if partial\_connection\_ok is
    false).
    Note: This variable is `const`, so may only be changed via `redef`.


`tcp_match_undelivered : bool`

    If a connection state is removed there may still be some undelivered
    data waiting in the reassembler. If T (the default), pass this to
    the signature engine before flushing the state.
    Note: This variable is `const`, so may only be changed via `redef`.


`tcp_SYN_timeout : interval`

    Check up on the result of an initial SYN after this much time.
    *Fixme: What exactly does this mean? Check that the connection is
    active?*
    Note: This variable is `const`, so may only be changed via `redef`.


`tcp_session_timer : interval`

    After a connection has closed, wait this long for further activity
    before checking whether to time out its state.
    Note: This variable is `const`, so may only be changed via `redef`.


`tcp_connection_linger : interval`

    When checking a closed connection for further activity, consider it
    inactive if there hasn't been any for this long. Complain if the
    connection is reused before this much time has elapsed.
    Note: This variable is `const`, so may only be changed via `redef`.


`tcp_attempt_delayv : interval`

    Wait this long upon seeing an initial SYN before timing out the
    connection attempt.
    Note: This variable is `const`, so may only be changed via `redef`.


`tcp_close_delay : interval`

    Upon seeing a normal connection close, flush state after this much
    time.

    Note: This variable is `const`, so may only be changed via `redef`.


`tcp_reset_delay : interval`

    Upon seeing a RST, flush state after this much time.

    Note: This variable is `const`, so may only be changed via `redef`.


`tcp_partial_close_delay : interval`

    Generate a connection\_partial\_close event this much time after one
    half of a partial connection closes, assuming there has been no
    subsequent activity.
    Note: This variable is `const`, so may only be changed via `redef`.


`non_analyzed_lifetime : interval`

    If a connection belongs to an application that we don't analyze,
    time it out after this interval. If 0 secs, then don't time it out.
    Note: This variable is `const`, so may only be changed via `redef`.


`inactivity_timeout : interval`

    If a connection is inactive, time it out after this interval. If 0
    secs, then don't time it out.
    Note: This variable is `const`, so may only be changed via `redef`.


`tcp_storm_thresh : count`

    This many FINs/RSTs in a row constitutes a "storm". See also
    `tcp_storm_interarrival_thresh`.
    Note: This variable is `const`, so may only be changed via `redef`.


`tcp_storm_interarrival_thresh : interval`

    The FINs/RSTs must come with this much time or less between them to
    be considered a storm. See also `tcp_storm_thresh`.
    Note: This variable is `const`, so may only be changed via `redef`.


`tcp_reassembler_ports_orig : set[port]`

    For services without a handler, these sets define which side of a
    connection is to be reassembled. *Fixme: What is the point of this
    exactly? What are you analyzing?*
    Note: This variable is `const`, so may only be changed via `redef`.


`tcp_reassembler_ports_resp : set[port]`

    For services without a handler, these sets define which side of a
    connection is to be reassembled. *Fixme: What is the point of this
    exactly? What are you analyzing?*
    Note: This variable is `const`, so may only be changed via `redef`.


`table_expire_interval : interval`

    Check for expired table entries after this amount of time *Fixme:
    Which tables?*
    Note: This variable is `const`, so may only be changed via `redef`.


`dns_session_timeout : interval`

    Time to wait before timing out a DNS request.

    Note: This variable is `const`, so may only be changed via `redef`.


`ntp_session_timeout : interval`

    Time to wait before timing out an NTP request.

    Note: This variable is `const`, so may only be changed via `redef`.


`rpc_timeout : interval`

    Time to wait before timing out an RPC request.

    Note: This variable is `const`, so may only be changed via `redef`.


`watchdog_interval : interval`

    A SIGALRM is set for this interval to make sure that Bro does not
    get caught up doing something for too long. *Fixme: True?* If this
    happens, Bro is termination after doing a dump of all remaining
    packets.
    Note: This variable is `const`, so may only be changed via `redef`.


`heartbeat_interval : interval`

    After each interval of this length, update the variable.

    Note: This variable is `const`, so may only be changed via `redef`.


`anonymize_ip_addr : bool`

    If true (default = false), then IP addresses are anonymized in
    notice and log generation.
    Note: This variable is `const`, so may only be changed via `redef`.


`omit_rewrite_place_holder : bool`

    If true, omit place holder packets when rewriting. *Fixme: Should
    this go somewhere else?*
    Note: This variable is `const`, so may only be changed via `redef`.


`rewriting_http_trace : bool`

    If true (default = F), HTTP traces are rewritten.

    Note: This variable is `const`, so may only be changed via `redef`.


`rewriting_smtp_trace : bool`

    If true (default = F), SMTP traces are rewritten.

    Note: This variable is `const`, so may only be changed via `redef`.


.. Next: \ :ref:`connbro <#connbro>`, Previous: \ :ref:`broinit <#broinit>`,
.. Up: \ :ref:`Predefined Variables <#Predefined-Variables>`

code-red.bro
^^^^^^^^^^^^^^^^^^

`code_red_log file`

    The file into which Code Red-related logs are written.

`code_red_list1 : table[addr] of count`

    A table which contains, for each IP address, how many Code Red I
    attacks were observed (based on a signature) by the machine at that
    address.

`code_red_list2 : table[addr] of count`

    A table which contains, for each IP address, how many Code Red II
    attacks were observed (based on a signature) by the machine at that
    address.

`local_code_red_response_pgm : string`

    By default, an empty string; if `&redef`\ ed, the specified
    program will be invoked with the attack source IP as the argument
    the first time an attack from that IP is observed.

`remote_code_red_response_pgm : string`

    By default, an empty string; if `&redef`\ ed, the specified
    program will be invoked with the attack destination IP as the
    argument the first time an attack on that IP is observed.

.. Next: \ :ref:`demuxbro <#demuxbro>`,
.. Previous: \ :ref:`code-redbro <#code_002dredbro>`, Up: \ `Predefined
.. Variables <#Predefined-Variables>`_

conn.bro
^^^^^^^^^^^^^^

`have_FTP : bool`

    If true, `ftp.bro` has been loaded.

`have_SMTP : bool`

    If true, `smtp.bro` has been loaded.

`have_stats : bool`

    True if was ever updated with packet capture statistics.

`hot_conns_reported : set[string]`

    The set of connections (indexed by the entire 'hot' message) that
    have previously been flagged as `hot`.

`last_stat : net_stats`

    The last recorded snapshot of packet capture statistics, in a
    record.

`last_stat_time : time`

    The last time that network statistics were read into .

`RPC_server_map : table[addr, port] of string`

    Maps a given port on a given server's address to an RPC service. If
    we haven't loaded `portmapper.bro`, then it will be empty; see
    `portmapper.bro` and the `portmapper` module documentation for
    more information.

.. Next: \ :ref:`dnsbro <#dnsbro>`, Previous: \ :ref:`connbro <#connbro>`,
.. Up: \ :ref:`Predefined Variables <#Predefined-Variables>`

demux.bro
^^^^^^^^^^^^^^^

For more information on demultiplexing of connections, see the :ref:`demux
Analysis Script <#demux-Analysis-Script>`.

`demux_dir : string`

    The name of the directory which will contain the files with
    demultiplexed connection data.

`demuxed_conn : set[conn_id]`

    The set of connections that are currently being demultiplexed.

.. Next: \ :ref:`dns-mappingbro <#dns_002dmappingbro>`,
.. Previous: \ :ref:`demuxbro <#demuxbro>`, Up: \ `Predefined
.. Variables <#Predefined-Variables>`_

dns.bro
^^^^^^^^^^^^^

`actually_rejected_PTR_anno : set[string]`

    Annotations that if returned for a PTR lookup actually indicate a
    rejected query; for example, "illegal-address.lbl.gov".
    Note: This variable is `const`, so may only be changed via `redef`.


`sensitive_lookup_hosts : set[addr]`

    Hosts in this set generate a notice when they are returned in PTR
    queries, unless the originating host is in
    `sensitive_lookup_hosts`.
    Note: This variable is `const`, so may only be changed via `redef`.


`okay_to_lookup_sensitive_hosts : set[addr]`

    If the DNS request originator is in this set, then it is allowed to
    look up “sensitive” hosts (see also `sensitive_lookup_hosts`)
    without causing a notice.

`dns_log : file`

    The file into which DNS-related logs are written.

`dns_sessions : table[addr, addr] of dns_session_info`

    A table of outstanding DNS sessions indexed by [client IP, server
    IP]. *Fixme: Need to illustrate dns\_sessions\_info.*

`num_dns_sessions : count`

    The total number of entries that have ever been in the table.

`distinct_PTR_requests : table[addr, string] of count`

    The number of DNS PTR requests observed with the given source
    address and request string.

`distinct_rejected_PTR_requests : table[addr] of count`

    How many DNS PTR requests from the given source address were
    rejected. A report is generated if this number crosses a threshold,
    namely, `report_rejected_PTR_thresh`.

`distinct_answered_PTR_requests : table[addr] of count`

    How many DNS PTR requests from the given source address were
    rejected.

`report_rejected_PTR_thresh : count`

    If this many DNS requests from a host are rejected, generate a
    possible PTR scan event.

`report_rejected_PTR_factor : double`

    If DNS requests from a host are rejected more than accepted by this
    factor, generate a event.

`allow_PTR_scans set[addr]`

    The set of hosts for which a `PTR_scan` event does not generate a
    report (that is, the scan is allowed).

`did_PTR_scan_event table[addr] of count`

    A table of hosts for which a event has been generated.

.. Next: \ :ref:`fingerbro <#fingerbro>`, Previous: \ :ref:`dnsbro <#dnsbro>`,
.. Up: \ :ref:`Predefined Variables <#Predefined-Variables>`

dns-mapping.bro
^^^^^^^^^^^^^^^^^^^^^

`dns_interesting_changes`

    The set of DNS mapping changes (according to lookups by Bro itself)
    that is interesting enough to notice.
    Note: This variable is `const`, so may only be changed via `redef`.


.. Next: \ :ref:`ftpbro <#ftpbro>`,
.. Previous: \ :ref:`dns-mappingbro <#dns_002dmappingbro>`, Up: \ `Predefined
.. Variables <#Predefined-Variables>`_

finger.bro
^^^^^^^^^^^^^^^^^

`hot_names : set[string]`

    If a finger request for any of the names in this set is observed,
    the associated connection is marked “hot”.
    Note: This variable is `const`, so may only be changed via `redef`.


`max_finger_request_len : count`

    If a finger request is longer than this length, then it is marked as
    “hot”.
    Note: This variable is `const`, so may only be changed via `redef`.


`rewrite_finger_trace : bool`

    Indicates whether or not finger requests are rewritten for
    anonymity.

.. Next: \ :ref:`hotbro <#hotbro>`, Previous: \ :ref:`fingerbro <#fingerbro>`,
.. Up: \ :ref:`Predefined Variables <#Predefined-Variables>`

ftp.bro
^^^^^^^^^^^^^^

`ftp_log : file`

    The file into which FTP-related logs are written.

`ftp_sessions : table[conn_id] of ftp_session_info`

`ftp_guest_ids : set[string]`

    The set of login IDs which are guest logins, e.g., “anonymous” and
    “ftp”.
    Note: This variable is `const`, so may only be changed via `redef`.


`ftp_skip_hot : set[addr, addr, string]`

    Indexed by source and destination addresses and the id, these
    connections are not marked as “hot” even if its data would to cause
    it to be otherwise.
    Note: This variable is `const`, so may only be changed via `redef`.


`ftp_hot_files : pattern`

    If a filename matching this pattern is requested, the
    `ftp_sensitive_files` event is generated. The default behavior is
    to alarm the connection.
    Note: This variable is `const`, so may only be changed via `redef`.


`ftp_hot_guest_files : pattern`

    If a user is logged in under a guest ID and attempts to retrieve a
    file matching this pattern, the `ftp_sensitive` event is
    generated. The default behavior is to alarm the connection.
    Note: This variable is `const`, so may only be changed via `redef`.


`ftp_hot_cmds : table[string] of pattern`

    If an FTP command matches an index into the table and its argument
    matches the associated pattern, the connection is alarmed.
    Note: This variable is `const`, so may only be changed via `redef`.


`skip_unexpected : set[addr]`

    Pairs of IP addresses for which we shouldn't bother logging if one
    of them is used in lieu of the other in a PORT or PASV directive.

`skip_unexpected_net : set[addr]`

    Similar to `skip_unexpected`, but matches a /24 subnet.

`ftp_data_expected : table[addr, port] of addr`

    Indexed by the server's responder pair, yields the address expected
    to make an FTP data connection to it.

`ftp_data_expected_session : table[addr, port] of ftp_session_info`

    Indexed by the server's responder pair, yields the associated
    `ftp_session_info` record for the expected incoming FTP data
    connection.

`ftp_excessive_filename_len : count`

    If an FTP request filename meets or exceeds this length, an
    `FTP_ExcessiveFilename` notice is generated.

`ftp_excessive_filename_trunc_len : count`

    How much of the excessively long filename is printed in the notice
    message.

`ftp_ignore_invalid_PORT : pattern`

    Invalid PORT/PASV directives that exactly match this pattern don't
    generate notices.

`ftp_ignore_privileged_PASVs : set[port]`

    If an FTP PASV port is specified to be a privileged port (<
    1024/tcp) then an `FTP_PrivPort` event is generated, EXCEPT if the
    port is in this set.

.. Next: \ :ref:`hot-idsbro <#hot_002didsbro>`,
.. Previous: \ :ref:`ftpbro <#ftpbro>`, Up: \ `Predefined
.. Variables <#Predefined-Variables>`_

hot.bro
^^^^^^^^^^^^^^

`same_local_net_is_spoof : bool`

    If true (default = F), it should be considered a spoofing attack if
    a connection has the same local net for source and destination.
    Note: This variable is `const`, so may only be changed via `redef`.


`allow_spoof_services : set[port]`

    The services in this set are not counted as spoofed even if they
    pass the test from `same_local_net_is_spoof`.
    Note: This variable is `const`, so may only be changed via `redef`.


`allow_pairs : set[addr, addr]`

    Connections between these (source address, destination address)
    pairs are never marked as “hot”.
    Note: This variable is `const`, so may only be changed via `redef`.


`allow_16_net_pairs : set[addr, addr]`

    Connections between these (/16 network, /32 destination host) pairs
    are never marked as “hot”.
    Note: This variable is `const`, so may only be changed via `redef`.


`hot_srcs : table[addr] of string`

    Connections from any of these sources are automatically marked “hot”
    with the associated message in the table.
    Note: This variable is `const`, so may only be changed via `redef`.


`hot_dsts : table[addr] of string`

    Connections to any of these destinations are automatically marked
    “hot” with the associated message in the table.
    Note: This variable is `const`, so may only be changed via `redef`.


`hot_src_24nets : table[addr] of string`

    Connections from any of these source /24 nets are automatically
    marked “hot” with the associated message in the table.
    Note: This variable is `const`, so may only be changed via `redef`.


`hot_dst_24nets : table[addr] of string`

    Connections to any of these destination /24 nets are automatically
    marked “hot” with the associated message in the table.
    Note: This variable is `const`, so may only be changed via `redef`.


`allow_services : set[port]`

    Connections to this set of services are never marked “hot” (based on
    port number).
    Note: This variable is `const`, so may only be changed via `redef`.


`allow_services_to : set[addr, port]`

    Connections to the specified host and port are never marked “hot”.

    Note: This variable is `const`, so may only be changed via `redef`.


`allow_service_pairs : set[addr, addr, port]`

    Connections from the first address to the second on the specified
    destination port are never marked “hot”.
    Note: This variable is `const`, so may only be changed via `redef`.


`flag_successful_service : table[port] of string`

    Successful connections to any of the specified ports are flagged
    with the accompanying message. Examples are popular backdoor ports.
    Note: This variable is `const`, so may only be changed via `redef`.


`flag_successful_inbound_service : table[port] of string`

    Incoming connections to the specified ports are flagged with the
    accompanying message. This is similar to , but may be used when the
    port gives to many false positives for outgoing connections.
    Note: This variable is `const`, so may only be changed via `redef`.


`terminate_successful_inbound_service : table[port] of string`

    Connections to this port, if previously flagged by
    `flag_successful_service` or `flag_incoming_service` are
    terminated.
    Note: This variable is `const`, so may only be changed via `redef`.


`flag_rejected_service : table[port] of string`

    Failed connection attempts to the specified ports are marked as
    “hot”.
    Note: This variable is `const`, so may only be changed via `redef`.


.. Next: \ :ref:`httpbro <#httpbro>`, Previous: \ :ref:`hotbro <#hotbro>`,
.. Up: \ :ref:`Predefined Variables <#Predefined-Variables>`

hot-ids.bro
^^^^^^^^^^^^^^^^^^

`forbidden_ids : set[string]`

    If any of these usernames/login IDs are used, the corresponding
    connection is terminated.
    Note: This variable is `const`, so may only be changed via `redef`.


`forbidden_ids_if_no_password : set[string]`

    If any of these usernames/login IDs are used with no password, the
    corresponding connection is terminated.
    Note: This variable is `const`, so may only be changed via `redef`.


`forbidden_id_patterns : pattern`

    If a username/login ID matches this pattern, the corresponding
    connection is terminated.
    Note: This variable is `const`, so may only be changed via `redef`.


`always_hot_ids : set[string]`

    Connections that attempt to login with these IDs are always marked
    “hot”, whether or not they succeed. See also `hot_ids`.
    Note: This variable is `const`, so may only be changed via `redef`.


`hot_ids : set[string]`

    Similar to , except that only successful connections are marked
    “hot”.
    Note: This variable is `const`, so may only be changed via `redef`.


.. Next: \ :ref:`http-abstractbro <#http_002dabstractbro>`,
.. Previous: \ :ref:`hot-idsbro <#hot_002didsbro>`, Up: \ `Predefined
.. Variables <#Predefined-Variables>`_

http.bro
^^^^^^^^^^^^^^^

`http_log : file`

    The file into which HTTP-related logs are written.

`http_sessions : table[addr, addr] of http_session_info`

    A [source, destination] indexed table of `http_session_info`
    records.

`include_HTTP_abstract : bool`

    Currently used to indicate whether or not an abstract of the HTTP
    request data will be included in a rewritten connection.

`log_HTTP_data : bool`

    If true, an abstract of the HTTP request data is included in a log
    message.

`maintain_http_sessions : bool`

    If true, HTTP sessions are maintained across multiple connections,
    otherwise we not (which saves some memory).

`process_HTTP_replies : bool`

    If true, HTTP replies (not just requests) are processed.

`process_HTTP_data : bool`

    If true, HTTP data is examined as needed (e.g., for making HTTP
    abstracts, as discussed below).

.. Next: \ :ref:`http-requestbro <#http_002drequestbro>`,
.. Previous: \ :ref:`httpbro <#httpbro>`, Up: \ `Predefined
.. Variables <#Predefined-Variables>`_

http-abstract.bro
^^^^^^^^^^^^^^^^^^^^^^^^

`http_abstract_max_length : count`

    The maximum number of bytes used to store an abstract for an HTTP
    connection.
    Note: This variable is `const`, so may only be changed via `redef`.


.. Next: \ :ref:`icmpbro <#icmpbro>`,
.. Previous: \ :ref:`http-abstractbro <#http_002dabstractbro>`,
.. Up: \ :ref:`Predefined Variables <#Predefined-Variables>`

http-request.bro
^^^^^^^^^^^^^^^^^^^^^^^

`skip_remote_sensitive_URIs : pattern`

    URIs matching this pattern should not be considered sensitive if
    accessed remotely, i.e., by a local client.

`have_skip_remote_sensitive_URIs : bool`

    Due to a quirk in Bro, this must be redef'ed to T if you want to use
    `skip_remote_sensitive_URIs`.
    Note: This variable is `const`, so may only be changed via `redef`.


`sensitive_URIs : pattern`

    URIs matching this pattern, but not matching `worm_URIs`, are
    noticed. See also `skip_remote_sensitive_URIs` and
    `sensitive_post_URIs`.
    Note: This variable is `const`, so may only be changed via `redef`.


`worm_URIs : pattern`

    URIs matching this pattern are not noticed even if they match
    `sensitive_URIs`, since worms are so common they would clutter the
    logs.
    Note: This variable is `const`, so may only be changed via `redef`.


`sensitive_post_URIs : pattern`

    URIs matching this pattern are noticed if they are used with the
    HTTP “POST” method (rather than “GET”).
    Note: This variable is `const`, so may only be changed via `redef`.


.. Next: \ :ref:`identbro <#identbro>`,
.. Previous: \ :ref:`http-requestbro <#http_002drequestbro>`, Up: \ `Predefined
.. Variables <#Predefined-Variables>`_

icmp.bro
^^^^^^^^^^^^^^^

`icmp_flows : table[icmp_flow_id] of icmp_flow_info`

    A table tracking all ICMP “flows” by `icmp_flow_info`. “Flows”,
    which are simply inferred related sequences of packets between two
    machines, based on ICMP ID, are timed out after (currently) 30
    seconds of inactivity.

.. Next: \ :ref:`interconnbro <#interconnbro>`,
.. Previous: \ :ref:`icmpbro <#icmpbro>`, Up: \ `Predefined
.. Variables <#Predefined-Variables>`_

ident.bro
^^^^^^^^^^^^^^^^

`hot_ident_ids : set[string]`

    If any of the User IDs in this set are returned in an `ident`
    response, an *IdentSensitiveID* notice is generated.

`hot_ident_exceptions : set[string]`

    Exceptions to the `hot_ident_ids` set.

`public_ident_user_ids : set[string]`

    User IDs in this set are described as “public” in a rewritten
    `ident` trace.

`public_ident_systems : set[string]`

    Operating system names in this set (e.g., “UNIX”) are reported
    directly in a rewritten `ident` trace; other OSes will be reported
    as “OTHER”.

`rewrite_ident_trace : bool`

    If true, traces will be rewritten (partially anonymized).

.. Next: \ :ref:`ircbro <#ircbro>`, Previous: \ :ref:`identbro <#identbro>`,
.. Up: \ :ref:`Predefined Variables <#Predefined-Variables>`

interconn.bro
^^^^^^^^^^^^^^^^^^^^

`interconn_conns : table [conn_id] of conn_info`

    A `conn_id`-indexed table of all currently-tracked interactive
    connections. The table entries are records containing some very
    basic information about the connection.

`interconn_log : file`

    The file into which generic interactive-connection-related logs are
    written.

`interconn_min_interarrival : interval`

    Used in computing the “alpha” parameter, which is used to determine
    which connections are interactive, based on the distribution of
    interarrival times. See also `interconn_max_interarrival`.
    Note: This variable is `const`, so may only be changed via `redef`.


`interconn_max_interarrival : interval`

    Used in computing the “alpha” parameter, which is used to determine
    which connections are interactive, based on the distribution of
    interarrival times. See also `interconn_max_interarrival`.
    Note: This variable is `const`, so may only be changed via `redef`.


`interconn_max_keystroke_pkt_size : count`

    The maximum packet size used to classify keystroke-containing
    packets.
    Note: This variable is `const`, so may only be changed via `redef`.


`interconn_default_pkt_size : count`

    The estimated packet size used to calculate the number of packets
    missed when we see an ack above a hole. *Fixme: Please verify.*
    Note: This variable is `const`, so may only be changed via `redef`.


`interconn_stat_period : interval`

    How often to generate a report of interconn stats.

    Note: This variable is `const`, so may only be changed via `redef`.


`interconn_stat_backoff : double`

    *Fixme: I don't fully understand is\_expire in timers.* The stat
    report generation interval (`interconn_stat_period`) is increased
    by this factor each time the report is generated [unless the report
    is generated because all timers are artificially expired].
    Note: This variable is `const`, so may only be changed via `redef`.


`interconn_min_num_pkts : count`

    A connection must have this number of packets transferred before it
    may be classified as interactive.
    Note: This variable is `const`, so may only be changed via `redef`.


`interconn_min_duration : interval`

    A connection must last least this long before it may be classified
    as interactive.
    Note: This variable is `const`, so may only be changed via `redef`.


`interconn_ssh_len_disabled : bool`

    If false (default = T), and at least one side of the connection has
    partial state (the initial negotiation was missed), then packets are
    examined to see if they fit the size distribution associated with
    interactive SSH connections.
    Note: This variable is `const`, so may only be changed via `redef`.


`interconn_min_ssh_pkts_ratio : double`

    Analogous to `ssh_min_ssh_pkts_ratio`, except used in the context
    described in `interconn_ssh_len_disabled`.
    Note: This variable is `const`, so may only be changed via `redef`.


`interconn_min_bytes : count`

    The number of bytes transferred on a connection must be at least
    this high before the connection may be classified as interactive.
    Note: This variable is `const`, so may only be changed via `redef`.


`interconn_min_7bit_ascii_ratio : double`

    The ratio of 7-bit ASCII characters to total bytes must be at least
    this high before the connection may be classified as interactive.
    Note: This variable is `const`, so may only be changed via `redef`.


`interconn_min_num_lines : count`

    The number of lines transferred on a connection must be at least
    this high before the connection may be classified as interactive.
    Note: This variable is `const`, so may only be changed via `redef`.


`interconn_min_normal_line_ratio : double`

    The ratio of “normal” lines to total lines must be at least this
    high before the connection may be classified as interactive. A
    normal line, roughly speaking, is one whose length is within a
    certain bound. *Fixme: Please verify this.*
    Note: This variable is `const`, so may only be changed via `redef`.


`interconn_min_alpha : double`

    The “alpha” parameter computed on connection must be at least this
    high before the connection may be classified as interactive. This
    parameter measures certain properties of packet interarrival times.
    See `interconn`.
    Note: This variable is `const`, so may only be changed via `redef`.


`interconn_min_gamma : double`

    The “gamma” parameter computed on connection must be at least this
    high before the connection may be classified as interactive.

`interconn_standard_ports : set[port]`

    Connections to or from these ports are marked as interactive
    automatically, unless `interconn_standard_ports` is set to true.
    Note: This variable is `const`, so may only be changed via `redef`.


`interconn_ignore_standard_ports : bool`

    If true (default = F), then all connections are analyzed for
    interactive patterns, regardless of port. See
    `interconn_standard_ports`.
    Note: This variable is `const`, so may only be changed via `redef`.


`interconn_demux_disabled : bool`

    If false (default = T), then interactive connections are demuxed
    when being logged.
    Note: This variable is `const`, so may only be changed via `redef`.


.. Next: \ :ref:`loginbro <#loginbro>`,
.. Previous: \ :ref:`interconnbro <#interconnbro>`, Up: \ `Predefined
.. Variables <#Predefined-Variables>`_

irc.bro
^^^^^^^^^^^^^^

`IRC::log_file: file`

    Where to log IRC sessions.

`hot_words`

    List of regular expressions that generate notices if found in
    session dialog.

`ignore_in_other_msgs: set[string]`

    Commands to ignore in generating events for unknown commands.

`ignore_in_other_responses: set[string]`

    Return codes to ignore in generating events for unknown return
    codes.

These variables contain information about the users and channels
identified by Bro:

`irc_users: table[string] of irc_user`

    All identified IRC users, indexed by IRC nick.

`irc_channels: table[string] of irc_channel`

    All identified IRC channels, indexed by IRC channel name.

.. Next: \ :ref:`mimebro <#mimebro>`, Previous: \ :ref:`ircbro <#ircbro>`,
.. Up: \ :ref:`Predefined Variables <#Predefined-Variables>`

login.bro
^^^^^^^^^^^^^^^^

`input_trouble : pattern`

    If a user's keystroke input matches this pattern, then a notice is
    generated.

`edited_input_trouble : pattern`

    If a user's keystroke input matches this pattern, taking into
    account backspace and delete characters, then a notice is generated.

`full_input_trouble : pattern`

    If this pattern is matched in a full line of input, a notice is
    generated.

`input_wait_for_output : pattern`

    The same as `edited_input_trouble`, except that the notice is
    delayed until the corresponding output is seen, so that both may be
    logged together.

`output_trouble : pattern`

    If the login output matches this pattern, a notice is generated.

`full_output_trouble : pattern`

    Similar to `output_trouble`, but the pattern must match the entire
    output.

`backdoor_prompts : pattern`

    If the login output matches this text, but not
    `non_backdoor_prompts`, generate a possible-backdoor notice.

`non_backdoor_prompts : pattern`

    See `backdoor_prompts`.

`hot_terminal_types : pattern`

    If the terminal type used matches this pattern, generate a notice.

`hot_telnet_orig_ports : set[port]`

    If the source port of a telnet connection is in this set, generate a
    notice.

`skip_authentication : set[string]`

    If a string in this set appears where an authentication prompt would
    normally, skip processing of authentication (typically for an
    unauthenticated system). *Fixme: Please verify.*
    Note: This variable is `const`, so may only be changed via `redef`.


`login_prompts : set[string]`

    The set of strings that are recognized as login prompts anywhere on
    a line, e.g., “Login:”.
    Note: This variable is `const`, so may only be changed via `redef`.


`login_failure_msgs : set[string]`

    If any of these strings appear on a line following an authentication
    attempt, the attempt is considered to have failed, unless a string
    from `login_non_failure_msgs` also appears on the line. This set
    has higher precedence than `login_success_msgs`, and the same
    precedence as `login_timeouts`.
    Note: This variable is `const`, so may only be changed via `redef`.


`login_non_failure_msgs : set[string]`

    If any of these strings appear on a line following an authentication
    attempt, the connection is not considered to have failed even if
    `login_failure_msgs` indicates otherwise.
    Note: This variable is `const`, so may only be changed via `redef`.


`login_success_msgs : set[string]`

    If any of these messages is seen, the connection attempt is assumed
    to have succeeded. This set has lower precedence than
    `login_failure_msgs` and `login_timeouts` .
    Note: This variable is `const`, so may only be changed via `redef`.


`login_timeouts : set[string]`

    If any of these messages is seen during the login phase, the
    connection attempt is assumed to have timed out. This set has higher
    precedence than `login_success_msgs`, and the same precedence as
    `login_failure_msgs`.

`router_prompts : pattern`

    *Fixme: Don't know what this is*

`non_ASCII_hosts : set[addr]`

    The set of hosts that do not use ASCII (and to whom logins are thus
    not processed).

`skip_logins_to : set[addr]`

    Do not process logins to this set of hosts.

`always_hot_login_ids : pattern`

    Login names which generate a notice even if the login is not
    successful.

`hot_login_ids : pattern`

    Login names which generate a notice, if the login is successful.

`rlogin_id_okay_if_no_password_exposed : set[string]`

    Login names in this set are those which are normally considered
    sensitive, but are allowed if the associated password is not
    exposed.

`login_sessions : table[conn_id] of login_session_info`

    A table, indexed by connection ID, of `login_session_info`
    records, characterizing each login session.

.. Next: \ :ref:`noticebro <#noticebro>`, Previous: \ :ref:`loginbro <#loginbro>`,
.. Up: \ :ref:`Predefined Variables <#Predefined-Variables>`

mime.bro
^^^^^^^^^^^^^^^

`mime_log : file`

    MIME message-related logs are written to this file.

`mime_sessions : table[conn_id] of mime_session_info`

    A table, indexed by connection ID, of `mime_session_info` records,
    characterizing each MIME session.

`check_relay_3 function(session: mime_session_info, msg_id: string): bool`

    *Fixme: Don't know about this*

`check_relay_4 function(session: mime_session_info, content_hash: string): bool`

    *Fixme: Don't know about this*

.. Next: \ :ref:`ntpbro <#ntpbro>`, Previous: \ :ref:`mimebro <#mimebro>`,
.. Up: \ :ref:`Predefined Variables <#Predefined-Variables>`

notice.bro
^^^^^^^^^^^^^^^^^

`notice_action_filters : table[Notice] of function(n: notice_info: NoticeAction`

    A table that maps each `notice` into a function that should be
    called to determine the action.

`notice_file : file`

    The file into which notices are written.

.. Next: \ :ref:`pop3bro <#pop3bro>`, Previous: \ :ref:`noticebro <#noticebro>`,
.. Up: \ :ref:`Predefined Variables <#Predefined-Variables>`

ntp.bro
^^^^^^^^^^^^^^

`excessive_ntp_request : count`

    NTP requests over this length are considered “excessive” and will be
    flagged (marked “hot”).
    Note: This variable is `const`, so may only be changed via `redef`.


`allow_excessive_ntp_requests : set[addr]`

    NTP requests from an address in this set are never considered
    excessively long (see `excessive_ntp_request`).
    Note: This variable is `const`, so may only be changed via `redef`.


.. Next: \ :ref:`port-namesbro <#port_002dnamesbro>`,
.. Previous: \ :ref:`ntpbro <#ntpbro>`, Up: \ `Predefined
.. Variables <#Predefined-Variables>`_

pop3.bro
^^^^^^^^^^^^^^^

‘\ `pop_connections: table[conn_id] of pop3_session_info`\ ’

This table contains all active POP3-sessions indexed by their Connection
IDs. Deleted as soon as the TCP Connection terminates or expires.

‘\ `pop_connection_weirds: table[addr] of count &default=0 &create_expire = 5 mins`\ ’

This table contains all the POP3-session originators for which
unexpected behavior was recorded.

‘\ `error_threshold: count = 3`\ ’

A threshold for the maximum of negative status indicators per originator
received by a server.

‘\ `ignore_commands: set[string]`\ ’

Set of commands that will be ignored while generating the log file.

--------------

Next: \ :ref:`portmapperbro <#portmapperbro>`,
Previous: \ :ref:`pop3bro <#pop3bro>`, Up: \ :ref:`Predefined
Variables <#Predefined-Variables>`

6.1.26 port-names.bro
^^^^^^^^^^^^^^^^^^^^^

`port_names : table[port] of string`

    A mapping of well-known port numbers to the associated service
    names.
    Note: This variable is `const`, so may only be changed via `redef`.


.. Next: \ :ref:`scanbro <#scanbro>`,
.. Previous: \ :ref:`port-namesbro <#port_002dnamesbro>`, Up: \ `Predefined
.. Variables <#Predefined-Variables>`_

portmapper.bro
^^^^^^^^^^^^^^^^^^^^^

`rpc_programs : table[count] of string`

    A table correlating numeric RPC service IDs to string names of the
    services, e.g., `[1000000] = `portmapper''`.

`NFS_services : set[string]`

    A set of string names of NFS-related RPC services.

    Note: This variable is `const`, so may only be changed via `redef`.


`RPC_okay : set[addr, addr, string]`

    Indexed by the host providing the service, the host requesting it,
    and the service; do not notice Sun portmapper requests from the
    specified requester to the specified provider for the specified
    service.
    Note: This variable is `const`, so may only be changed via `redef`.


`RPC_okay_nets : set[net]`

    Hosts in any of the networks in this set may make portmapper
    requests without being flagged.
    Note: This variable is `const`, so may only be changed via `redef`.


`RPC_okay_services : set[string]`

    Requests for services in this set will not be flagged.

    Note: This variable is `const`, so may only be changed via `redef`.


`NFS_world_servers : set[addr]`

    Any host may request NFS services from any of the machines in this
    set without being flagged..
    Note: This variable is `const`, so may only be changed via `redef`.


`any_RPC_okay : set[addr, string]`

    Indexed by the service provider and the service (in string form);
    any host may access these services without being flagged.
    Note: This variable is `const`, so may only be changed via `redef`.


`RPC_dump_okay : set[addr, addr]`

    Indexed by requesting host and providing host, respectively; dumps
    of RPC portmaps are allowed between these pairs.
    Note: This variable is `const`, so may only be changed via `redef`.


`RPC_do_not_complain : set[string, bool]`

    Indexed by the portmapper request and a boolean that's T if the
    request was answered, F it was attempted but not answered. If
    there's an entry in the set matching the current request/attempt,
    then the access won't be noticed (unless the connection is hot for
    some other reason).

`suppress_pm_log : set[addr, string]`

    Indexed by source and portmapper service. If set, we already noticed
    and shouldn't do so again. *Fixme: Presumably this can be preloaded
    with stuff, or we wouldn't need to document it.*

.. Next: \ :ref:`signaturesbro <#signaturesbro>`,
.. Previous: \ :ref:`portmapperbro <#portmapperbro>`, Up: \ `Predefined
.. Variables <#Predefined-Variables>`_

scan.bro
^^^^^^^^^^^^^^^

`suppress_scan_checks : bool`

    If true, we suppress scan checking (we still do account-tried
    accounting). This is provided because scan checking can consume a
    lot of memory.

`report_peer_scan : set[count]`

    When the number of distinct machines connected to by a given
    external host reaches each of the levels in the set, a notice is
    generated.
    Note: This variable is `const`, so may only be changed via `redef`.


`report_outbound_peer_scan : set[count]`

    When the number of distinct machines connected to by a given
    internal host reaches each of the levels in the set, a notice is
    generated.
    Note: This variable is `const`, so may only be changed via `redef`.


`num_distinct_peers : table[addr] of count`

    A table indexed by a host's address which indicates how many
    distinct machines that host has connected to.

`distinct_peers : set[addr,addr]`

    A table indexed by source host and target machine that tracks which
    machines have been scanned by each host.

`num_distinct_ports : table[addr] of count`

    A table indexed by a host's address which indicates how many
    distinct ports that host has connected to.

`distinct_ports : set[addr, port]`

    A table indexed by source host and target port that tracks which
    ports have been scanned by each host.

`report_port_scan : set[count]`

    When the number of distinct ports connected to by a given external
    host reaches each of the levels in the set, a notice is generated.
    Note: This variable is `const`, so may only be changed via `redef`.


`possible_port_scan_thresh : count`

    If a host tries to connect to more than this number of ports, it is
    considered a possible scanner.
    Note: This variable is `const`, so may only be changed via `redef`.


`possible_scan_sources : set[addr]`

    Hosts are put in this set once they have scanned more than ports.

`num_scan_triples : table[addr, addr] of count`

    Indexed by source address and destination address, the number of
    services scanned for on the latter by the former. This is only
    tracked for `possible_scan_sources`.

`scan_triples : set[addr, addr, port]`

    For `possible_scan_sources` as a source address, the triples of
    (source address, destination address, and service/port) scanned.

`accounts_tried : set[addr, string, string]`

    Which account names were tried, indexed by source address, user name
    tried, password tried.

`num_accounts_tried : table[addr] of count`

    How many accounts, as defined by a (user name, password) pair, were
    tried by the host with the given address.

`report_accounts_tried : set[count]`

    When the number of distinct accounts (username, password) tried by a
    given external host reaches each of the levels in the set, a notice
    is generated.
    Note: This variable is `const`, so may only be changed via `redef`.


`report_remote_accounts_tried : set[count]`

    When the number of distinct remote accounts (username, password)
    tried by a given internal host reaches each of the levels in the
    set, a notice is generated.
    Note: This variable is `const`, so may only be changed via `redef`.


`skip_accounts_tried : set[addr]`

    Hosts in this set are not subject to notices based on
    `report_accounts_tried` and `report_remote_accounts_tried`.
    Note: This variable is `const`, so may only be changed via `redef`.


`addl_web : set[port]`

    Ports in this set are treated as HTTP services.

    Note: This variable is `const`, so may only be changed via `redef`.


`skip_services : set[port]`

    Connections to ports in this set are ignored for the purposes of
    scan detection.
    Note: This variable is `const`, so may only be changed via `redef`.


`skip_outbound_services : set[port]`

    Connections to external machines on ports in this set are ignored
    for the purposes of scan detection.
    Note: This variable is `const`, so may only be changed via `redef`.


`skip_scan_sources : set[addr]`

    Hosts in this set are ignored as possible sources of scans.

    Note: This variable is `const`, so may only be changed via `redef`.


`skip_scan_nets_16 : set[addr,port]`

    Connections matching the specified (source host /16 subnet, port)
    pairs are ignored for the purpose of scan detection.
    Note: This variable is `const`, so may only be changed via `redef`.


`skip_scan_nets_24 : set[addr,port]`

    Connections matching the specified (source host /24 subnet, port)
    pairs are ignored for the purpose of scan detection.
    Note: This variable is `const`, so may only be changed via `redef`.


`backscatter_ports : set[port]`

    Reverse (SYN-ack) scans seen from these ports are considered to
    reflect possible SYN flooding backscatter and not true (stealth)
    scans.
    Note: This variable is `const`, so may only be changed via `redef`.


`num_backscatter_peers : table[addr] of count`

    Indexed by a host, how many other hosts it connected to with a
    possible backscatter signature.

`distinct_backscatter_peers :  table[addr, addr] of count`

    A table of [source, destination] observed backscatter activity; the
    table entry is a count of backscatter packets from the source to the
    destination.

`report_backscatter : set[count]`

    When the number of machines that a host has sent backscatter packets
    to reaches each of the levels in the set, a notice is generated.

    *Fixme: Need to document connection-dropping related variables.*

    ::

                  global can_drop_connectivity = F &redef;
                  global drop_connectivity_script = "drop-connectivity" &redef;
                  global connectivity_dropped set[addr];
                  const shut_down_scans: set[port] &redef;
                  const shut_down_all_scans = F &redef;
                  const shut_down_thresh = 100 &redef;
                  never_shut_down set[addr]
                  never_drop_nets set[net]
                  never_drop_16_nets set[net]
                  did_drop_address table[addr] of count

`root_servers : set[host]`

    The set of root DNS servers.

    Note: This variable is `const`, so may only be changed via `redef`.


`gtld_servers : set[host]`

    The set of Generic Top-Level Domain servers (.com, .net, .org,
    etc.).
    Note: This variable is `const`, so may only be changed via `redef`.


.. Next: \ :ref:`sitebro <#sitebro>`, Previous: \ :ref:`scanbro <#scanbro>`,
.. Up: \ :ref:`Predefined Variables <#Predefined-Variables>`

signatures.bro
^^^^^^^^^^^^^^^^^^^^^

`horiz_scan_thresholds : set[count]`

    Notice if for a pair (orig, signature) the number of different
    responders has reached one of the thresholds in this set.
    Note: This variable is `const`, so may only be changed via `redef`.


`vert_scan_thresholds : set[count]`

    Notice if for a pair (orig, resp) the number of different signature
    matches has reached one of the thresholds in this set.
    Note: This variable is `const`, so may only be changed via `redef`.


.. Next: \ :ref:`smtpbro <#smtpbro>`,
.. Previous: \ :ref:`signaturesbro <#signaturesbro>`, Up: \ `Predefined
.. Variables <#Predefined-Variables>`_

site.bro
^^^^^^^^^^^^^^^

`local_nets : set[net]`

    Class A/B/C networks that are considered “local”.

    Note: This variable is `const`, so may only be changed via `redef`.


`local_16_nets : set[addr]`

    /16 address blocks that are considered “local”. These are derived
    directly from `local_nets` . *Fixme: Please verify this*.
    Note: This variable is `const`, so may only be changed via `redef`.


`local_24_nets : set[addr]`

    /24 address blocks that are considered “local”. These are derived
    directly from `local_nets`. *Fixme: Please verify this*.
    Note: This variable is `const`, so may only be changed via `redef`.


`neighbor_nets : set[net]`

    Class A/B/C networks that are considered “neighbors”. Note that
    unlike for local\_nets, `local_16_nets` is *not* merely a /16 addr
    version of neighbor\_nets, but instead is consulted *in addition* to
    neighbor\_nets.
    Note: This variable is `const`, so may only be changed via `redef`.


`neighbor_16_nets : set[addr]`

    /16 address blocks that are considered “neighbors”. Note that unlike
    for local\_nets, neighbor\_16\_nets is *not* merely a /16 addr
    version of `neighbor_nets`, but instead is consulted *in addition*
    to `neighbor_nets`.
    Note: This variable is `const`, so may only be changed via `redef`.


.. Next: \ :ref:`smtp-relaybro <#smtp_002drelaybro>`,
.. Previous: \ :ref:`sitebro <#sitebro>`, Up: \ `Predefined
.. Variables <#Predefined-Variables>`_

smtp.bro
^^^^^^^^^^^^^^^

`local_mail_addr : pattern`

    Email addresses matching this pattern are considered to be local.
    This is used to detect relaying.

`smtp_log : file`

    The file into which SMTP-related notices are written.

`smtp_sessions : table[conn_id] of smtp_session_info`

    A table of `smtp_session_info` records tracking SMTP-related state
    for a given connection.

`process_smtp_relay : bool`

    If true (default = F), processing is done to check for mail
    relaying.
    Note: This variable is `const`, so may only be changed via `redef`.


    ::

                  type smtp_session_info: record {
                    id: count;
                    connection_id: conn_id;
                    external_orig: bool;
                    in_data: bool;
                    num_cmds: count;
                    num_replies: count;
                    cmds: smtp_cmd_info_list;
                    in_header: bool;
                    keep_current_header: bool;  # a hack till MIME rewriter is ready
                    recipients: string;
                    subject: string;
                    content_hash: string;
                    num_lines_in_body: count;   # lines in RFC 822 body before MIME decoding
                    num_bytes_in_body: count;   # bytes in entity bodies after MIME decoding
                    content_gap: bool;      # whether there is content gap in conversation
                  
                    relay_1_rcpt: string;   # external recipients
                    relay_2_from: count;    # session id of same recipient
                    relay_2_to: count;
                    relay_3_from: count;    # session id of same msg id
                    relay_3_to: count;
                    relay_4_from: count;    # session id of same content hash
                    relay_4_to: count;
                  };

`smtp_legal_cmds : set[string]`

    The set of allowed SMTP commands (not currently used). *Fixme: Is it
    used somewhere?*

`smtp_hot_cmds : table[string] of pattern`

    If an SMTP command matching an index into the table has an argument
    matching the associated pattern, then the request and its reply are
    logged.

`smtp_sensitive_cmds : set[string]`

    If an SMTP command is in this set, the request and its reply are
    logged.

.. Next: \ :ref:`softwarebro <#softwarebro>`,
.. Previous: \ :ref:`smtpbro <#smtpbro>`, Up: \ `Predefined
.. Variables <#Predefined-Variables>`_

smtp-relay.bro
^^^^^^^^^^^^^^^^^^^^^

`relay_log : file`

    Logs related to email relaying go in this file.

`smtp_relay_table : table[count] of smtp_session_info`

    A table indexed by SMTP session ID (session$id) that keeps track of
    each session in an record.

`smtp_session_by_recipient : table[string] of smtp_session_info`

    A table indexed by the recipient that holds the corresponding
    `smtp_session_info` record.

`smtp_session_by_message_id : table[string] of smtp_session_info`

    A table indexed by the email message ID that holds the corresponding
    `smtp_session_info` record.

`smtp_session_by_content_hash : table[string] of smtp_session_info`

    A table indexed by the MD5 hash of the message that holds the
    corresponding record. *Fixme: Currently unimplemented?*

.. Next: \ :ref:`sshbro <#sshbro>`,
.. Previous: \ :ref:`smtp-relaybro <#smtp_002drelaybro>`, Up: \ `Predefined
.. Variables <#Predefined-Variables>`_

software.bro
^^^^^^^^^^^^^^^^^^^

`software_file : file`

    Logs related to host software detection go in this file.

`software_table : table[addr] of software_set`

    A table of the software running on each host. A `software_set` is
    itself a table, indexed by the name of the software, of `software`
    records.

`software_ident_by_major : set[string]`

    Software names in this set could be installed twice on the same
    machine with different major version numbers. Such software is
    identified as “Software-N” where N is the major version number, to
    disambiguate the two.

.. Next: \ :ref:`steppingbro <#steppingbro>`,
.. Previous: \ :ref:`softwarebro <#softwarebro>`, Up: \ `Predefined
.. Variables <#Predefined-Variables>`_

ssh.bro
^^^^^^^^^^^^^^

`ssh_log : file`

    Logs related to ssh connections go in this file.

`did_ssh_version : table[addr, bool] of count`

    Indexed by host IP and (T for client, F for server), the table
    tracks if we have recorded the SSH version. Values of one and
    greater are essentially equivalent.

.. Next: \ :ref:`tftpbro <#tftpbro>`, Previous: \ :ref:`sshbro <#sshbro>`,
.. Up: \ :ref:`Predefined Variables <#Predefined-Variables>`

stepping.bro
^^^^^^^^^^^^^^^^^^^

`step_log : file`

    Logs related to stepping-stone detection go in this file.

`display_pairs : table[addr, string] of connection`

    If <conn> was a login to <dst> propagating a $DISPLAY of <display>,
    then we make an entry of [<dst>, <display>] = <conn>.

`tag_to_conn_map : table[string] of connection`

    Maps login tags like "Last login ..." to connections.

`conn_tag_info : table[conn_id] of tag_info`

    A table, indexed by connection ID, of the `tag_info` related to
    it. Roughly, “tag info” consists of login strings like “Last login”
    and `$DISPLAY` variables. Since this information can stay constant
    across stepping stones, it is used to detect them.

`detected_stones : table[addr, port, addr, port, addr, port, addr, port] of count`

    Indexed by two pairs of connections: (addr,port)->(addr,port) and
    (addr,port)->(addr,port) that have been detected to be multiple
    links in a stepping stone chain. The table value is the “score” of
    the pair of connections; the higher the score, the more likely it is
    to be a real stepping stone pair. More points are assigned for a
    timing-based correlation than, say, a `$DISPLAY`-based
    correlation.

`did_stone_summary : table[addr, port, addr, port, addr, port, addr, port] of count`

    Basically tracks which suspected stepping stone connection pairs
    have had notices generated for them. See `detected_stones` for the
    indexing scheme.

`stp_delta : interval`

    Note: This variable is `const`, so may only be changed via `redef`.


`stp_idle_min : interval`

    Note: This variable is `const`, so may only be changed via `redef`.


`stp_ratio_thresh : double`

    For timing correlations, the proportion of idle times that must
    match up for the correlation to be considered significant.
    Note: This variable is `const`, so may only be changed via `redef`.


`stp_scale : double`

    Note: This variable is `const`, so may only be changed via `redef`.


`stp_common_host_thresh : count`

    Note: This variable is `const`, so may only be changed via `redef`.


`stp_random_pair_thresh : count`

    Note: This variable is `const`, so may only be changed via `redef`.


`stp_demux_disabled : count`

    Note: This variable is `const`, so may only be changed via `redef`.


`skip_clear_ssh_reports : set[addr, string]`

    Note: This variable is `const`, so may only be changed via `redef`.


.. Next: \ :ref:`udpbro <#udpbro>`, Previous: \ :ref:`steppingbro <#steppingbro>`,
.. Up: \ :ref:`Predefined Variables <#Predefined-Variables>`

tftp.bro
^^^^^^^^^^^^^^^

`tftp_notice_count : table[addr] of count`

    Keeps track of the number of observed outbound TFTP connections from
    each host.


.. Next: \ :ref:`weirdbro <#weirdbro>`, Previous: \ :ref:`tftpbro <#tftpbro>`,
.. Up: \ :ref:`Predefined Variables <#Predefined-Variables>`

udp.bro
^^^^^^^^^^^^^^

`udp_req_count : table[conn_id] of count`

    Keeps track of the number of UDP requests sent over each connection.

`udp_rep_count : table[conn_id] of count`

    *Fixme: not really sure*

`udp_did_summary : table[conn_id] of count`

    Keeps track of which connections have been summarized/recorded
    *Fixme: what is it really? do people use this?*

.. Next: \ :ref:`wormbro <#wormbro>`, Previous: \ :ref:`udpbro <#udpbro>`,
.. Up: \ :ref:`Predefined Variables <#Predefined-Variables>`

weird.bro
^^^^^^^^^^^^^^^^

`weird_log : file`

    Logs related to `weird` (unexpected or inconsistent) traffic go in
    this file.

`weird_action : table[string] of WeirdAction`

    A table of what to do (a `WeirdAction` ) when faced with a
    particular “weird” scenario (the index). Example include logging to
    the special “weird” file or ignoring the condition.

`weird_action_filters : table[string] of function(c: connection): WeirdAction`

    If an entry exists in this table for a given weird situation, then
    the corresponding entry is used to determine what action to take;
    the default is to look in `weird_action`.

`weird_ignore_host : set[addr, string]`

    (host, weird condition) pairs in this set are ignored for the
    purposes of reporting.
    Note: This variable is `const`, so may only be changed via `redef`.


`weird_do_not_ignore_repeats : set[string]`

    The included conditions are reported even if they are repeated.

    Note: This variable is `const`, so may only be changed via `redef`.


.. Next: \ :ref:`Uncategorized <#Uncategorized>`,
.. Previous: \ :ref:`weirdbro <#weirdbro>`, Up: \ `Predefined
.. Variables <#Predefined-Variables>`_

worm.bro
^^^^^^^^^^^^^^^

`worm_log : file`

    The file into which worm-detection-related logs are written.

`worm_list : table[addr] of count`

    A table of infected hosts, indexed by the infected hosts' addresses.
    The value is how many times the instance has been seen sending
    packets.

`worm_type_list : table[addr, string] of count`

    A table of infected hosts, indexed by host address and type of worm.
    The value is how many times that particular worm has been seen on
    the host.

.. Previous: \ :ref:`wormbro <#wormbro>`, Up: \ `Predefined
.. Variables <#Predefined-Variables>`_

.. _#Uncategorized:

Uncategorized
^^^^^^^^^^^^^^^^^^^^

*Fixme: These need categorization.*

`bro_alarm_file : file`

    Used to record the messages logged by `alarm` statements.
    Default: *stderr*, unless you `@load` the `alarm` analyzer; see
    `bro_alarm_file` for further discussion.

`capture_filters : table[string] of string`

    Specifies what packets Bro's filter should record.

`direct_login_prompts : set[string]`

    Strings that when seen in a login dialog indicate that the user will
    be directly logged in after entering their username, without
    requiring a password.

`discarder_maxlen : int`

    The maximum amount of data that Bro should pass to a TCP or UDP
    *discarder*.
    Default: 128 bytes.

`done_with_network : bool`

    Set to true when Bro is done reading from the network (or from the
    save files being played back, per
    :ref:`play-back <#Playing-back-traces>`). The variable is set by a
    handler for `net_done`.
    Default: initially set to false.

`interfaces : string`

    A blank-separated list of network interfaces from which Bro should
    read network traffic. Bro merges packets from the interfaces
    according to their timestamps. *Deficiency: All interfaces must have
    the same link layer type.*

    If empty, then Bro does not read any network traffic, unless one or
    more interfaces are specified using the -i flag.

    *Note:* `interfaces` has an `&add_func` that allows you to add
    interfaces to the list simply using a `+=` initialization
    refinement.

    Default: empty.

`max_timer_expires : count`

    Sets an upper limit on how many pending timers Bro will expire per
    newly arriving packet. If set to 0, then Bro expires all pending
    timers whose time has come or past. This variable trades off timer
    accuracy and memory requirements (because a number of Bro's internal
    timers relate to expiring state) with potentially bursty load spikes
    due to a lot of timers expiring at the same time, which can trigger
    the watchdog, if active.

`restrict_filter : string`

    Restricts what packets Bro's filter should record.

.. Previous: \ :ref:`Predefined Variables <#Predefined-Variables>`,
.. Up: \ `Predefined Variables and
.. Functions <#Predefined-Variables-and-Functions>`_

.. _#Predefined-Functions:

Predefined Functions
~~~~~~~~~~~~~~~~~~~~~~~~

Bro provides a number of built-in functions:

`active_connection (id: conn_id) : bool`

    Returns true if the given connection identifier
    (originator/responder addresses and ports) corresponds to a
    currently-active connection.

`active_file (f: file): bool`

    Returns true if the given `file` is open.

`add_interface (iold: string, inew: string): string`

    Used to refine the initialization of `interfaces`. Meant for
    internal use, and as an example of refinement.

`add_tcpdump_filter (fold: string, fnew: string): string`

    Used to refine the initializations of `capture_filters` and
    `restrict_filters`. Meant for internal use, and as an example of
    refinement.

`alarm_hook (msg: string): bool`

    If you define this function, then Bro will call it with each string
    it is about to log in an alarm. The function should return true if
    Bro should go ahead with the alarm, false otherwise. See for further
    discussion and an example.

`byte_len (s: string): count`

    Returns the number of bytes in the given string. This includes any
    embedded NULs, and also a trailing NUL, if any (which is why the
    function isn't called *strlen*; to remind the user that Bro strings
    can include NULs).

`cat (args: any): string`

    Returns the concatenation of the string representation of its
    arguments, which can be of any type. For example,
    `cat("foo", 3, T)` returns `"foo3T"`.

`clean (s: string): string`

    Returns a cleaned up version of `s`, meaning that:

        -  embedded NULs become the text “\ `\0`\ ”
        -  embedded DELs (delete characters) become the text
           “\ `^?`\ ”
        -  ASCII “control” characters with code <= 26 become the text
           “\ `^`\ *Letter*\ ”, where *Letter* is the corresponding
           (upper case) control character; for example, ASCII 2 becomes
           “\ `^B`\ ”
        -  ASCII “control” characters with codes between 26 and 32
           (non-inclusive) become the text “\ `\x`\ *hex-code*\ ”; for
           example, ASCII 31 becomes “\ `\x1f`\ ”
        -  if the string does not yet have a trailing NUL, one is added.

`close (f: file): bool`

    Flushes any buffered output for the given file and closes it.
    Returns true if the file was open, false if already closed or never
    opened.

`connection_record (id: conn_id): connection`

    Returns the `connection` record corresponding to the non-existing
    connection id if not a known connection. *Note: If the connection
    does not exist, then exits with a fatal run-time error.*
    *Deficiency: If Bro had an exception mechanism, then we could avoid
    the fatal run-time error, and likewise could get rid
    of*\ `active_connection`\ *.*

`contains_string (big: string, little: string): bool`

    Returns true if the string `little` occurs somewhere within
    `big`, false otherwise.

`current_time (): time`

    Returns the current clock time. You will usually instead want to use
    `network_time`.

`discarder_check_icmp (i: ip_hdr, ih: icmp_hdr): bool`

    Not documented.

`discarder_check_ip (i: ip_hdr): bool`

    Not documented.

`discarder_check_tcp (i: ip_hdr, t: tcp_hdr, d: string): bool`

    Not documented.

`discarder_check_udp (i: ip_hdr, u: udp_hdr, d: string): bool`

    Not documented.

`edit (s: string, edit_char: string): string`

    Returns a version of `s` assuming that `edit_char` is the
    “backspace” character (usually `"\x08"` for backspace or
    `"\x7f"` for DEL). For example, `edit("hello there", "e")`
    returns `"llo t"`.

    `edit_char` must be a string of exactly one character, or Bro
    generates a run-time error and uses the first character in the
    string.

    *Deficiency: To do a proper job, edit should also know about
    delete-word and delete-line editing; and it would be very convenient
    if it could do multiple types of edits all in one shot, rather than
    requiring separate invocations.*

`exit (): int`

    Exits Bro with a status of 0.

    *Deficiency: This function should probably allow you to specify the
    exit status.*

    *Note: If you invoke this function, then the usual cleanup
    functions*\ `net_done`\ *and*\ `bro_done`\ *are NOT invoked.
    There probably should be an additional “*\ `shutdown`\ *” function
    that provides for cleaner termination.*

`flush_all (): bool`

    Flushes all open files to disk.

`fmt (args: any): string`

    Performs *sprintf*-style formatting. The first argument gives the
    format specifier to which the remaining arguments are formatted,
    left-to-right. As with *sprintf*, the format for each argument is
    introduced using “%”, and formats beginning with a positive integer
    *m* specify that the given field should have a width of *m*
    characters. Fields with fewer characters are right-padded with
    blanks up to this width.

    A format specifier of “\ `.$n`\ ” (coming after `m`, if present)
    instructs `fmt` to use a precision of *n* digits. You can only
    specify a precision for the `e`, `f` or `g` formats. (`fmt`
    generates a run-time error if either *m* or *n* exceeds 127.)

    The different format specifiers are:

    ‘%’

    A literal percent-sign character.

    ‘\ `D`\ ’

    Format as a date. Valid only for values of type `time`.

    The exact format is *yy*–*mm*–*dd*–*hh*:*mm*:*ss* for the local time
    zone, per *strftime*.

    ‘\ `d`\ ’

    Format as an integer. Valid for types `bool`, `count`, `int`,
    ` port`, `addr`, and `net`, with the latter three being
    converted from network order to host order prior to formatting.
    `bool` values of true format as the number 1, and false as 0.

    ‘\ `e, f, g`\ ’

    Format as a floating point value. Valid for types `double`,
    `time`, and `interval`. The formatting is the same as for
    *printf*, including the field width *m* and precision *n*.

    Given no arguments, `fmt` returns an empty string.

    Given a non-string first argument, `fmt` returns the concatenation
    of all its arguments, per `cat`.

    Finally, given the wrong number of additional arguments for the
    given format specifier, `fmt` generates a run-time error.

`get_login_state (c: conn_id): count`

    Returns the state of the given login (Telnet or Rlogin) connection,
    one of:
    ‘\ `LOGIN_STATE_AUTHENTICATE`\ ’
    The connection is in its initial authentication dialog.
    ‘\ `LOGIN_STATE_LOGGED_IN`\ ’
    The analyzer believes the user has successfully authenticated.
    ‘\ `LOGIN_STATE_SKIP`\ ’
    The analyzer has skipped any further processing of the connection.
    ‘\ `LOGIN_STATE_CONFUSED`\ ’
    The analyzer has concluded that it does not correctly know the state
    of the connection, and/or the username associated with it.

`connection_id` is not a known login connection or a run-time error
and a value of `LOGIN_STATE_AUTHENTICATE` if the connection is not a
login connection.

`get_orig_seq (c: conn_id): count`

    Returns the highest sequence number sent by a connection's
    originator, or 0 if there's no such TCP connection. Sequence numbers
    are absolute (i.e., they reflect the values seen directly in packet
    headers; they are not relative to the beginning of the connection).

`get_resp_seq (c: conn_id): count`

    Returns the highest sequence number sent by a connection's
    responder, or 0 if there's no such TCP connection.

`getenv (var: string): string`

    Looks up the given environment variable and returns its value, or an
    empty string if it is not defined.

`is_tcp_port (p: port): bool`

    Returns true if the given `port` value corresponds to a TCP port,
    false otherwise (i.e., it belongs to a UDP port).

`length (args: any): count`

    Returns the number of elements in its argument, which must be of
    type `table` or `set`. If not exactly one argument is specified,
    or if the argument is not a table or a set, then generates a
    run-time message and returns 0.
    *Deficiency: If Bro had a union type, then we could get rid of the
    magic “*\ `args: any`\ *” specification and catch parameter
    mismatches at compile-time instead of run-time.*

`log_file_name (tag: string): string`

    Returns a name for a log file (such as `weird` or `conn` ) in a
    standard form. The form depends on whether $BRO\_LOG\_SUFFIX is set.
    If so, then the format is
    “\ `<`\ *tag*\ `>.<\$BRO_LOG_SUFFIX>`\ ”. Otherwise, it is
    simply `tag`.

`mask_addr (a: addr, top_bits_to_keep: count): addr`

    Returns the address `a` masked down to the number of upper bits
    indicated by `top_bits_to_keep`, which must be greater than 0 and
    less than 33. For example, `mask_addr(1.2.3.4, 18)` returns
    `1.2.0.0`, and `mask_addr(1.2.255.4, 18)` returns `1.2.192.0`.
    Compare with `to_net`.

`max_count (a: count, b: count): count`

    Returns the larger of `a` or `b`.

`max_double (a: double, b: double): double`

    Returns the larger of `a` or `b`.

`max_interval (a: interval, b: interval): interval`

    Returns the larger of `a` or `b`.
    *Deficiency: If Bro supported polymorphic functions, then this
    function could be merged with its predecessors, gaining simplicity
    and clarity.*

`min_count (a: count, b: count): count`

    Returns the smaller of `a` or `b`.

`min_double (a: double, b: double): double`

    Returns the smaller of `a` or `b`.

`min_interval (a: interval, b: interval): interval`

    Returns the smaller of `a` or `b`.
    *Deficiency: If Bro supported polymorphic functions, then this
    function could be merged with its predecessors, gaining simplicity
    and clarity.*

`mkdir (f: string): bool`

    Creates a directory with the given name, if it does not already
    exist. Returns true upon success, false (with a run-time message) if
    unsuccessful.

`network_time (): time`

    Returns the timestamp of the most recently read packet, whether read
    from a live network interface or from a save file. Compare against
    `current_time`. In general, you should use `network_time` unless
    you're using Bro for non-networking uses (such as general scripting;
    not particularly recommended), because otherwise your script may
    behave very differently on live traffic versus played-back traffic
    from a save file.

`open (f: string): file`

    Opens the given filename for write access. Creates the file if it
    does not already exist. Generates a run-time error if the file
    cannot be opened/created.

`open_for_append (f: string): file`

    Opens the given filename for append access. Creates the file if it
    does not already exist. Generates a run-time error if the file
    cannot be opened/created.

`open_log_file (tag: string): file`

    Opens a log file associated with the given tag, using a filename
    format as returned by .

`parse_ftp_pasv (s: string): ftp_port`

    Parses the server's reply to an FTP `PASV` command to extract the
    IP address and port number indicated by the server. The values are
    returned in an `ftp_port` record, which has three fields: `h`,
    the address (*h* is mnemonic for *host*); `p`, the (TCP) port; and
    `valid`, a boolean that is true if the server's reply was in the
    required format, false if not, or if any of the individual values
    (or the indicated port number) are out of range.

`parse_ftp_port (s: string): ftp_port`

    Parses the argument included in a client's FTP `PORT` request to
    extract the IP address and port number indicated by the server. The
    values are returned in an `ftp_port`, which has three fields, as
    indicated in the discussion of `parse_ftp_pasv`.

`reading_live_traffic (): bool`

    Returns true if Bro was invoked to read live network traffic (from
    one or more network interfaces, per ), false if it's reading from
    save files being played back .
    *Note: This function returns true even after Bro has stopped reading
    network traffic, for example due to receiving a termination signal.*

`set_buf (f: file, buffered: bool)`

    Specifies that writing to the given file should either be fully
    buffered (if `buffered` is true), or line-buffered (if false).
    Does not return a value.

`set_contents_file (c: conn_id, direction: count, f: file): bool`

    Specifies that the traffic stream of the given connection in the
    given direction should be recorded to the given file. `direction`
    is one of the values given in the table below.

    +---------------------+-------------------------------------------------------------------------+
    | **Direction**       | **Meaning**                                                             |
    +---------------------+-------------------------------------------------------------------------+
    | `CONTENTS_NONE`     | Stop recording the connection's content                                 |
    +---------------------+-------------------------------------------------------------------------+
    | `CONTENTS_ORIG`     | Record the data sent by the connection originator (often the client).   |
    +---------------------+-------------------------------------------------------------------------+
    | `CONTENTS_RESP`     | Record the data sent by the connection responder (often the server).    |
    +---------------------+-------------------------------------------------------------------------+
    | `CONTENTS_BOTH`     | Record the data sent in both directions.                                |
    +---------------------+-------------------------------------------------------------------------+

    **Table 6.1: Different types of directions for `set_contents`
    file**

    *Note: CONTENTS\_BOTH results in the two directions being intermixed
    in the file, in the order the data was seen by Bro.*

    *Note: The data recorded to the file reflects the byte stream, not
    the contents of individual packets. Reordering and duplicates are
    removed. If any data is missing, the recording stops at the missing
    data; see*\ `ack_above_hole`\ *for how this can happen.*

    *Deficiency: Bro begins recording the traffic stream starting with
    new traffic it sees. Experience has shown it would be highly handy
    if Bro could record the entire connection to the file, including
    previously seen traffic. In principle, this is possible if Bro is
    recording the traffic to a save file , which a separate utility
    program could then read to extract the stream.*

    Returns true upon success, false upon an error.

`set_login_state (c: conn_id, new_state: count): bool`

    Manually sets the state of the given login (Telnet or Rlogin)
    connection to `new_state`, which should be one of the values
    described in .
    Generates a run-time error and returns false if the connection is
    not a login connection. Otherwise, returns true.

`set_record_packets (c: conn_id, do_record: bool): bool`

    Controls whether Bro should or should not record the packets
    corresponding to the given connection to the save file , if any.
    Returns true upon success, false upon an error.

`skip_further_processing (c: conn_id): bool`

    Informs bro that it should skip any further processing of the
    contents of the given connection. In particular, Bro will refrain
    from reassembling the TCP byte stream and from generating events
    relating to any analyzers that have been processing the connection.
    Bro will still generate connection-oriented events such as
    `connection_finished` .

    This function provides a way to shed some load in order to reduce
    the computational burden placed on the monitor.

    Returns true upon success, false upon an error.

`sub_bytes (s: string, start: count, n: count): string`

    Returns a copy of `n` bytes from the given string, starting at
    position `start`. The beginning of a string corresponds to
    position 1.

    If `start` is 0 or exceeds the length of the string, returns an
    empty string.

    If the string does not have `n` characters from `start` to its
    end, then returns the characters from `start` to the end.

`system (s: string): int`

    Runs the given string as a *sh* command (via C's *system* call).

    *Note: The command is run in the background with stdout redirected
    to stderr.*

    Returns the return value from the *system* call. *Note: This
    corresponds to the status of backgrounding the given command, NOT to
    the exit status of the command itself.* A value of 127 corresponds
    to a failure to execute *sh*, and -1 to an internal system failure.

`to_lower (s: string): string`

    Returns a copy of the given string with the uppercase letters (as
    indicated by *isascii* and *isupper*) folded to lowercase (via
    *tolower*).

`to_net (a: addr): net`

    Returns the network prefix historically associated with the given
    address. That is, if `a`'s leading octet is less than 128, then
    returns `<`\ *a*\ `>`\ */8*; if between 128 and 191, inclusive,
    then `<`\ *a*\ `>`\ */16*; if between 192 and 223, then
    `<`\ *a*\ `>`\ */24*; and, otherwise, `<`\ *a*\ `>`\ */32*.
    See the discussion of the type for more about network prefixes.

    Generates a run-time error and returns `0.0.0.0` if the address is
    IPv6.

    *Note: Such network prefixes have become obsolete with the advent of
    CIDR; still, for some sites they prove useful because they
    correspond to existing address allocations.*

    Compare with `mask_addr`.

`to_upper s: string): string`

    Returns a copy of the given string with the lowercase letters (as
    indicated by *isascii* and *islower*) folded to uppercase (via
    *toupper*).

.. Next: \ `Run-time errors for strings with
.. NULs <#Run_002dtime-errors-for-strings-with-NULs>`_, Up: \ `Predefined
.. Functions <#Predefined-Functions>`_

Run-time errors for non-existing connections
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Note that for all functions that take a `conn_id` argument except
`active-connection`, Bro generates a run-time error and returns false
if the given connection does not exist.

.. Next: \ `Functions for manipulating
.. strings <#Functions-for-manipulating-strings>`_, Previous: \ `Run-time
.. errors for non-existing
.. connections <#Run_002dtime-errors-for-non_002dexisting-connections>`_,
.. Up: \ :ref:`Predefined Functions <#Predefined-Functions>`

Run-time errors for strings with NULs
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

While Bro allows NULs embedded within strings, for many of the
predefined functions, their presence spells trouble, particularly when
the string is being passed to a C run-time function. The same holds for
strings that are *not* NUL-terminated. Because Bro string constants and
values returned by Bro functions that construct strings such as `fmt`
and `cat` are all NUL-terminated, such strings will not ordinarily
arise; but their presence could indicate an attacker attempting to
manipulate either a TCP endpoint, or the monitor itself, into
misinterpreting a string they're sending.

In general, any of the functions above that are passed a string argument
will check for the presence of an embedded NUL or the lack of a
terminating NUL. If either occurs, they generate a run-time message, and
the string is transformed into the value `"<string-with-NUL>"`.

There are three exceptions: `clean`, `byte_len`, and `sub_bytes`.
These functions do not complain about embedded NULs or lack of trailing
NULs.

.. Next: \ `Functions for manipulating
.. time <#Functions-for-manipulating-time>`_, Previous: \ `Run-time errors
.. for strings with NULs <#Run_002dtime-errors-for-strings-with-NULs>`_,
.. Up: \ :ref:`Predefined Functions <#Predefined-Functions>`

Functions for manipulating strings
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

*Fixme: Missing*

.. Previous: \ `Functions for manipulating
.. strings <#Functions-for-manipulating-strings>`_, Up: \ `Predefined
.. Functions <#Predefined-Functions>`_

.. _#Functions-for-manipulating-time:

Functions for manipulating time
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

*Fixme: Missing*


