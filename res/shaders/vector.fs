// Uber Shader V0.1
// Used for rendering all game objects :)

// Most Basic of Basic!


// Texture
uniform sampler2D g_diffuseTexture;



// Passed Along the Pipe
in vec2 v_bezier;

// Output
out vec4 o_color;


// Entry Point
void main()
{
	// Derivitives
	// TODO: Optimize the texture coordinates.
	// Probably do not require the absolute value across the entire thing :)
	vec2 p = abs(v_bezier);
	vec2 px = abs(dFdx(v_bezier));
	vec2 py = abs(dFdy(v_bezier));

	// Chain Rule
	float fx = (2.0 * p.x) * px.x - px.y;
	float fy = (2.0 * p.x) * py.x - py.y;

	// Signed Distance
	float sd = (p.x * p.x - p.y) / sqrt(fx * fx + fy * fy);

	// Alpha
	float alpha = 0.5 - sd;
	float a = 1.0;

	float r = 1.0;
	float g = 1.0;
	float b = 1.0;


	// Texture coordinates are set, so convex curves have positive coordinate, concave curves have negative curves 

	// Mutliply the Alpha by the sign result from the X-Axis bezier coordinates... which designate convex/concave curves.
	alpha *= sign(v_bezier.x);

	// Determine whether to show the pixel, and how transparent it should be
	if (alpha > 1)
		a = 1.0;
	else if (alpha < 0)
	{
		a = 0.25;
		discard;
	}
	else
	{
		// AA-pass
		a = alpha;
	}

	// So this actually is anti-aliased..... but the blending isn't working with "standard" primitives due to them not needing any calculations done!
	// And always resulting in ZERO
//	r = a;
//	g = a;
//	b = a;

	// Set Output Color
	o_color = vec4(r, g, b, a);
}
