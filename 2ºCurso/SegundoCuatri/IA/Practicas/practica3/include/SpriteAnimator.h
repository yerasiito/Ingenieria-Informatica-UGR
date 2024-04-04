#ifndef __SPRITEANIMATOR_H_
#define __SPRITEANIMATOR_H_

#include "IncludesSFML.h"
#include <iostream>

using namespace std;

class SpriteAnimator{
private:
    // Reference to the sprite to be animated.
    Transformable *sprite;

    // Starting position of the animation.
    Vector2f start_pos;

    // Ending position of the animation.
    Vector2f end_pos;

    // Total time of the animation.
    int animation_time;

    // Internal clock of the animation (in miliseconds)
    Clock animation_clock;

    /**
     * @brief Construct a new Sprite Animator object
     *
     * @param s Sprite to animate.
     * @param start_pos Starting position of the animation.
     * @param end_pos Ending position of the animation.
     * @param animation_time Total time of the animation.
     */
    void initParameters(Transformable &s, const Vector2f &start_pos, const Vector2f &end_pos, int animation_time = 1000);

public :
    /**
     * @brief Construct a new Sprite Animator object
     *
     * @param s Sprite to animate.
     * @param start_pos Starting position of the animation.
     * @param end_pos Ending position of the animation.
     * @param animation_time Total time of the animation.
     */
    SpriteAnimator(Transformable &s, const Vector2f &start_pos, const Vector2f &end_pos, int animation_time = 1000);

    /**
     * @brief Construct a new Sprite Animator object. The starting position is taken from the sprite.
     *
     * @param s Sprite to animate.
     * @param end_pos Ending position of the animation.
     * @param animation_time Total time of the animation.
     */
    SpriteAnimator(Transformable &s, const Vector2f &end_pos, int animation_time = 1000);

    /**
     * @brief Construct a new Sprite Animator object
     *
     * @param s Sprite to animate.
     * @param start_pos Starting position of the animation.
     * @param end_pos Ending position of the animation.
     * @param animation_time Total time of the animation.
     */
    SpriteAnimator(Transformable &s, const Vector2i &start_pos, const Vector2i &end_pos, int animation_time = 1000);

    /**
     * @brief Construct a new Sprite Animator object. The starting position is taken from the sprite.
     *
     * @param s Sprite to animate.
     * @param end_pos Ending position of the animation.
     * @param animation_time Total time of the animation.
     */
    SpriteAnimator(Transformable &s, const Vector2i &end_pos, int animation_time = 1000);

    /**
     * @brief Restarts the animation.
     * 
     */
    void restart();

    /**
     * @brief Updates the sprite according to the animation.
     * 
     */
    void update();

    /**
     * @brief Checks if the animation has been completed.
     * 
     * @return true 
     * @return false 
     */
    bool hasEnded();

    /**
     * @brief Set the Start Position object
     * 
     */
    void setStartPosition();

    /**
     * @brief Set the Start Position object
     * 
     * @param start_pos 
     */
    void setStartPosition(const Vector2f & start_pos);
};

#endif