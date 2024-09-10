#version 130

varying vec3 Normal;
varying vec3 vecLuz;
out vec4 Color;
out float visibilidad;
const float aumento = 2;


void main()
{
	//aqui definimos la textura activa con la que trabajaremos
	//por lo pronto es la 0, si hay mas pues entonces con su numero
    gl_TexCoord[0] = gl_MultiTexCoord0;

	//aqui pasamos la degradacion de la textura, no es color
	//para este caso
	Color = gl_Color;

	//obtenemos al vertice y lo transformamos para que obtenga su nueva posicion
	//esta es con la que trabajaremos en lo siguiente
    gl_Position = gl_ModelViewProjectionMatrix*gl_Vertex;
	//Agregué esto
	//gl_FogFragCoord = abs(gl_Position.z/gl_Position.w);
	//Aquí dejé de agregar

	//La normal matrix es la transpuesta de la ModelView Matrix
	//con vectores es necesario manejarlo asi y tambien es necesario
	//mover la normal ya que se movio el punto o vertice
	Normal = normalize(gl_NormalMatrix * gl_Normal);

	//esta es la luz que definimos en el render, tenemos esta fuente de posicion
	//aunque tambien podemos definirla fuera de esto.	
	vecLuz = normalize(gl_LightSource[0].position.xyz);			
	
	float distancia = length(gl_Position.xyz);
	visibilidad = exp(-pow((distancia* gl_Fog.density), aumento));
	visibilidad = clamp(visibilidad,0.0,1.0);
}