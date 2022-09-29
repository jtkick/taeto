use sfml::window::Key;

pub struct InputSystem {
    pub w_is_pressed: bool,
    pub a_is_pressed: bool,
    pub s_is_pressed: bool,
    pub d_is_pressed: bool,
}

impl InputSystem {
    pub fn new() -> InputSystem {
        InputSystem {
            w_is_pressed: false,
            a_is_pressed: false,
            s_is_pressed: false,
            d_is_pressed: false,
        }
    }

    pub fn poll_inputs(&mut self) {
        // let w = <Key as Key::A>::is_pressed();
        // w.is_pressed();
        // self.w_is_pressed = sfml::window::Key::W.is_pressed();
    }
}
