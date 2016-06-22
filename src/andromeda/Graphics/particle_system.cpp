#include <andromeda/Graphics/particle_system.h>

using namespace andromeda;

/*

*/
ParticleSystem::ParticleSystem()
{
	const Int32 COUNT = 1000;

	_Particle particles[COUNT];

	memset(particles, 0, sizeof(_Particle) * COUNT);

	particles[0].lifetime = 0;
	particles[0].position = glm::vec3(0, 0, 0);
	particles[0].velocity = glm::vec3(0, 0, 0);


	// Generate Buffers
	glGenTransformFeedbacks(2, _transform);
	glGenBuffers(2, _buffer);
	

	// Bind Buffers
	for (Int32 i = 0; i < 2; ++i)
	{
		glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, _transform[i]);
		glBindBuffer(GL_ARRAY_BUFFER, _buffer[i]);

		glBufferData(GL_ARRAY_BUFFER, sizeof(_Particle) * COUNT, particles, GL_DYNAMIC_DRAW);

		glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, _buffer[i]);
	}

	// Unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, 0);
}


/*

*/
ParticleSystem::~ParticleSystem()
{
	glDeleteTransformFeedbacks(2, _transform);
	glDeleteBuffers(2, _transform);
}




/*

*/
void ParticleSystem::update(Float ft)
{


}


/*
	
*/
void ParticleSystem::render(const std::shared_ptr<IShader> shader, MatrixStack & ms)
{

	// Update the Particles
	glEnable(GL_RASTERIZER_DISCARD);


	glBindBuffer(GL_ARRAY_BUFFER, _buffer[_activeBuffer]);
	glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, _transform[_activeTransform]);
	
	
	// Update Particles!
//	glBeginTransformFeedback(GL_POINTS);

	/*
	
	if (!_process)
	{
		glDrawArrays(GL_POINTS, 0, 1);
		_process = true;
	}
	else
	{
		glDrawTransformFeedback(GL_POINTS, _transform[_activeTransform]);
	}
	*/

//	glEndTransformFeedback();



	// Render the Particles
	glDisable(GL_RASTERIZER_DISCARD);


	glBindBuffer(GL_ARRAY_BUFFER, _buffer[_activeTransform]);		// Why _activeTransform ?


	glEnableVertexAttribArray(0);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(_Particle), 0); // position

	
	glDrawArrays(GL_POINTS, 0, 1);

	glDisableVertexAttribArray(0);
}

















