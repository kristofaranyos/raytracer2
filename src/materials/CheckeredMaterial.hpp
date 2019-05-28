//
// Created by kristof on 2019.05.25..
//

#ifndef RAYTRACER2_CHECKEREDMATERIAL_HPP
#define RAYTRACER2_CHECKEREDMATERIAL_HPP


#include "Material.hpp"

class CheckeredMaterial : public Material {
public:
	CheckeredMaterial();
	CheckeredMaterial(Vector3f color, Vector3f a, float spec);
	~CheckeredMaterial() override = default;

	Vector3f getColor(float u, float v) const override;
};


#endif //RAYTRACER2_CHECKEREDMATERIAL_HPP
