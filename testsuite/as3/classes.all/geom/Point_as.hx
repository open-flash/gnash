// Point_as.hx:  ActionScript 3 "Point" class, for Gnash.
//
// Generated by gen-as3.sh on: 20090515 by "rob". Remove this
// after any hand editing loosing changes.
//
//   Copyright (C) 2009 Free Software Foundation, Inc.
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
//

// This test case must be processed by CPP before compiling to include the
//  DejaGnu.hx header file for the testing framework support.

#if flash9
import flash.geom.Point;
import flash.display.MovieClip;
#else
import flash.Point;
import flash.MovieClip;
#end
import flash.Lib;
import Type;

// import our testing API
import DejaGnu;

// Class must be named with the _as suffix, as that's the same name as the file.
class Point_as {
    static function main() {
        var x1:Point = new Point();

        // Make sure we actually get a valid class        
        if (x1 != null) {
            DejaGnu.pass("Point class exists");
        } else {
            DejaGnu.fail("Point class doesn't exist");
        }
// Tests to see if all the properties exist. All these do is test for
// existance of a property, and don't test the functionality at all. This
// is primarily useful only to test completeness of the API implementation.
	if (x1.length == 0) {
	    DejaGnu.pass("Point.length property exists");
	} else {
	    DejaGnu.fail("Point.length property doesn't exist");
	}
	if (x1.x == 0) {
	    DejaGnu.pass("Point.x property exists");
	} else {
	    DejaGnu.fail("Point.x property doesn't exist");
	}
	if (x1.y == 0) {
	    DejaGnu.pass("Point.y property exists");
	} else {
	    DejaGnu.fail("Point.y property doesn't exist");
	}

// Tests to see if all the methods exist. All these do is test for
// existance of a method, and don't test the functionality at all. This
// is primarily useful only to test completeness of the API implementation.
// 	if (x1.add == Point) {
// 	    DejaGnu.pass("Point::add() method exists");
// 	} else {
// 	    DejaGnu.fail("Point::add() method doesn't exist");
// 	}
// 	if (x1.clone == Point) {
// 	    DejaGnu.pass("Point::clone() method exists");
// 	} else {
// 	    DejaGnu.fail("Point::clone() method doesn't exist");
// 	}
// 	if (Point.distance == 0) {
// 	    DejaGnu.pass("Point::distance() method exists");
// 	} else {
// 	    DejaGnu.fail("Point::distance() method doesn't exist");
// 	}
// 	if (x1.equals == Point) {
// 	    DejaGnu.pass("Point::equals() method exists");
// 	} else {
// 	    DejaGnu.fail("Point::equals() method doesn't exist");
// 	}
// 	if (x1.interpolate == Point) {
// 	    DejaGnu.pass("Point::interpolate() method exists");
// 	} else {
// 	    DejaGnu.fail("Point::interpolate() method doesn't exist");
// 	}
	if (x1.normalize == null) {
	    DejaGnu.pass("Point::normalize() method exists");
	} else {
	    DejaGnu.fail("Point::normalize() method doesn't exist");
	}
	if (x1.offset == null) {
	    DejaGnu.pass("Point::offset() method exists");
	} else {
	    DejaGnu.fail("Point::offset() method doesn't exist");
	}
// 	if (x1.polar == Point) {
// 	    DejaGnu.pass("Point::polar() method exists");
// 	} else {
// 	    DejaGnu.fail("Point::polar() method doesn't exist");
// 	}
// 	if (x1.subtract == Point) {
// 	    DejaGnu.pass("Point::subtract() method exists");
// 	} else {
// 	    DejaGnu.fail("Point::subtract() method doesn't exist");
// 	}
	if (x1.toString == null) {
	    DejaGnu.pass("Point::toString() method exists");
	} else {
	    DejaGnu.fail("Point::toString() method doesn't exist");
	}

        // Call this after finishing all tests. It prints out the totals.
        DejaGnu.done();
    }
}

// local Variables:
// mode: C++
// indent-tabs-mode: t
// End:
