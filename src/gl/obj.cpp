#include <iostream>
#include <fstream>
#include <stdint.h>
#include <algorithm>

#define GLEW_STATIC
#include <GL/glew.h>

#include "model.h"
#include "util.h"
#include "obj.h"

Model::ptr OBJ::load(std::string filename)
{
	std::ifstream file(filename, std::ifstream::in);

	std::string line;

	std::vector<Vec3D> temp_verts;
	std::vector<Vec3D> temp_normals;
	std::vector<Vec2D> temp_tex;

	std::vector<int> vert_indices;
	std::vector<int> normal_indices;
	std::vector<int> tex_indices;

	std::vector<Vertex> unique_vertices;

	while(std::getline(file, line))
	{
		std::cout << line << std::endl;
		if(line[0] != '#' && line.size() > 2)
		{
			std::string dat = line.substr(2);

			switch(line[0])
			{
				case 'o':
					// object
				break;

				case 'g':
					// group.
				break;

				case 's':
					// shade group
				break;

				case 'v':
					switch(line[1])
					{
						case 'n':
							{
								auto vert = util::split(dat.substr(1), " ", false);
								temp_normals.push_back(Vec3D(std::stof(vert[0]), std::stof(vert[1]), std::stof(vert[2])));
							}
						break;

						case 't':
							{
								auto vert = util::split(dat.substr(1), " ", false);
								temp_tex.push_back(Vec2D(std::stof(vert[0]), std::stof(vert[1])));
							}
						break;

						default:
							{
								auto vert = util::split(dat, " ", false);
								temp_verts.push_back(Vec3D(std::stof(vert[0]), std::stof(vert[1]), std::stof(vert[2])));
							}
						break;
					}
				break;

				case 'f':
					{
						
						auto vecs = util::split(dat, " ", false);
						if(vecs.size() != 3)
						{
							throw std::exception();
						}
						else
						{
							for(auto v: vecs)
							{
								auto a = util::split(v, "/");
								if(a.size() == 3)
								{
									vert_indices.push_back(std::stoi(a[0]));
									if(a[1] != "") tex_indices.push_back(std::stoi(a[1]));
									normal_indices.push_back(std::stoi(a[2]));
								}
								else if(a.size() == 2)
								{
									vert_indices.push_back(std::stoi(a[0]));
									tex_indices.push_back(std::stoi(a[1]));
								}
								else if(a.size() == 1)
								{
									vert_indices.push_back(std::stoi(a[0]));
								}
							}
						}
					}
				break;
			}
			
		}
	}

	int i = 0;
	std::vector<uint32_t> indices;

	for(; i < vert_indices.size(); i++)
	{
		Vec3D v = temp_verts[vert_indices[i] - 1];
		Vec3D n = (temp_normals.size() != 0) ? temp_normals[normal_indices[i] - 1] : Vec3D(0,0,0);
		Vec2D t = (temp_tex.size() != 0) ? temp_tex[tex_indices[i] - 1] : Vec2D(0,0);

		Vertex v_ = Vertex(v, n, t);

		std::vector<Vertex>::iterator it = std::find(unique_vertices.begin(), unique_vertices.end(), v_);
		if(it == unique_vertices.end())
		{
			unique_vertices.push_back(v_);
			indices.push_back(unique_vertices.size() - 1);
		}
		else
		{
			indices.push_back(it - unique_vertices.begin());
		}
	}

	Model::ptr p = util::make_unique<Model>(unique_vertices, indices);
	return p;
}