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

// Linking Gnash statically or dynamically with other modules is making a
// combined work based on Gnash. Thus, the terms and conditions of the GNU
// General Public License cover the whole combination.
//
// As a special exception, the copyright holders of Gnash give you
// permission to combine Gnash with free software programs or libraries
// that are released under the GNU LGPL and with code included in any
// release of Talkback distributed by the Mozilla Foundation. You may
// copy and distribute such a system following the terms of the GNU GPL
// for all but the LGPL-covered parts and Talkback, and following the
// LGPL for the LGPL-covered parts.
//
// Note that people who make modified versions of Gnash are not obligated
// to grant this special exception for their modified versions; it is their
// choice whether to do so. The GNU General Public License gives permission
// to release a modified version without this exception; this exception
// also makes it possible to release a modified version which carries
// forward this exception.
// 
//

#ifndef GNASH_MOVIE_DEFINITION_H
#define GNASH_MOVIE_DEFINITION_H

#include "container.h"
#include "button.h" // for mouse_button_state
#include "timers.h" // for Timer
#include "fontlib.h"
#include "font.h"
#include "jpeg.h"
#include "tu_file.h"

namespace gnash
{

/// Client program's interface to the definition of a movie
//
/// (i.e. the shared constant source info).
///
struct movie_definition : public character_def
{
	virtual int	get_version() const = 0;
	virtual float	get_width_pixels() const = 0;
	virtual float	get_height_pixels() const = 0;
	virtual int	get_frame_count() const = 0;
	virtual float	get_frame_rate() const = 0;
	
	/// Create a playable movie instance from a def.
	//
	/// This calls add_ref() on the movie_interface internally.
	/// Call drop_ref() on the movie_interface when you're done with it.
	/// Or use smart_ptr<T> from base/smart_ptr.h if you want.
	///
	virtual movie_interface*	create_instance() = 0;
	
	virtual void	output_cached_data(tu_file* out, const cache_options& options) = 0;
	virtual void	input_cached_data(tu_file* in) = 0;
	
	/// \brief
	/// Causes this movie def to generate texture-mapped
	/// versions of all the fonts it owns. 
	//
	/// This improves
	/// speed and quality of text rendering.  The
	/// texture-map data is serialized in the
	/// output/input_cached_data() calls, so you can
	/// preprocess this if you load cached data.
	///
	virtual void	generate_font_bitmaps() = 0;
	
	//
	// (optional) API to support gnash::create_movie_no_recurse().
	//
	
	/// \brief
	/// Call visit_imported_movies() to retrieve a list of
	/// names of movies imported into this movie.
	//
	/// visitor->visit() will be called back with the name
	/// of each imported movie.
	struct import_visitor
	{
	    virtual ~import_visitor() {}
	    virtual void	visit(const char* imported_movie_filename) = 0;
	};
	virtual void	visit_imported_movies(import_visitor* visitor) = 0;
	
	/// Call this to resolve an import of the given movie.
	/// Replaces the dummy placeholder with the real
	/// movie_definition* given.
	virtual void	resolve_import(const char* name, movie_definition* def) = 0;
	
	//
	// (optional) API to support host-driven creation of textures.
	//
	// Create the movie using gnash::create_movie_no_recurse(..., DO_NOT_LOAD_BITMAPS),
	// and then initialize each bitmap info via get_bitmap_info_count(), get_bitmap_info(),
	// and bitmap_info::init_*_image() or your own subclassed API.
	//
	// E.g.:
	//
	// // During preprocessing:
	// // This will create bitmap_info's using the rgba, rgb, alpha contructors.
	// my_def = gnash::create_movie_no_recurse("myfile.swf", DO_LOAD_BITMAPS);
	// int ct = my_def->get_bitmap_info_count();
	// for (int i = 0; i < ct; i++)
	// {
	//	my_bitmap_info_subclass*	bi = NULL;
	//	my_def->get_bitmap_info(i, (bitmap_info**) &bi);
	//	my_precomputed_textures.push_back(bi->m_my_internal_texture_reference);
	// }
	// // Save out my internal data.
	// my_precomputed_textures->write_into_some_cache_stream(...);
	//
	// // Later, during run-time loading:
	// my_precomputed_textures->read_from_some_cache_stream(...);
	// // This will create blank bitmap_info's.
	// my_def = gnash::create_movie_no_recurse("myfile.swf", DO_NOT_LOAD_BITMAPS);
	// 
	// // Push cached texture info into the movie's bitmap_info structs.
	// int	ct = my_def->get_bitmap_info_count();
	// for (int i = 0; i < ct; i++)
	// {
	//	my_bitmap_info_subclass*	bi = (my_bitmap_info_subclass*) my_def->get_bitmap_info(i);
	//	bi->set_internal_texture_reference(my_precomputed_textures[i]);
	// }
	virtual int	get_bitmap_info_count() const = 0;
	virtual bitmap_info*	get_bitmap_info(int i) const = 0;

	// From movie_definition_sub

	virtual const std::vector<execute_tag*>&	get_playlist(int frame_number) = 0;
	virtual const std::vector<execute_tag*>*	get_init_actions(int frame_number) = 0;
	virtual smart_ptr<resource>	get_exported_resource(const tu_string& symbol) = 0;
	virtual character_def*	get_character_def(int id) = 0;

	virtual bool	get_labeled_frame(const char* label, int* frame_number) = 0;

	// For use during creation.
	virtual int	get_loading_frame() const = 0;
	virtual void	add_character(int id, character_def* ch) = 0;
	virtual void	add_font(int id, font* ch) = 0;
	virtual font*	get_font(int id) = 0;
	virtual void	add_execute_tag(execute_tag* c) = 0;
	virtual void	add_init_action(int sprite_id, execute_tag* c) = 0;
	virtual void	add_frame_name(const char* name) = 0;
	virtual void	set_jpeg_loader(jpeg::input* j_in) = 0;
	virtual jpeg::input*	get_jpeg_loader() = 0;
	virtual bitmap_character_def*	get_bitmap_character(int character_id) = 0;
	virtual void	add_bitmap_character(int character_id, bitmap_character_def* ch) = 0;
	virtual sound_sample*	get_sound_sample(int character_id) = 0;
	virtual void	add_sound_sample(int character_id, sound_sample* sam) = 0;
	virtual void	export_resource(const tu_string& symbol, resource* res) = 0;
	virtual void	add_import(const char* source_url, int id, const char* symbol_name) = 0;
	virtual void	add_bitmap_info(bitmap_info* ch) = 0;

	virtual create_bitmaps_flag	get_create_bitmaps() const = 0;
	virtual create_font_shapes_flag	get_create_font_shapes() const = 0;
};

} // namespace gnash

#endif // GNASH_MOVIE_DEFINITION_H
