pub trait Light {
    fn direction(&self, p: Point) -> Direction;

    fn color(&self, p: Point) -> Color;

    fn brightness(&self, p: Point) -> f64;
}

pub trait Renderable {
    fn current_frame(&self) -> Frame;

    fn location(&self) -> Point;
}

pub trait Collidable {

}

pub trait Physical {
    
}
