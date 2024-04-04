#include "SpriteAnimator.h"

void SpriteAnimator::initParameters(Transformable & s, const Vector2f &start_pos, const Vector2f &end_pos, int animation_time){
    this->sprite = &s;
    this->start_pos = start_pos;
    this->end_pos = end_pos;
    this->animation_time = animation_time;
    this->animation_clock.restart();
}

SpriteAnimator::SpriteAnimator(Transformable &s, const Vector2f &start_pos, const Vector2f &end_pos, int animation_time)
{
    initParameters(s, start_pos, end_pos, animation_time);
}

SpriteAnimator::SpriteAnimator(Transformable &s, const Vector2f &end_pos, int animation_time)
{
    const Vector2f start_pos = s.getPosition();
    initParameters(s, start_pos, end_pos, animation_time);
}

SpriteAnimator::SpriteAnimator(Transformable &s, const Vector2i &start_pos, const Vector2i &end_pos, int animation_time)
{
    initParameters(s, (Vector2f)start_pos, (Vector2f)end_pos, animation_time);
}

SpriteAnimator::SpriteAnimator(Transformable &s, const Vector2i &end_pos, int animation_time)
{
    const Vector2f start_pos = s.getPosition();
    initParameters(s, start_pos, (Vector2f)end_pos, animation_time);
}

void SpriteAnimator::restart(){
    this->animation_clock.restart();
}

void SpriteAnimator::update(){
    int t = this->animation_clock.getElapsedTime().asMilliseconds();
    if(t > animation_time) t = animation_time;
    float fa_time = animation_time; 
    Vector2f curr_pos = (1.f - t / fa_time) * start_pos + (t / fa_time) * end_pos;
    //cout << t << endl;
    sprite->setPosition(curr_pos);
    //cout << sprite << endl;
}

bool SpriteAnimator::hasEnded(){
    return this->animation_clock.getElapsedTime().asMilliseconds() >= animation_time;
}

void SpriteAnimator::setStartPosition(const Vector2f & start_pos){
    this->start_pos = start_pos;
}

void SpriteAnimator::setStartPosition()
{
    this->start_pos = sprite->getPosition();
}
