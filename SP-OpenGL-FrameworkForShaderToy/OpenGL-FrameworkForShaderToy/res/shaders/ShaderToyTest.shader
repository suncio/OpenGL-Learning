#shader vertex
#version 330 core

layout(location = 0) in vec3 in_position;
layout(location = 1) in vec2 in_texcoord;

out vec2 texcoord;

void main()
{
    gl_Position = vec4(in_position.x, in_position.y, in_position.z, 1.0); 
    texcoord = in_texcoord;
}

#shader fragment
#version 330 core
uniform vec3 iResolution;
uniform float iTime;
uniform vec4 iMouse;
in vec2 texcoord;
layout(location = 0) out vec4 fragColor;

#define S(a, b, t) smoothstep(a,b,t)

float TaperBox(vec2 p, float wb, float wt, float yb, float yt, float blur) {
	float m = S(-blur, blur, p.y - yb);
	m *= S(blur, -blur, p.y - yt);

	p.x = abs(p.x);

	// 0 p.y=yb  1 p.y=yt
	float w = mix(wb, wt, (p.y - yb) / (yt - yb));
	m *= S(blur, -blur, p.x - w);
	return m;
}

vec4 Tree(vec2 uv, /*float x, float y, */vec3 col, float blur) {
	//uv -= vec2(x, y);

	float m = TaperBox(uv, .03, .03, -.05, .25, blur); // trunk
	m += TaperBox(uv, .2, .1, .25, .5, blur); // canopy 1
	m += TaperBox(uv, .15, .05, .5, .75, blur); // canopy 2
	m += TaperBox(uv, .1, .0, .75, 1., blur); // top

	float shadow = TaperBox(uv - vec2(0.2, 0), .1, .5, .15, .25, blur);
	shadow += TaperBox(uv + vec2(0.25, 0), .1, .5, .45, .5, blur);
	shadow += TaperBox(uv - vec2(0.25, 0), .1, .5, .7, .75, blur);
	col -= shadow * .3;
	return vec4(col, m);
}

float GetHeight(float x) {
	return sin(x*.423)*.657 + sin(x + 0.5)*.245;
}

vec4 Layer(vec2 uv, float blur) {
	vec4 col = vec4(0);
	float id = floor(uv.x);
	float n = fract(sin(id*234.12)*5463.3)*2. - 1.;
	float x = n * .3;
	float y = GetHeight(uv.x);

	float ground = S(blur, -blur, uv.y + y); // ground
	col += ground;

	y = GetHeight(id + .5 + x);
	uv.x = fract(uv.x) - .5;

	vec4 tree = Tree((uv - vec2(x, -y))*vec2(1, 1. + n * .2), vec3(.4, .47, .4), blur);

	col = mix(col, tree, tree.a);
	col.a = max(ground, tree.a);

	return col;

}

float Hash21(vec2 p) {
	p = fract(p*vec2(234.45, 765.43));
	p += dot(p, p + 547.123);
	return fract(p.x*p.y);
}

void main()
{
	// Normalized pixel coordinates (from 0 to 1)
	vec2 uv = (gl_FragCoord.xy - .5*iResolution.xy) / iResolution.y;
	vec2 M = (iMouse.xy / iResolution.xy)*2. - 1.;
	//vec2 M = vec2(0., 0.);

	float t = iTime * .5;

	float blur = .005;


	float twinkle = dot(length(sin(uv + t)), length(cos(uv*vec2(22, 6.7) - t * 3.)));
	twinkle = sin(twinkle*10.)*.5 + .5;
	float stars = pow(Hash21(uv), 100.)*twinkle;
	vec4 col = vec4(stars);


	float moon = S(.01, -.01, length(uv - vec2(.4, .2)) - .15);
	col *= 1. - moon;
	moon *= S(-.01, .1, length(uv - vec2(.5, .25)) - .15);
	col += moon;



	vec4 layer;

	for (float i = 0.; i < 1.; i += 1. / 10.) {
		float scale = mix(25., 1., i);
		blur = mix(.1, .005, i);
		layer = Layer(uv*scale + vec2(t + i * 100., i) - M, blur);
		layer.rgb *= (1. - i)*vec3(.8, .85, .96);
		col = mix(col, layer, layer.a);
	}

	layer = Layer(uv + vec2(t, 0.8) - M, .05);
	col = mix(col, layer*.1, layer.a);

	float thickness = 1. / iResolution.y;

	fragColor = col;
}
