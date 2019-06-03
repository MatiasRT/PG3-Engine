#pragma once
#ifndef COMPONENT_H
#define COMPONENT_H
#include "Exports.h"
class ENGINEDLL_API Component {
public:
	Component();
	~Component();
	void Update();
	void Draw();
	void Start();
};
#endif