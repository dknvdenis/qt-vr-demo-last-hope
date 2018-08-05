#ifdef GL_ES
precision mediump int;
precision mediump float;
#endif

uniform mat4 p_matrix;
uniform mat4 m_matrix;
uniform vec2 center;
uniform float maxRadius;
uniform float k1;
uniform float k2;

attribute vec4 a_position;
attribute vec2 a_texcoord;

varying vec2 v_texcoord;

float Distort(float r, float k1, float k2)
{
    float r2 = r * r;
    return r * (1.0 + k1 * r2 + k2 * r2 * r2);
}

void main()
{
    vec4 C = vec4(center, 0, 1);
    vec4 P = (m_matrix * a_position);
    vec2 V = (P.xy - C.xy);

    V /= maxRadius;
    float r = length(V);

    float d = Distort(r, k1, k2);
    vec2 nPos = normalize(V) * d * maxRadius + C.xy;

    gl_Position = p_matrix * vec4(nPos, P.z, P.w);
    //gl_Position = p_matrix * m_matrix * a_position;
    v_texcoord = a_texcoord;
}
