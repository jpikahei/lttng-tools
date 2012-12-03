#!/bin/bash
#
# Copyright (C) - 2012 David Goulet <dgoulet@efficios.com>
#
# This library is free software; you can redistribute it and/or modify it under
# the terms of the GNU Lesser General Public License as published by the Free
# Software Foundation; version 2.1 of the License.
#
# This library is distributed in the hope that it will be useful, but WITHOUT
# ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
# FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more
# details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with this library; if not, write to the Free Software Foundation, Inc.,
# 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301 USA
TEST_DESC="UST - Wildcard overlap"

CURDIR=$(dirname $0)/
TESTDIR=$CURDIR/../..
SESSION_NAME="wildcard-overlap"

DEMO_EVENT1="ust_tests_demo:starting"
DEMO_EVENT1_2="ust_tests_demo:done"
DEMO_EVENT2="ust_tests_demo2:loop"
DEMO_EVENT3="ust_tests_demo3:done"

NUM_DEMO1_EVENT=1
NUM_DEMO1_2_EVENT=1
NUM_DEMO2_EVENT=5
NUM_DEMO3_EVENT=1

source $TESTDIR/utils.sh

print_test_banner "$TEST_DESC"

if [ ! -x "$CURDIR/demo/demo" ]; then
	echo -e "No UST nevents binary detected. Passing."
	exit 0
fi

# MUST set TESTDIR before calling those functions

run_demo_app()
{
	local dir=`pwd`

	cd demo

	# Start test
	echo -n "Starting application... "
	./$CURDIR/demo-trace >/dev/null 2>&1
	echo -n "Ended "
	print_ok

	cd $dir
}

# Ease our life a bit ;)
trace_match_demo1_events()
{
	trace_matches $DEMO_EVENT1 $NUM_DEMO1_EVENT $TRACE_PATH
	trace_matches $DEMO_EVENT1_2 $NUM_DEMO1_EVENT $TRACE_PATH
}

# Ease our life a bit ;)
trace_match_all_demo_events()
{
	trace_match_demo1_events
	trace_matches $DEMO_EVENT2 $NUM_DEMO2_EVENT $TRACE_PATH
	trace_matches $DEMO_EVENT3 $NUM_DEMO3_EVENT $TRACE_PATH
}

# Ease our life a bit ;)
trace_match_no_demo_events()
{
	trace_matches $DEMO_EVENT1 0 $TRACE_PATH
	trace_matches $DEMO_EVENT1_2 0 $TRACE_PATH
	trace_matches $DEMO_EVENT2 0 $TRACE_PATH
	trace_matches $DEMO_EVENT3 0 $TRACE_PATH
}

# Expect all "demo" events, no duplicate.
test_enable_simple_wildcard()
{
	local event_wild1="us*"
	local event_wild2="ust*"

	echo ""
	echo "=== Simple wildcard overlap"

	enable_ust_lttng_event $SESSION_NAME $event_wild1
	enable_ust_lttng_event $SESSION_NAME $event_wild2

	start_lttng_tracing $SESSION_NAME >/dev/null 2>&1

	run_demo_app

	stop_lttng_tracing $SESSION_NAME >/dev/null 2>&1

	trace_match_all_demo_events

	return $?
}

# Expect all "demo" events, no duplicate.
test_enable_wildcard_filter()
{
	local event_wild1="us*"
	local event_wild2="ust*"

	echo ""
	echo "=== Wildcard overlap with filter"

	enable_ust_lttng_event_filter $SESSION_NAME $event_wild1 "1==1"
	enable_ust_lttng_event_filter $SESSION_NAME $event_wild2 "1==0"

	start_lttng_tracing $SESSION_NAME >/dev/null 2>&1

	run_demo_app

	stop_lttng_tracing $SESSION_NAME >/dev/null 2>&1

	trace_match_all_demo_events
	return $?
}

# Expect all "demo" events, no duplicate.
test_enable_wildcard_filter_2()
{
	local event_wild1="us*"
	local event_wild2="ust*"

	echo ""
	echo "=== Wildcard overlap with filter 2"

	enable_ust_lttng_event_filter $SESSION_NAME $event_wild1 "1==0"
	enable_ust_lttng_event_filter $SESSION_NAME $event_wild2 "1==1"

	start_lttng_tracing $SESSION_NAME >/dev/null 2>&1

	run_demo_app

	stop_lttng_tracing $SESSION_NAME >/dev/null 2>&1

	trace_match_all_demo_events
	return $?
}

# Expect all "demo" events, no duplicate.
test_enable_wildcard_filter_3()
{
	local event_wild1="us*"
	local event_wild2="ust*"

	echo ""
	echo "=== Wildcard overlap with filter 3"

	enable_ust_lttng_event_filter $SESSION_NAME $event_wild1 "1==1"
	enable_ust_lttng_event_filter $SESSION_NAME $event_wild2 "1==1"

	start_lttng_tracing $SESSION_NAME >/dev/null 2>&1

	run_demo_app

	stop_lttng_tracing $SESSION_NAME >/dev/null 2>&1

	trace_match_all_demo_events
	return $?
}

# Expected: No events.
test_enable_wildcard_filter_4()
{
	local event_wild1="us*"
	local event_wild2="ust*"

	echo ""
	echo "=== Wildcard overlap with filter 4"

	enable_ust_lttng_event_filter $SESSION_NAME $event_wild1 "1==0"
	enable_ust_lttng_event_filter $SESSION_NAME $event_wild2 "1==0"

	start_lttng_tracing $SESSION_NAME >/dev/null 2>&1

	run_demo_app

	stop_lttng_tracing $SESSION_NAME >/dev/null 2>&1

	trace_match_no_demo_events
	return $?
}

# Expect all "demo" events, no duplicate.
test_enable_wildcard_filter_5()
{
	local event_wild1="us*"
	local event_wild2="$DEMO_EVENT1"

	echo ""
	echo "=== Wildcard overlap with filter 5"

	enable_ust_lttng_event_filter $SESSION_NAME $event_wild1 "1==1"
	enable_ust_lttng_event_filter $SESSION_NAME $event_wild2 "1==0"

	start_lttng_tracing $SESSION_NAME >/dev/null 2>&1

	run_demo_app

	stop_lttng_tracing $SESSION_NAME >/dev/null 2>&1

	trace_match_all_demo_events
	return $?
}

# Expect all $DEMO_EVENT1 events, no duplicate.
test_enable_wildcard_filter_6()
{
	local event_wild1="us*"
	local event_wild2="$DEMO_EVENT1"

	echo ""
	echo "=== Wildcard overlap with filter 6"

	enable_ust_lttng_event_filter $SESSION_NAME $event_wild1 "1==0"
	enable_ust_lttng_event_filter $SESSION_NAME $event_wild2 "1==1"

	start_lttng_tracing $SESSION_NAME >/dev/null 2>&1

	run_demo_app

	stop_lttng_tracing $SESSION_NAME >/dev/null 2>&1

	trace_matches $DEMO_EVENT1 $NUM_DEMO1_EVENT $TRACE_PATH
	trace_matches $DEMO_EVENT1_2 0 $TRACE_PATH
	trace_matches $DEMO_EVENT2 0 $TRACE_PATH
	trace_matches $DEMO_EVENT3 0 $TRACE_PATH
	return $?
}

# Expect all events, no duplicate.
test_enable_wildcard_filter_7()
{
	local event_wild1="us*"
	local event_wild2="$DEMO_EVENT1"

	echo ""
	echo "=== Wildcard overlap with filter 7"

	enable_ust_lttng_event_filter $SESSION_NAME $event_wild1 "1==1"
	enable_ust_lttng_event_filter $SESSION_NAME $event_wild2 "1==1"

	start_lttng_tracing $SESSION_NAME >/dev/null 2>&1

	run_demo_app

	stop_lttng_tracing $SESSION_NAME >/dev/null 2>&1

	trace_match_all_demo_events
	return $?
}

# Expected: No events.
test_enable_wildcard_filter_8()
{
	local event_wild1="us*"
	local event_wild2="$DEMO_EVENT1"

	echo ""
	echo "=== Wildcard overlap with filter 8"

	enable_ust_lttng_event_filter $SESSION_NAME $event_wild1 "1==0"
	enable_ust_lttng_event_filter $SESSION_NAME $event_wild2 "1==0"

	start_lttng_tracing $SESSION_NAME >/dev/null 2>&1

	run_demo_app

	stop_lttng_tracing $SESSION_NAME >/dev/null 2>&1

	trace_match_no_demo_events
	return $?
}

# Expect all events.
test_enable_same_wildcard_filter()
{
	local event_wild1="ust*"
	local event_wild2="ust*"

	echo ""
	echo "=== Same wildcard overlap with filter"

	enable_ust_lttng_event_filter $SESSION_NAME $event_wild1 "1==1&&1==1"
	enable_ust_lttng_event_filter $SESSION_NAME $event_wild2 "1==1"

	start_lttng_tracing $SESSION_NAME >/dev/null 2>&1

	run_demo_app

	stop_lttng_tracing $SESSION_NAME >/dev/null 2>&1

	trace_match_all_demo_events
	return $?
}

# Expect all events.
test_enable_same_wildcard_filter_2()
{
	local event_wild1="ust*"
	local event_wild2="ust*"

	echo ""
	echo "=== Same wildcard overlap with filter 2"

	enable_ust_lttng_event_filter $SESSION_NAME $event_wild1 "1==1"
	enable_ust_lttng_event_filter $SESSION_NAME $event_wild2 "1==1"

	start_lttng_tracing $SESSION_NAME >/dev/null 2>&1

	run_demo_app

	stop_lttng_tracing $SESSION_NAME >/dev/null 2>&1

	trace_match_all_demo_events
	return $?
}

# Expect all events.
test_enable_same_wildcard_filter_3()
{
	local event_wild1="ust*"
	local event_wild2="ust*"

	echo ""
	echo "=== Same wildcard overlap with filter 3"

	enable_ust_lttng_event_filter $SESSION_NAME $event_wild1 "1==1"
	enable_ust_lttng_event_filter $SESSION_NAME $event_wild2 "1==0"

	start_lttng_tracing $SESSION_NAME >/dev/null 2>&1

	run_demo_app

	stop_lttng_tracing $SESSION_NAME >/dev/null 2>&1

	trace_match_all_demo_events
	return $?
}

# Expected: No events.
test_enable_same_wildcard_filter_4()
{
	local event_wild1="ust*"
	local event_wild2="ust*"

	echo ""
	echo "=== Same wildcard overlap with filter 4"

	enable_ust_lttng_event_filter $SESSION_NAME $event_wild1 "1==0&&1==0"
	enable_ust_lttng_event_filter $SESSION_NAME $event_wild2 "1==0"

	start_lttng_tracing $SESSION_NAME >/dev/null 2>&1

	run_demo_app

	stop_lttng_tracing $SESSION_NAME >/dev/null 2>&1

	trace_match_no_demo_events
	return $?
}

# Expected: Only $DEMO_EVENT1
test_enable_same_event_filter()
{
	local event_wild1="$DEMO_EVENT1"
	local event_wild2="$DEMO_EVENT1"

	echo ""
	echo "=== Enable same event with filter."

	enable_ust_lttng_event_filter $SESSION_NAME $event_wild1 "1==1&&1==1"
	enable_ust_lttng_event_filter $SESSION_NAME $event_wild2 "1==1"

	disable_ust_lttng_event $SESSION_NAME "ust*"

	start_lttng_tracing $SESSION_NAME >/dev/null 2>&1

	run_demo_app

	stop_lttng_tracing $SESSION_NAME >/dev/null 2>&1

	trace_matches $DEMO_EVENT1 $NUM_DEMO1_EVENT $TRACE_PATH
	trace_matches $DEMO_EVENT1_2 0 $TRACE_PATH
	trace_matches $DEMO_EVENT2 0 $TRACE_PATH
	trace_matches $DEMO_EVENT3 0 $TRACE_PATH
	return $?
}

# Expected: No events.
test_disable_same_wildcard_filter()
{
	local event_wild1="ust*"
	local event_wild2="ust*"

	echo ""
	echo "=== Disable same wildcard with filter."

	enable_ust_lttng_event_filter $SESSION_NAME $event_wild1 "1==1&&1==1"
	enable_ust_lttng_event_filter $SESSION_NAME $event_wild2 "1==1"

	disable_ust_lttng_event $SESSION_NAME "ust*"

	start_lttng_tracing $SESSION_NAME >/dev/null 2>&1

	run_demo_app

	stop_lttng_tracing $SESSION_NAME >/dev/null 2>&1

	trace_match_no_demo_events
	return $?
}

# Expect no events
test_enable_bad_wildcard()
{
	# Invalid event
	local event_wild1="ust_tests_demo"
	local event_wild2="ust_tests_demo2"
	local event_wild3="ust_tests_demo3"

	echo ""
	echo "=== Enable bad wildcard"

	enable_ust_lttng_event $SESSION_NAME $event_wild1
	enable_ust_lttng_event $SESSION_NAME $event_wild2
	enable_ust_lttng_event $SESSION_NAME $event_wild3

	start_lttng_tracing $SESSION_NAME >/dev/null 2>&1

	run_demo_app

	stop_lttng_tracing $SESSION_NAME >/dev/null 2>&1

	trace_match_no_demo_events
	return $?
}

# Expect all "demo" events, no duplicate.
test_enable_simple_wildcard_2()
{
	local event_wild1="us*"
	local event_wild2="$DEMO_EVENT1"

	echo ""
	echo "=== Simple wildcard 2"

	enable_ust_lttng_event $SESSION_NAME $event_wild1
	enable_ust_lttng_event $SESSION_NAME $event_wild2

	start_lttng_tracing $SESSION_NAME >/dev/null 2>&1

	run_demo_app

	stop_lttng_tracing $SESSION_NAME >/dev/null 2>&1

	trace_match_all_demo_events
	return $?
}

# Expected: all CRIT events, + all warning events.
test_enable_loglevel_overlap()
{
	local event_wild1="us*"
	local event_wild2="ust*"

	echo ""
	echo "=== Enable loglevel overlap"

	enable_ust_lttng_event_loglevel $SESSION_NAME "$event_wild1" "TRACE_WARNING"
	enable_ust_lttng_event_loglevel $SESSION_NAME "$event_wild2" "TRACE_CRIT"

	start_lttng_tracing $SESSION_NAME >/dev/null 2>&1

	run_demo_app

	stop_lttng_tracing $SESSION_NAME >/dev/null 2>&1

	trace_match_all_demo_events
	return $?
}

# Expected: all CRIT events, + all warning events.
test_enable_loglevel_only_overlap()
{
	local event_wild1="us*"
	local event_wild2="ust*"

	echo ""
	echo "=== Enable loglevel only overlap"

	enable_ust_lttng_event_loglevel $SESSION_NAME "$event_wild1" "TRACE_WARNING"
	enable_ust_lttng_event_loglevel_only $SESSION_NAME "$event_wild2" "TRACE_CRIT"

	start_lttng_tracing $SESSION_NAME >/dev/null 2>&1

	run_demo_app

	stop_lttng_tracing $SESSION_NAME >/dev/null 2>&1

	trace_match_all_demo_events
	return $?
}

# Expected: all events
test_enable_loglevel_overlap_2()
{
	local event_wild1="us*"
	local event_wild2="$DEMO_EVENT2"

	echo ""
	echo "=== Enable loglevel overlap 2"

	enable_ust_lttng_event_loglevel $SESSION_NAME "$event_wild1" "TRACE_WARNING"
	enable_ust_lttng_event_loglevel $SESSION_NAME "$event_wild2" "TRACE_CRIT"

	start_lttng_tracing $SESSION_NAME >/dev/null 2>&1

	run_demo_app

	stop_lttng_tracing $SESSION_NAME >/dev/null 2>&1

	trace_match_all_demo_events
	return $?
}

# Expected only ust_tests_demo* events.
test_enable_same_wildcard_loglevels()
{
	local event_wild1="ust*"
	local event_wild2="ust*"

	echo ""
	echo "=== Enable same wildcard with different loglevels"

	enable_ust_lttng_event_loglevel $SESSION_NAME "$event_wild1" "TRACE_CRIT"
	enable_ust_lttng_event_loglevel $SESSION_NAME "$event_wild2" "TRACE_WARNING"

	start_lttng_tracing $SESSION_NAME >/dev/null 2>&1

	run_demo_app

	stop_lttng_tracing $SESSION_NAME >/dev/null 2>&1

	trace_match_all_demo_events
	return $?
}

# Expected only ust_tests_demo:starting events.
test_enable_same_event_loglevels()
{
	local event_wild1="$DEMO_EVENT1"
	local event_wild2="$DEMO_EVENT1"

	echo ""
	echo "=== Enable same event with different loglevels"

	enable_ust_lttng_event_loglevel $SESSION_NAME "$event_wild1" "TRACE_CRIT"
	enable_ust_lttng_event_loglevel $SESSION_NAME "$event_wild2" "TRACE_WARNING"

	start_lttng_tracing $SESSION_NAME >/dev/null 2>&1

	run_demo_app

	stop_lttng_tracing $SESSION_NAME >/dev/null 2>&1

	trace_matches $DEMO_EVENT1 $NUM_DEMO1_EVENT $TRACE_PATH
	trace_matches $DEMO_EVENT1_2 0 $TRACE_PATH
	trace_matches $DEMO_EVENT2 0 $TRACE_PATH
	trace_matches $DEMO_EVENT3 0 $TRACE_PATH
	return $?
}

# Expect 0 event
test_disable_simple_wildcard()
{
	local event_wild1="us*"
	local event_wild2="$DEMO_EVENT1"

	echo ""
	echo "=== Disable simple wildcard"

	enable_ust_lttng_event $SESSION_NAME $event_wild1
	enable_ust_lttng_event $SESSION_NAME $event_wild2

	disable_ust_lttng_event $SESSION_NAME $event_wild1
	disable_ust_lttng_event $SESSION_NAME $event_wild2

	start_lttng_tracing $SESSION_NAME >/dev/null 2>&1

	run_demo_app

	stop_lttng_tracing $SESSION_NAME >/dev/null 2>&1

	# No events are expected.
	trace_match_no_demo_events
	return $?
}

# Expect only "ust_tests_demo" events.
test_disable_wildcard_overlap()
{
	local event_wild1="us*"
	local event_wild2="$DEMO_EVENT1"

	echo ""
	echo "=== Disable wildcard overlap"

	enable_ust_lttng_event $SESSION_NAME $event_wild1
	enable_ust_lttng_event $SESSION_NAME $event_wild2

	disable_ust_lttng_event $SESSION_NAME $event_wild1

	start_lttng_tracing $SESSION_NAME >/dev/null 2>&1

	run_demo_app

	stop_lttng_tracing $SESSION_NAME >/dev/null 2>&1

	# Expect only "ust_tests_demo" events.
	trace_matches $DEMO_EVENT1 $NUM_DEMO1_EVENT $TRACE_PATH
	trace_matches $DEMO_EVENT1_2 0 $TRACE_PATH
	trace_matches $DEMO_EVENT2 0 $TRACE_PATH
	trace_matches $DEMO_EVENT3 0 $TRACE_PATH
	return $?
}

TESTS=(
	"test_enable_wildcard_filter"
	"test_enable_wildcard_filter_2"
	"test_enable_wildcard_filter_3"
	"test_enable_wildcard_filter_4"
	"test_enable_wildcard_filter_5"
	"test_enable_wildcard_filter_6"
	"test_enable_wildcard_filter_7"
	"test_enable_wildcard_filter_8"
	"test_enable_same_wildcard_filter"
	"test_enable_same_wildcard_filter_2"
	"test_enable_same_wildcard_filter_3"
	"test_enable_same_wildcard_filter_4"
	"test_enable_same_event_filter"
	"test_enable_loglevel_only_overlap"
	"test_enable_same_event_loglevels"
	"test_enable_same_wildcard_loglevels"
	"test_enable_bad_wildcard"
	"test_enable_loglevel_overlap_2"
	"test_enable_simple_wildcard"
	"test_enable_simple_wildcard_2"
	"test_enable_loglevel_overlap"
	"test_disable_simple_wildcard"
	"test_disable_wildcard_overlap"
)

TEST_COUNT=${#TESTS[@]}
i=0

start_lttng_sessiond

while [ "$i" -lt "$TEST_COUNT" ]; do

	TRACE_PATH=$(mktemp -d)

	create_lttng_session $SESSION_NAME $TRACE_PATH >/dev/null 2>&1

	# Execute test
	${TESTS[$i]}
	if [ $? -ne 0 ]; then
		stop_lttng_sessiond
		exit 1
	fi

	destroy_lttng_session $SESSION_NAME >/dev/null 2>&1

	rm -rf $TRACE_PATH

	let "i++"
done

stop_lttng_sessiond