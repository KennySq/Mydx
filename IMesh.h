#pragma once

struct IMesh
{
	virtual bool Load(const char* path) = 0;
};