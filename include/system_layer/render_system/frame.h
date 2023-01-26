#ifndef NEW_FRAME_H
#define NEW_FRAME_H

#include <string>
#include <vector>

/* Note to self: since these are mostly templated functions, they kind of have
 * to be in their own .h file. Compiler doesn't like the declaration and
 * definitions to be separated.
 */

class NewFrame
{
    protected:

        // Dimensions for error and bounds checking
        // Vector lengths should never deviate from these values
        unsigned int height;
        unsigned int width;


    public:
        /**
         * Returns the current height of the frame.
         *
         * @return The height of the frame.
         */
        unsigned int get_height()
        {
            return height;
        }


        /**
         * Returns the current width of the frame.
         *
         * @return The width of the frame.
         */
        unsigned int get_width()
        {
            return width;
        }


    protected:
        /**
         * The following methods are for calling from any derived classes.
         * I'm not good enough with C++ to make an actual templated data
         * member, so this is going to have to suffice. Each derived class
         * calls these methods with it's own values to emulate inherited
         * methods, but with their own return types.
         */

        /**
         * Get value at given location in two-dimensional vector.
         *
         * @param values Two-dimensional vector of given type to access.
         * @param y Row of vector to get value from.
         * @param x Collumn of selected row to get value from.
         * @return A reference to the value at the given location.
         */
        template<typename T>
        static T& at(std::vector<std::vector<T>>& values,
                     long int y,
                     long int x)
        {
            return values.at(y).at(x);
        }


        /**
         * Overwrite the second given two-dimensional vector onto the first
         * two-dimensional vector at the given location.
         *
         * @param f1 Base frame to be written to.
         * @param f1_height Height of the first frame.
         * @param f1_width Width of the first frame.
         * @param f2 Frame to be written onto the first frame.
         * @param f2_height Height of the second frame.
         * @param f2_width Width of the second frame.
         * @param y Row of the first frame to begin writing the second to.
         * @param x Collumn of the row to begin writing the second frame to.
         * @param tile_y True if the function should tile the second frame on
         *               the Y axis.
         * @param tile_x True if the function should tile the second frame on
         *               the X axis.
         * @param normalize True if the function should normalize the values.
         * @return The first given frame with the second given frame pasted on
         *         at the given location.
         */
        template <class T>
        static std::vector<std::vector<T>> combine(
            std::vector<std::vector<T>>& f1,
            unsigned int f1_height,
            unsigned int f1_width,
            std::vector<std::vector<T>>& f2,
            unsigned int f2_height,
            unsigned int f2_width,
            unsigned int y,
            unsigned int x,
            bool tile_y,
            bool tile_x,
            bool normalize)
        {
            // Keep location within this frame
            y = (y % f1_height + f1_height) % f1_height;
            x = (x % f1_width + f1_width) % f1_width;

            // If tiling, dimensions are across the entire frame
            unsigned int top = 0;
            unsigned int bottom = f1_height;
            unsigned int left = 0;
            unsigned int right = f1_width;

            // Trancate range if not tiling vertically
            if (!tile_y)
            {
                top = y;
                bottom = std::min(y + f2_height, f1_height);
            }

            // Same for horizontal
            if (!tile_x)
            {
                left = x;
                right = std::min(x + f2_width, f1_width);
            }

            // Start copying over values
            for (int i = top; i < bottom; ++i)
            {
                for (int j = left; j < right; ++j)
                {

                }
            }

            return f1;
        }


        /**
         * Serializes the frame into a format that can be used to initialize
         * a new frame.
         *
         * @param values The frame to be serialized.
         * @param height The height of the frame.
         * @param width The width of the frame.
         * @return String containing values to initialize a frame.
         */
        template<class T>
        static std::string serialize(std::vector<std::vector<T>> values, unsigned int height, unsigned int width)
        {
            std::string s = "";

            // Open frame
            s += "{";

            // Open pixels vector
            s += "{";

            for (int i = 0; i < height; i++)
            {
                // Open row vector
                s += "{";

                for (int j = 0; j < width; j++)
                {
                    // Add row pixels
                    s += values.at(i).at(j).serialize();

                    // Don't add comma after last value
                    if (i != height - 1) s += ",";
                }

                // Close row vector
                s += "}";

                // Don't add comma after last value
                if (i != height - 1) s += ",";

            }

            // Close pixels vector
            s += "}";

            // Close frame
            s += "}";

            return s;
        }
};

#endif
