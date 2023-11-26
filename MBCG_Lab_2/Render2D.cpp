#include "Render2D.h"

Render2D::~Render2D()
{
	//for (const auto& object : m_objects)
		//if (object)
			//delete object;
}



void Render2D::draw(const HDC& hdc, Camera2D& camera)
{
	for (const auto& object : m_objects)
		if (object)
			object->draw(hdc, camera);
}

void Render2D::addObject(Model2D* model)
{
	m_objects.push_back(model);
}
