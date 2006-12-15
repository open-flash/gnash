// 
//   Copyright (C) 2005, 2006 Free Software Foundation, Inc.
// 
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <map>
#include <iostream>
#include <string>
#include "log.h"
#include "dejagnu.h"
#include "fn_call.h"
#include "as_object.h"
#include "builtin_function.h" // need builtin_function

using namespace std;

namespace gnash
{

void dejagnu_pass(const fn_call& fn);
void dejagnu_fail(const fn_call& fn);
void dejagnu_totals(const fn_call& fn);

LogFile& dbglogfile = LogFile::getDefaultInstance();

class dejagnu_as_object : public as_object
{
public:
    DejaGnu obj;
};

static void
attachInterface(as_object *obj)
{
//    GNASH_REPORT_FUNCTION;

    obj->set_member("pass", &dejagnu_pass);
    obj->set_member("fail", &dejagnu_fail);
    obj->set_member("totals", &dejagnu_totals);
}

static as_object*
getInterface()
{
//    GNASH_REPORT_FUNCTION;
    static boost::intrusive_ptr<as_object> o;
    if (o == NULL) {
	o = new as_object();
    }
    return o.get();
}

static void
dejagnu_ctor(const fn_call& fn)
{
//    GNASH_REPORT_FUNCTION;
    dejagnu_as_object* obj = new dejagnu_as_object();

//    attachInterface(obj);
    fn.result->set_as_object(obj); // will keep alive
    printf ("Hello World from %s !!!\n", __PRETTY_FUNCTION__);
}


DejaGnu::DejaGnu() 
    : passed(0), failed(0), xpassed(0), xfailed(0)
{
//    GNASH_REPORT_FUNCTION;
}

DejaGnu::~DejaGnu()
{
//    GNASH_REPORT_FUNCTION;
}

const char *
DejaGnu::pass (const char *msg)
{
//    GNASH_REPORT_FUNCTION;

    passed++;
    dbglogfile << "PASSED: " << msg << endl;
}

const char *
DejaGnu::fail (const char *msg)
{
//    GNASH_REPORT_FUNCTION;

    failed++;
    dbglogfile << "FAILED: " << msg << endl;
}

void
dejagnu_pass(const fn_call& fn)
{
//    GNASH_REPORT_FUNCTION;
    dejagnu_as_object *ptr = (dejagnu_as_object*)fn.this_ptr;
    assert(ptr);
    
    if (fn.nargs > 0) {
	const char *text = fn.env->bottom(fn.first_arg_bottom_index).to_string();
	fn.result->set_string(ptr->obj.pass(text));
    }
}

void
dejagnu_fail(const fn_call& fn)
{
//    GNASH_REPORT_FUNCTION;
    dejagnu_as_object *ptr = (dejagnu_as_object*)fn.this_ptr;
    assert(ptr);
    
    if (fn.nargs > 0) {
	const char *text = fn.env->bottom(fn.first_arg_bottom_index).to_string();
	fn.result->set_string(ptr->obj.fail(text));
    }
}

void
dejagnu_totals(const fn_call& fn)
{
//    GNASH_REPORT_FUNCTION;
    dejagnu_as_object *ptr = (dejagnu_as_object*)fn.this_ptr;
    assert(ptr);
    
    ptr->obj.totals();
    fn.result->set_bool(true);
}

    
std::auto_ptr<as_object>
init_dejagnu_instance()
{
    return std::auto_ptr<as_object>(new dejagnu_as_object());
}

extern "C" {
    void
    dejagnu_class_init(as_object &obj)
    {
//	GNASH_REPORT_FUNCTION;
	// This is going to be the global "class"/"function"
	static boost::intrusive_ptr<builtin_function> cl;
	if (cl == NULL) {
	    cl = new builtin_function(&dejagnu_ctor, getInterface());
// 	    // replicate all interface to class, to be able to access
// 	    // all methods as static functions
 	    attachInterface(cl.get());
	}
	
	obj.set_member("DejaGnu", cl.get());
    }
} // end of extern C


} // end of gnash namespace

// Local Variables:
// mode: C++
// indent-tabs-mode: t
// End:
