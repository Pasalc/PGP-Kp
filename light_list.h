#ifndef LIGHTLISTH
#define LIGHTLISTH
#include "light.h"

class light_list: public light  {
    public:
        //hitable_list() {}
        light_list(light **l, int n) :list(l),list_size(n) {};
        virtual vec3 illumination(const vec3& norm, const vec3& intersection) const override;
        light **list;
        int list_size;
};

vec3 light_list::illumination(const vec3& norm, const vec3& intersection) const {
	vec3 color(0,0,0);
    for (int i = 0; i < list_size; i++) {
		//std::cerr<<"i:"<<i<<std::endl;
		color+=list[i]->illumination(norm,intersection);
       
    }
	color.cell_one();
    return color;
}


#endif
