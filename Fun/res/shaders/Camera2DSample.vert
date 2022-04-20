#version 330 core
layout (location = 0) in vec3 aPos;
  
out vec4 vertexColor; 
uniform mat3 proj=mat3(1);
void main()
{
	vec3 pv=proj*vec3(aPos.xy,1.0f);;
    gl_Position = vec4(pv, 1.0); 
    vertexColor = vec4(1.0, 0.0, 0.0, 1.0); 
}
