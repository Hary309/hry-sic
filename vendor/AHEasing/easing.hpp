//
//  easing.h
//
//  Copyright (c) 2011, Auerhaus Development, LLC
//
//  This program is free software. It comes without any warranty, to
//  the extent permitted by applicable law. You can redistribute it
//  and/or modify it under the terms of the Do What The Fuck You Want
//  To Public License, Version 2, as published by Sam Hocevar. See
//  http://sam.zoy.org/wtfpl/COPYING for more details.
//

#pragma once

#ifndef _USE_MATH_DEFINES
#    define _USE_MATH_DEFINES
#endif // !_USE_MATH_DEFINES

#include <math.h>

// TODO: use concepts

struct Easing
{
    template<typename T>
    using Function_t = T (*)(T);

    // Modeled after the line y = x
    template<typename T>
    static T LinearInterpolation(T p)
    {
        return p;
    }

    // Modeled after the parabola y = x^2
    template<typename T>
    static T QuadraticEaseIn(T p)
    {
        return p * p;
    }

    // Modeled after the parabola y = -x^2 + 2x
    template<typename T>
    static T QuadraticEaseOut(T p)
    {
        return -(p * (p - 2));
    }

    // Modeled after the piecewise quadratic
    // y = (1/2)((2x)^2)             ; [0,  0.5)
    // y = -(1/2)((2x-1)*(2x-3) - 1) ; [0.5, 1]
    template<typename T>
    static T QuadraticEaseInOut(T p)
    {
        if (p < static_cast<T>(0.5))
        {
            return 2 * p * p;
        }
        else
        {
            return (-2 * p * p) + (4 * p) - 1;
        }
    }

    // Modeled after the cubic y = x^3
    template<typename T>
    static T CubicEaseIn(T p)
    {
        return p * p * p;
    }

    // Modeled after the cubic y = (x - 1)^3 + 1
    template<typename T>
    static T CubicEaseOut(T p)
    {
        static T f = (p - 1);
        return f * f * f + 1;
    }

    // Modeled after the piecewise cubic
    // y = (1/2)((2x)^3)       ; [0,  0.5)
    // y = (1/2)((2x-2)^3 + 2) ; [0.5, 1]
    template<typename T>
    static T CubicEaseInOut(T p)
    {
        if (p < static_cast<T>(0.5))
        {
            return 4 * p * p * p;
        }
        else
        {
            static T f = ((2 * p) - 2);
            return static_cast<T>(0.5) * f * f * f + 1;
        }
    }

    // Modeled after the quartic x^4
    template<typename T>
    static T QuarticEaseIn(T p)
    {
        return p * p * p * p;
    }

    // Modeled after the quartic y = 1 - (x - 1)^4
    template<typename T>
    static T QuarticEaseOut(T p)
    {
        static T f = (p - 1);
        return f * f * f * (1 - p) + 1;
    }

    // Modeled after the piecewise quartic
    // y = (1/2)((2x)^4)        ; [0,  0.5)
    // y = -(1/2)((2x-2)^4 - 2) ; [0.5, 1]
    template<typename T>
    static T QuarticEaseInOut(T p)
    {
        if (p < static_cast<T>(0.5))
        {
            return 8 * p * p * p * p;
        }
        else
        {
            static T f = (p - 1);
            return -8 * f * f * f * f + 1;
        }
    }

    // Modeled after the quintic y = x^5
    template<typename T>
    static T QuinticEaseIn(T p)
    {
        return p * p * p * p * p;
    }

    // Modeled after the quintic y = (x - 1)^5 + 1
    template<typename T>
    static T QuinticEaseOut(T p)
    {
        static T f = (p - 1);
        return f * f * f * f * f + 1;
    }

    // Modeled after the piecewise quintic
    // y = (1/2)((2x)^5)       ; [0,  0.5)
    // y = (1/2)((2x-2)^5 + 2) ; [0.5, 1]
    template<typename T>
    static T QuinticEaseInOut(T p)
    {
        if (p < static_cast<T>(0.5))
        {
            return 16 * p * p * p * p * p;
        }
        else
        {
            static T f = ((2 * p) - 2);
            return static_cast<T>(0.5) * f * f * f * f * f + 1;
        }
    }

    // Modeled after quarter-cycle of sine wave
    template<typename T>
    static T SineEaseIn(T p)
    {
        return sin((p - 1) * M_PI_2) + 1;
    }

    // Modeled after quarter-cycle of sine wave (different phase)
    template<typename T>
    static T SineEaseOut(T p)
    {
        return sin(p * M_PI_2);
    }

    // Modeled after half sine wave
    template<typename T>
    static T SineEaseInOut(T p)
    {
        return static_cast<T>(0.5) * (1 - cos(p * M_PI));
    }

    // Modeled after shifted quadrant IV of unit circle
    template<typename T>
    static T CircularEaseIn(T p)
    {
        return 1 - sqrt(1 - (p * p));
    }

    // Modeled after shifted quadrant II of unit circle
    template<typename T>
    static T CircularEaseOut(T p)
    {
        return sqrt((2 - p) * p);
    }

    // Modeled after the piecewise circular function
    // y = (1/2)(1 - sqrt(1 - 4x^2))           ; [0,  0.5)
    // y = (1/2)(sqrt(-(2x - 3)*(2x - 1)) + 1) ; [0.5, 1]
    template<typename T>
    static T CircularEaseInOut(T p)
    {
        if (p < static_cast<T>(0.5))
        {
            return static_cast<T>(0.5) * (1 - sqrt(1 - 4 * (p * p)));
        }
        else
        {
            return static_cast<T>(0.5) * (sqrt(-((2 * p) - 3) * ((2 * p) - 1)) + 1);
        }
    }

    // Modeled after the exponential function y = 2^(10(x - 1))
    template<typename T>
    static T ExponentialEaseIn(T p)
    {
        return (p == static_cast<T>(0.0)) ? p : pow(2, 10 * (p - 1));
    }

    // Modeled after the exponential function y = -2^(-10x) + 1
    template<typename T>
    static T ExponentialEaseOut(T p)
    {
        return (p == static_cast<T>(1.0)) ? p : 1 - pow(2, -10 * p);
    }

    // Modeled after the piecewise exponential
    // y = (1/2)2^(10(2x - 1))         ; [0,0.5)
    // y = -(1/2)*2^(-10(2x - 1))) + 1 ; [0.5,1]
    template<typename T>
    static T ExponentialEaseInOut(T p)
    {
        if (p == static_cast<T>(0.0) || p == static_cast<T>(1.0))
            return p;

        if (p < static_cast<T>(0.5))
        {
            return static_cast<T>(0.5) * pow(2, (20 * p) - 10);
        }
        else
        {
            return -static_cast<T>(0.5) * pow(2, (-20 * p) + 10) + 1;
        }
    }

    // Modeled after the damped sine wave y = sin(13pi/2*x)*pow(2, 10 * (x - 1))
    template<typename T>
    static T ElasticEaseIn(T p)
    {
        return sin(13 * M_PI_2 * p) * pow(2, 10 * (p - 1));
    }

    // Modeled after the damped sine wave y = sin(-13pi/2*(x + 1))*pow(2, -10x) + 1
    template<typename T>
    static T ElasticEaseOut(T p)
    {
        return sin(-13 * M_PI_2 * (p + 1)) * pow(2, -10 * p) + 1;
    }

    // Modeled after the piecewise exponentially-damped sine wave:
    // y = (1/2)*sin(13pi/2*(2*x))*pow(2, 10 * ((2*x) - 1))      ; [0,0.5)
    // y = (1/2)*(sin(-13pi/2*((2x-1)+1))*pow(2,-10(2*x-1)) + 2) ; [0.5, 1]
    template<typename T>
    static T ElasticEaseInOut(T p)
    {
        if (p < static_cast<T>(0.5))
        {
            return static_cast<T>(0.5) * sin(13 * M_PI_2 * (2 * p)) * pow(2, 10 * ((2 * p) - 1));
        }
        else
        {
            return static_cast<T>(0.5) * (sin(-13 * M_PI_2 * ((2 * p - 1) + 1)) * pow(2, -10 * (2 * p - 1)) + 2);
        }
    }

    // Modeled after the overshooting cubic y = x^3-x*sin(x*pi)
    template<typename T>
    static T BackEaseIn(T p)
    {
        return p * p * p - p * sin(p * M_PI);
    }

    // Modeled after overshooting cubic y = 1-((1-x)^3-(1-x)*sin((1-x)*pi))
    template<typename T>
    static T BackEaseOut(T p)
    {
        static T f = (1 - p);
        return 1 - (f * f * f - f * sin(f * M_PI));
    }

    // Modeled after the piecewise overshooting cubic function:
    // y = (1/2)*((2x)^3-(2x)*sin(2*x*pi))           ; [0,  0.5)
    // y = (1/2)*(1-((1-x)^3-(1-x)*sin((1-x)*pi))+1) ; [0.5, 1]
    template<typename T>
    static T BackEaseInOut(T p)
    {
        if (p < static_cast<T>(0.5))
        {
            static T f = 2 * p;
            return static_cast<T>(0.5) * (f * f * f - f * sin(f * M_PI));
        }
        else
        {
            static T f = (1 - (2 * p - 1));
            return static_cast<T>(0.5) * (1 - (f * f * f - f * sin(f * M_PI))) + static_cast<T>(0.5);
        }
    }

    template<typename T>
    static T BounceEaseIn(T p)
    {
        return 1 - BounceEaseOut(1 - p);
    }

    template<typename T>
    static T BounceEaseOut(T p)
    {
        if (p < 4 / static_cast<T>(11.0))
        {
            return (121 * p * p) / static_cast<T>(16.0);
        }
        else if (p < 8 / static_cast<T>(11.0))
        {
            return (363 / static_cast<T>(40.0) * p * p) - (99 / static_cast<T>(10.0) * p) + 17 / static_cast<T>(5.0);
        }
        else if (p < 9 / static_cast<T>(10.0))
        {
            return (4356 / static_cast<T>(361.0) * p * p) - (35442 / static_cast<T>(1805.0) * p) + 16061 / static_cast<T>(1805.0);
        }
        else
        {
            return (54 / static_cast<T>(5.0) * p * p) - (513 / static_cast<T>(25.0) * p) + 268 / static_cast<T>(25.0);
        }
    }

    template<typename T>
    static T BounceEaseInOut(T p)
    {
        if (p < static_cast<T>(0.5))
        {
            return static_cast<T>(0.5) * BounceEaseIn(p * 2);
        }
        else
        {
            return static_cast<T>(0.5) * BounceEaseOut(p * 2 - 1) + static_cast<T>(0.5);
        }
    }
};
