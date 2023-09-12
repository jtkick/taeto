#ifndef FRAMES_FRAME_HPP_
#define FRAMES_FRAME_HPP_

#include <functional>
#include <string>
#include <vector>

namespace taeto
{

template <class T>
class Frame
{
public:
    Frame()
    {
        resize(0, 0, T());
    };

    // Frame(unsigned long int h, unsigned long int w, T t = T())
    // {
    //     resize(h, w, t);
    // };
    //
    // Frame(unsigned long int h, unsigned long int w)
    // {
    //     resize(h, w, T());
    // };


    // Frame(std::vector<std::vector<T>> v)
    // {
    //
    // };

    /**
     * Returns the value at the given y and x coordinates.
     *
     * @param y Row of vector to get value from.
     * @param x Collumn of selected row to get value from.
     * @return T A reference to the value at the given location.
     */
    inline T& at(int y, int x) { return values_.at(y).at(x); };

    /**
     * Returns the current height of the frame.
     *
     * @return The height of the frame.
     */
    inline unsigned int height() { return values_.size(); };


    /**
     * Returns the current width of the frame.
     *
     * @return The width of the frame.
     */
    inline unsigned int width()
    {
        if (values_.size() == 0)
            return 0;
        else
            return values_.at(0).size(0);
    };


    /**
     * Resizes the frame to the given height and width, with all new values
     * initialized with the given object.
     *
     * @param y New height of the frame.
     * @param x New width of the frame.
     * @param value Value of any new instances of the frame type.
     */
    void resize(int y, int x, T t = T())
    {
        values_.resize(y, t);
        for (std::vector<T> row : values_)
            row.resize(x, t);
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
    const Frame<U>& extract_member_frame(std::function<U(T)>& extractor)
    {

    }

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
    // void apply(
    //     Frame<T>& other,
    //     int y = 0,
    //     int x = 0,
    //     bool tile = false,
    //     std::function<T(T, T)> op = std::plus)
    // {
    //     // If tiling, dimensions are across the entire frame
    //     unsigned int top = tile ? 0 : y;
    //     unsigned int bottom =
    //         tile ? height()-1 : std::min(y + other.height() - 1, height());
    //     unsigned int left = tile ? 0 : x;
    //     unsigned int right =
    //         tile ? width()-1 : std::min(x + other.width() - 1, width());
    //
    //     // Start applying values
    //     int o_h = other.height();
    //     int o_w = other.width();
    //     for (int i = top; i < bottom; ++i)
    //         for (int j = left; j < right; ++j)
    //             at(i, j) = op(
    //                 at(i, j),
    //                 other.at((i % o_h + o_h) % o_h, (j % o_w + o_w) % o_w)
    //             );
    // }


    /**
     * Serializes the frame into a format that can be used to initialize
     * a new frame.
     *
     * @param values The frame to be serialized.
     * @param height The height of the frame.
     * @param width The width of the frame.
     * @return String containing values to initialize a frame.
     */
    std::string serialize()
    {
        std::string s = "";

        // Open frame
        s += "{";

        // Open pixels vector
        s += "{";

        for (int i = 0; i < height(); i++)
        {
            // Open row vector
            s += "{";

            for (int j = 0; j < width(); j++)
            {
                // Add row pixels
                s += values_.at(i).at(j).serialize();

                // Don't add comma after last value
                if (i != height() - 1) s += ",";
            }

            // Close row vector
            s += "}";

            // Don't add comma after last value
            if (i != height() - 1) s += ",";

        }

        // Close pixels vector
        s += "}";

        // Close frame
        s += "}";

        return s;
    }

    std::vector<std::vector<T>> values_;
};

}   // namespace taeto

#endif  // FRAMES_FRAME_HPP_
