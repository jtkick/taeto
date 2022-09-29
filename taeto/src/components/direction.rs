use fixed::{types::extra::U8, FixedU8};

pub type Q8 = FixedU8<U8>;

pub struct Direction {
    /// For simplicity, I have decided not to normalize any component values, and just assume
    /// that whoever is using this struct normalizes the values themselves
    pub x: Q8,
    pub y: Q8,
    pub z: Q8,
}

impl Direction {
    pub fn magnitude(&self) -> Q8 {
        Q8::from_num((f64::from(self.x).powi(2) +
                      f64::from(self.y).powi(2) +
                      f64::from(self.z).powi(2)).sqrt())
    }

    pub fn new() -> Direction {
        Direction {
            x: Q8::MIN,
            y: Q8::MIN,
            z: Q8::MAX,
        }
    }
}
