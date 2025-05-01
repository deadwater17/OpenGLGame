#include "UIShader.h"

const GLchar* uiVertexShaderSrc =
"attribute vec2 aPos;                             " \
"attribute vec2 aTexCoord;                        " \
"uniform mat4 u_Projection;                       "\
"uniform vec2 u_Position;                         "\
"uniform vec2 u_Scale;                            "\
"varying vec2 v_TexCoord;                         "\
"void main()                                      "\
"{                                                "\
"    vec2 scaledPos = aPos * u_Scale + u_Position;"\
"    gl_Position = u_Projection * vec4(scaledPos, 0.0, 1.0);"\
"    v_TexCoord = aTexCoord;                      "\
"};";


const GLchar* uiFragmentShaderSrc =
"uniform sampler2D u_Texture;                     " \
"varying vec2 v_TexCoord;                         "\
"void main()                                      "\
"{                                                "\
"    vec4 texColor = texture2D(u_Texture, v_TexCoord);"\
"    if (texColor.a < 0.1) discard;               "\
"    gl_FragColor = texColor;                     "\
"};";
