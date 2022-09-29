use crate::components::pixels::Pixel;
use crate::components::color::Q8;
use crate::systems::Frame;

use std::time::{SystemTime, UNIX_EPOCH};

// Because I like OOP
pub struct RenderSystem {

    pub camera_location: [i64; 3],

    // For calculating frame rate
    averaging_second: u64,
    frame_rate_count: u64,
    pub frame_rate: u64,

    // Just overall frame number
    pub frame_count: u64,
}

impl RenderSystem {

    pub fn new() -> RenderSystem {
        // Yo
        print!("Welcome to Flavortown!");
        RenderSystem {
            camera_location: [0, 0, 0],
            averaging_second: 0,
            frame_rate_count: 0,
            frame_rate: 0,
            frame_count: 0,
        }
    }

    pub fn render_alpha(&self, frame: &mut Frame) {
        for (y, row) in frame.iter_mut().enumerate() {
            for (x, pixel) in row.iter_mut().enumerate() {
                if (x % 4 < 2) != (y % 2 < 1) {
                    pixel.background_color.red = Q8::MAX;
                    pixel.background_color.green = Q8::MAX;
                    pixel.background_color.blue = Q8::MAX;
                } else {
                    pixel.background_color.red = Q8::from_num(0.5 as f64);
                    pixel.background_color.green = Q8::from_num(0.5 as f64);
                    pixel.background_color.blue = Q8::from_num(0.5 as f64);
                }
            }
        }
    }

    pub fn render_frame(&self, frame: &mut Frame) {

        // Write alpha background texture for debugging missing assets
        if True {
            render_alpha(frame);
        }

        // Ensure proper focal length
        !assert(self.focal_length > 0);

        // Loop over each pixel in frame
        for row in frame {
            for rendered_pixel in row{

                // Reset pixel
                rendered_pixel.clear();

            }
        }

        for row in frame {
            for pixel in row {
                pixel.c = ' ';
            }
        }
    }

    pub fn render_stats(&mut self, frame: &mut Frame) {

        // Calculate FPS
        let now = match SystemTime::now().duration_since(UNIX_EPOCH) {
            Ok(secs) => secs,
            Err(error) => panic!("Well suck me silly, there's no time left."),
        }.as_secs();

        // If on new second, reset frame rate and start counting again
        if now != self.averaging_second {
            self.frame_rate = self.frame_rate_count;
            self.frame_rate_count = 0;
            self.averaging_second = now;
        } else {
            self.frame_rate_count += 1;
        }

        // Add frame rate to stats to be printed
        let mut lines = vec![String::new(); 6];
        lines[0] = String::from("FPS: ") + &self.frame_rate.to_string();

        // Add current frame number
        self.frame_count += 1;
        lines[1] = String::from("Current frame: ") + &self.frame_count.to_string();

        // Number of sprites
        lines[2] = String::from("Num sprites loaded: 0");

        // Number of lights
        lines[3] = String::from("Num lights loaded: 0");

        // Camera location
        lines[4] = String::from("Camera location: (0, 0, 0)");

        // Will to live
        lines[5] = String::from("Will to live: 0.5");

        // Write all lines to frame
        for (row_num, line) in lines.iter().enumerate() {

            // Render stats
            let row = match frame.get_mut(row_num) {
                Some(row) => row,
                None => panic!("Definitely bones!"),
            };

            // Write string to row
            for (i, c) in line.chars().enumerate() {
                let pixel = match row.get_mut(i) {
                    Some(pixel) => pixel,
                    None => panic!("Nun so sei mein liebes Weibchen!"),
                };
                pixel.c = c;
                pixel.background_color.red = Q8::MIN;
                pixel.background_color.green = Q8::MIN;
                pixel.background_color.blue = Q8::MIN;
            }
        }
    }
}
