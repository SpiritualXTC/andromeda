#include <andromeda/Renderer/view_builder.h>

using namespace andromeda;


/*

*/
LayerBuilder::LayerBuilder(const std::string & name)
	: _name(name)
{

}


/*

*/
LayerBuilder & LayerBuilder::setGroup(const std::string & groupName)
{
	_group = groupName;
	return *this;
}

/*

*/
LayerBuilder & LayerBuilder::setRenderGroup(const std::string & groupName)
{
	_renderGroup = groupName;
	return *this;
}

/*

*/
LayerBuilder & LayerBuilder::setEffect(const std::string & effectName)
{
	_effectName = effectName;
	return *this;
}

/*

*/
LayerBuilder & LayerBuilder::setEffect(const std::string & effectName, const std::string & techniqueName)
{
	_effectName = effectName;
	_techniqueName = techniqueName;
	return *this;
}
