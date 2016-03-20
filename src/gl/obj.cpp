#include <iostream>
#include <fstream>
#include <stdint.h>

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
	std::vector<Vec3D> verts;
	std::vector<Vec3D> normals;
	std::vector<Vec2D> texcoords;
	std::vector<uint32_t> indices;

	for(; i < vert_indices.size(); i++)
	{
		verts.push_back(temp_verts[vert_indices[i] - 1]);
		if(temp_normals.size() != 0)
			normals.push_back(temp_normals[normal_indices[i] - 1]);

		if(temp_tex.size() != 0)
		texcoords.push_back(temp_tex[tex_indices[i] - 1]);
		indices.push_back(i);
	}

	Model::ptr p = util::make_unique<Model>(verts, texcoords, indices);
	return p;
}