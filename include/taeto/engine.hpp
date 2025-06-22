#ifndef ENGINE_HPP_
#define ENGINE_HPP_

#include <curses.h>

#include <chrono>
#include <cmath>
#include <iostream>
#include <memory>
#include <vector>

#include "spdlog/spdlog.h"

#include "systems/physics_system.hpp"
#include "taeto/objects/camera.hpp"
#include "taeto/objects/lights/light.hpp"
#include "taeto/objects/object.hpp"
#include "taeto/objects/sprites/sprite.hpp"
#include "taeto/scenes/scene.hpp"
#include "taeto/systems/render_system/render_system.hpp"
#include "taeto/widgets/widget.hpp"

namespace taeto
{

/**
 * This struct contains all of the engine's settings, including the settings
 * options of the component systems within the engine.
 */
struct EngineSettings {
    // Engine system settings
    // AudioSettings audio_settings;
    // ChemistrySettings chemistry_settings;
    // DisplaySettings display_settings;
    // InputSettings input_settings;
    // PhysicsSettings physics_settings;
    RenderSettings render_settings;
    // TimingSettings timing_settings;
    // Engine specific settings
    bool debug_mode = false;
    
};

/**
 * Gets the camera object that the engine is currently using to render a scene.
 *
 * @returns A reference to the camera object.
 */
Camera& camera();

/**
 * Gets the current state of the input with the given ID.
 * 
 * @param[in] id The ID number of the input being requested.
 * @return The state of the input where 1.0 is fully pressed and 0.0 is not
 * pressed at all.
 * @throws std::invalid_argument If the given ID does not relate to an
 * input that has been mapped to a key yet.
 */
float key_state(int id);

/**
 * @brief Loads a sprite into the engine.
 * 
 * @details Loads a sprite game object into the engine world to be rendered and
 * otherwise interact with other objects. If the sprite has already been loaded, it
 * will simply be ignored. Unloading is done by destroying the source shared
 * pointer to the sprite.
 *
 * @param sprite A weak_ptr to the sprite to be loaded.
 *
 * @code
 * // Create a sprite using std::shared_ptr
 * auto rect = std::make_shared<taeto::Rectangle>(10, 10);
 *
 * // Load into the engine for rendering
 * taeto::load_sprite(rect);
 * @endcode
 */
void load_sprite(std::weak_ptr<Sprite> sprite);

/**
 * @brief Loads a light into the engine. If the light has already been loaded, it will
 * simply be ignored. Unloading is done by destroying the source shared pointer
 * to the light.
 *
 * @param light A weak_ptr to the light to be loaded.
 */
void load_light(std::weak_ptr<Light> light);

/**
 * Loads a widget into the engine. If the widget has already been loaded, it
 * will simply be ignored. Unloading is done by destroying the source shared
 * pointer to the widget.
 *
 * @param sprite A weak_ptr to the widget to be loaded.
 */
void load_widget(std::weak_ptr<widgets::Widget> widget);

/**
 * Loads a scene into the engine. When loaded, any previous scene will be
 * dropped, along with all objects that had been loaded with that scene.
 *
 * @param scene A weak_ptr to the scene to be loaded.
 */
void load_scene(std::shared_ptr<Scene> scene);

/**
 * Continually render and display frames until program stopped.
 */
void run();

/**
 * Gets whether or not debug mode is currently on.
 *
 * @return True is debug mode is on.
 */
bool debug_mode();

/**
 * Set whether or not debug information will be printed to screen, as well as
 * logging at the debug level instead of the info level.
 *
 * @param debug_mode_on Whether or not the engine should print debug info.
 */
void debug_mode(bool);

EngineSettings& settings();

}   // namespace taeto

#endif  // ENGINE_HPP_
