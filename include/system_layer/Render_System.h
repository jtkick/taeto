#ifndef RENDER_SYSTEM_H
#define RENDER_SYSTEM_H

#include <stuff>

class Render_System
{

    // Sprites to be rendered
    vector<Sprite*> sprites;

    // Light sources
    vector<Light*> lights;

    // Current frame rate of render system
    // List of times each frame was rendered
    vector<time> frame_times;

    // Camera position
    long int camera_x_position;
    long int camera_y_position;
    long int camera_z_position;

    // If set to true, engine information is added to top-left of frame
    bool display_debug_info;

    public:

        // Contructor
        Render_System(void);

	// Destructor
	~Render_System(void);

	// Read messages from message bus
	void handle_message(Message* message);

    // These methods are for doing work in this system
    // They are private since all calls to do work should be done
    // using the message bus
    private:

        // Move camera to specified location
	void move_camera(long int, long int, long int);

	// Used to render new frame
	void render_frame(Frame*);

};

#endif
