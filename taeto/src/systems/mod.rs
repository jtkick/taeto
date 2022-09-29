pub mod display_system;
pub mod input_system;
pub mod render_system;

use crate::components::pixels::Pixel;
pub type Frame = Vec<Vec<Pixel>>;

pub trait System {
    fn initialize(&self);

    fn shutdown(&self);
}
