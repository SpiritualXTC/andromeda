#pragma once

#include "component.h"

#include <andromeda/Graphics/light.h>

namespace andromeda
{
	class ITransform;

	class LightDirectionalComponent : public Component<LightDirectionalComponent>, public LightDirectional
	{
	public:
		LightDirectionalComponent(const std::shared_ptr<ITransform> & transform);
		virtual ~LightDirectionalComponent();


	//	inline LightDirectional & getLight() { return _light; }
	//	inline const LightDirectional & getLight() const { return _light; }

	protected:
		void update(const Float timeStep) override;

	private:
		std::shared_ptr<ITransform> _transform;

	//	LightDirectional _light;
	};





#if 0
	template <typename T>
	class LightComponentType : public LightComponent
	{
		static_assert(std::is_base_of<Light, T>::value, "T needs to be a light");

	public:
		LightComponentType(){}
		virtual ~LightComponentType(){}
		
		inline T & getLight() { return _light; }
		inline const T & getLight() const { return _light; }

	private:
		T _light;
	};




	typedef LightComponentType<LightDirectional> LightDirectionalComponent;
#endif
}
