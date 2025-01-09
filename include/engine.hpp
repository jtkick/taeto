#ifndef ENGINE_HPP_
#define ENGINE_HPP_

#include <curses.h>

#include <chrono>
#include <cmath>
#include <iostream>
#include <memory>
#include <vector>

#include "spdlog/spdlog.h"

#include "components/camera.hpp"
#include "object/light.hpp"
#include "object/object.hpp"
#include "object/sprite.hpp"
#include "scenes/scene.hpp"
#include "systems/window_system/widget.hpp"

namespace taeto
{

/**
 * Returns a reference to a boolean that will change as button inputs change.
 *
 * @param ID number of the button to get a reference to.
 */
std::shared_ptr<bool> get_button_reference(int);

/**
 * Returns the camera object that the engine is using.
 */
taeto::Camera& get_camera();

/**
 * Loads an object into the engine.
 * Is a weak pointer because the owner of the object can destroy the
 * object at any time and the engine will drop its weak pointer.
 *
 * @param object_ptr A weak_ptr to the object to be loaded.
 */
void load_sprite(std::weak_ptr<Sprite>);
void load_light(std::weak_ptr<Light>);
void load_widget(std::weak_ptr<Widget>);

/**
 * Loads a scene into the engine.
 *
 * @param scene A Scene object that the engine will load
 */
void load_scene(std::shared_ptr<Scene>);

/**
 * Loads a widget, i.e., an in-game window that the user interacts with that
 * is independent of and usually in front of the rendered game world.
 *
 * @param widget A weak pointer to the widget to be displayed
 */
 void load_widget(std::weak_ptr<Widget>);

/**
 * Continually render and display frames until program stopped.
 */
void run();

/**
 * Set whether or not debug information will be printed to screen, as well as
 * logging at the debug level instead of the info level.
 *
 * @param debug_mode_on Whether or not the engine should print debug info.
 */
void set_debug_mode(bool);

}   // namespace taeto

#endif  // ENGINE_HPP_
