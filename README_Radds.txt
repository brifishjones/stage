Dave,

I've ironed out more bugs and am at a point soon to ship you a version
of openGL program.  I believe I've fixed most of the bugs in the inverse
kinematics for the staubli robot.  Lefty, Elbow up, and Wrist Flip
appear functional.  Note that joints values computed are the same
as a puma 560 because I used the example in Craig's book.  Also,
don't have proper joint limits.  You can enter them by pushing Setup
button when robot dialog is displayed.

"Snap to" works for Coordinates (i.e. tags), parts, polygon centers,
edges, edge centers, and vertices most of the time.  Occasionally
an adjacent polygon is picked but most of the time "Snap To"
appears to be correct.  To snap to something open a part dialog,
by double clicking on the part, choose "Snap To" and pick a
point in the openGL window.

It's easy to put a tag on the robot TCF.  First create a path and
associate it with a part (like a table).  The tags themselves are
each numbered, and when a new tag is created, autonumbered.
Position the robot, create the tag (or select an existing tag), then
choose Tag on TCF.

To move around the workcell:
Left mouse click selects a part or tag.
Left mouse double click opens dialog for selected part or tag.
Right mouse click aims camera at pick point.
Right mouse down and moving pans in and out.
Left mouse down and moving either walks or pans depending on
	buttons to left of main openGL window.

To enable a RADDS connect, click the upper left button with
a rectangle on it.  When it turns yellow RADDS can connect.
Default port is 1650.

The following RADDS commands are now functional:
	mcMoveTo
	mcMoveTo <robotName> <pathName > <tagNumber>
	mcMoveTo rx130North b 1

	mcMoveAppro
	mcMoveAppro <robotName> <pathName > <tagNumber> <offset in mm>
	mcMoveTo rx130North b 1 250.0

	mcConfigureRobot
	mcConfigureRobot <lefty> <elbowup> <wristFlipped>
	mcConfigureRobot 1 1 0   (leftly, elbowUp, wrist not Flipped)

	mcSetSpeed
	mcSetSpeed <speed (0.0-1.0)>
	mcSetSpeed 0.2

	mcAttach
	mcAttach <deviceName> <attachToDeviceName> <attachToPartName>
	mcAttach cannisterGreen rx130north J6
	(note: you don't have to detach a device before reattaching)

	mcDetach
	mcDetach <deviceName>
	mcDetach cannisterGreen

Do these follow the RADDS convention?

I do not have asynchronous command capability at
present but I'm working on it, so for now only do
one thing at a time.

I've just created a rotary table object.  Double click
the table enter an end position, and click the Go button.
Don't Home, and don't try anything with RADDS connected.
 R.T. is still buggy.

I'll be makeing scale, gripper, and bar code reader
classes in the next few weeks, so hopefully there will be a
basic working version of the lab soon.

-------------------------------------------------------

Database:

Have revised command set so that it makes more sense.
Tell me what you think and ask Wood/Beer for a go-ahead.
If we can get DB integrated it may help to define levels up
from RADDS workcells.

command_type:
	L	manager login
	O	manager logout
	I	instantaneous RADDS command (like a bar code read, or scale weigh)
	B	RADDS command with beginning and ending time (B signifies start of command)
	E	RADDS command with beginning and ending time (E signifies end of command)
		
syntax: varies with command type
	<radds_id> L <employee_id> <timestamp>
	<radds_id> O <login_record_primary_key_from_database> <timestamp>
	<radds_id> I <"command"> <timestamp>
	<radds_id> B <"command"> <timestamp>
	<radds_id> E <command_record_primary_key_from_database> <timestamp>

timestamp: year-month-day [hour:minute:second.millisecond]
	(year is 4 digits, 24 hour clock, Greenwich Mean Time)

return values: <command_char> <primary_key_from_database_for_command> (success)
	X (error)

examples:
5002 L 5 1998-12-30 [18:50:09.160]					login for employee id 5
									(returned to RADDS: L 500)
5002 I "mcBarCode bcr5 100000560009 cannisterGreen"		bar code reader 5 obtains UPC-A code
	 1998-12-30 [18:51:34.345]					for the device named cannisterGreen
									(returned to RADDS: I 501)
5002 B "mcMoveTo rx130North t 5"					begin move of rx130North robot to path
	1998-12-30 [18:51:55.887]					named t, tag #5
									(returned to RADDS: B 502)
5002 E 502 1998-12-30 [18:52:03.026]					rx130North has reached tag t5--end of move
									(returned to RADDS: E 502)
5002 B "mcMoveTo rx130South s 1"				begin move of rx130South robot to path
	1998-12-30 [18:52:44.281]					named s, tag #1
									(invalid move returned to RADDS: X)
5002 O 500 1998-12-30 [18:53:20.19]					employee id 5 logged off
									(returned to RADDS: O 500)





