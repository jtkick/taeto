/**
 * @file irenderable.hpp
 * @brief Definition of the renderable object interface.
 * @details This file contains the definitions of methods that an object must
 * define in order to be rendered in the Taeto engine.
 */

#ifndef OBJECT_IRENDERABLE_HPP_
#define OBJECT_IRENDERABLE_HPP_

#include <memory>
#include <vector>

#include "taeto/components/render_pixel.hpp"
#include "taeto/objects/ishaped.hpp"
#include "taeto/shaders/shader.hpp"

namespace taeto
{

/**
 * @class IRenderable
 * @brief An interface defining how an object implements the ability to be
 * rendered on the screen as a widget or an object.
 */
class IRenderable : public IShaped
{
public:
    /**
     * @brief Gets the pixel at the given position.
     * @details When the engine goes to render a pixel, it determines what
     * position on the object corresponds to the relevant position in the game
     * world, and then gets it with this function. This function returns what
     * the object looks like at the given position relative to the object's
     * origin.
     * @param pos Position of pixel relative to the object's position.
     */
    virtual RenderPixel pixel_at(const glm::uvec2& pos) = 0;

    /**
     * @brief Defines whether the object responds to dynamic lights.
     * @details If this method returns True, the engine will determine what
     * color and how bright an object is based on lights loaded into the
     * engine. If False, the object will look the same as what pixel_at()
     * returns.
     * @return bool Whether or not to use dynamic lighting.
     */
    virtual bool respect_light_sources() { return rls_; };

    virtual void respect_light_sources(bool rls) { rls_ = rls; };

    /**
     * @brief Defines whether or not this object should be rendered.
     * @details If set to false, the object will not be rendered even when it is
     * loaded in the engine.
     */
    virtual void render(bool r) { render_ = r; };
    virtual bool render() { return render_; };

    /**
     * @brief Loads a shader to adjust the look of the object.
     * @details Adds a shader that will apply to all pixels rendered with this
     * object.
     */
    virtual void load_shader(std::shared_ptr<shaders::Shader> shader)
    {
        shaders_.push_back(shader);
    };

    /**
     * @brief Returns a list of all the shaders applied to this object.
     * @returns std::vector<std::shared_ptr<Shader>> List of shaders
     */
    virtual std::vector<std::shared_ptr<shaders::Shader>> shaders()
    {
        return shaders_;
    };

private:
    bool rls_ = false;
    bool render_ = true;
    std::vector<std::shared_ptr<shaders::Shader>> shaders_;
};

}   // namespace taeto

 #endif // OBJECT_RENDERABLE_HPP_