#include <sstream>
#include <stdint.h>
#include <algorithm>

#define GLEW_STATIC
#include <GL/glew.h>

#include "model.h"
#include "util.h"
#include "obj.h"

void do_index(std::string idx, std::vector<int> &vert_indices, std::vector<int> &normal_indices, std::vector<int> &tex_indices)
{
	auto a = util::split(idx, "/");
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

void triangulate(std::vector<std::string> indices, std::vector<int> &verts, std::vector<int> &normals, std::vector<int> &tex)
{
	int i = 1;

	// a polygon of x sides decomposes into x-2 tris

	// todo: does this make clockwise triangles??

	for(; i <= indices.size() - 2; i++) 
	{
		do_index(indices[0], verts, normals, tex);
		do_index(indices[i], verts, normals, tex);
		do_index(indices[i+1], verts, normals, tex);
	}
}

Model::ptr OBJ::load(std::string filename)
{
	std::string file_contents = util::read_file(filename);
	std::stringstream file(file_contents);

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
							triangulate(vecs, vert_indices, normal_indices, tex_indices);
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
		Vec3D n = (temp_normals.size() != 0 && normal_indices.size() != 0) ? temp_normals[normal_indices[i] - 1] : Vec3D(0,0,0);
		Vec2D t = (temp_tex.size() != 0 && tex_indices.size() != 0) ? temp_tex[tex_indices[i] - 1] : Vec2D(0,0);

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