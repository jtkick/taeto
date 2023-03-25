#ifndef SCENES_SCENE_H_
#define SCENES_SCENE_H_

namespace taeto
{

class Scene
{
public:
    Scene();

    ~Scene();

    virtual void animate();

    virtual void load();
};

}   // namespace taeto

#endif  // SCENES_SCENE_H_
