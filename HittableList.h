#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "Hittable.h"

#include <vector>
#include <memory>

class HittableList : public Hittable
{
public:
    HittableList() {}
    HittableList(std::shared_ptr<Hittable> hittable) { Add(hittable); }

    void Clear() { hittables.clear(); }
    void Add(std::shared_ptr<Hittable> hittable) { hittables.push_back(hittable); }
    virtual bool Hit(const Ray &ray, const float &min_t, const float &max_t) override;

private:
    std::vector<std::shared_ptr<Hittable>> hittables;
};

bool HittableList::Hit(const Ray &ray, const float &min_t, const float &max_t)
{
    bool hit_something = false;
    float nearest_t = max_t;
    HitRecord nearest_hit;

    for(auto &hittable : hittables)
    {
        if(hittable->Hit(ray, min_t, nearest_t))
        {
            hit_something = true;
            nearest_hit = hittable->GetHit();
            nearest_t = nearest_hit.t;
        }
    }
    hit = nearest_hit;
    return hit_something;
}

#endif