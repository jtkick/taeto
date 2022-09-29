use fixed::{types::extra::U8, FixedU8};

pub type Q8 = FixedU8<U8>;

pub struct Color {
    pub red: Q8,
    pub green: Q8,
    pub blue: Q8,
    pub alpha: Q8,
}

impl Color {
    pub fn new() -> Color {
        Color {
            red: Q8::MAX,
            green: Q8::MAX,
            blue: Q8::MAX,
            alpha: Q8::MAX,
        }
    }

    pub fn set_brightness(&mut self, brightness: f64) {
        self.red *= Q8::from_num(brightness);
        self.green *= Q8::from_num(brightness);
        self.blue *= Q8::from_num(brightness);
    }
}

impl std::ops::Add<Color> for Color {
    /// Implement the Color '+' operator
    type Output = Color;

    fn add(self, other: Color) -> Color {
        Color {
            red: self.red.saturating_add(other.red),
            green: self.green.saturating_add(other.green),
            blue: self.blue.saturating_add(other.blue),
            alpha: self.alpha.saturating_add(other.alpha)
        }
    }
}

impl std::ops::AddAssign<Color> for Color {
    /// Implement the Color '+=' operator
	//type Output = Color;

	fn add_assign(&mut self, other: Color) {
		*self = Color {
		    red: self.red.saturating_add(other.red),
		    green: self.green.saturating_add(other.green),
		    blue: self.blue.saturating_add(other.blue),
		    alpha: self.alpha.saturating_add(other.alpha),
		};
	}
}

impl std::ops::BitAnd<Color> for Color {
    /// Implement the Color '&' operator
	type Output = Color;

	fn bitand(self, other: Color) -> Color {
		let t_alpha: Q8 = Q8::from_num(f64::from(self.alpha) / 255.0);
		let c_alpha: Q8 = Q8::from_num(f64::from(other.alpha) / 255.0);

		Color {
			red: (self.red * t_alpha * (Q8::MAX - c_alpha)).saturating_add(other.red * c_alpha),
			green: (self.green * t_alpha * (Q8::MAX - c_alpha)).saturating_add(other.green * c_alpha),
			blue: (self.blue * t_alpha * (Q8::MAX - c_alpha)).saturating_add(other.blue * c_alpha),
			alpha: (t_alpha * (Q8::MAX - c_alpha).saturating_add(c_alpha)) * Q8::MAX,
		}
	}
}

impl std::ops::Mul<Color> for Color {
    /// Implement the Color '*' operator
	type Output = Color;

    fn mul(self, other: Color) -> Color {
        Color {
            red: self.red * other.red,
            green: self.green * other.green,
            blue: self.blue * other.blue,
            alpha: self.alpha,
        }
    }
}
