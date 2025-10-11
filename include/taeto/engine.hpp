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
#include "taeto/objects/object.hpp"
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
 * This enumeration is used to specify how an object is loaded into the engine.
 * For example, by default an object may be loaded in to be an object that is
 * in the game world, but another might be loaded to be a hud element to always
 * reside in the same place on the screen with a specific size. This enum
 * allows the user to specify when loading the object.
 */
enum class Context {
    kSkyboxSpace = 0,
    kWorldSpace,
    kScreenSpace,
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
 * @brief Loads an object into the engine.
 * 
 * @details Loads a game object into the engine world to be rendered and
 * otherwise interact with other objects. If the object has already been loaded, it
 * will simply be ignored. Unloading is done by destroying the source shared
 * pointer to the object.
 *
 * @param object A weak_ptr to the object to be loaded.
 *
 * @code
 * // Create an object using std::shared_ptr
 * auto rect = std::make_shared<taeto::Rectangle>(10, 10);
 *
 * // Load into the engine for rendering
 * taeto::load_object(rect);
 * @endcode
 */
void load_object(
    std::weak_ptr<Object> object,
    Context context = Context::kWorldSpace);

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
