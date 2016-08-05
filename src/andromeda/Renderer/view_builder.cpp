#include <andromeda/Renderer/view_builder.h>

#include <andromeda/Renderer/view.h>
#include <andromeda/Math/projection_matrix.h>
#include <andromeda/Math/view_matrix.h>

#include <andromeda/andromeda.h>

using namespace andromeda;


/*
	Create Orthogonal Projection Matrix
*/
ViewBuilder & ViewBuilder::setProjectionOrth()
{
	_projection = std::make_shared<OrthogonalMatrix>();
	return *this;
}

/*
	Create Perspective Fov Projection Matrix
*/
ViewBuilder & ViewBuilder::setProjectionPerspective()
{
	_projection = std::make_shared<PerspectiveMatrix>();
	return *this;
}

/*
	Sets the Views Region
*/
ViewBuilder & ViewBuilder::setRegion(Float x, Float y, Float width, Float height)
{
	_screen = Region2f(glm::vec2(x, y), glm::vec2(x + width, y + height));

	return *this;
}

/*

*/
ViewBuilder & ViewBuilder::addLayer(LayerBuilder & lb)
{
	_layers.push_back(lb);

	return *this;
}

/*

*/
ViewBuilder & ViewBuilder::addGroup(const std::string & name, const std::shared_ptr<SceneGraph> sceneGraph)
{
	_Group g;
	g.groupName = name;
	g.sceneGraph = sceneGraph;

	_groups.push_back(g);

	return *this;
}

/*

*/
std::shared_ptr<View> ViewBuilder::build()
{
	/*
		TODO:
		Remove ScreenView and only use the normal View

		This requires a method for the View to auto-resize when the Screen/Display resolution is changed
	*/

	std::shared_ptr<View> view = std::make_shared<View>(_screen.minimum.x, _screen.minimum.y, _screen.size().x, _screen.size().y);

	
	// Rebuild the View
	rebuild(view);


	return view;
}

/*

*/
std::shared_ptr<View> & ViewBuilder::rebuild(std::shared_ptr<View> & view)
{
	assert(view);

	// Clear view Groups (LayerGroups, RenderGroups ???)
	view->clear();

	
	// Build Layer Groups ... and attach the apprioriate layers
	for (const auto & it : _groups)
	{
//		view->addGroup(it.groupName, it.sceneGraph);	// TODO: Remove meh when changes are made to view layers
	}


	// New







	/*
		TODO:
		Remove
	*/
	// Old
	// Build Layers
	for (const auto & it : _layers)
	{
		// Load/Get the Effect
	//	std::shared_ptr<Effect> effect = LoadResource<Effect>(it.getEffectName());

		// Add Layer
	//	view->addLayer(it.getName(), effect, it.getTechniqueName(), it.getGroup(), it.getRenderGroup());
	}

	return view;
}


