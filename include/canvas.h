#ifndef CANVAS_H
#define CANVAS_H

#include <vector>
using std::vector;
#include <stdexcept>
#include <iostream>
#include <algorithm>

#include "common.h"

namespace life {

    //! Provides methods for drawing on an image.
    /*!
     * This is a drawing area on which we shall draw a Life representation.
     *
     * Here some information on the canvas properties:
     *
     * 1. The drawing area has the origin set to the bottom left corner, with
     * positive `X` axis going to the right and positive `Y` axis going to
     * the top of the canvas.
     * 2. A pixel on the canvas has a square shape based on the pixel size
     * set when the canvas is instantiated.
     * 3. Because of 2, we have the `virtual` dimension (set by the client),
     * and the `real` dimension, which is w * pixel_size by h * pixel_size.
     *
     * This class returns to the client an image (object) representation of the maze,
     * which might be recorded by the client as a PNG image file.
     */
    class Canvas
    {
    public:
        //=== Alias
        typedef unsigned char component_t; //!< Type of a color channel.
        static constexpr int image_depth=4; //!< Default value is RGBA (4 channels).

    public:

        //=== Special members
        /// Constructor
        /*! Creates an empty canvas of the requested size.
         * @param w_ The canvas width in pixels.
         * @param h_ The canvas height in pixels.
         */
        Canvas( size_t w=0, size_t h=0, short bs=4 )
                : m_width{w*bs}, m_height{h*bs}, m_block_size{ bs }
        {
            // Remember to adjust the virtual size to real dimensions.
            m_pixels.resize( m_width  * m_block_size * m_height  * m_block_size * image_depth);
        }

        /// Destructor.
        virtual ~Canvas( void )
        {
            // Do nothing, RAII (resource acquisition is resource initialization) approach
        }

        //=== Special members
        /// Copy constructor.
        Canvas( const Canvas &it )
        {
            *this = it;
        }
        /// Assignment operator.
        Canvas & operator=( const Canvas &it )
        {
            m_width =  it.m_width;
            m_height = it.m_height;
            m_block_size = it.m_block_size;
            m_pixels = it.m_pixels;

            return *this;
        }
        /// Move constructor.
        Canvas( Canvas && clone )
        {
            *this = clone;
        }
        /// Move assignment operator.
        Canvas & operator=( Canvas && move)
        {
            m_width =  move.m_width;
            m_height = move.m_height;
            m_block_size = move.m_block_size;
            m_pixels = move.m_pixels;

            return *this;
        }

        //=== Members
        /// Clear the canvas with black color.
        void clear( void )
        {
            for (size_t i = 0; i < m_pixels.size(); i++)
            {
                m_pixels.at(i) = 0;
            }
        }
        /// Set the color of a pixel on the canvas.
        void pixel( const Point2& p,  const Color& c) //redo
        {
            int offset = (p.x * m_block_size * image_depth) + (p.y * m_width * m_block_size * image_depth);

            for(size_t j = 0; j < (m_block_size * m_block_size); j++)
            {
                int i = 0;

                for (; i < m_block_size * image_depth; i = i + image_depth)
                {
                    m_pixels[offset + i] = c.channels[0];
                    m_pixels[offset + i + 1] = c.channels[1];
                    m_pixels[offset + i + 2] = c.channels[2];
                    m_pixels[offset + i + 3] = 255;
                }

                offset = offset + i + m_block_size * image_depth;
            }
            /*
                //16
            m_pixels[offset + 16] = c.channels[0];
            m_pixels[offset + 16 + 1] = c.channels[1];
            m_pixels[offset + 16 + 2] = c.channels[2];
            m_pixels[offset + 16 + 3] = 255;
            m_pixels[offset + 20] = c.channels[0];
            m_pixels[offset + 20 + 1] = c.channels[1];
            m_pixels[offset + 20 + 2] = c.channels[2];
            m_pixels[offset + 20 + 3] = 255;
            //32
            m_pixels[offset + 32] = c.channels[0];
            m_pixels[offset + 32 + 1] = c.channels[1];
            m_pixels[offset + 32 + 2] = c.channels[2];
            m_pixels[offset + 32 + 3] = 255;
            m_pixels[offset + 36] = c.channels[0];
            m_pixels[offset + 36 + 1] = c.channels[1];
            m_pixels[offset + 36 + 2] = c.channels[2];
            m_pixels[offset + 36 + 3] = 255;
            //48
            m_pixels[offset + 48] = c.channels[0];
            m_pixels[offset + 48 + 1] = c.channels[1];
            m_pixels[offset + 48 + 2] = c.channels[2];
            m_pixels[offset + 48 + 3] = 255;
            m_pixels[offset + 52] = c.channels[0];
            m_pixels[offset + 52 + 1] = c.channels[1];
            m_pixels[offset + 52 + 2] = c.channels[2];
            m_pixels[offset + 52 + 3] = 255;
*/
        }
        /// Get the pixel color from the canvas.
        Color pixel( const Point2& p) const
        {
            int pos = p.x * m_block_size * image_depth + p.y * m_height * m_block_size * image_depth;

            Color c;

            c.channels[0] = m_pixels.at(pos);
            c.channels[1] = m_pixels.at(pos + 1);
            c.channels[2] = m_pixels.at(pos + 2);

            return c;
        }

        //=== Attribute accessors members.
        /// Get the canvas width.
        size_t width( void ) const
        { return m_width; }
        /// Get the canvas height.
        size_t height( void ) const
        { return m_height; }
        /// Get the canvas pixels, as an array of `unsigned char`.
        const component_t* pixels( void ) const
        { return m_pixels.data(); }

        /// Draw a horizontal line with `length` pixels on the canvas, starting at a `p` location.
        /*
         * Example:
         *
         * ```
         * (p.x, p.y), length = 15.
         *  |
         *  v
         *  . . . . . . . . . . . . . . .
         *  ```
         */
        void hline( const Point2 &p, size_t length, const Color& );
        /// Draw a vertical line with `length` pixels on the canvas, starting at a `p` location.
        /*
         * Example:
         *
         * ```
         * (p.x, p.y), length = 6.
         *  |
         *  v
         *  .
         *  .
         *  .
         *  .
         *  .
         *  .
         *  ```
         */
        void vline( const Point2 &p, size_t length, const Color & );

    private:
        size_t m_width;    //!< The image width in pixel units.
        size_t m_height;   //!< The image height in pixel units.
        short m_block_size; //!< Cell size in pixels
        vector< component_t > m_pixels; //!< The pixels, stored as 3 RGB components.
    };
} // namespace

#endif // CANVAS_H
