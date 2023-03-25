#ifndef ENGINE_H_
#define ENGINE_H_

#include <curses.h>

#include <chrono>
#include <cmath>
#include <iostream>
#include <memory>
#include <vector>

#include "spdlog/spdlog.h"

#include "components/camera.hpp"
#include "components/light.h"
#include "components/sprite.h"
#include "scenes/scene.hpp"

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
 * Loads a light into the engine.
 * Is a weak pointer because the owner of the light can destroy the
 * light at any time and the engine will drop its weak pointer.
 *
 * @param sprite_ptr A weak_ptr to the sprite to be loaded.
 */
void load_light(std::weak_ptr<Light>);

/**
 * Loads a sprite into the engine.
 * Is a weak pointer because the owner of the sprite can destroy the
 * sprite at any time and the engine will drop its weak pointer.
 *
 * @param sprite_ptr A weak_ptr to the sprite to be loaded.
 */
void load_sprite(std::weak_ptr<Sprite>);

/**
 * Loads a scene into the engine.
 *
 * @param scene A Scene object that the engine will load
 */
void load_scene(std::shared_ptr<Scene>);

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

#endif  // ENGINE_H_
