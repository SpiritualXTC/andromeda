
/*
	Calculates a normal
*/
vec3 calcNormal(vec3 v0, vec3 v1, vec3 v2)
{
	// Subtraction
	vec3 vs1 = v0 - v1;
	vec3 vs2 = v1 - v2;

	// Cross Product : Calculate Normal
	float nx = vs1.y * vs2.z - vs1.z * vs2.y;
	float ny = vs1.z * vs2.x - vs1.x * vs2.z;
	float nz = vs1.x * vs2.y - vs1.y * vs2.x;

	return vec3(nx, ny, nz);
}
