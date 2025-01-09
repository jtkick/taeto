#ifndef FRAMES_FRAME_HPP_
#define FRAMES_FRAME_HPP_

#include <functional>
#include <string>
#include <vector>

#include <glm/glm.hpp>

namespace taeto
{

template <class T>
class Frame
{
public:
    Frame()
    {
        resize(glm::uvec2(0, 0), T());
    };

    Frame(glm::uvec2 shape, T t = T())
    {
        resize(shape, t);
    };

    /**
     * Returns the value at the given y and x coordinates.
     *
     * @param y Row of vector to get value from.
     * @param x Collumn of selected row to get value from.
     * @return T A reference to the value at the given location.
     */
    inline constexpr T& at(glm::uvec2 pos)
    {
        return values_.at(pos.y).at(pos.x);
    };
    // inline constexpr const T& at(int y, int x) const { return values_.at(y).at(x); };


    /**
     * Returns the current height of the frame.
     *
     * @return The height of the frame.
     */
    inline unsigned int height() const { return values_.size(); };


    /**
     * Returns the current width of the frame.
     *
     * @return The width of the frame.
     */
    inline unsigned int width() const
    {
        if (values_.size() == 0)
            return 0;
        else
            return values_.at(0).size();
    };


    /**
     * Returns the dimensions of the frame with a uvec2.
     *
     * @return The height and width of the frame
     */
    inline glm::uvec2 size() const
    {
        return glm::uvec2(height(), width());
    };


    /**
     * Resizes the frame to the given height and width, with all new values
     * initialized with the given object.
     *
     * @param h New height of the frame.
     * @param w New width of the frame.
     * @param value Value of any new instances of the frame type.
     */
    void resize(glm::uvec2 shape, T t = T())
    {
        values_.resize(shape.y, std::vector<T>(shape.x, t));
    };


    /**
     * Writes the given frame over top of this frame, replacing whatever was
     * already there.
     *
     * @param y Row to write to
     * @param x Column to write to
     * @param frame Other frame
     */
    void overwrite(const Frame<T>& frame, glm::uvec2 pos)
    {
        // Just use the apply function for simplicity
        apply(frame, pos.y, pos.x, false, [](T t1, T t2){ return t2; });
    };


protected:

    /**
     * This method is designed to allow for getting data members from the
     * underlying value types in an easy way. e.g. instead of defining a dozen
     * methods that all get foreground_color from pixel and all the others,
     * frames can just call this method with a function defining how to get the
     * member from the value.
     */
    template<class U>
    const Frame<U>& extract_member_frame(std::function<U(T)>& extractor) const
    {
        taeto::Frame<U> frame(height(), width());
        for (int i = 0; i < frame.height(); ++i)
            for (int j = 0; j < frame.width(); ++j)
                frame.at(i, j) = extractor(at(i, j));
        return frame;

    }

    // template<class U>
    // void apply_member_frame(std::function<(T))

    // const Frame<T>& displace(const ColorFrame& frame)
    // {
    //
    // }
    //
    // const Frame<T>& displace(const UCharFrame& frame)
    // {
    //
    // }
    //
    // const Frame<T>& displace(const CharFrame& frame)
    // {
    //
    // }

    /**
     * Overwrite the second given two-dimensional vector onto the first
     * two-dimensional vector at the given location.
     *
     * @param other Frame<T> to be written onto this frame.
     * @param y Row of the first frame to begin writing the second to.
     * @param x Collumn of the row to begin writing the second frame to.
     * @param tile True if the function should tile the second frame on.
     */
public:
    void apply(
        Frame<T>& other,
        glm::uvec2 pos,
        bool tile,
        std::function<T&(T&, T&)> func)
    {
        // If tiling, dimensions are across the entire frame
        unsigned int top = tile ? 0 : pos.y;
        unsigned int bottom =
            tile ? height()-1 : std::min(pos.y + other.height() - 1, height());
        unsigned int left = tile ? 0 : pos.x;
        unsigned int right =
            tile ? width()-1 : std::min(pos.x + other.width() - 1, width());

        // Start applying values
        int o_h = other.height();
        int o_w = other.width();
        for (int i = top; i < bottom; ++i)
            for (int j = left; j < right; ++j)
                at({i, j}) = func(
                    at({i, j}),
                    other.at({(i % o_h + o_h) % o_h, (j % o_w + o_w) % o_w})
                );
    }


    /**
     * Serializes the frame into a format that can be used to initialize
     * a new frame.
     *
     * @param serialize Function to serialize the values contained within this
     *                  frame
     * @return String containing values to initialize a frame.
     */
    std::string serialize(std::function<std::string(const T&)> serialize)
    {
        std::string s = "{{";
        for (int i = 0; i < height(); i++)
        {
            s += "{";
            for (int j = 0; j < width(); j++)
            {
                s += serialize(values_.at(i).at(j));
                if (i != height() - 1) s += ",";
            }
            s += "}";
            if (i != height() - 1) s += ",";
        }
        s += "}}";
        return s;
    }

public:
    std::vector<std::vector<T>> values_;
};

}   // namespace taeto

#endif  // FRAMES_FRAME_HPP_
