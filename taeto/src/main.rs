#![crate_name = "taeto"]

pub mod components;
pub mod systems;

use term_size;
use std::{thread, time::Duration};
use ctrlc;
use std::sync::atomic::{AtomicBool, Ordering};
use std::sync::Arc;

use systems::{display_system, Frame, render_system::RenderSystem};
use components::color::{Q8, Color};
use components::direction::{Direction};
use components::pixels::Pixel;

fn main() {
    
    display_system::initialize();

    // Run flag for main game loop
    let run = Arc::new(AtomicBool::new(true));
    let run_flag = run.clone();

    ctrlc::set_handler(move || {
        display_system::destroy();
        run_flag.store(false, Ordering::SeqCst);
    }).expect("Error setting Ctrl-C handler");

    let test_pixel = Pixel {
    	c: ' ',
    	background_color: Color {red: Q8::MIN, green: Q8::MIN, blue: Q8::MIN, alpha: Q8::MAX},
    	foreground_color: Color {red: Q8::MAX, green: Q8::MAX, blue: Q8::MAX, alpha: Q8::MAX},
    	bold: false,
        italic: false,
        underline: false,
        strikethrough: false,
        normal: Direction {x: Q8::MIN, y: Q8::MIN, z: Q8::MAX},
    };

    // Get terminal dimensions
    let (w, h) = match term_size::dimensions() {
        Some((x, y)) => (x, y),
        None => panic!("Oh god, oh fuck!"),
    };

    // Create from from terminal dimensions
    let mut frame = vec![vec![Pixel::new(); w]; h];

    let mut rs = RenderSystem::new();

    while run.load(Ordering::SeqCst) {
        rs.render_alpha(&mut frame);
        rs.render_frame(&mut frame);
        rs.render_stats(&mut frame);
        display_system::display_frame(&frame);
    }
}
