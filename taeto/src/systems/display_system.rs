use termios::*;

use crate::systems::Frame;

// Temporary
use term_size;
use std::time::{SystemTime, UNIX_EPOCH};

pub fn initialize() {

    // Open alternate terminal screen
    print!("\x1b[?1049h");

    // Make cursor invisible
    print!("\x1b[?25l");

    // Turn off character echo
    let mut termios = Termios::from_fd(0).unwrap();
    termios.c_lflag &= !ECHO;
    tcsetattr(0, TCSANOW, &termios);

    // Change terminal title
    //print!("\x1b]0;Taeto\x3f");

}

static mut averaging_second: u64 = 0;
static mut frame_count: u64 = 0;
static mut frame_rate: u64 = 0;

pub fn display_frame(frame: & Frame) {

    let mut width;
    let mut height;
    if let Some((w, h)) = term_size::dimensions() {
        width = w;
        height = h;
    } else { panic!("bitch") };

    // let mut s = String::new();
    // s.push_str("\x1b[0;0H");

    for y in 0..height {
        for x in 0..width {
            let mut s = String::new();

            // Move to this row and collumn on screen
            if x == 0 && y == 0 {
                s.push_str("\x1b[");
                s.push_str(&(y+1).to_string());
                s.push_str(";");
                s.push_str(&(x+1).to_string());
                s.push_str("H");
            }

            s.push_str("\x1b[38;2;255;255;255m");

            let r = (f32::from(frame[y][x].background_color.red) * 255.0) as u8;
            let g = (f32::from(frame[y][x].background_color.green) * 255.0) as u8;
            let b = (f32::from(frame[y][x].background_color.blue) * 255.0) as u8;
            s += &format!("\x1b[48;2;{};{};{}m", r, g, b);

            //lines[0] = String::from("FPS: ") + &self.frame_rate.to_string();

            s.push(frame[y][x].c);

            print!("{}", s);
        }
    }

    //let period = time::Duration::from_millis(1);
    //thread::sleep(period);
}

pub fn destroy() {

    // Go back to original terminal screen
    print!("\x1b[?1049l");

    // Make cursor visible again
    print!("\x1b[?25h");

    // Turn character echo back on
    let mut termios = Termios::from_fd(0).unwrap();
    termios.c_lflag |= ECHO;
    tcsetattr(0, TCSANOW, &termios);

}
