use crate::components::color::Color;
use crate::components::direction::Direction;

/// An object pixel is everything that is needed to render a pixel, and nothing more
pub struct Pixel {
	/// Actual character that will appear
	pub c: char,

	/// Color of space behind the character
	pub background_color: Color,

	/// Color of character that will be rendered
	pub foreground_color: Color,

	/// Whether or not this pixel will be bold
	pub bold: bool,

    // Whether the char is italicized
    pub italic: bool,

    // Whether or not the pixel is underlined
    pub underline: bool,

    // Whether the character has a line through it
    pub strikethrough: bool,

	// Normal vector
	pub normal: Direction,
}

// NOTE TO SELF: Make each object have, optionally, a 2D array of renderable pixels, a
// 2D array of bools for collision, and what not, and 2D array of Direction for normal map

impl Pixel {
	pub fn new() -> Pixel {
		Pixel {
			c: ' ',
			background_color: Color::new(),
			foreground_color: Color::new(),
			bold: false,
			italic: false,
			underline: false,
			strikethrough: false,
			normal: Direction::new(),
		}
	}
}

impl Clone for Pixel {
	fn clone(&self) -> Pixel {
		Pixel::new()
	}
}
