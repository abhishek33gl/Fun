#version 330 core
out vec4 FragColor;
  
in vec4 vertexColor; 
uniform vec4 u_color=vec4(1,1,1,1);
void main()
{
    FragColor = u_color;
} 