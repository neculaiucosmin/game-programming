//
// Created by cosmi on 12/3/2022.
//

#ifndef GAME_DEV_CAP_2_ACTOR_H
#define GAME_DEV_CAP_2_ACTOR_H


class Actor {
public:
    Actor();
    virtual void Update(float deltaTime);
    virtual void  Draw();

};

#endif //GAME_DEV_CAP_2_ACTOR_H
