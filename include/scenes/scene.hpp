#ifndef SCENES_SCENE_H_
#define SCENES_SCENE_H_

namespace taeto
{

class Scene
{
public:
    Scene();

    virtual ~Scene();

    virtual void load(int, int);
};

}   // namespace taeto

#endif  // SCENES_SCENE_H_
