
#type vertex
#version 330 core
layout(location = 0) in vec3 a_position;
layout(location = 1) in vec2 a_texCoord;

uniform mat4 u_viewProjection;
uniform mat4 u_transform;

out vec2 v_texCoord;

void main()
{
    v_texCoord = a_texCoord;
    gl_Position = u_viewProjection * u_transform * vec4(a_position, 1.0);
}

#type fragment
#version 330 core
layout(location = 0) out vec4 color;
in vec2 v_texCoord;

uniform vec4 u_color;
uniform float u_tilingFactor;
uniform sampler2D u_texture;

void main()
{
    color = texture(u_texture, v_texCoord * u_tilingFactor) * u_color;
}
